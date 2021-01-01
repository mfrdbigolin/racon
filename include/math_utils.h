/* math_utils.h -- header for math_utils.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "types.h"

# include <gmp.h>
# include <mpfr.h>

extern mpfr_ptr log_b(CPC_mpfr num, CPC_mpfr base);

#endif /* !MATH_UTILS_H  */
