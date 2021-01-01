/* debug.h -- header for debug.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
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
