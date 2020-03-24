/* converter.c -- numeric conversion functions
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

#include "converter.h"

const char DIGITS[62 + 1] = "0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const char PROTECTED[13 + 1] = "[]()|.,+-*/^\\";
/* Precision for mpfr_t variables.  */
const size_t PREC = 128;
/* Rounding mode for mpfr_t, currently round to the nearest.  */
const int8_t ROUND = MPFR_RNDN;

/* Declare as static after debugging.  */
mpfr_ptr ut_dec(const char *input_num, const mpfr_ptr radix_i);
mpfr_ptr ut_dec_f(const char *frac_num, const mpfr_ptr radix_i);
char *ex_dec(const mpfr_ptr dec_num, const mpfr_ptr radix_o);
char *ex_dec_f(const mpfr_ptr frac_num, const mpfr_ptr radix_o);

/* General wrapper function for conversions, calls the error checking,
 * formatting and later the conversion functions.
 *   Receives as input the output (<radix_o>) and input radix (<radix_i>)
 * and the number for conversion (<num>).
 *   Returns the output number after conversions (<num_o>).
 */
char *
conv(const char *radix_o, const char *num, const char *radix_i)
{
  if ((check_radix(radix_o) == EXIT_FAILURE)
      || (check_radix(radix_i) == EXIT_FAILURE)
      || (check_number(num, radix_i) == EXIT_FAILURE))
    exit(EXIT_FAILURE);

  char *num_i = strip(num);

  mpfr_ptr rad_o = SALLOC(1, sizeof (*rad_o));
  mpfr_ptr rad_i = SALLOC(1, sizeof (*rad_i));

  mpfr_inits2(PREC, rad_o, rad_i, NULL);

  mpfr_set_str(rad_o, radix_o, 10, ROUND);
  mpfr_set_str(rad_i, radix_i, 10, ROUND);

  mpfr_ptr dec_num = ut_dec(num_i, rad_i);

  if (((!mpfr_integer_p(dec_num)) || (!mpfr_integer_p(rad_o)))
      && (mpfr_sgn(rad_o) < 0))
    {
      fprintf(stderr, "racon: fractional conversions to negative radices "
              "or fractional negative radices are currently not "
              "supported\n");
      mpfr_clears(rad_o, rad_i, dec_num, NULL);
      free(num_i);
      exit(EXIT_FAILURE);
    }

  char *num_o = ex_dec(dec_num, rad_o);

  mpfr_clears(rad_o, rad_i, dec_num, NULL);
  mpfr_free_cache();
  free(num_i);
  free(rad_o);
  free(rad_i);
  free(dec_num);
  return num_o;
}

mpfr_ptr
ut_dec(const char *input_num, const mpfr_ptr radix_i)
{
  struct Number *num = tok_num(input_num, ".");
  const bool sgn = num->int_part[0] == '-';
  mpfr_ptr dec_num = SALLOC(1, sizeof (*dec_num));
  mpfr_t digit;

  mpfr_inits2(PREC, dec_num, digit, NULL);

  mpfr_set_ui(dec_num, 0, ROUND);

  for (size_t i = sgn; i < strlen(num->int_part); ++i)
    {
      char *pos = strchr(DIGITS, num->int_part[i]);
      char *blk = expand(num->int_part + i, "[]");

      if (pos != NULL)
        {
          mpfr_set_ui(digit, pos - DIGITS, ROUND);
        }
      else if (blk != NULL)
        {
          mpfr_set_str(digit, blk, 10, ROUND);

          i += strcspn(num->int_part + i, "]");

          free(blk);
        }

      mpfr_mul(dec_num, dec_num, radix_i, ROUND);
      if (!sgn)
        mpfr_add(dec_num, dec_num, digit, ROUND);
      else
        mpfr_sub(dec_num, dec_num, digit, ROUND);
    }

  if (num->frac_part != NULL)
    {
      mpfr_ptr frac = ut_dec_f(num->frac_part, radix_i);

      if (!sgn)
        mpfr_add(dec_num, dec_num, frac, ROUND);
      else
        mpfr_sub(dec_num, dec_num, frac, ROUND);

      mpfr_clear(frac);
      free(frac);
    }

  mpfr_clear(digit);
  mpfr_free_cache();
  free_num(num);
  return dec_num;
}

