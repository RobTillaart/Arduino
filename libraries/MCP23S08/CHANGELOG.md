# Change Log MCP23S08

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.5.3] - 2024-07-04
- Fix #20, documentation bug

## [0.5.2] - 2024-05-25
- add several interrupt functions (sync MCP23S17)
- update **MCP23x08_registers.h** (reuse with MCP23008)
- change return type of several functions
  - e.g **bool enable/disableControlRegister()**
- fix support for ARDUINO_ARCH_MBED
- update readme.md
- update keywords.txt

## [0.5.1] 2024-03-02
- Fix #17, add parameter to **begin(bool pullup)**
- update GitHub/actions to version v4 in workflows.
- using ints as parameter in constructor.

## [0.5.0] - 2024-01-20
- Fix #14, improve handling SPI dependency.
- update examples

----

## [0.4.1] - 2024-01-05
- Fix URL in examples
- minor edits

## [0.4.0] - 2023-12-01
- Fix #30, support for Arduino ESP32 S3 - breaking change
- update readme.md
- update examples.

----

## [0.3.0] - 2023-12-01
- refactor constructor interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- update readme.md
- update examples

----

## [0.2.1] - 2023-11-13
- update readme.md
- update keywords.txt

## [0.2.0] - 2023-08-19
- add ESP32 support
- sync with MCP23S17
- add **getAddress()**
- add **MCP23S08_registers.h**
- update readme.md
- update examples
- minor edits

----

## [0.1.3] - 2023-02-04
- UPDATE README.MD
- update GitHub actions
- update license 2023

## [0.1.2] - 2022-11-17
- add RP2040 in build-CI
- add changelog.md
- minor edit readme.md
- fix **PinStatus** bug for RP2040 build

## [0.1.1] - 2022-09-28
- optimize digitalWrite - most used one only.
- add MCP23S08_REGISTER_ERROR

## [0.1.0] - 2022-01-10
- initial version.

