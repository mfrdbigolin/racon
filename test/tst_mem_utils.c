/* tst_mem_utils.c -- test functions for mem_utils.c
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

#include "tst_mem_utils.h"
#include "cases_mem_utils.h"

#include "mem_utils.h"
#include "test_driver.h"
#include "types.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int
main(void)
{
  printf("------------------\ncheck_mult_overflow:\n\n");
  ITERATED_CALL(tst_check_mult_overflow, CASES_CHECK_MULT_OVERFLOW);

  printf("------------------\nsstrdup:\n\n");
  ITERATED_CALL(tst_sstrdup, CASES_SSTRDUP);

  return EXIT_SUCCESS;
}

void
tst_check_mult_overflow(const struct Check_mult_overflow* const tst_case)
{
  const bool res = check_mult_overflow(tst_case->num_1, tst_case->num_2);

  if (res != tst_case->expected)
    fail("%zu * %zu -> %s, %s\n", tst_case->num_1, tst_case->num_2,
         res ? "true" : "false", tst_case->expected ? "True" : "False");
  else
    success("%zu * %zu -> %s\n", tst_case->num_1, tst_case->num_2,
            tst_case->expected ? "true" : "false");
}

void
tst_sstrdup(const struct Sstrdup* const tst_case)
{
  char* str = _((sstrdup), tst_case->str, tst_case->num);

  if (strcmp(str, tst_case->expected))
    fail("(\"%s\", %zu) -> \"%s\", \"%s\"\n", tst_case->str,
         tst_case->num, str, tst_case->expected);
  else
    success("(\"%s\", %zu) -> \"%s\"\n", tst_case->str,
            tst_case->num, tst_case->expected);

  free(str);
}
