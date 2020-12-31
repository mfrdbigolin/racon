/* cases_mem_utils.h -- test cases for mem_utils.c
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

#ifndef CASES_MEM_UTILS_H
# define CASES_MEM_UTILS_H

static const struct Check_mult_overflow CASES_CHECK_MULT_OVERFLOW[] =
  {
   {SIZE_MAX, SIZE_MAX, true},
   {SIZE_MAX, 1, false},
   {UINT32_MAX, UINT32_MAX, false},
   {(size_t) UINT32_MAX + 1, UINT32_MAX, false},
   {(size_t) UINT32_MAX + 1, (size_t) UINT32_MAX + 1, true},
   {(size_t) UINT32_MAX * (size_t) UINT16_MAX, UINT16_MAX, false},
   {((size_t) UINT32_MAX + 1) * ((size_t) UINT16_MAX + 1),
    UINT16_MAX + 1, true},
   {SIZE_MAX, 0, false},
   {0, SIZE_MAX, false}
  };

static const struct Sstrdup CASES_SSTRDUP[] =
  {
   {"TEST_CASE_1", 4, "TEST"},
   {"TEST_CASE_2", 0, ""},
  };

#endif /* !CASES_MEM_UTILS_H  */
