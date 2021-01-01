/* types.h -- basic and library types redefinition
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#ifndef TYPES_H
# define TYPES_H

/* This is necessary here because GMP is not self-contained.  */
# include <stdio.h>

# include <gmp.h>
# include <mpfr.h>

typedef const char* const CPC_char;
typedef const char* CP_char;
typedef const __mpfr_struct* const CPC_mpfr;
typedef const __mpfr_struct* CP_mpfr;

#endif /* !TYPES_H  */
