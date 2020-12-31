/* str_utils.h -- header for str_utils.c
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
