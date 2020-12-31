/* mem_utils.h -- header for mem_utils.c
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
