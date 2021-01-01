/* str_utils.c -- string manipulations functions
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
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
