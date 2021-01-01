/* tst_str_utils.h -- header for tst_str_utils.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#ifndef TST_STR_UTILS_H
# define TST_STR_UTILS_H

# include "str_utils.h"

struct Expand
{
  CP_char blk;
  char opening;
  char closing;
  CP_char expected;
};

struct Strip
{
  CP_char str;
  CP_char print_str; /* <str> to be printed, without escape sequences.  */
  CP_char expected;
};

struct Tok_num
{
  CP_char str;
  CP_char delim;
  struct Number* expected;
};

extern void tst_expand(const struct Expand* const tst_case);
extern void tst_strip(const struct Strip* const tst_case);
extern void tst_tok_num(const struct Tok_num* const tst_case);

#endif /* !TST_STR_UTILS_H  */
