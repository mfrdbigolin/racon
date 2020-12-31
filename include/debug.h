/* debug.h -- header for debug.c
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

#ifndef DEBUG_H
# define DEBUG_H

# include "types.h"

# include <stdint.h>

# define DBG_DIR "Racon:%s(%s):%zu"
# define DBG_INFO dbg->func, dbg->file, dbg->line
# define DBG_ARGS (&((struct Debug) {__func__, __FILE__, __LINE__}))

/* Wrap the function (<f>) with a variadic list of arguments and obtain
 * the environment debug information.
 */
# define _(f, ...) f(DBG_ARGS, __VA_ARGS__)

# ifndef DEBUG
#  define SCOPE static
# else /* DEBUG  */
#  define SCOPE
# endif /* DEBUG  */

typedef const struct Debug* const CPC_Debug;

/* Debug struct holding the function (<func>) and file name (<file>) and
 * the line number (<line>).
 */
struct Debug
{
  CP_char func;
  CP_char file;
  size_t line;
};

/* Exit the program with <signal>, print the debug information (<dbg>) and
 * the exit message (<format> with the variadic list of arguments) if any
 * or both are non-NULL.
 */
extern void die(CPC_Debug dbg, int8_t signal, CPC_char format, ...);

#endif /* !DEBUG_H  */
