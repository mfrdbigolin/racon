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

#include "converter.h"
#include "mem_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>

static void tst_form_u(mpfr_ptr (* fun)(CPC_char, CPC_mpfr),
                       const struct Form form);
static void tst_form_e(char* (* fun)(CPC_mpfr, CPC_mpfr),
                       const struct Form form);
static void tst_fail(char* (* fun)(CPC_char, CPC_char, CPC_char),
                     const struct Form_Fail form);

int
main(const int arg_c, char** arg_v)
{
  if (arg_c <= 1)
    {
      fprintf(stderr, "Please input a number (1-4)\n");
      return EXIT_FAILURE;
    }

  switch (arg_v[1][0])
    {
    case '1':
      for (size_t i = 0; i < (sizeof tst_cases
                              / sizeof tst_cases[0]); ++i)
        tst_form_u(ut_dec, tst_cases[i]);
      break;
    case '2':
      for (size_t i = 0; i < (sizeof tst_cases_f
                              / sizeof tst_cases_f[0]); ++i)
        tst_form_u(ut_dec, tst_cases_f[i]);
      break;
    case '3':
      for (size_t i = 0; i < (sizeof fail_cases
                              / sizeof fail_cases[0]); ++i)
        tst_fail(conv, fail_cases[i]);
      break;
    case '4':
      for (size_t i = 0; i < (sizeof etst_cases
                              / sizeof etst_cases[0]); ++i)
        tst_form_e(ex_dec, etst_cases[i]);
    }

  return EXIT_SUCCESS;
}

static void
tst_form_u(mpfr_ptr (* fun)(CPC_char, CPC_mpfr),
           const struct Form form)
{
  mpfr_t bas, expc;
  mpfr_inits2(PREC, bas, expc, NULL);
  mpfr_set_str(bas, form.radix, 10, ROUND);
  mpfr_set_str(expc, form.expected, 10, ROUND);
  mpfr_ptr output = fun(form.input, bas);

  if (!mpfr_cmp(output, expc))
    printf("SUCC: %s(%s) -> %s\n", form.radix, form.input, form.expected);
  else
    mpfr_printf("FAIL: %s(%s) -> %.32R*f, %s\n",
                form.radix, form.input, ROUND, output, form.expected);

  mpfr_clears(bas, expc, output, NULL);
  mpfr_free_cache();
  _((sfree), output);
}

static void
tst_form_e(char* (* fun)(CPC_mpfr, CPC_mpfr),
           const struct Form form)
{
  mpfr_ptr input = _((salloc), 1, sizeof *input);
  mpfr_ptr bas = _((salloc), 1, sizeof *bas);

  mpfr_inits(input, bas, NULL);

  mpfr_set_str(input, form.input, 10, 128);
  mpfr_set_str(bas, form.radix, 10, 128);
  char* output = fun(input, bas);

  if (!strcmp(output, form.expected))
    printf("SUCC: %s(%s) -> %s\n", form.radix, form.input, output);
  else
    printf("FAIL: %s(%s) -> %s, %s\n",
           form.radix, form.input, output, form.expected);

  mpfr_clears(input, bas, NULL);
  _((sfree), input);
  _((sfree), bas);
  _((sfree), output);
}

static void
tst_fail(char* (* fun)(CPC_char, CPC_char, CPC_char),
         const struct Form_Fail form)
{
  char* output = fun(form.radix_o, form.input, form.radix_i);

  if (output)
    {
      printf("FAIL: %s(%s) -> %s\n", form.radix_i, form.input, output);
      _((sfree), output);
    }
}
