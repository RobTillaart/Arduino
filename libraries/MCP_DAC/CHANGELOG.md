# Change Log MCP_DAC

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.5.1] - 2024-06-05
- add support for ARDUINO_ARCH_MBED

## [0.5.0] - 2024-01-20
- Fix #29, improve handling SPI dependency.
- update examples

----

## [0.4.0] - 2023-12-19
- fix #27, support for Arduino ESP32 S3 - breaking change
- update examples
- fix SPIClass define

----

## [0.3.0] - 2023-11-21
- refactor constructor interface - breaking changes.
  - minimize conditional code.
  -- create __SPI_CLASS__ macro to solve it.
- fix #24 support for ESP32-S3
  - remove ESP32 specific functions and dependencies.
- update readme.md
- update examples

----

## [0.2.1] - 2023-11-13
- update readme.md

## [0.2.0] - 2023-03-23
- fix #21 bug LDAC invert
- fix **setPercentage()**
- move code from .h to .cpp
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

----

## [0.1.8] - 2022-10-18
- improve RP2040 support (kudos to Intubun)
- add CHANGELOG.md
- update readme.md

## [0.1.7] - 2022-10-02
- support for RP2040 pico (kudos to Intubun)
- update documentation for RP2040 (kudos to Intubun)
- update build-CI to support RP2040

## [0.1.6] - 2021-12-21
- update library.json, license, minor edits

## [0.1.5] - 2021-11-08
- update build-CI, badges,
- default parameter 1 for setGain()
- default parameter false for setBufferedMode()
- default parameter 0 for getPercentage()
- extended unit tests

## [0.1.4] - 2021-08-01
- fix setGPIOpins() - needs more testing.

## [0.1.3] - 2021-07-31
- add increment() and decrement()

## [0.1.2] - 2021-07-29
- VSPI / HSPI support for ESP32 (default pins only
- faster software SPI
- minor optimizations / refactor

## [0.1.1] - 2021-05-26
- moved SPI.begin() from constructor to begin()

## [0.1.0] - 2021-02-03
- initial version

