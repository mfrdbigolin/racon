/* str_utils.h -- header for str_utils.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#ifndef STR_UTILS_H
# define STR_UTILS_H

# include "debug.h"
# include "types.h"

struct Number
{
  char* int_part;
  char* frac_part;
};

extern char* expand(CPC_Debug dbg, CPC_char blk,
                    char opening, char closing);
/* Strip the string (<str>) from all space characters (locale defined).
 *   Return the pointer to the stripped string.
 */
extern char* strip(CPC_Debug dbg, CPC_char str);
extern struct Number* tok_num(CPC_Debug dbg, CPC_char str, CPC_char delim);
/* Free a allocated struct Number variable (<num>) and its components.  */
extern void free_num(CPC_Debug dbg, struct Number* num);

#endif /* !STR_UTILS_H  */
