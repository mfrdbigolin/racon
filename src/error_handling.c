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

static bool check_iter(const char *num_part, const char *radix);
static bool check_tok(const char *num, const char *rad_point);
static bool check_pos(const char *pos, const char *radix);
static bool check_blk(const char *blk, const char *radix);

bool
check_radix(const char *radix)
{
  if (radix == NULL)
    {
      fprintf(stderr, "racon: NULL input or output radix\n");
      return EXIT_FAILURE;
    }

  mpfr_t radix_num;
  char *end_ptr = NULL;

  mpfr_init2(radix_num, PREC);

  mpfr_strtofr(radix_num, radix, &end_ptr, 10, ROUND);

  if ((end_ptr[0] == '\0') && (strspn(radix, "-.0123456789")
                               == strlen(radix)))
    {
      if ((!mpfr_cmp_si(radix_num, -1)) || (!mpfr_sgn(radix_num))
          || (!mpfr_cmp_si(radix_num, 1)))
        {
          fprintf(stderr, "racon: the radix cannot be "
                  "equal '%s'\n", radix);
        }
      else
        {
          mpfr_clear(radix_num);
          mpfr_free_cache();
          return EXIT_SUCCESS;
        }
    }
  else
    {
      fprintf(stderr, "racon: the radix '%s' cannot be evaluated\n", radix);
    }

  mpfr_clear(radix_num);
  mpfr_free_cache();
  return EXIT_FAILURE;
}

bool
check_number(const char *num, const char *radix)
{
  if (num == NULL)
    {
      fprintf(stderr, "racon: NULL number string\n");
      return EXIT_FAILURE;
    }

  if (check_tok(num, ".") == EXIT_FAILURE)
    return EXIT_FAILURE;

  char *num_strip = strip(num);
  struct Number *number = tok_num(num_strip, ".");

  free(num_strip);
  if ((check_iter(number->int_part, radix) == EXIT_FAILURE)
      || ((number->frac_part != NULL)
          && (check_iter(number->frac_part, radix) == EXIT_FAILURE)))
    {
      free_num(number);
      return EXIT_FAILURE;
      }

  free_num(number);
  return EXIT_SUCCESS;
}

static bool
check_iter(const char *num_part, const char *radix)
{
  for (size_t i = num_part[0] == '-'; i < strlen(num_part); ++i)
    {
      char *pos = strchr(DIGITS, num_part[i]);
      char *blk = expand(num_part + i, "[]");

      if (pos != NULL)
        {
          if (check_pos(pos, radix) == EXIT_FAILURE)
            return EXIT_FAILURE;
        }
      else if (blk != NULL)
        {
          if (check_blk(blk, radix) == EXIT_FAILURE)
            {
              free(blk);
              return EXIT_FAILURE;
            }

          i += strcspn(num_part + i, "]");

          free(blk);
        }
      else
        {
          fprintf(stderr, "racon: unknown symbol '%c'\n", num_part[i]);
          return EXIT_FAILURE;
        }
    }
  return EXIT_SUCCESS;
}

/* Checks if the number is well-formed, id est has only one or none
 * radix point.
 *   Receives as input the number string (<num>) and the
 * radix point (<rad_point>).
 *   Returns the flag for success or failure.
 */
static bool
check_tok(const char *num, const char *rad_point)
{
  if (strstr(num, rad_point) != NULL)
    if (strstr(strstr(num, rad_point) + 1, rad_point) != NULL)
      {
        fprintf(stderr, "racon: please enter a well-formed number\n");
        return EXIT_FAILURE;
      }

  return EXIT_SUCCESS;
}

static bool
check_pos(const char *pos, const char *radix)
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
      mpfr_fprintf(stderr, "racon: the digit [%c] (%zu)10 is %s the "
                   "|radix| (%.6R*g)10\n", pos[0], pos - DIGITS,
                   (!mpfr_cmp_ui(radix_num, pos - DIGITS)
                    ? "equal" : "greater than"), ROUND, radix_num);

      mpfr_clears(radix_num, radix_num_inv, NULL);
      mpfr_free_cache();
      return EXIT_FAILURE;
    }
  else if ((mpfr_cmp_ui(radix_num_inv, pos - DIGITS + 1) < 0)
           && ((mpfr_cmp_si(radix_num_inv, -1) < 0)
               || (mpfr_cmp_si(radix_num_inv, 1) > 0)))
    {
      mpfr_fprintf(stderr, "racon: the digit [%c] (%zu)10 is %s the "
                   "|radix|^-1 (%.6R*g)10\n", pos[0], pos - DIGITS,
                   mpfr_cmp_ui(radix_num_inv, pos - DIGITS) > 0
                   ? "equal" : "greater than", ROUND, radix_num_inv);

      mpfr_clears(radix_num, radix_num_inv, NULL);
      mpfr_free_cache();
      return EXIT_FAILURE;
    }

  mpfr_clears(radix_num, radix_num_inv, NULL);
  mpfr_free_cache();
  return EXIT_SUCCESS;
}

static bool
check_blk(const char *blk, const char *radix)
{
  mpfr_t radix_num;
  mpz_t blk_val;
  char *endptr = NULL;

  mpfr_init2(radix_num, PREC);

  mpfr_set_str(radix_num, radix, 10, ROUND);
  mpfr_abs(radix_num, radix_num, ROUND);
  mpz_init_set_str(blk_val, blk, 10);
  strtol(blk, &endptr, 10);

  if ((endptr[0] == '\0') && (strspn(blk, "-+.0123456789") == strlen(blk)))
    {
      if (mpfr_cmp_z(radix_num, blk_val) <= 0)
        {
          fprintf(stderr, "racon: the digit [%s] is %s the radix (%s)\n",
                  blk, !mpfr_cmp_z(radix_num, blk_val)
                  ? "equal" : "greater than", radix);
        }
      else if (mpz_sgn(blk_val) < 0)
        {
          fprintf(stderr, "racon: the digit [%s] is negative\n", blk);
        }
      else
        {
          mpfr_clear(radix_num);
          mpz_clear(blk_val);
          mpfr_free_cache();
          return EXIT_SUCCESS;
        }
    }
  else
    {
      fprintf(stderr, "racon: the digit [%s] cannot be evaluated\n", blk);
    }

  mpfr_clear(radix_num);
  mpz_clear(blk_val);
  mpfr_free_cache();
  return EXIT_FAILURE;
}
