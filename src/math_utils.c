/* math_utils.c -- mathematical functions
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

#include "math_utils.h"

#include "converter.h"
#include "debug.h"
#include "mem_utils.h"
#include "types.h"

#include <gmp.h>
#include <mpfr.h>

mpfr_ptr
log_b(CPC_mpfr num, CPC_mpfr base)
{
  mpfr_t log_num, log_base;
  mpfr_ptr log_div = _((salloc), 1, sizeof *log_div);

  mpfr_inits2(PREC, log_num, log_base, log_div, NULL);

  mpfr_log(log_num, num, ROUND);
  mpfr_log(log_base, base, ROUND);
  mpfr_div(log_div, log_num, log_base, ROUND);

  mpfr_clears(log_num, log_base, NULL);
  mpfr_free_cache();
  return log_div;
}
