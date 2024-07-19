# Change Log FRAM_I2C
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.8.1] - 2024-07-19
- Fix #56, performance sketch
- minor edits

## [0.8.0] - 2024-01-15
- Fix #51 - bug in FRAM32::_readBlock()
- improve fram32 example to test both low and high addresses
- add memory address guarding for the FRAM32 _readBlock() and _writeBlock()
- update readme.md.

----

## [0.7.1] - 2024-01-09
- improve getSize() to support Infineon FM24V10 and FM24V05 (#49)
- update readme.md
- minor edits examples

## [0.7.0] - 2023-10-30
- refactor / simplify begin() =>  
  - User has to call Wire.begin() explicitly.
  - improves support for RP2040 (setSDA/SetSCL).
- add example for ESP32 => use Wire1 and set pins (SDA/SCL).
- Add example for RP2040 => setSDA() + setSCL()
- update badges in some document.md files.

----

## [0.6.1] - 2023-09-16
- add Wire1 support for ESP32
- fix changelog.md

## [0.6.0] - 2023-09-16
- fix #42 ReadObject, WriteObject for FRAM32
- add examples
- minor edits

----

## [0.5.4] - 2023-09-04
- merge #39 add **read64(), write64()**  (kudos to pvogt09)
- merge #40 add **MB85RC64V** info (kudos to pvogt09)
- rewrite **getManufacturerID, getProductID, getSize()**
  to handle non existent metadata (See #38)
- update keywords.txt
- update unit test
- improved readability parameter names
- update readme.md

## [0.5.3] - 2023-04-28
- major redo FRAM9 and FRAM11, see #35
- update FRAM32 to match FRAM
- update readme.md.
- minor edits

## [0.5.2] - 2023-04-22
- add **FRAM_ML** class - see FRAM_MULTILANGUAGE.md
- add examples.
- update readme.md.
- update keywords.txt

## [0.5.1] - 2023-04-20
- add **readUntil(uint16_t memaddr, char \* buf, uint16_t buflen, char separator)**.
- add **readLine(uint16_t memaddr, char \* buf, uint16_t buflen)** (separator = '\n').
- add examples.
- update readme.md.

## [0.5.0] - 2023-02-15
- add FRAM11 - 11 bit addresses
- add FRAM9 - 9 bit addresses
- update readme.md
- add example **FRAM9_test.ino**
- add example **FRAM11_test.ino**

----

## [0.4.3] - 2022-12-28
- add **writeFloat()**, **readFloat()**
- refactor
- add nano_every to build-ci  (test)
- update readme.md
- update license
- update Github actions to v3  (test)
- simplified changelog

## [0.4.2] - 2022-10-03
- add **FRAM_RINGBUFFER** class - see FRAM_RINGBUFFER.md
- build-ci support for RP2040 pico
- updated documentation
- moved code from FRAM.h to FRAM.cpp

## [0.4.1] - 2022-09-24
- changed ESP32 **begin()** parameters to **int** to prevent link error.
  see https://github.com/RobTillaart/PCA9635/issues/17
- updated documentation

## [0.4.0] - 2022-05-02
- add **FRAM32** derived class to support the MB85RC1MT as it need 32 bits addressing. 
  This class uses 4 byte memory addresses internally.
  Note **FRAM32** can also address 16 bit FRAM devices.
- updated documentation

----

## [0.3.6] - 2022-05-02
- add **void sleep()** experimental.
- add **bool wakeup(trec = 400)** experimental. wakeup time of 400us. returns true if connected after call.
- add example **FRAM_sleep.ino**
- updated readme.md
- updated keywords.txt
- minor edits

## [0.3.5] - 2022-03-23
- add **uint32_t clear(uint8_t value = 0)**
- add **void setSizeBytes(uint32_t value)**
- added defines for size of known types for e.g. **void setSizeBytes(uint32_t value)**
- add \_sizeinBytes private var. Needed in clear a.o.
- **getSize()** automatically called in **begin()**
- updated example **FRAM_clear.ino**
- renamed private functions with \_
- updated readme.md

## [0.3.4] - 2022-03-16
- add **uint16_t writeObject(memaddr, &obj)** see #13
- add **uint16_t readObject(memaddr, &obj)** see #13
- add examples for write- and readObject()
- renamed releaseNotes.md => CHANGELOG.md
- some edits in readme.md

## [0.3.3] - 2022-02-08
- added **getSizeBytes()**
- created releaseNotes.md
- updated readme.md
- add example FRAM_logging.ino

## [0.3.2] - 2021-12-18
- update Arduino-CI,
- add badges in readme.md
- update library.json,
- update license,
- minor edits

## [0.3.1] - 2021-02-05
- fix #7 typo in .cpp

## [0.3.0] - 2021-01-13
- fix #2 ESP32
- add WireN support

----

## [0.2.3] - 2021-01-11
- fix getMetaData (kudos to PraxisSoft)

## [0.2.2] - 2020-12-23
- add Arduino-CI + unit test
- add **getWriteProtect()**

## [0.2.1] - 2020-06-10
- fix library.json

## [0.2.0] - 2020-04-30
- refactor,
- add writeProtectPin code

## [0.1.1] - 2019-07-31
- added support for Fujitsu 64Kbit MB85RC64T (kudos to ysoyipek)

## [0.1.0] - 2018-01-24
- initial version

