/* form_utils.c -- number formatting functions
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

#include "form_utils.h"

#include "converter.h"
#include "debug.h"
#include "mem_utils.h"
#include "str_utils.h"
#include "types.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <gmp.h>
#include <mpfr.h>

/* Smallest possible error upper bound with the current number of
 * significant digits.
 */
static const char EPSILON[] = "0.00000000000000000000000000000001";

#ifndef DEBUG
static char* form_f(CPC_mpfr frac);
#endif /* !DEBUG  */

char*
format(CPC_mpfr num)
{
  mpz_t int_op;
  mpfr_t frac_op, epsilon;

  mpz_init(int_op);
  mpfr_inits2(PREC, frac_op, epsilon, NULL);

  mpfr_get_z(int_op, num, MPFR_RNDZ);
  mpfr_frac(frac_op, num, ROUND);
  mpfr_abs(frac_op, frac_op, ROUND);
  mpfr_set_str(epsilon, EPSILON, 10, ROUND);

  char* form_num, * frac_str = form_f(frac_op);

  if ((!mpfr_integer_p(num)) && (frac_str != NULL)
      && (mpfr_cmp(frac_op, epsilon) >= 0))
    {
      mpz_abs(int_op, int_op);
      char* int_str = mpz_get_str(NULL, 10, int_op);

      form_num = _((salloc), strlen(int_str) + strlen(frac_str)
                             + strlen(".") + (mpfr_sgn(num) < 0) + 1,
                             sizeof *form_num);
      sprintf(form_num, "%s%s%s%s", (mpfr_sgn(num) < 0 ? "-" : ""),
              int_str, ".", frac_str);

      _((sfree), int_str);
      _((sfree), frac_str);
    }
  else
    {
      if (!frac_str)
        mpz_add_ui(int_op, int_op, 1);
      else
        _((sfree), frac_str);
      form_num = mpz_get_str(NULL, 10, int_op);
    }

  mpfr_clears(frac_op, epsilon, NULL);
  mpfr_free_cache();
  mpz_clear(int_op);
  return form_num;
}

SCOPE char*
form_f(CPC_mpfr frac)
{
  mpfr_exp_t* exp = _((salloc), 1, sizeof *exp);
  char* frac_str = mpfr_get_str(NULL, exp, 10, SIG_DIGIT,
                                frac, ROUND);
  size_t trail_zeros = strlen(frac_str) - 1;

  if ((*exp) > 0)
    {
      mpfr_free_str(frac_str);
      _((sfree), exp);
      return NULL;
    }

  while (('0' == frac_str[trail_zeros])
         && (((mpfr_exp_t) (trail_zeros)) > (*exp)))
    --trail_zeros;

  char* form_num = _((salloc), trail_zeros + 2, sizeof *form_num);
  memcpy(form_num, frac_str, trail_zeros + 1);

  if ((*exp) != ((mpfr_exp_t) trail_zeros))
    {
      form_num = _((srealloc), form_num,
                   strlen(form_num) + fabs(*exp) + 1, sizeof *form_num);
      memmove(form_num + (size_t) fabs(*exp), form_num, strlen(form_num));
      memset(form_num, '0', (size_t) fabs(*exp));
    }

  mpfr_free_str(frac_str);
  _((sfree), exp);
  return form_num;
}
