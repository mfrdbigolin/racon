/* debug.c -- exiting and debug information
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#include "debug.h"

#include "types.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void
die(CPC_Debug dbg, int8_t signal, CPC_char format, ...)
{
  if (dbg)
    {
      fprintf(stderr, DBG_DIR, DBG_INFO);
      if (format)
        fprintf(stderr, ": ");
    }
  if (format)
    {
      va_list args;

      va_start(args, format);

      vfprintf(stderr, format, args);

      va_end(args);
    }

#ifndef DEBUG
  exit(signal);
#endif /* !DEBUG  */
}
