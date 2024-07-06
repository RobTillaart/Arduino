# Change Log MCP23017_RT

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.7.1] 2024-06-06
- Fix #36, documentation bug.

## [0.7.0] 2024-06-06
- fix #33 bug, kudos to JelleWilbrink

----

## [0.6.3] 2024-05-25
- sync MCP23S17, add several interrupt functions (experimental)
- add **MCP23x17_registers.h**
- add **readReg16()** and **writeReg16()** optimization
- update readme.md
- update keywords.txt

## [0.6.2] 2024-03-02
- Fix #29, add parameter to **begin(bool pullup)**
- remove DATE field from examples as it adds no value.
- update GitHub/actions to version v4 in workflows.

## [0.6.1] 2024-01-05
- Fix URL in examples
- minor edits

## [0.6.0] 2023-12-24
- Fix #26, support for Arduino ESP32 S3 - breaking change
- update readme.md
- update examples.

----

## [0.5.0] 2023-12-10
- refactor API, begin()
- add **uimt8_t getADdress()**
- update readme.md
  - note more about REV-D "feature"
- update examples

----

## [0.4.2] 2023-11-13
- fix readme.md badge platformIO

## [0.4.1] 2023-09-23
- add Wire1 support for ESP32
- update readme.md
- add CMakeLists.txt - See #8 mcp23008
- fix keywords.txt

## [0.4.0] - 2023-02-04
- breaking REV D chips => new release
- no change in code compared to 0.3.3
- update readme.md REV D
- update GitHub actions
- update license 2023

----

## [0.3.2] - 2022-11-17
- add RP2040 in build-CI
- add changelog.md
- edit readme.md
- fix version number .cpp

## [0.3.1] - 2022-09-28
- optimize digitalWrite() - most used one only.

## [0.3.0] - 2022-06-28
- fix incorrect masking - see #10 MCP23S17

----

## [0.2.6] - 2022-01-09
- add 16 bit interface
- update register defines

## [0.2.5] - 2021-12-21
- update library.json
- update license
- minor edits

## [0.2.4] - 2021-09-16
- add polarity support
- add pull-up support

## [0.2.3] - 2021-06-06
- add lastError() unit test + minor refactor.

## [0.2.2] - 2021-04-23
- fix for platformIO compatibility

## [0.2.1] - 2021-02-17
- fix #7 DDR is defined in ESP32

## [0.2.0] - 2021-01-11
- Multiple Wire support Wire0 .. 5
- error handling

----

## [0.1.2] - 2021-01-01
- add Arduino-CI + unit test

## [0.1.1] - 2020-06-19
- refactor
- add #pragma once

## [0.1.0] - 2019-10-12
- initial version.

