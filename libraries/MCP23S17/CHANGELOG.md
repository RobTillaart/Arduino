# Change Log MCP23S17

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.5.4] - 2024-07-04
- fix #45, documentation bug

## [0.5.3] - 2024-06-12
- #43 optimize read/write16, kudos to Olkal
- add performance test output 0.5.2, 0.5.3
- add datasheet REV C and REV D to repo

## [0.5.2] - 2024-05-19
- Fix #40, add several interrupt functions (experimental)
- update **MCP23S17_registers.h** (reuse with MCP23017)
- change return type of several functions
  - e.g **bool enable/disableControlRegister()**
- fix support for ARDUINO_ARCH_MBED
- update readme.md
- update keywords.txt

## [0.5.1] - 2024-03-02
- Fix #38, add parameter to **begin(bool pullup)**
- update GitHub/actions to version v4 in workflows.
- Fix #37, using ints as parameter in constructor.

## [0.5.0] - 2024-01-20
- Fix #32, improve handling SPI dependency.
- update examples

----

## [0.4.0] - 2023-12-24
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

## [0.2.7] - 2023-11-13
- update readme.md
- add ledbar example

## [0.2.6] - 2023-08-15
- optimize 16 bit interface
  - add readReg16() + writeReg16()
  - based upon ideas from Alex Uta (PR #23)
- update performance test sketch (multi speeds in one run)
- update readme.md
- minor edits

## [0.2.5] - 2023-08-14
- add ESP32 HSPI / VSPI support (Kudo's to Alex Uta, PR #22)
  - add **performance_0.2.4.md** for ESP32
- add example **MCP23S17_two_SELECT.ino** (#19)
- add example **MCP23S17_two_ADDRESS.ino** (#19)
- add **void enableHardwareAddress()** (#19)
- add **void disableHardwareAddress()** (#19)
- add keywords.txt (#20)
- update readme.md
- minor edits

## [0.2.4] - 2023-02-04
- update readme.md
- update GitHub actions
- update license 2023

## [0.2.3] - 2022-10-20
- add CHANGELOG.md
- add **enableControlRegister(uint8_t mask)**
- add **disableControlRegister(uint8_t mask)**
- add mcp23S17_registers.h  )moved register defines in one place.

## [0.2.2] - 2022-09-28
- optimize digitalWrite - most used one only.

## [0.2.1] - 2022-06-29
- add SPIClass as parameter for constructor (See #10)
- redo constructors.
- add getAddress() + optimized (_address << 1)
- update readme.md

## [0.2.0] - 2022-06-28
- fix #10 incorrect mask

----

## [0.1.3] - 2022-04-13
- fix compiling for NANO33 BLE

## [0.1.2] - 2022-01-12
- change the URL for library manager

## [0.1.1] - 2022-01-10
- add 16 bit interface

## [0.1.0] - 2021-12-30
- initial version (a 2019 version did not make it)