mpfr_ptr
ut_dec_f(const char *frac_num, const mpfr_ptr radix_i)
{
  mpfr_ptr dec_num = SALLOC(1, sizeof (*dec_num));
  mpfr_t digit;

  mpfr_inits2(PREC, dec_num, digit, NULL);

  mpfr_set_ui(dec_num, 0, ROUND);

  for (size_t i = strlen(frac_num); i != 0; --i)
    {
      char *pos = strchr(DIGITS, frac_num[i - 1]);
      char *blk, *addr = SALLOC(i + 1, sizeof (*addr));

      memcpy(addr, frac_num, i);
      blk = expand(strrchr(addr, '['), "[]");

      if (pos)
        {
          mpfr_set_ui(digit, pos - DIGITS, ROUND);
        }
      else if (blk)
        {
          mpfr_set_str(digit, blk, 10, ROUND);

          i -= strcspn(frac_num + i - strlen(blk) - 2, "]");

          free(blk);
        }

      mpfr_div(dec_num, dec_num, radix_i, ROUND);
      mpfr_add(dec_num, dec_num, digit, ROUND);

      free(addr);
    }
  mpfr_div(dec_num, dec_num, radix_i, ROUND);

  mpfr_clear(digit);
  mpfr_free_cache();
  return dec_num;
}

char *
ex_dec(const mpfr_ptr dec_num, const mpfr_ptr radix_o)
{
  char *ot_num = ex_dec_f(dec_num, radix_o);
  return ot_num;
}

char *
ex_dec_f(const mpfr_ptr frac_num, const mpfr_ptr radix_o)
{
  mpfr_t tmp, ratio, radix_power, significant;
  mpfr_ptr power;
  char *ot_num = SALLOC(2, sizeof (*ot_num));

  mpfr_inits2(PREC, tmp, ratio, radix_power, significant, NULL);

  mpfr_abs(tmp, frac_num, ROUND);
  /* Attention to negative values for radix_o  */
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
          ot_num = SREALLOC(ot_num, (i + 2) * sizeof (*ot_num));
          ot_num[i] = DIGITS[mpfr_get_uj(ratio, ROUND)];
        }
      else
        {
          size_t sz = snprintf(NULL, 0, "[%" PRIuMAX "]",
                               mpfr_get_uj(ratio, ROUND));
          char *blk = SALLOC(sz + 1, sizeof (*blk));

          sprintf(blk, "[%" PRIuMAX "]", mpfr_get_uj(ratio, ROUND));
          ot_num = SREALLOC(ot_num, (strlen(blk) + i + 1)
                            * sizeof (*ot_num));
          memcpy(ot_num + strlen(ot_num), blk, strlen(blk));
          i += (sz - 1);

          free(blk);
        }

      if ((!mpfr_sgn(power)) && (!mpfr_integer_p(tmp)))
        {
          ot_num = SREALLOC(ot_num, (strlen(".") + i + 2)
                            * sizeof (*ot_num));
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

      ot_num = SREALLOC(ot_num, (sz + mpfr_get_uj(power, ROUND) + 2)
                        * sizeof (*ot_num));
      memset(ot_num + sz, DIGITS[0], mpfr_get_uj(power, ROUND) + 1);
      ot_num[sz + mpfr_get_uj(power, ROUND) + 1] = '\0';
    }

  if ((mpfr_sgn(frac_num) < 0) && (mpfr_sgn(radix_o) > 0))
    {
      size_t sz = strlen(ot_num);

      ot_num = SREALLOC(ot_num, sz + 2);
      memmove(ot_num + 1, ot_num, sz);
      ot_num[0] = '-';
      ot_num[sz + 1] = '\0';
    }

  mpfr_clears(tmp, power, ratio, radix_power, significant, NULL);
  mpfr_free_cache();
  free(power);
  return ot_num;
}
