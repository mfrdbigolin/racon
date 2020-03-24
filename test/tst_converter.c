/* tst_converter.c -- test functions for converter.c
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

#include "tst_converter.h"
#include "cases_converter.h"
#include "str_utils.h"

extern char *conv(const char *radix_o, const char *num,
                  const char *radix_i);
extern mpfr_ptr ut_dec(const char *input_num, const mpfr_ptr radix_i);
extern mpfr_ptr ut_dec_f(const char *frac_num, const mpfr_ptr radix_i);
extern char *ex_dec(const mpfr_ptr dec_num, const mpfr_ptr radix_o);

static void tst_form_u(mpfr_ptr (*fun)(const char *, const mpfr_ptr),
                       const struct Form *form);
static void tst_form_e(char *(*fun)(const mpfr_ptr, const mpfr_ptr),
                       const struct Form *form);
static void tst_fail(char *(*fun)(const char *, const char *,
                                  const char *),
                     const struct Form_Fail *form);

int
main(int arg_c, char **arg_v)
{
  if (arg_v[1][0] == '1')
    for (size_t i = 0; i < (sizeof tst_cases / sizeof (struct Form)); ++i)
      tst_form_u(ut_dec, &(tst_cases[i]));
  else if (arg_v[1][0] == '2')
    for (size_t i = 0; i < (sizeof tst_cases_f
                            / sizeof (struct Form)); ++i)
      tst_form_u(ut_dec, &(tst_cases_f[i]));
  else if (arg_v[1][0] == '3')
    for (size_t i = 0; i < (sizeof fail_cases /
                            sizeof (struct Form_Fail)); ++i)
      tst_fail(conv, &(fail_cases[i]));
  else if (arg_v[1][0] == '4')
    for (size_t i = 0; i < (sizeof etst_cases /
                            sizeof (struct Form)); ++i)
      tst_form_e(ex_dec, &(etst_cases[i]));

  return 0;
}

static void
tst_form_u(mpfr_ptr (*fun)(const char *, const mpfr_ptr),
           const struct Form *form)
{
  mpfr_ptr bas = calloc(1, sizeof (mpfr_t));
  mpfr_init(bas);
  mpfr_set_str(bas, form->radix, 10, 128);
  mpfr_ptr output = fun(form->input, bas);
  char *str = format(output);

  if (!strcmp(str, form->expected))
    printf("SUCC: %s(%s) -> %s\n", form->radix, form->input, str);
  else
    printf("FAIL: %s(%s) -> %s, %s\n",
    form->radix, form->input, str, form->expected);

  mpfr_clears(bas, output, NULL);
  free(bas);
  free(output);
  free(str);
}

static void
tst_form_e(char *(*fun)(const mpfr_ptr, const mpfr_ptr),
           const struct Form *form)
{
  mpfr_ptr input = calloc(1, sizeof (mpfr_t));
  mpfr_ptr bas = calloc(1, sizeof (mpfr_t));

  mpfr_inits(input, bas, NULL);

  mpfr_set_str(input, form->input, 10, 128);
  mpfr_set_str(bas, form->radix, 10, 128);
  char *output = fun(input, bas);

  if (!strcmp(output, form->expected))
    printf("SUCC: %s(%s) -> %s\n", form->radix, form->input, output);
  else
    printf("FAIL: %s(%s) -> %s, %s\n",
           form->radix, form->input, output, form->expected);

  mpfr_clears(input, bas, NULL);
  free(input);
  free(bas);
  free(output);
}

static void
tst_fail(char *(*fun)(const char *, const char *, const char *),
         const struct Form_Fail *form)
{
  char *output = fun(form->radix_o, form->input, form->radix_i);

  if (output)
    printf("FAIL: %s(%s) -> %s\n", form->radix_i, form->input, output);
  else
    free(output);
}
