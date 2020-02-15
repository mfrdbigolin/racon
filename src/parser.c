/* parser.c -- parser frontend for racon.
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

#include "parser.h"

const char *argp_program_version =
  "racon 1.0\n"
  "Copyright (C) 2020 Matheus Fernandes Bigolin\n"
  "License GPLv3+: GNU GPL version 3 or later "
  "<https://gnu.org/licenses/gpl.html>\n"
  "This is free software: you are free to change and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.";
static const char doc[] = "\nNumeric radix conversion system.\n";
const char *argp_program_bug_address = "<mfrdrbigolin@disroot.org>";
static const char args_doc[] = "value";
static struct argp_option options[] =
  {
   {"verbose", 'v', 0, 0, "Verbose output"},
   {"input", 'i', "Input radix", 0, "Input radix"},
   {"output", 'o', "Output radix", 0, "Output radix"},
   {"number", 'n', "Input number", 0, "Input number"},
   //{0}
  };

static error_t parse_opt(int key, char *arg, struct argp_state *state);

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments *args = state->input;

  switch (key)
    {
    case 'v':
      args->verb = 1;
      break;
    case 'i':
      args->radix_i = arg;
      break;
    case 'o':
      args->radix_o = arg;
      break;
    case 'n':
      args->num = arg;
      break;
      //case ARGP_KEY_ARG:
      //  if (state->arg_num > 3)
      //    argp_usage(state);
      //  args->args[state->arg_num] = arg;
      //  break;
      //case ARGP_KEY_END:
      //  if (state->arg_num < 1)
      //    argp_usage(state);
      //  break;
    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}

struct argp argp = {options, parse_opt, args_doc, doc};
