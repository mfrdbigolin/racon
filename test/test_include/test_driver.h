/* test_driver.h -- header for test_driver.c
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
