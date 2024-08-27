# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [1.0.8] - 2024-08-27
- Merged #23, compilation error on C++17 or later (kudos to toge) 

## [1.0.7] - 2024-08-20
- Fix #21, add **getCoefficientOfVariation()**
- update readme.md
- update keywords.txt

## [1.0.6] - 2023-11-22
- update readme.md

## [1.0.5] - 2023-06-29
- fix #18 add **range()** and **middle()**
  - fast first order functions, based on minimum() and maximum()
  - statistic value is (very) limited.
  - add example.
- update readme.md

## [1.0.4] - 2023-05-09
- fix #16 => defined(__AVR__) to catch all ARCH_AVR

## [1.0.3] - 2023-05-09
- fix #13 **sqrtf()** missing
- prep more correct NaN when \_cnt == 0;

## [1.0.2] - 2023-03-14
- update readme.md
- update FAQ.md
- update GitHub actions
- update license 2023
- minor edits

## [1.0.1] - 2022-11-25
- simplified changelog.md

## [1.0.0] - 2022-03-09
- CHANGELOG.md: moved history in Statistic.cpp to this file.
- Turned this into a header-only library to make use of compiler
  inline optimizations.
- Turned this into a class template to reduce dead code at compile
  time and allow for the use of other floating point formats (double,
  long double for example).
- Replaced `#include <Arduino.h>` with `#include <cstdint>` to find
  the proper location of `uint32_t`.  This also allows one to use the
  library in non-Arduino environments.

----

## [0.4.4] - 2021-12-28
- update library.json, readme, license, minor edits

## [0.4.3] - 2021-01-20
- add() returns how much was actually added.

## [0.4.2] - 2021-01-08
- add Arduino-CI + unit tests

## [0.4.1] - 2020-06-19
- fix library.json

## [0.4.0] - 2020-05-13
- refactor
- Added flag to switch on the use of `stdDev` runtime. [idea marc.recksiedl]

----

## [0.3.5] - 2017-09-27
- Added `#include <Arduino.h>` to fix `uint32_t` bug

## [0.3.4] - 2017-07-31
- Refactored const in many places
- reverted double to float on request as float is 99.99% of the
  cases good enough and float(32 bit) is supported in HW for some
  processors (e.g. Teensy).

## [0.3.3] - 2015-03-07
- float -> double to support ARM (compiles)
- moved count() sum() min() max() to .h; for optimizing compiler

## [0.3.2] - 2012-11-10
- minor edits
- added variance()
- changed count -> unsigned long allows for 2^32 samples

## [0.3.1] - 2012-11-10
- minor edits

## [0.3.0] - 2011-01-07
- branched from 0.2.01 version of Rob Tillaart's code

----

## [0.2.01] - 2010-10-30
- added minimum(), maximum(), unbiased stdev().
- changed counter to long -> int overflows @32K samples

## [0.2.0] - 2010-10-29
- stripped to minimal functionality

----

## [0.1.0] - 2010-10-29
- initial version
