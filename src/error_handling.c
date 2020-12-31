/* error_handling.c -- error checking, messaging and signaling
 * Copyright (C) 2020 Matheus Fernandes Bigolin
 * Contact e-mail: <mfrdrbigolin@disroot.org>
 */

/* This file is part of Racon.
 *   Racon is free software (libre); you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *   Racon is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *   See the GNU General Public License for more details, you should have
 * received a copy of it along with Racon; otherwise, see
 * <https://www.gnu.org/licenses/gpl.html>.
 */

#include "error_handling.h"

#include "converter.h"
#include "debug.h"
#include "mem_utils.h"
#include "str_utils.h"
#include "types.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gmp.h>
#include <mpfr.h>

#ifndef DEBUG
static bool check_radix(CPC_Debug dbg, CPC_char radix);
static bool check_number(CPC_Debug dbg, CPC_char num, CPC_char radix);
static bool check_tok(CPC_char num, CPC_char rad_point);
static bool check_iter(CPC_char num_part, CPC_char radix);
static bool check_pos(CPC_char pos, CPC_char radix);
static bool check_expand(CPC_Debug dbg, CPC_char blk,
                         char opening, char closing);
static bool check_blk(CPC_char blk, CPC_char radix);
#endif /* !DEBUG  */

bool
check_core(CPC_Debug dbg, CPC_char radix_o,
           CPC_char num, CPC_char radix_i)
{
  if (!radix_o)
    die(dbg, EXIT_FAILURE, "NULL output radix\n");
  if (!radix_i)
    die(dbg, EXIT_FAILURE, "NULL input radix\n");
  if (!num)
    die(dbg, EXIT_FAILURE, "NULL number string\n");

  if ((!check_radix(dbg, radix_o))
      || (!check_radix(dbg, radix_i))
      || (!check_number(dbg, num, radix_i)))
    return false;

  return true;
}

SCOPE bool
check_radix(CPC_Debug dbg, CPC_char radix)
{
  mpfr_t radix_num;
  char* end_ptr = NULL;

  mpfr_init2(radix_num, PREC);

  mpfr_strtofr(radix_num, radix, &end_ptr, 10, ROUND);

  if (!end_ptr[0] && (strspn(radix, "-.0123456789") == strlen(radix)))
    {
      if ((!mpfr_cmp_si(radix_num, -1)) || (!mpfr_sgn(radix_num))
          || (!mpfr_cmp_si(radix_num, 1)))
        {
          fprintf(stderr, "Racon: the radix cannot be "
                  "equal '%s'\n", radix);
          mpfr_clear(radix_num);
          return false;
        }
    }
  else
    {
      fprintf(stderr, "Racon: the radix '%s' cannot be evaluated\n", radix);
      mpfr_clear(radix_num);
      return false;
    }

  mpfr_clear(radix_num);
  return true;
}

SCOPE bool
check_number(CPC_Debug dbg, CPC_char num, CPC_char radix)
{
  char* num_strip = _((strip), num);

  if (!check_tok(num_strip, "."))
    return false;

  struct Number* number = _((tok_num), num_strip, ".");
  _((sfree), num_strip);
  if (!check_iter(number->int_part, radix)
      || !check_iter(number->frac_part, radix))
    {
      _((free_num), number);
      return false;
    }

  _((free_num), number);
  return true;
}

SCOPE bool
check_tok(CPC_char num, CPC_char rad_point)
{
  //printf("%d %d\n", strcmp(num, rad_point), strcmp(num, ""));
  /*if (strcmp(num, rad_point) || strcmp(num, ""))
    {
      fprintf(stderr, "Racon: empty number\n");
      return false;
      }*/
  if (strstr(num, rad_point))
    if (strstr(strstr(num, rad_point) + 1, rad_point))
      {
        fprintf(stderr, "Racon: please enter a well-formed number\n");
        return false;
      }
  return true;
}

SCOPE bool
check_iter(CPC_char num_part, CPC_char radix)
{
  for (size_t i = ('-' == num_part[0]); i < strlen(num_part); ++i)
    if (strchr(DIGITS, num_part[i]))
      {
        if (!check_pos(strchr(DIGITS, num_part[i]), radix))
          return false;
      }
    else if (_((check_expand), num_part + i, '<', '>'))
      {
        char* blk = _((expand), num_part + i, '<', '>');

        if (!check_blk(blk, radix))
          {
            _((sfree), blk);
            return false;
          }

        i += strcspn(num_part + i, ">");

        _((sfree), blk);
      }
    else
      {
        fprintf(stderr, "Racon: unknown symbol '%c'\n", num_part[i]);
        return false;
      }

  return true;
}

