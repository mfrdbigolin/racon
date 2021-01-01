/* tst_converter.h -- header for tst_converter.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#ifndef TST_CONVERTER_H
# define TST_CONVERTER_H

struct Form
{
  char* radix;
  char* input;
  char* expected;
};

struct Form_Fail
{
  char* radix_o;
  char* radix_i;
  char* input;
};

#endif /* !TST_CONVERTER_H  */
