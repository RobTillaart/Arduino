# Change Log Float16

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-04-17
- Fix #12, breaking change. Thanks to Andyjbm for the measurements.
- remove Printable interface as it makes the effective footprint larger!
- remove getDecimals() and setDecimals().
- patch examples and unit test for the above.
- add example **float16_sizeof_array.ino**.
- add **isPosInf()** and **isNegInf()**
- add link to **float16ext** class with a larger range than float16.
- update readme.md.
- update unit-tests.

----

## [0.2.0] - 2024-03-05
- **warning: breaking changes!**
- Fix #10, mantissa overflow
- Fix convert to subnormal numbers ( < 0.000061035...)
- Fix printing subnormal numbers
- update unit tests with **test_all**
- update GitHub/actions to version 4
- remove DATE from examples as it has no added value.
- minor edits

----

## [0.1.8] - 2023-11-02
- update readme.md
- add **isNan()** (experimental).
- minor edits.

## [0.1.7] - 2022-11-07
- add changelog.md
- add rp2040 to build-CI
- update readme.md
- update keywords.txt

## [0.1.6] - 2021-12-18
- update library.json
- update license
- minor edits

## [0.1.5] - 2021-12-02
- add basic math
- optimize compare operators

## [0.1.4] - 2021-11-26
- setup repo to get it working again.
- still experimental.

----

## [0.1.03] - eons ago ??
- ??

## [0.1.02] - 2015-03-14
- getting rounding right

## [0.1.01] - 2015-03-12
- make base conversion separate functions

## [0.1.00] - 2015-03-10
- initial version

