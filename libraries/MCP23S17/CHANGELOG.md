# Change Log MCP23S17

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.5] - 2023-07-31

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



