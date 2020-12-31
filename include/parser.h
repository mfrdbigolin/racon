/* parser.h -- header for parser.c
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

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

# include <argp.h>
# include <stdbool.h>

struct Args
{
  bool verb;
  CP_char radix_o;
  CP_char radix_i;
  CP_char num;
};

/* Program version information.  */
extern CP_char argp_program_version;
/* E-mail for bug reporting.  */
extern CPC_char argp_program_bug_adress;
extern struct argp argp;

# ifdef DEBUG
extern error_t parse_opt(int key, char* arg, struct argp_state* state);
# endif /* DEBUG  */

#endif /* !PARSER_H  */
