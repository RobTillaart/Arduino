# Change Log MCP_ADC

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.5.1] - 2024-06-05
- add support for ARDUINO_ARCH_MBED

## [0.5.0] - 2024-01-20
- Fix #22, improve handling SPI dependency.
- update examples

----

## [0.4.0] - 2023-12-18
- fix #18, support for Arduino ESP32 S3 - breaking change
- update examples
- Fix #17, readme.md

----

## [0.3.0] - 2023-11-29
- refactor constructor interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- update readme.md
- update examples

----

## [0.2.1] - 2023-09-08
- fix #13 support **MCP3201**
- add **MCP3001** support
- fix startup pulse for **select** pin.
- update readme.md
- fix version number in .cpp
- update keywords.txt

## [0.2.0] - 2023-08-15
- add analogReadMultiple(channels\[], numChannels, readings\[]) 
  - Kudo's to Alex Uta.
- add performance example
  - add performance output files.
- add support MCP3201 (experimental)
- fix differentialRead()
- update examples (print lib version).
- update readme.md
- update library.properties
- minor edits

----

## [0.1.9] - 2022-11-16
- add RP2040 in build-CI
- add changelog.md
- minor edit readme.md
- clean up unit test


## [0.1.8] - 2021-12-21
- update library.json
- update license
- minor edits

----

## [0.1.7] - 2021-11-07

## [0.1.6] - 2021-08-01

## [0.1.5] - 2021-07-31

## [0.1.4] - 2021-03-31

## [0.1.3] - 2021-02-04

## [0.1.2] - 2021-01-01

## [0.1.1] - 2020-08-14

## [0.1.0] - 2019-10-24
- initial version.

