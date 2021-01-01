/* cases_str_utils.h -- test cases for str_utils.c
 * Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
 * SPDX-License-Identifier: GPL-3.0-or-later OR MIT
 */

#ifndef CASES_STR_UTILS_H
# define CASES_STR_UTILS_H

static const struct Expand CASES_EXPAND[] =
  {
   {"L154643,54P", 'L', 'P', "154643,54"},
   {".--_---_-|-.", '.', '.', "--_---_-|-"},
   {"|as|de|", '|', '|', "as"},
   {"'!", '\'', '!', ""}
  };

static const struct Strip CASES_STRIP[] =
  {
   {" T  E S T  _ C A  SE  _  1", " T  E S T  _ C A  SE  _  1",
    "TEST_CASE_1"},
   {"T\n\n E\r S T_ \fCA\t S\v E  _2 ",
    "T\\n\\n E\\r S T_ \\fCA\\t S\\v E  _2 ", "TEST_CASE_2"},
   {"  \n\n  \f \t  \t\v  \v\t  \f   ",
    "  \\n\\n  \\f \\t  \\t\\v  \\v\\t  \\f   ", ""}
  };

static const struct Tok_num CASES_TOK_NUM[] =
  {
   {"4483829.6457193", ".", &((struct Number) {"4483829", "6457193"})},
   {"X,121AFFre", ",", &((struct Number) {"X", "121AFFre"})},
   {"TEST<>CASE", "<>", &((struct Number) {"TEST", "CASE"})},
   {"123456789", "\\", &((struct Number) {"123456789", ""})},
   {"101010111|", "|", &((struct Number) {"101010111", ""})},
   {"^CASE", "^", &((struct Number) {"", "CASE"})}
  };

#endif /* !CASES_STR_UTILS_H  */
