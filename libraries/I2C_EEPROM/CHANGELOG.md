# Change Log I2C_EEPROM

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [1.8.5] - 2024-04-22
- Fix #72, force requestFrom parameters to use int type


## [1.8.4] - 2024-04-20
- Fix #70, increase length internal buffer.
- add compile time flag **EN_AUTO_WRITE_PROTECT** (thanks to microfoundry)
- improve readability: cnt => count  addr => address
- add URL to examples
- minor edits.

## [1.8.3] - 2024-03-28
- Fix #64, compiler warning.
- add **verifyBlock(memoryAddress, buffer, length)**
- add example **I2C_eeprom_verifyBlock.ino**
- update GitHub actions
- update keywords.txt
- update examples
- update readme.md

## [1.8.2] - 2024-01-02
- updated **uint32_t determineSizeNoWrite()**, kudos to roelandkluit
- minor edits

## [1.8.1] - 2023-12-14
- add **uint32_t determineSizeNoWrite()**, kudos to roelandkluit
- add example
- minor edits

## [1.8.0] - 2023-11-24  (breaking change)
- simplify **begin()**, remove setting Wire pins from library.
- add **getAddress()**
- update readme.md
- update examples

----

## [1.7.4] - 2023-09-06
- solve #57 add support for WriteProtectPin
- add writeProtectPin as optional parameter in **begin()**
- add **bool hasWriteProtectPin()**
- add **void allowWrite()**
- add **void preventWrite()**
- add **void setAutoWriteProtect(bool b)**
- add **bool getAutoWriteProtect()**
- optimized **waitEEReady()**
- update keywords.txt
- update readme.md

## [1.7.3] - 2023-05-10
- fix #55 ==> redo fix #53
  - add test to detect **MBED** and **RP2040**
- adjust **I2C_BUFFERSIZE** for RP2040 to 128.
- update readme.md

## [1.7.2] - 2023-05-02
- fix #53 support RP2040 (kudos to jotamachuca)
- move code from .h to .cpp
- make I2C_WRITEDELAY overridable
- minor edits

## [1.7.1] - 2023-01-12
- add setDeviceSize()
- add setPageSize()
- use setDeviceSize() in constructor to force power of 2.
- update unit test
- update GitHub actions
- update license
- update readme.md
- minor edits

## [1.7.0] - 2022-12-02
- fix #48 rewrote constructor.

----

## [1.6.2] - 2022-10-30
- Add RP2040 support to build-CI.
- Add CHANGELOG.md
- remove **yield()** calls in writeBlock(), readBlock() and updateBlock()
  as these are already handled on a lower level. See #46
- better explain **begin()** in readme.md

## [1.6.1] - 2022-06-11
- update documentation
- minor edits
- minor improvements / bug fixes

## [1.6.0] - 2022-06-02
- add verify functions.

----

## [1.5.2] - 2021-12-19
- update library.json
- update license
- minor edits

## [1.5.1] - 2021-10-14
- function to add extra for write cycle (experimental)

## [1.5.0] - 2021-06-30
- #28 fix addressing 24LC04/08/16

----

## [1.4.3] - 2021-05-05
- adjust buffer size AVR / ESP
- rename ?

## [1.4.2] - 2021-01-31
- add updateBlock()

## [1.4.1] - 2021-01-28
- fix addressing bug 24LC04/08/16 equivalents from ST e.g. m24c08w
- add Wire1..WireN;

## [1.4.0] - 2021-01-27
- rewrite addressing scheme
- fix determineSize() - See determineSize for all tested.

----

## [1.3.2] - 2021-01-18
- add cyclic store functionality (Thanks to Tomas Hübner)

## [1.3.1] - 2020-12-22
- add Arduino-CI + unit tests
- add updateByte()

## [1.3.0] - 2020-06-19
- refactor
- remove pre 1.0 support
- add ESP32 support.

----

## [1.2.7] - 2019-09-03
- fix issue #113 and #128

## [1.2.6] - 2019-02-01
- fix issue #121

## [1.2.5] - 2017-04-20
- refactor the removed timeout (Thanks to Koepel)

## [1.2.4] - 2017-04-19
- remove timeout - issue #63

## [1.2.03] - 2015-05-15
- fix in \_pageBlock & example (thanks ifreislich )

## [1.2.02] - 2015-03-06
- stricter interface

## [1.2.01] - 2014-05-21
- Refactoring

## [1.2.00] - 2014-05-21
- Add support for Arduino DUE ( thanks to Tyler F.)

----

## [1.1.00] - 2013-11-13
- added begin() function (Note breaking interface)
- use faster block Wire.write()
- int casting removed

----

## [1.0.05] - 2013-11-06
- improved waitEEReady(),
- add determineSize()

## [1.0.04] - 2013-11-03
- fix bug in readBlock
- moved waitEEReady() -> more efficient.

## [1.0.03] - 2013-11-03
- refactor 5 millis() write-latency

## [1.0.02] - 2013-11-03
- optimize internal buffers
- refactor
## [1.0.01] - 2013-11-01
- fixed writeBlock bug
- refactor
## [1.0.00] - 2013-06-09
- support for Arduino 1.0.x

----

## [0.2.01] - 2011-08-13
- \_readBlock made more robust + return value

## [0.2.00] - 2011-02-11
- fix 64 bit boundary bug

----

## [0.1.01] - 2011-02-07
- add setBlock function

## [0.1.00] - 2011-01-21
- initial version
