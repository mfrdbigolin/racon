/* Racon -- numeric radix conversion system
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#include "racon.h"

#include "converter.h"
#include "debug.h"
#include "mem_utils.h"
#include "parser.h"

#include <argp.h>

int
main(const int argc, char** argk)
{
  struct Args args = {0, "", ""};

  argp_parse(&argp, argc, argk, 0, 0, &args);

  char* ot_num = conv(args.radix_o, args.num, args.radix_i);
  printf("RESULT: %s\n", ot_num);

  _((sfree), ot_num);
  return EXIT_SUCCESS;
}
