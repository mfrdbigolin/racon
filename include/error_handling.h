/* error_handling.h -- header for error_handling.c
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

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

# include "debug.h"
# include "types.h"

# include <stdbool.h>

extern bool check_core(CPC_Debug dbg, CPC_char radix_o,
                       CPC_char num, CPC_char radix_i);

# ifdef DEBUG
extern bool check_radix(CPC_Debug dbg, CPC_char radix);
extern bool check_number(CPC_Debug dbg, CPC_char num, CPC_char radix);
extern bool check_tok(CPC_char num, CPC_char rad_point);
extern bool check_iter(CPC_char num_part, CPC_char radix);
extern bool check_pos(CPC_char pos, CPC_char radix);
extern bool check_expand(CPC_Debug dbg, CPC_char blk,
                         char opening, char closing);
extern bool check_blk(CPC_char blk, CPC_char radix);
# endif /* DEBUG  */

#endif /* !ERROR_HANDLING_H  */
