/* tst_str_utils.h -- header for tst_str_utils.c
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
