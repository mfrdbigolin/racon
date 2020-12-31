/* types.h -- basic and library types redefinition
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
