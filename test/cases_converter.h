/* cases_converter.h -- test cases for converter.c.
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

#ifndef CASES_CONVERTER_H
# define CASES_CONVERTER_H

const struct Form tst_cases[] =
  {
   {"19", "-0", "0"},
   {"2", "10101011", "171"},
   {"2", "-10101011", "-171"},
   {"-2", "10111001", "-151"},
   {"-2", "-10111001", "151"},
   {"100", "AzBC9D2", "10611112091302"},
   {"100", "-AzBC9D2", "-10611112091302"},
   {"365", "[54][12][257][98]", "2627557353"},
   {"365", "-[54][12][257][98]", "-2627557353"},
   {"3.1415", "121301213123", "541392.24475664988833749452746843806247"},
   {"3.1415", "-121301213123", "-541392.24475664988833749452746843806247"},
   {"-2.7172", "10120101212", "22569.14748486818789935462093230699298"},
   {"-2.7172", "-10120101212", "-22569.14748486818789935462093230699298"}
  };

const struct Form etst_cases[] =
  {
   {"5", "-0", "0"},
   {"2", "123", "1111011"},
   {"12", "-156", "-110"},
   /*{"-7", "1732", "12153"},
     {"-2", "-5", "1111"},*/
   {"666", "994838291", "3[244][579][125]"},
   {"666", "-994838291", "-3[244][579][125]"},
   {"2.5", "-3221", "-200112001.01112020001201202002101000000002"},
   {"10", "3.14159265358979323846264338327950",
    "3.1415926535897932384626433832795"},
   {"10", "0.5", "0.5"},
   {"7777", "5.0898978797897987978798797879789787997896978968798698", "1"}
  };

const struct Form tst_cases_f[] =
  {
   {"10", "0.0", "0"},
   {"2", "0.10101011", "0.66796875"},
   {"2", "-0.10101011", "-0.66796875"},
   {"-2", "0.10111001", "-0.58984375"},
   {"100", "0.AzBC9D2", "0.10611112091302"},
   {"365", "0.[54][12][257][98]", "0.14804056930145779099487183026583"},
   {"10", "3.141592653589793238462643383279502",
    "3.1415926535897932384626433832795"},
   {"10", "2.001", "2.001"},
   {"10", "0.00000000000000000000000000000000999999999", "0"},
   {"10", "0.00000000000000000000000000000002",
    "0.00000000000000000000000000000002"},
   {"0.125", "56.234", "2262.625"},
   {"10", "0.9999999999999999999999999999999999999999999999999999", "1"}
  };

const struct Form_Fail fail_cases[] =
  {
   {"2", "2", "1010121001"},
   {"2", "2", "1010110012"},
   {"2", "2", "2101.010010"},
   {"2", "2", "10101z31001"},
   {"2", "2", "10101.110014"},
   {"2", "2", "510101110010"},
   {"0.1", "0.1", "87657A8965"},
   {"0.1", "0.1", "87657.8965A"},
   {"0.1", "0.1", "A876578965"},
   {"-0.35", "-0.35", "10101301010"},
   {"-0.35", "-0.35", "10101010103"},
   {"-0.35", "-0.35", "3101.0101010"},
   {"15", "15", "[12]2A[15]1"},
   {"15", "15", "[12]2.AB5[15]"},
   {"15", "15", "[15]C3[12]2AB5"},
   {"15", "15", "[12]2A[16]1"},
   {"15", "15", "[12]2C3A[17]"},
   {"15", "15", "[18]6C[12]2A1"},
   {"32", "32", "124AB[-6][4]"},
   {"32", "32", "124AB[23][-1]"},
   {"32", "32", "[-5439]124AB[4]"},
   {"43", "43", "AB27[32][1fd]7[28]"},
   {"43", "43", "AB27[32]A7[28][hf6]"},
   {"43", "43", "[mgm6kRF]AB27[32]A7[28]"},
   {"69", "69", "14dfAf.ftR34.a"},
   {"10", "10", "1288438\\58788"},
   {"10", "10", "128843858788\\"},
   {"10", "10", "\\128843858788"},

   {"112e35", "112e35", "cannoteval1"},
   {"7544H", "7544H", "cannoteval2"},
   {">12986", ">12986", "cannoteval3"},
   {"-1", "-1", "-1base"},
   {"0", "0", "0base"},
   {"1", "1", "1base"}
  };

#endif /* CASES_CONVERTER_H  */
