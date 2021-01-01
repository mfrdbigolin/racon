/* mem_utils.c -- memory allocation functions
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
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
