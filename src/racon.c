/* Racon -- numeric radix conversion system
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

#include "racon.h"

int
main(const int arg_c, char **arg_k)
{
  struct arguments args = {0, "", ""};

  argp_parse(&argp, arg_c, arg_k, 0, 0, &args);

  char *ot_num = conv(args.radix_o, args.num, args.radix_i);
  printf("RESULTADO: %s\n", ot_num);

  free(ot_num);
  return 0;
}
