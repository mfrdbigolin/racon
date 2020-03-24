/* converter.h -- header for converter.c
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

#ifndef CONVERTER_H
# define CONVERTER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <gmp.h>
# include <mpfr.h>
# include <stdbool.h>
# include <ctype.h>
# include <inttypes.h>

# include "str_utils.h"
# include "error_handling.h"
# include "math_utils.h"

# define exit(EXIT_FAILURE) return NULL;

extern const char DIGITS[62 + 1];
extern const char PROTECTED[13 + 1];
extern const size_t PREC;
extern const int8_t ROUND;

char *conv(const char *radix_o, const char *num, const char *radix_i);

#endif /* !CONVERTER_H  */
