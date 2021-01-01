/* converter.c -- numeric conversion functions
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#include "converter.h"

#include "debug.h"
#include "error_handling.h"
#include "math_utils.h"
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

CPC_char DIGITS = "0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
CPC_char PROTECTED = "[]()<>|.,+-*/^\\";
const size_t PREC = 128;
const int8_t ROUND = MPFR_RNDF;
const uint16_t SIG_DIGIT = 32;

#ifndef DEBUG
static mpfr_ptr ut_dec(CPC_char input_num, CPC_mpfr radix_i);
static mpfr_ptr ut_dec_f(CPC_char frac_num, CPC_mpfr radix_i);
static char* ex_dec(CPC_mpfr dec_num, CPC_mpfr radix_o);
static char* ex_dec_f(CPC_mpfr frac_num, CPC_mpfr radix_o);
#endif /* !DEBUG  */

char*
conv(CPC_char radix_o, CPC_char num, CPC_char radix_i)
{
  if (!_((check_core), radix_o, num, radix_i))
#ifndef DEBUG
    die(NULL, EXIT_FAILURE, NULL);
#else /* !DEBUG  */
    return NULL;
#endif /* !DEBUG  */

  char* num_i = _((strip), num);

  mpfr_ptr rad_o = _((salloc), 1, sizeof *rad_o);
  mpfr_ptr rad_i = _((salloc), 1, sizeof *rad_i);

  mpfr_inits2(PREC, rad_o, rad_i, NULL);

  mpfr_set_str(rad_o, radix_o, 10, ROUND);
  mpfr_set_str(rad_i, radix_i, 10, ROUND);

  mpfr_ptr dec_num = ut_dec(num_i, rad_i);

  mpfr_clear(rad_i);
  _((sfree), rad_i);
  _((sfree), num_i);
  if (((!mpfr_integer_p(dec_num)) || (!mpfr_integer_p(rad_o)))
      && (mpfr_sgn(rad_o) < 0))
    {
      mpfr_clears(rad_o, dec_num, NULL);
      mpfr_free_cache();
      _((sfree), rad_o);
      _((sfree), dec_num);
      die(NULL, EXIT_FAILURE, "fractional conversions to negative "
          "radices or fractional negative radices are currently not "
          "supported\n");
    }

  char* num_o = ex_dec(dec_num, rad_o);

  mpfr_clears(rad_o, dec_num, NULL);
  mpfr_free_cache();
  _((sfree), rad_o);
  _((sfree), dec_num);
  return num_o;
}

SCOPE mpfr_ptr
ut_dec(CPC_char input_num, CPC_mpfr radix_i)
{
  struct Number* num = _((tok_num), input_num, ".");
  const bool sgn = '-' == num->int_part[0];
  mpfr_ptr dec_num = _((salloc), 1, sizeof *dec_num);
  mpfr_t digit;

  mpfr_inits2(PREC, dec_num, digit, NULL);

  mpfr_set_ui(dec_num, 0, ROUND);

  for (size_t i = sgn; i < strlen(num->int_part); ++i)
    {
      char* pos = strchr(DIGITS, num->int_part[i]);

      if (pos)
        {
          mpfr_set_uj(digit, pos - DIGITS, ROUND);
        }
      else
        {
          char* blk = _((expand), num->int_part + i, '<', '>');

          mpfr_set_str(digit, blk, 10, ROUND);

          i += strcspn(num->int_part + i, ">");

          _((sfree), blk);
        }

      mpfr_mul(dec_num, dec_num, radix_i, ROUND);
      if (!sgn)
        mpfr_add(dec_num, dec_num, digit, ROUND);
      else
        mpfr_sub(dec_num, dec_num, digit, ROUND);
    }

  if (strcmp(num->frac_part, ""))
    {
      mpfr_ptr frac = ut_dec_f(num->frac_part, radix_i);

      if (!sgn)
        mpfr_add(dec_num, dec_num, frac, ROUND);
      else
        mpfr_sub(dec_num, dec_num, frac, ROUND);

      mpfr_clear(frac);
      _((sfree), frac);
    }

  mpfr_clear(digit);
  _((free_num), num);
  return dec_num;
}

