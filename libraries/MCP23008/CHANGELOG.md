# Change Log MCP23008

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.4] 2024-07-04
- Fix #21, documentation bug

## [0.3.3] 2024-05-25
- add several interrupt functions (sync MCP23S17)
- update **MCP23x08_registers.h** (reuse with MCP23008)
- change return type of several functions
  - e.g **bool enable/disableControlRegister()**
- fix support for ARDUINO_ARCH_MBED
- update readme.md
- update keywords.txt

## [0.3.2] 2024-03-02
- Fix #17, add parameter to **begin(bool pullup)**
- remove DATE field from examples as it adds no value.
- update GitHub/actions to version v4 in workflows.

## [0.3.1] - 2024-01-05
- add URL to examples
- minor edits

## [0.3.0] - 2023-12-24
- Fix #14, support for Arduino ESP32 S3 - breaking change
- update readme.md
- update examples.

----

## [0.2.0] - 2023-12-10
- refactor API, begin()
- update readme.md
- add **uint8_t getAddress()**
- update examples

----

## [0.1.5] - 2023-09-23
- add Wire1 support for ESP32
- update readme.md

## [0.1.4] - 2023-06-20
- add CMakeLists.txt #8
- add debug function **uint8_t getPinMode8()**
- add keywords.txt
- update examples

## [0.1.3] - 2023-02-04
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.1.2] - 2022-11-17
- add RP2040 in build-CI
- add changelog.md
- minor edit readme.md
- update datasheet page numbers of registers MCP23008.cpp

## [0.1.1] - 2022-09-28 
- optimize digitalWrite() - as that is the most used one

## [0.1.0] - 2022-01-10
- initial version released

## [0.0.0] - 2019-10-12
- pre release