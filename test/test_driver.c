/* test_driver.c -- general test functions
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

#include "test_driver.h"

#include "types.h"

#include <stdio.h>
#include <stdarg.h>

void
success(CPC_char format, ...)
{
#ifdef QUIET
  return;
#endif /* QUIET  */

  va_list args;

  va_start(args, format);

  printf("SUCC: ");
  vprintf(format, args);

  va_end(args);
}

void
fail(CPC_char format, ...)
{
  va_list args;

  va_start(args, format);

  printf("FAIL: ");
  vprintf(format, args);

  va_end(args);
}
