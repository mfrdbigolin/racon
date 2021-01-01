/* error_handling.h -- header for error_handling.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
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
