# Change Log FastShiftOut

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.2] - 2025-10-12
- update GitHub actions
- update examples
- minor edits

## [0.4.1] - 2024-10-31
- fix #17, add more optimizations, kudos to nt314p

## [0.4.0] - 2024-09-03
- fix #15, loop unroll option, improving performance, kudos to nt314p
- fixed bug in test program (see #15)
- added flag to select LOOP UNROLL (is optional as it gives larger code size)
- optimized the not unrolled loop with ideas of the unrolling version.
- corrected type lastValue to uint8_t
- add FastShiftOut_scope_test.ino
- update readme.md
- minor edits

----

## [0.3.3] - 2024-07-23
- Fix #13, add wrapper functions
  - write16/24/32, write(array, size)
- improved timing measurement in FastShiftOut_test.ino
- update readme.md
- minor edits

## [0.3.2] - 2023-10-31
- update readme.md

## [0.3.1] - 2023-02-20
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.3.0] - 2022-11-05
- major refactor

----

## [0.2.5] - 2022-11-05
- add changelog.md
- add rp2040 to build-CI
- update readme.md

## [0.2.4] - 2021-12-17
- license

## [0.2.3] - 2021-05-27

----

## no history ...


## [0.1.0] - 2013-08-22
- initial version
