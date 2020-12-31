/* mem_utils.c -- memory allocation functions
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

#include "mem_utils.h"

#include "debug.h"
#include "types.h"

#include <stdlib.h>
#include <string.h>

char*
sstrdup(CPC_Debug dbg, CPC_char str, size_t num)
{
  if (!str || !strcmp(str, ""))
    die(dbg, EXIT_FAILURE, "NULL or empty string\n");
  if (num > strlen(str))
    die(dbg, EXIT_FAILURE, "attempt to copy %zu byte(s) from %zu byte(s) "
        "string\n", num, strlen(str));

  char* n_str = _((salloc), num + 1, sizeof *n_str);
  memcpy(n_str, str, num);

  return n_str;
}
