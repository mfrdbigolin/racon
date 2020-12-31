/* tst_mem_utils.h -- header for tst_mem_utils.c
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

#ifndef TST_MEM_UTILS_H
# define TST_MEM_UTILS_H

# include "types.h"

# include <stdbool.h>
# include <stdint.h>

struct Check_mult_overflow
{
  size_t num_1;
  size_t num_2;
  bool expected;
};

struct Sstrdup
{
  CP_char str;
  size_t num;
  CP_char expected;
};

extern void
tst_check_mult_overflow(const struct Check_mult_overflow* const tst_case);
extern void tst_sstrdup(const struct Sstrdup* const tst_case);

#endif /* !TST_MEM_UTILS_H  */
