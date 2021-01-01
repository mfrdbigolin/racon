/* converter.h -- header for converter.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
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
