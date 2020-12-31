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

# include "types.h"

# include <stdint.h>

# include <gmp.h>
# include <mpfr.h>

/* Default set of digits.  */
extern CPC_char DIGITS;
/* Protected symbols, may not be used as digits.  */
extern CPC_char PROTECTED;
/* Precision for mpfr_t variables.  */
extern const size_t PREC;
/* Rounding mode for mpfr_t, currently round to the nearest.  */
extern const int8_t ROUND;
/* Number of significant fractional digits.  */
extern const uint16_t SIG_DIGIT;

/* General wrapper function for conversions, calls the error checking,
 * formatting and later the conversion functions.
 *   The output radix (<radix_o>), the number (<num>) and the input radix
 * (<radix_i>) as char arrays.
 *   Returns the output number after conversion in case of success, if not
 * exits with failure.
 */
extern char* conv(CPC_char radix_o, CPC_char num, CPC_char radix_i);

# ifdef DEBUG
extern mpfr_ptr ut_dec(CPC_char input_num, CPC_mpfr radix_i);
extern mpfr_ptr ut_dec_f(CPC_char frac_num, CPC_mpfr radix_i);
extern char* ex_dec(CPC_mpfr dec_num, CPC_mpfr radix_o);
extern char* ex_dec_f(CPC_mpfr frac_num, CPC_mpfr radix_o);
# endif /* DEBUG  */

#endif /* !CONVERTER_H  */
