# Change Log CHT8305

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.1] - 2024-01-30
- add multiplexing section to readme.md
- update examples (URL)
- minor edits


## [0.2.0] - 2023-12-05
- refactor API, constructor, begin()
- update readme.md
- rename setHumOffset => **setHumidityOffset()**
- rename getHumOffset => **getHumidityOffset()**
- rename setTempOffset => **setTemperatureOffset()**
- rename getTempOffset => **getTemperatureOffset()**
- update examples
- update keywords.txt
- minor edits

----

## [0.1.7] - 2023-09-21
- add Wire1 support for ESP32
- fix humidity offset underflow + overflow.
- update readme.md
- minor performance optimization in humidity math

## [0.1.6] - 2023-02-01
- update GitHub actions
- update license 2023
- update readme.md
- minor edits

## [0.1.5] - 2022-10-29
- fix changelog.md
- add readTemperature()
- add readHumidity()

## [0.1.4] - 2022-10-15
- add CHT8305_DEFAULT_ADDRESS (0x40).
- add CHANGELOG.md.
- minor refactor.
- update readme.md.

## [0.1.3] - 2022-10-13
- adjust getVoltage() formula. (still unclear).
- update readme.md   (some AVR test results).
- add get- setConversionDelay().

## [0.1.2] - 2022-10-09
- update unit tests.
- fix humidity resolution parameter.
- fix setAlertLevels().
- refactor, move code to .cpp file.

## [0.1.1] - 2022-10-08
- add configuration specific functions.
- fix ESP32 begin() address check.
- add configuration ALERT functions.
- add constants for registers.
- fix getVoltage() register.

## [0.1.0] - 2022-10-06
- initial version.