SCOPE mpfr_ptr
ut_dec_f(CPC_char frac_num, CPC_mpfr radix_i)
{
  mpfr_ptr dec_num = _((salloc), 1, sizeof *dec_num);
  mpfr_t digit;

  mpfr_inits2(PREC, dec_num, digit, NULL);

  mpfr_set_ui(dec_num, 0, ROUND);

  for (size_t i = strlen(frac_num); i; --i)
    {
      if (strchr(DIGITS, frac_num[i - 1]))
        {
          char* pos = strchr(DIGITS, frac_num[i - 1]);

          mpfr_set_uj(digit, pos - DIGITS, ROUND);
        }
      else
        {
          char* addr = _((sstrdup), frac_num, i);

          char* blk = _((expand), strrchr(addr, '<'), '<', '>');

          mpfr_set_str(digit, blk, 10, ROUND);

          i -= strcspn(frac_num + i - strlen(blk) - 2, ">");

          _((sfree), addr);
          _((sfree), blk);
        }

      mpfr_add(dec_num, dec_num, digit, ROUND);
      mpfr_div(dec_num, dec_num, radix_i, ROUND);
    }

  mpfr_clear(digit);
  return dec_num;
}

SCOPE char*
ex_dec(CPC_mpfr dec_num, CPC_mpfr radix_o)
{
  char* ot_num = ex_dec_f(dec_num, radix_o);
  return ot_num;
}

SCOPE char*
ex_dec_f(CPC_mpfr frac_num, CPC_mpfr radix_o)
{
  mpfr_t tmp, ratio, radix_power, significant;
  mpfr_ptr power;
  char* ot_num = _((salloc), 2, sizeof *ot_num);

  mpfr_inits2(PREC, tmp, ratio, radix_power, significant, NULL);

  mpfr_abs(tmp, frac_num, ROUND);
  /* Attention to negative values for radix_o.  */
  power = log_b(tmp, radix_o);
  mpfr_floor(power, power);

  if (!mpfr_sgn(tmp))
    ot_num[0] = DIGITS[0];

  for (size_t i = 0; (mpfr_sgn(tmp))
         && (mpfr_cmp_si(power, -((int32_t) SIG_DIGIT)) >= 0); ++i)
    {
      mpfr_pow(radix_power, radix_o, power, ROUND);
      mpfr_div(ratio, tmp, radix_power, ROUND);
      mpfr_trunc(ratio, ratio);

      if (mpfr_cmp_ui(ratio, strlen(DIGITS)) < 0)
        {
          ot_num = _((srealloc), ot_num, i + 2, sizeof *ot_num);
          ot_num[i] = DIGITS[mpfr_get_uj(ratio, ROUND)];
        }
      else
        {
          size_t sz = snprintf(NULL, 0, "<%" PRIuMAX ">",
                               mpfr_get_uj(ratio, ROUND));
          char* blk = _((salloc), sz + 1, sizeof *blk);

          sprintf(blk, "<%" PRIuMAX ">", mpfr_get_uj(ratio, ROUND));
          ot_num = _((srealloc), ot_num, strlen(blk) + i + 1,
                     sizeof *ot_num);
          memcpy(ot_num + strlen(ot_num), blk, strlen(blk));
          i += (sz - 1);

          _((sfree), blk);
        }

      if ((!mpfr_sgn(power)) && (!mpfr_integer_p(tmp)))
        {
          ot_num = _((srealloc), ot_num, strlen(".") + i + 2,
                     sizeof *ot_num);
          memcpy(ot_num + i + 1, ".", strlen("."));
          i += strlen(".");
        }

      ot_num[i + 1] = '\0';

      mpfr_mul(significant, ratio, radix_power, ROUND);
      mpfr_sub(tmp, tmp, significant, ROUND);
      mpfr_sub_ui(power, power, 1, ROUND);
    }

  if (mpfr_sgn(power) >= 0)
    {
      size_t sz = strlen(ot_num);

      ot_num = _((srealloc), ot_num, sz + mpfr_get_uj(power, ROUND) + 2,
                 sizeof *ot_num);
      memset(ot_num + sz, DIGITS[0], mpfr_get_uj(power, ROUND) + 1);
      ot_num[sz + mpfr_get_uj(power, ROUND) + 1] = '\0';
    }

  if ((mpfr_sgn(frac_num) < 0) && (mpfr_sgn(radix_o) > 0))
    {
      size_t sz = strlen(ot_num);

      ot_num = _((srealloc), ot_num, sz + 2, sizeof *ot_num);
      memmove(ot_num + 1, ot_num, sz);
      ot_num[0] = '-';
      ot_num[sz + 1] = '\0';
    }

  mpfr_clears(tmp, power, ratio, radix_power, significant, NULL);
  mpfr_free_cache();
  _((sfree), power);
  return ot_num;
}
