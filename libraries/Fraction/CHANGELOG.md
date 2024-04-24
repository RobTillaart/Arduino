# Change Log Fraction

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.0] - 2024-04-22
- removed **Printable** interface, braking change
- improve quality of **fractionize()** search
  - split of integer part before search improves precision.
- add support for arrays
  - default value for constructor (0, 1)
  - add **fraction_array.ino** + **fraction_sizeof.ino**
- add **toString()**
- add **isInteger()**
- update examples
  - add **fraction_extensive.ino** test range and accuracy sketch
  - add **fraction_sqrts.ino** test sketch
  - add **fraction_fast.ino**, fast determination of fraction with 9900 as denominator.
    - this is very fast, with an accuracy ~1e-4
  - add **fraction_full_scan.ino** for a full scan search.
  - optimized **FractionMediant.ino** determine fraction with mediant.
  - add **fraction_setDenominator.ino** demo
  - add **FactionPowers2.ino**, fast determination of fraction with powers of 2.- add examples including tests.
- update readme.md

----

## [0.1.16] - 2023-11-02
- update readme.md
- minor edits

## [0.1.15] - 2023-02-02
- update GitHub actions
- update license 2023
- update readme.md
- move code to .cpp
- change signature **double toDouble()**
- add **Fraction_performance.ino** to start performance testing.

## [0.1.14] - 2022-11-07
- add changelog.md
- add rp2040 to build-CI
- update readme.md

## [0.1.13] - 2021-12-18
- update library.json
- update license
- minor edits

## [0.1.12] - 2021-11-01
- update Arduino-CI
- add badges
- refactor

## [0.1.11] - 2020-12-23
- add Arduino-CI + unit tests

## [0.1.10] - 2020-06-10
- fix library.json

---- 

## [0.1.9] - 2020-04-26
- refactor

## [0.1.8] - 2018-04-02
- refactor made constructors explicit
- fix issue #33 double --> float

## [0.1.07] - 2015-03-05
- major refactoring by Chris-A

## [0.1.06] - 2015-02-15
- added proper(), mediant(), angle()

## [0.1.05] - 2015-02-14
- tested negative Fractions math
- added constructors,
- minor refactoring

## [0.1.04] - 2015-02-09
- stabilizing code
- add simplify() for some code paths.

## [0.1.03] - 2015-02-07
- add toDouble()
- tested several fractionize() codes
- bug fixes.

## [0.1.02] - 2015-02-07
- faster fractionize code

## [0.1.01] - 2015-02-03
- some fixes

## [0.1.00] - 2015-01-25
- initial version