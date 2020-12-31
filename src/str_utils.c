/* str_utils.c -- string manipulations functions
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

#include "str_utils.h"

#include "debug.h"
#include "mem_utils.h"
#include "types.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char*
expand(CPC_Debug dbg, CPC_char blk, char opening, char closing)
{
  if (!blk)
    die(dbg, EXIT_FAILURE, "the block is NULL\n");

  char* buf = _((salloc), strchr(blk, closing) - blk, sizeof *buf);

  memcpy(buf, blk + 1, strchr(blk + 1, closing) - blk - 1);

  return buf;
}

char*
strip(CPC_Debug dbg, CPC_char str)
{
  if (!str)
    die(dbg, EXIT_FAILURE, "the string is NULL\n");

  char* n_str = _((salloc), strlen(str) + 1, sizeof *n_str);

  for (size_t i = 0, j = 0; i < strlen(str); ++i)
    if (!isspace(str[i]))
      n_str[j++] = str[i];

  n_str = _((srealloc), n_str, strlen(n_str) + 1, sizeof *n_str);

  return n_str;
}

struct Number*
tok_num(CPC_Debug dbg, CPC_char str, CPC_char delim)
{
  if (!str)
    die(dbg, EXIT_FAILURE, "the string is NULL\n");
  if (!delim)
    die(dbg, EXIT_FAILURE, "the delimiter string is NULL\n");

  struct Number* num = _((salloc), 1, sizeof *num);
  char* copy = _((sstrdup), str, strlen(str));

  char* left = strtok(copy, delim);
  if (!(strstr(copy, delim) - copy))
    {
      num->int_part = calloc(1, sizeof *num->int_part);
      num->frac_part = _((sstrdup), left, strlen(left));
    }
  else
    {
      num->int_part = _((sstrdup), left, strlen(left));
      char* right = strtok(NULL, delim);
      num->frac_part = right ? _((sstrdup), right, strlen(right))
        : calloc(1, sizeof *num->int_part);
    }

  _((sfree), copy);
  return num;
}

void
free_num(CPC_Debug dbg, struct Number* num)
{
  if (num)
    {
      sfree(dbg, num->int_part);
      sfree(dbg, num->frac_part);
    }
  sfree(dbg, num);
}