SCOPE bool
check_pos(CPC_char pos, CPC_char radix)
{
  mpfr_t radix_num, radix_num_inv;

  mpfr_inits2(PREC, radix_num, radix_num_inv, NULL);

  mpfr_set_str(radix_num, radix, 10, ROUND);
  mpfr_abs(radix_num, radix_num, ROUND);
  mpfr_ui_div(radix_num_inv, 1, radix_num, ROUND);

  if ((mpfr_cmp_ui(radix_num, pos - DIGITS) <= 0)
      && ((mpfr_cmp_si(radix_num, -1) < 0)
          || (mpfr_cmp_si(radix_num, 1) > 0)))
    {
      mpfr_fprintf(stderr, "Racon: the digit [%c] (<%zu>) is %s the "
                   "|radix| (%.6R*g)\n", pos[0], pos - DIGITS,
                   (!mpfr_cmp_ui(radix_num, pos - DIGITS)
                    ? "equal" : "greater than"), ROUND, radix_num);
      mpfr_clears(radix_num, radix_num_inv, NULL);
      mpfr_free_cache();
      return false;
    }
  else if ((mpfr_cmp_ui(radix_num_inv, pos - DIGITS + 1) < 0)
           && ((mpfr_cmp_si(radix_num_inv, -1) < 0)
               || (mpfr_cmp_si(radix_num_inv, 1) > 0)))
    {
      mpfr_fprintf(stderr, "Racon: the digit [%c] (<%zu>) is %s the "
                   "|radix|^-1 (%.6R*g)\n", pos[0], pos - DIGITS,
                   mpfr_cmp_ui(radix_num_inv, pos - DIGITS) > 0
                   ? "equal" : "greater than", ROUND, radix_num_inv);
      mpfr_clears(radix_num, radix_num_inv, NULL);
      mpfr_free_cache();
      return false;
    }

  mpfr_clears(radix_num, radix_num_inv, NULL);
  mpfr_free_cache();
  return true;
}

SCOPE bool
check_expand(CPC_Debug dbg, CPC_char blk, char opening, char closing)
{
  if (!blk)
    die(dbg, EXIT_FAILURE, "the block is NULL\n");

  /* Check if <blk> starts and closes with
   * <opening> and <closing>, respectively.
   */
  if ((blk[0] != opening) || !memchr(blk, closing, strlen(blk)))
    return false;

  /* Check if there is another <opening> before <closing>.  */
  if (memchr(blk + 1, opening, strlen(blk) - 1)
      && (memchr(blk + 1, opening, strlen(blk) - 1)
          < memchr(blk + 1, opening, strlen(blk) - 1)))
    return false;

  return true;
}

SCOPE bool
check_blk(CPC_char blk, CPC_char radix)
{
  mpfr_t radix_num, blk_val;
  char* end_ptr = NULL;

  mpfr_inits2(PREC, radix_num, blk_val, NULL);

  mpfr_strtofr(radix_num, radix, &end_ptr, 10, ROUND);
  mpfr_abs(radix_num, radix_num, ROUND);
  mpfr_set_str(blk_val, blk, 10, ROUND);

  if (!end_ptr[0] && (strspn(blk, "-+.0123456789") == strlen(blk)))
    {
      if (mpfr_cmp(radix_num, blk_val) <= 0)
        {
          fprintf(stderr, "Racon: the digit [%s] (<%" PRIuMAX  ">) is %s "
                  "the radix (%s)\n", blk, mpfr_get_uj(blk_val, ROUND),
                  !mpfr_cmp(radix_num, blk_val)
                  ? "equal" : "greater than", radix);
        }
      else if (mpfr_sgn(blk_val) < 0)
        {
          fprintf(stderr, "Racon: the digit [%s] cannot be "
                  "negative\n", blk);
        }
      else
        {
          mpfr_clears(radix_num, blk_val, NULL);
          return true;
        }
    }
  else
    {
      fprintf(stderr, "Racon: the digit [%s] cannot be evaluated\n", blk);
    }

  mpfr_clears(radix_num, blk_val, NULL);
  return false;
}
