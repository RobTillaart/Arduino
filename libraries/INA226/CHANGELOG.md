# Change Log INA226

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.6.5] - 2025-11-11
- fix #61, improvements on ALERT register functions
- removed FC00 mask in **bool setAlertRegister()**
- add **uint16_t getAlertRegister()** to get all register bits.
  - obsoletes getAlertFlag().
- add **void setAlertLatchEnable(bool latch = false)**
- add **void setAlertPolarity(bool inverted = false)**
- add **void getAlertLatchEnable()**
- add **void getAlertPolarity()**
- add **INA226_pointer.ino** examples
- make **INA226_MINIMAL_SHUNT_OHM** command line option
- update GitHub actions
- update readme.md
- minor edits


## [0.6.4] - 2025-03-05
- add **getLastError()** low level (I2C) error handling

## [0.6.3] - 2025-02-12
- fix #53, BUG in 0.6.2 **getBusVoltage()** looses decimals.

## [0.6.2] - 2025-02-11
- Add **configure()**, thanks to pk17r
- Add **INA226_calibrate.ino** example
- update readme.md
- align debug prints of configure() and setMaxCurrentShunt()
- minor optimization in getBusVoltage()


## [0.6.1] - 2025-01-27
- fix #49, precision math setMaxCurrentShunt() in INA226.cpp
- change max shunt voltage to 81.9 mV (0.02 under datasheet limit)
- change INA226_MINIMAL_SHUNT_OHM
- update comments in INA226.h
- add INA_comparison_table.md
- update readme.md

## [0.6.0] - 2024-05-27
- Fix #47, calibration register is 15 bit, not 16 bit.
- minor edits

----

## [0.5.5] - 2024-04-22
- Fix possible overflow in **getPower()**


## [0.5.4] - 2024-04-04
- add multi device and array example
- add address table to readme.md
- minor edits

## [0.5.3] - 2024-03-25
- add enum **ina226_average_enum** (Thanks to Henk Holdijk)
- add enum **ina226_timing_enum** for BVCT SVCT conversion timing
- update keywords
- update GitHub actions
- update section **Configuration** in readme.md.
- update unit test
- minor edits

## [0.5.2] - 2024-01-06
- Thanks to Henk Holdijk for his improvements.
- fix #35, add **bool isConversionReady()**
- add **bool waitConversionReady(uint32_t timeout = INA226_MAX_WAIT_MS)**
- add constant **INA226_MAX_WAIT_MS**
- changed return type **bool setAlertRegister(uint16_t mask)**
- changed return type **bool setAlertLimit(uint16_t limit)**
- reorder functions in .cpp file to match .h
- remove not needed include from examples.
- update readme.md

## [0.5.1] - 2023-12-10
- reimplementation of **setMaxCurrentShunt()**,
  - thanks to tileiar
- update readme.md
- minor edits

## [0.5.0] - 2023-12-04
- Fix #31, refactor API - support ESP32-S3
- update readme.md
- update examples

----

## [0.4.4] - 2023-09-23
- add Wire1 support for ESP32
- update readme.md

## [0.4.3] - 2023-05-07
- add constant INA226_MINIMAL_SHUNT

## [0.4.2] - 2023-04-03
- added **getBusVoltage_uV()** for completeness
- INA226_test_I2C.ino to prep performance tests
- fix changelog.md
- fix keywords.txt
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.4.1] - 2022-11-12
- Add RP2040 support to build-CI.
- Add CHANGELOG.md, replaces release_notes to be consistent over my libraries.
- minor edit unit test

## [0.4.0] - 2022-08-26
- fix #16 - change error to warning for max current
  setMaxCurrentShunt now returns an int indicating OK == 0
  otherwise error. See INA226.h for error codes.
- updated readme.md
- updated unit tests (error codes)

----

## [0.3.0] - 2022-07-01
- fix #14 RESET FLAG
- add getAddress()

----

## [0.2.0] - 2022-02-02
- fix #11 normalize
- fix #13 simplify sign handling shunt and current
- add releaseNotes.md
- **reset()** also resets the calibration (current_lsb, maxCurrent and shunt),
thereby forcing the user to redo the calibration call with **setMaxCurrentShunt()**.
- fixes issue #11 => a factor 10 bug in current_lsb.
- some edits in readme.md.
- added **bool isCalibrated()**.

----

## [0.1.6] - 2021-12-20
- update library.json,
- license,
- minor edits

## [0.1.5] - 2021-11-05
- update build-CI,
- add badges in readme.md
- fix address in constructor

## [0.1.4] - 2021-08-07
- fix getCurrent()

## [0.1.3] - 2021-06-22
- add getCurrentLSB_uA()
- improve examples
- fix for calibration

## [0.1.2] - 2021-06-22
- add check of parameters of several functions
- add unit tests
- add getShunt()
- add getMaxCurrent()

## [0.1.1] - 2021-06-21
- improved calibration
- added functions

## [0.1.0] - 2021-05-18
- initial version



