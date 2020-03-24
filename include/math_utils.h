/* math_utils.h -- header for math_utils.c
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

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include <gmp.h>
# include <mpfr.h>
# include <stdint.h>

# include "str_utils.h"

extern const size_t PREC;
extern const int8_t ROUND;

mpfr_ptr log_b(const mpfr_ptr num, const mpfr_ptr base);

#endif /* !MATH_UTILS_H  */
