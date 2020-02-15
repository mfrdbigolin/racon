/* math_utils.h -- header for math_utils.h.
 * Copyright (C) 2020 Matheus Fernandes Bigolin
 */

/* This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* Contact e-mail: mfrdrbigolin@disroot.org  */

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
