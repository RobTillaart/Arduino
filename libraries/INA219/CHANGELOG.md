# Change Log INA219

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] - 2024-08-14
- fix **float getShuntVoltage()** for negative values, kudos to aguilerabr
- add **int getMaxShuntVoltage()**, depends on GAIN (Table 7).
- removed default for **setGain()** as it was not sensors default.
- update readme.md

----

## [0.3.1] - 2024-04-22
- Bump version after Fix #17, Kudos to ChrisRed255


## [0.3.0] - 2024-03-15
- Fix #14, change round to truncate.
- update GitHub actions to v4
- update json check to v2
- update readme.md
- minor edits

----

## [0.2.1] - 2024-01-17
- add **bool setBusResolution(bits)**
- add **bool setBusSamples(value)**
- add **bool setShuntResolution(bits)**
- add **bool setShuntSamples(value)**
- improve error checking several functions
  - calls to **writeRegister()** should return 0.
  - error handling needs improvement, this is a first step.
- improve **INA219_get_settings.ino**
- update keywords.txt
- update readme.md

## [0.2.0] - 2023-12-04
- Fix #8, refactor API - support ESP32-S3
- update readme.md
- update examples
- add **getAddress()**

----

## [0.1.5] - 2023-09-24
- Add Wire1 support for ESP32
- update readme.md

## [0.1.4] - 2023-06-12
- improve RP2040 support
- add address test in isConnected()
- update readme.md
- add array example

## [0.1.3] - 2023-03-31
- fix setBusADC() range check
- fix setShuntADC() range check
- fix setMode() range check
- add getMathOverflowFlag()
- add getConversionFlag()
- add example to test settings
- add example to test I2C speed
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.1.2] - 2022-11-14
- Add RP2040 support to build-CI.
- Add CHANGELOG.md

## [0.1.1] - 2022-09-06
- refactor and first public release

## [0.1.0] - 2021-05-18
- initial version


