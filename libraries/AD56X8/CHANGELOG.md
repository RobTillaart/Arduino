# Change Log AD56X8

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2024-05-24
- add support for ARDUINO_ARCH_MBED

## [0.3.0] - 2024-01-19
- fix #10, improve handling SPI dependency.

----

## [0.2.1] - 2024-01-02
- fix __SPI_CLASS__
- fix examples
- minor edits

## [0.2.0] - 2023-11-27
- refactor constructor interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- reordered parameters software SPI constructor.
- update readme.md
- update examples

----

## [0.1.4] - 2023-09-19
- add hardware LDAC support 
  - **void setLDACPin(ldac)** and **bool triggerLDAC()**
- update README.md
- minor edits


## [0.1.3] - 2023-01-18
- fix build
- add unit tests (get_setPercentage)
- add example: AD56X8_test_percentage.ino
- move code from .h to .cpp
- update README.md

## [0.1.2] - 2023-01-09
- update GitHub actions
- update license
- add wave example (triangle)
- add bool setPercentage(channel, percentage)
- add float getPercentage(channel)

## [0.1.1] - 2022-12-01
- initial release
- add changelog.md
- add derived type - AD5668_3() starts up at midscale
- initialize internal values\[] array.
- improve unit tests
- clean up code
- update README.md

## [0.1.0] - 2022-07-28
- rework (add from DAC855x + MCP_DAC)
- not released.

----

## Eons ago
- initial work



