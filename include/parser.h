/* parser.h -- header for parser.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
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
