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

const uint16_t SIG_DIGIT = 32;
static const char EPSILON[] = "0.00000000000000000000000000000001";

static char *form_f(const mpfr_ptr frac);

/* Insert a substring inside a string in a specific position.  The string
 * (<str>) and the substring (<sub>) shall be non-NULL and the position
 * (<pos>) shall be greater or equal to zero and smaller than <str>.
 * Returns the pointer to the char array when the operation is succeeded,
 * returns NULL otherwise.
 */

char *
ins_str(const char *str, const char *sub, const unsigned long pos)
{
  if ((!str) || (!sub))
    {
      fprintf(stderr, "%s:%u: string or substring is NULL",
              __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    }
  if (pos > strlen(str))
    {
      fprintf(stderr, "%s:%u: insert position is bigger than string"
              "length\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    }

  char *buf = SALLOC(strlen(str) + strlen(sub) + 1, sizeof (char));

  if (pos > 0) memcpy(buf, str, pos);
  memcpy(buf + strlen(buf), sub, strlen(sub));
  memcpy(buf + strlen(buf), str + pos, strlen(str) - pos);

  return buf;
}

/* Expand an expression inside a delimited block.  The expression (<str>)
 * and the delimiter pair (<delim>), with the length.  Returns the char
 * array containing the expanded expression in case of success or returns
 * NULL otherwise.
 */
char *
expand(const char *str, const char delim[2 + 1])
{
  const char *expr = str + 1;
  if ((str == NULL) || (*str != *delim)
      || (memchr(str, delim[1], strlen(str)) == NULL))
    return NULL;

  if ((memchr(expr, *delim, strlen(expr)) != NULL)
      && (memchr(expr, *delim, strlen(expr))
          < memchr(expr, delim[1], strlen(expr))))
    return NULL;

  char *buf = SALLOC(strcspn(expr, delim) + 1, sizeof (char));
  memcpy(buf, expr, strcspn(expr, delim));
  //((char *) memchr(expr, delim[1],
  //                 strlen(expr)) - expr));

  return buf;
}

char *
strip(const char *str)
{
  char *n_str = SALLOC(1, sizeof (char));
  size_t j = 0;

  for (size_t i = 0; i < strlen(str); ++i)
    {
      if (!isspace(str[i]))
        {
          n_str = SREALLOC(n_str, j + 2);
          n_str[j++] = str[i];
        }
    }
  n_str[j] = '\0';

  return n_str;
}

/* Tokenize a number by its integer and fractional part and store it in a
 * struct Number variable.  The number is stored in a non-NULL char array
 * variable (<str>).  Returns the pointer to the struct Number variable in
 * case of success or returns NULL otherwise.
 */
struct Number *
tok_num(const char *str, const char *delim)
{
  struct Number *num = SALLOC(1, sizeof (struct Number));
  char *copy = SSTRDUP(str, 0);

  num->int_part = SSTRDUP(strtok(copy, delim), 0);
  num->frac_part = strstr(str, delim) != NULL
                   ? SSTRDUP(strtok(NULL, delim), 0) : NULL;

  free(copy);
  return num;
}

/* Safely and completely frees a struct Number variable (<num>).  */
void
free_num(struct Number *num)
{
  if (num != NULL) {
    if (num->int_part != NULL)
      free(num->int_part);
    if (num->frac_part != NULL)
      free(num->frac_part);
    free(num);
  }
}

void *
salloc(const size_t num, const size_t size, const unsigned int line)
{
  void *ptr = calloc(num, size);
  if (!ptr)
    {
      fprintf(stderr, "%s:%u: out of memory (%zu bytes)\n",
              __FILE__, line, num * size);
      exit(EXIT_FAILURE);
    }
  return ptr;
}

void *
srealloc(void *ptr, const size_t size, const unsigned int line)
{
  void *n_ptr = ptr != NULL ? realloc(ptr, size) : calloc(1, size);

  if (n_ptr == NULL)
    {
      fprintf(stderr, "%s:%u: out of memory (%zu bytes)\n",
              __FILE__, line, size);
      exit(EXIT_FAILURE);
    }

  return n_ptr;
}

char *
sstrdup(const char *str, const size_t num, const unsigned int line)
{
  if (!str)
    {
      fprintf(stderr, "%s:%u: NULL string\n", __FILE__, line);
      exit(EXIT_FAILURE);
    }

  char *n_str = NULL;
  n_str = calloc(strlen(str) + 1, sizeof (char));

  if (!n_str)
    {
      fprintf(stderr, "%s:%u out of memory (%zu bytes)\n",
                __FILE__, line, (strlen(str) + 1) * sizeof (char));
      exit(EXIT_FAILURE);
    }

  if ((!num) || (num > strlen(str + 1)))
    memcpy(n_str, str, strlen(str));
  else
    memcpy(n_str, str, num);

  return n_str;
}

char *
format(const mpfr_ptr num)
{
  char *form_num;
  mpz_t int_op;
  mpfr_t frac_op, epsilon;

  mpz_init(int_op);
  mpfr_inits2(PREC, frac_op, epsilon, NULL);

  mpfr_get_z(int_op, num, MPFR_RNDZ);
  mpfr_frac(frac_op, num, ROUND);
  mpfr_abs(frac_op, frac_op, ROUND);
  mpfr_set_str(epsilon, EPSILON, 10, ROUND);

  char *frac_str = form_f(frac_op);

  if ((!mpfr_integer_p(num)) && (frac_str != NULL)
      && (mpfr_cmp(frac_op, epsilon) >= 0))
    {
      mpz_abs(int_op, int_op);
      char *int_str = mpz_get_str(NULL, 10, int_op);

      form_num = SALLOC(strlen(int_str) + strlen(frac_str) + strlen(".")
                        + (mpfr_sgn(num) < 0) + 1, sizeof (char));
      sprintf(form_num, "%s%s%s%s", (mpfr_sgn(num) < 0 ? "-" : ""),
              int_str, ".", frac_str);

      free(int_str);
      free(frac_str);
    }
  else
    {
      if (frac_str == NULL)
        mpz_add_ui(int_op, int_op, 1);
      else
        free(frac_str);
      form_num = mpz_get_str(NULL, 10, int_op);
    }

  mpfr_clears(frac_op, epsilon, NULL);
  mpfr_free_cache();
  mpz_clear(int_op);
  return form_num;
}

static char *
form_f(const mpfr_ptr frac)
{
  mpfr_exp_t *exp = SALLOC(1, sizeof (mpfr_exp_t));
  char *frac_str = mpfr_get_str(NULL, exp, 10, SIG_DIGIT,
                                frac, ROUND);
  size_t trail_zeros = strlen(frac_str) - 1;

  if ((*exp) > 0)
    {
      mpfr_free_str(frac_str);
      free(exp);
      return NULL;
    }

  while ((frac_str[trail_zeros] == '0')
         && (((mpfr_exp_t) (trail_zeros)) > (*exp)))
    --trail_zeros;

  char *form_num = SALLOC(trail_zeros + 2, sizeof (char));
  memcpy(form_num, frac_str, trail_zeros + 1);

  if ((*exp) != ((mpfr_exp_t) trail_zeros))
    {
      void *addr = form_num;
      char *zeros = SALLOC(fabs(*exp) + 1, sizeof (char));

      memset(zeros, '0', fabs(*exp));
      form_num = ins_str(form_num, zeros, 0);

      free(addr);
      free(zeros);
    }

  mpfr_free_str(frac_str);
  free(exp);
  return form_num;
}
