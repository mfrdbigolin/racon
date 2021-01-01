/* math_utils.c -- mathematical functions
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
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
