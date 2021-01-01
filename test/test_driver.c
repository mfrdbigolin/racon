/* test_driver.c -- general test functions
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
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
