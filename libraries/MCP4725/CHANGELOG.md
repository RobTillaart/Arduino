# Change Log MCP4725
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] - 2023-12-08
- refactor API, begin()
- update readme.md
- add **uint8_t getAddress()**
- update examples
- fix **MCP4725_voltage.ino** example
- minor edits

----

## [0.3.9] - 2023-09-25
- add Wire1 support for ESP32

## [0.3.8] - 2023-09-18
- fix #30 Voltage functions (wrapper).
  - **void setMaxVoltage(float v)**
  - **void getMaxVoltage(float v)**
  - **void setVoltage(float v)**
  - **float getVoltage()**
- add examples
- update readme.md

## [0.3.7] - 2023-08-25
- fix #27 - support for multiple MCP4725
  - add two examples.
- update readme.md
- minor edits

## [0.3.6] - 2023-07-19
- fix #25 - buffer overflow in examples
- update keywords.txt
- moved code to MCP4725.cpp
- minor edits

## [0.3.5] - 2023-01-17
- update GitHub actions
- update license
- fix #23 add note about RP2040
- add **MCP4725_MIDPOINT** constant
- minor edits

## [0.3.4] - 2022-10-17
- Add RP2040 support (kudos to intubun)
- Add RP2040 in build-CI
- Add changelog.md

## [0.3.3] - 2021-12-21
- update library.json,
- update license
- minor edits

## [0.3.2] - 2021-06-06
- Verify input of setPercentage()

## [0.3.1] - 2021-05-27
- Fix Arduino-CI / Arduino-lint

## [0.3.0] - 2021-01-15
- Add WireN support (e.g. teensy)

----

## [0.2.3] - 2020-12-26
- Arduino-CI,
- add bool isConnected(),
- update bool begin()

## [0.2.2] - 2020-07-05
- add get/setPercentage();

## [0.2.1] - 2020-07-04
- Add yield();
- add getLastWriteEEPROM();
- update readme.md
- update keywords.txt

## [0.2.0] - 2020-06-20
- use #pragma once;
- remove pre 1.0 support;
- refactor a lot
- rename RDY() -> ready()

----

## [0.1.9] - 2019-10-14
- replace AVR specific TWBR with \_wire->setClock() #131

## [0.1.8] - 2018-10-24
- fix read only variables #115 (kudos to perl1234)

## [0.1.7] - 2017-04-20
- refactor the removed timeout (Thanks to Koepel)

## [0.1.6] - 2017-04-19
- refactor
- remove timeout - https://github.com/RobTillaart/Arduino/issues/63

## [0.1.05] - 2015-03-06
- refactoring, stricter interfaces

## [0.1.04] - 2013-12-04
- improved the generalCall code (still experimental)

## [0.1.03] - 2013-12-01
- added powerDownMode code

## [0.1.02] - 2013-12-01
- added readEEPROM()
- added RDY()

## [0.1.01] - 2013-11-30
- added readDAC()
- added writeDAC(registerwrite)

## [0.1.00] - 2013-11-24
- initial version

