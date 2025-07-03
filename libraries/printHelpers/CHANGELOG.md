# Change Log printHelpers

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.5.0] - 2025-06-30
- fix #24, add printHelpersMT.h,
  - class implementation for multThreading.
  - scieng(), sci() and eng()
  - print64()
  - toBytes()
  - hex(), bin()
  - toRoman()
  - printInch(), printFeet()
  - csi(), fraction()
- add several MT examples
- update unit tests
- fix PRINTHELPERS_LIB_VERSION
- obsolete PRINTHELPERS_VERSION
- catch error in print64() (buffer too small)
- catch error in toBytes() (NAN)
- catch error in printInch() (NEG)
- catch error in printFeet() (NEG)
- fix output of printFeet()
- add parameter in csi for separator, default ','
- update readme.md
- minor edits

----

## [0.4.6] - 2024-11-21
- fix #22, negative fractions
- fix unofficial **toRoman()** for > 4888
- add support for negative sign for **toRoman()**
- changed parameter to signed **toRoman(int32_t value)**
- add unit tests
- update readme.md

## [0.4.5] - 2024-11-20
- add experimental **fraction()**
- add **print_fractions.ino** example
- add **print_fractions_denum.ino** example
- update **print_sci_experimental.ino** example
- added define PRINTHELPERS_LIB_VERSION.
- update readme.md

## [0.4.4] - 2024-01-05
- fix URL in examples
- minor edits

## [0.4.3] - 2023-11-15
- added **csi()** comma separated integers for readability e.g. 123,458,654
- update readme.md.
- update examples

## [0.4.2] - 2023-11-15
- update readme.md
- update keywords.txt

## [0.4.1] - 2023-07-13
- fix #16  signed/unsigned warning
- update example **print_toRoman.ino** to print 1..5000
- update example **print_sci.ino** when double = 8 bytes.
- update readme.md
- fix description range **toBytes()**
- change return type of **size_t sci(Stream, value, decimals)**
- add **printInch(inch, step)** e.g 7 7/16
- add **printFeet(feet)**

## [0.4.0] - 2023-01-28
- bump version number as fix in 0.3.1 was serious
- add **toRoman()**
- add toRoman example
- redo **toBytes()** (less RAM)
- update readme.md
- update unit test
- minor edits

----

## [0.3.1] - 2023-01-27
- fix **scieng()** itoa() => sprintf()  + conditional ESP32
- add leading 0 for exponents smaller than 10, to better align columns.
- update GitHub actions
- update license 2023
- add performance example
- update readme.md
- minor edits

## [0.3.0] - 2022-11-29
- add hex(value, digits) + bin(value, digits) 32 and 64 bit
- leading zero's - no separators - no prefix.
- add example show the difference
- update readme.md
- update unit test

----

## [0.2.5] - 2022-11-22
- add changelog.md
- add RP2040 to build-CI

## [0.2.4] - 2022-04-15
- no info

## [0.2.3] - 2021-24-12

## [0.2.2] - 2021-11-13

----

## [0.1.0] -  2018-01-21
- initial version


