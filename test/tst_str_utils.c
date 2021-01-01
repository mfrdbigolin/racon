/* tst_str_utils.c -- test functions for str_utils.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#include "tst_str_utils.h"
#include "cases_str_utils.h"

#include "str_utils.h"
#include "types.h"
#include "test_driver.h"

#include <stdlib.h>
#include <string.h>

int
main(void)
{
  printf("------------------\nexpand:\n\n");
  ITERATED_CALL(tst_expand, CASES_EXPAND);

  printf("------------------\nstrip:\n\n");
  ITERATED_CALL(tst_strip, CASES_STRIP);

  printf("------------------\ntok_num:\n\n");
  ITERATED_CALL(tst_tok_num, CASES_TOK_NUM);

  return EXIT_SUCCESS;
}

void
tst_expand(const struct Expand* const tst_case)
{
  char *str = _((expand), tst_case->blk, tst_case->opening,
                tst_case->closing);

  if (strcmp(str, tst_case->expected))
    fail("(\"%s\", '%c', '%c') -> \"%s\", \"%s\"\n", tst_case->blk,
         tst_case->opening, tst_case->closing, str, tst_case->expected);
  else
    success("(\"%s\", '%c', '%c') -> \"%s\"\n", tst_case->blk,
            tst_case->opening, tst_case->closing, tst_case->expected);

  free(str);
}

void
tst_strip(const struct Strip* const tst_case)
{
  char *str = _((strip), tst_case->str);

  if (strcmp(str, tst_case->expected))
    fail("\"%s\" -> \"%s\", \"%s\"\n", tst_case->print_str, str,
         tst_case->expected);
  else
    success("\"%s\" -> \"%s\"\n", tst_case->print_str, tst_case->expected);

  free(str);
}

void
tst_tok_num(const struct Tok_num* const tst_case)
{
  struct Number* num = _((tok_num), tst_case->str, tst_case->delim);

  if (strcmp(num->int_part, tst_case->expected->int_part)
      && strcmp(num->frac_part, tst_case->expected->frac_part))
    fail("(\"%s\", \"%s\") -> \"%s\", \"%s\"; \"%s\", \"%s\"\n",
         tst_case->str, tst_case->delim, num->int_part,
         tst_case->expected->int_part, num->frac_part,
         tst_case->expected->frac_part);
  else if (strcmp(num->int_part, tst_case->expected->int_part))
    fail("(\"%s\", \"%s\") -> \"%s\", \"%s\"; \"%s\"\n",
         tst_case->str, tst_case->delim, num->int_part,
         tst_case->expected->int_part, tst_case->expected->frac_part);
  else if (strcmp(num->frac_part, tst_case->expected->frac_part))
    fail("(\"%s\", \"%s\") -> \"%s\"; \"%s\", \"%s\"\n",
         tst_case->str, tst_case->delim, tst_case->expected->int_part,
         num->frac_part, tst_case->expected->frac_part);
  else
    success("(\"%s\", \"%s\") -> \"%s\"; \"%s\"\n",
            tst_case->str, tst_case->delim, tst_case->expected->int_part,
            tst_case->expected->frac_part);

  _((free_num), num);
}
