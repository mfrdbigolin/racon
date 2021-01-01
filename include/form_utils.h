/* form_utils.h -- header for form_utils.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#ifndef FORM_UTILS_H
# define FORM_UTILS_H

# include "types.h"

extern char* format(CPC_mpfr num);

# ifdef DEBUG
extern char* form_f(CPC_mpfr frac);
# endif /* DEBUG  */

#endif /* !FORM_UTILS_H  */
