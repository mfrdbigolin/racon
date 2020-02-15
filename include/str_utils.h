/* str_utils.h -- header for str_utils.c.
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

#ifndef STR_UTILS_H
# define STR_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <gmp.h>
# include <mpfr.h>
# include <stdbool.h>
# include <ctype.h>
# include <stdint.h>

# include "converter.h"
# include "error_handling.h"

# define SALLOC(n, s) salloc(n, s, __LINE__)
# define SREALLOC(p, s) srealloc(p, s, __LINE__)
# define SSTRDUP(s, n) sstrdup(s, n, __LINE__)

struct Number
{
  char *int_part;
  char *frac_part;
};

extern const uint16_t SIG_DIGIT;

char *ins_str(const char *str, const char *sub, const unsigned long pos);
char *expand(const char *str, const char *delim);
char *strip(const char *str);
struct Number *tok_num(const char *str, const char *delim);
void free_num(struct Number *num);
void *salloc(const size_t num, const size_t size, const unsigned int line);
void *srealloc(void *ptr, const size_t size, const unsigned int line);
char *sstrdup(const char *str, const size_t num, const unsigned int line);
char *format(const mpfr_ptr num);

#endif /* !STR_UTILS_H  */
