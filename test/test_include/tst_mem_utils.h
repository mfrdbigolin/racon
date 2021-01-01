/* tst_mem_utils.h -- header for tst_mem_utils.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
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
