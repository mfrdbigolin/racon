/* error_handling.h -- header for error_handling.c
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

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <gmp.h>
# include <mpfr.h>
# include <stdbool.h>

# include "str_utils.h"

bool check_radix(const char *radix);
bool check_number(const char *num, const char *radix);

#endif /* !ERROR_HANDLING_H  */
