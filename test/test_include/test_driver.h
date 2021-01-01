/* test_driver.h -- header for test_driver.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#ifndef TEST_DRIVER_H
# define TEST_DRIVER_H

# include "types.h"

/* Call function <f> with each element of array <a> once.  */
# define ITERATED_CALL(f, a)                            \
  for (size_t i = 0; i < (sizeof a / sizeof a[0]); ++i) \
    f(&a[i]);

extern void success(CPC_char format, ...);
extern void fail(CPC_char format, ...);

#endif /* !TEST_DRIVER_H  */
