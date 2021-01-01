/* mem_utils.h -- header for mem_utils.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#ifndef MEM_UTILS_H
# define MEM_UTILS_H

# include "debug.h"
# include "types.h"

# include <stdbool.h>
# include <stdlib.h>

extern char* sstrdup(CPC_Debug dbg, CPC_char str, size_t num);

static inline bool
check_mult_overflow(size_t num_1, size_t num_2)
{
  return num_1 && num_2 > (size_t) (SIZE_MAX / num_1);
}

static inline void*
salloc(CPC_Debug dbg, size_t num, size_t size)
{
  if (check_mult_overflow(num, size))
    die(dbg, EXIT_FAILURE, "multiplication overflow (%zu * %zu)\n",
        num, size);

  void* ptr = calloc(num, size);

  if (!ptr)
    die(dbg, EXIT_FAILURE, "out of memory (%zu bytes)\n", num * size);

  return ptr;
}

static inline void*
srealloc(CPC_Debug dbg, void* ptr, size_t num, size_t size)
{
  if (check_mult_overflow(num, size))
    die(dbg, EXIT_FAILURE, "multiplication overflow (%zu * %zu)\n",
        num, size);

  void* n_ptr = ptr ? realloc(ptr, num * size) : calloc(num, size);

  if (!n_ptr)
    die(dbg, EXIT_FAILURE, "out of memory (%zu bytes)\n", num * size);

  return n_ptr;
}

static inline void
sfree(CPC_Debug dbg, void* ptr)
{
  if (!ptr)
    die(dbg, EXIT_FAILURE, "NULL pointer or double free attempt\n");

  free(ptr);
}

#endif /* !MEM_UTILS_H  */
