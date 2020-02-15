/* tst_converter.h -- header for tst_converter.c.
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

#ifndef TST_CONVERTER_H
# define TST_CONVERTER_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <gmp.h>
# include <mpfr.h>

struct Form
{
  char radix[100];
  char input[300];
  char expected[300];
};

struct Form_Fail
{
  char radix_o[100];
  char radix_i[300];
  char input[300];
};

extern const struct Form tst_cases[];
extern const struct Form etst_cases[];
extern const struct Form tst_cases_f[];
extern const struct Form_Fail fail_cases[];

#endif /* TST_CONVERTER_H  */

