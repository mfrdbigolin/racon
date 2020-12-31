/* debug.c -- exiting and debug information
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
