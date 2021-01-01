<!--
  - Copyright (C) 2020 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
  - SPDX-License-Identifier: GPL-3.0-or-later OR MIT
  -->

# Racon (RAdix CONverter) [![Public license](https://img.shields.io/badge/GPL--3.0--or--later-yellow?logo=spdx&logoColor=white)](./LICENSE.GPL-3.0-or-later) [![Public license](https://img.shields.io/badge/MIT_(Expat)-yellow?logo=spdx&logoColor=white)](./LICENSE.MIT)

This was my first  serious project, I can say that,  at least, the software
works for its  original purpose.  I am  here at the last hours  of the last
day of  the last year of  the 201st decade  of Anno Domini to  publish this
software and avoid having to change  all the ''Copyright (C)`` from 2020 to
2021.

Racon is,  as its description says,  a numeric RAdix CONversion  system; id
est, a base converter.   Built with the GNU GMP and  the GNU MPFR libraries
the program holds a lot of digits and has a good decimal precision; you can
use integer and fractional numbers.

I originally wrote this software between October of 2019 and March of 2020.
I  only started  using  `git`  when the  software  development was  already
stagnating at the end.

I left the software almost intact,  with the exception of the file headers,
this `README` and some  fixes to make the software build.   I plan to write
about Racon  internals in  a *blog*,  and maybe rewrite  it in  a different
language (probably Julia) in the next year.

## Building

0. Have the GNU MPFR and GNU GMP libraries installed in your machine.

1. Type `make` at the root of the project.

2. The executable file will be at `/bin`.

3. `make clean` cleans the build and binary repository.

## Usage

The usage is pretty simple, it is just:

`racon -i "`*`<basor>`*`" -o "`*`<basend>`*`" -n "`*`<number>`*`"`

* *`<basor>`*: input base.

* *`<basend>`*: output base.

## License

I originally intended to publish Racon under GPLv3+, however, now for
historical and pragmatical purposes I will dual-license it with the MIT.

SPDX-License-Identifier: GPL-3.0-or-later OR MIT

This software is dual-licensed with the GNU General Public License version
3 or (at your option) later version OR the MIT (Expat) License; this means
that to use this software you can comply with either the GPLv3+ OR with the
MIT.

It is important to state that both licenses provide NO WARRANTY of any kind
for this material, and the auteur is NOT LIABLE in any event arising from
the use of this program.

Please read the full licenses at /LICENSE.GPL-3.0-or-later, for GPLv3+; or
at /LICENSE.MIT, for MIT.
