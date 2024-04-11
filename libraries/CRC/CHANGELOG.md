# Changelog CRC

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [1.0.3] - 2024-04-11
- update GitHub actions
- add URL to examples
- minor edits

## [1.0.2] - 2023-10-19
- update readme.md (badges)
- fix changelog

## [1.0.1] - 2023-07-13
- added headers in examples
- added headers in src
- bumped version number
- update readme.md
- replaced ..._REF_IN ==> ..._REV_IN (OUT iden)

## [1.0.0] - 2023-05-19
- See issue #32 / #31
- new library interface
- changed CRC32 defaults
- added FastCRC32
- reused parameters and algorithms
- added platformio.ini

----

## [0.3.3] - 2023-01-17
- update GitHub actions
- update license
- renamed releaseNotes.md to CHANGELOG.md (in line with other libs)
- update readme.md

## [0.3.2] - 2022-10-30
- add RP2040 to build-CI
- fix version numbers

## [0.3.1] - 2022-05-20
- added constructors with all parameters. 
  CRC16(uint16_t polynome, uint16_t XORstart, uint16_t XORend, bool reverseIn, bool reverseOut);
  All five parameters are mandatory, no defaults in this first release. 
  Defaults would allow the constructors merge in the future.
- remove #ifndef Header guards as these are not needed.
- update documentation

## [0.3.0] - 2022-04-15
- split CRC.h in CRC.h and CRC.cpp to fix #21 (again)
- remove #ifndef Header guards as these are not needed.

----

## [0.2.3] - 2022-04-13
- replace #pragma once with #ifndef Header guards  #21

## [0.2.2]
- fix #19 enable/disable yield call

## [0.2.1]
- fix #17 yield() count in **add(array, length)**
  (kudo's to dlsloan)
- added defaults for CRC64 static function.
- static functions
  - increased length from uint8_t => uint16_t
  - added conditional yield().
- added CRC_polynomes.h

## [0.2.0]
- added getters for parameters 
- made yield conditional in **add(array, length)**
- improved examples
- added releaseNotes.md

----

## [0.1.6]
- add CRC12 function
- add CRC12 class

## [0.1.5]
- TODO (just as older versions)

That's all folks!

