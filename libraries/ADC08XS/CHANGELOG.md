# Change Log ADC08XS

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2025-11-06
- fix typo in readme.md
- update GitHub actions
- update examples
- minor edits

## [0.3.0] - 2024-10-06
- fix #9, set SPI_MODE3, tests see #9
- redo software SPI too.
- add **uint8_t lastChannel()**
- if channel changes do an extra read.
- add examples.

----

## [0.2.2] - 2024-06-02
- add support for ARDUINO_ARCH_MBED

## [0.2.1] - 2024-03-03
- Fix #6, add example for SPI1
- update Github/actions to v4 (build-CI)
- minor edits

## [0.2.0] - 2024-01-19
- Fix #4, improve SPI dependency

----

## [0.1.1] - 2024-01-16
- add **int deltaRead(chanA, chanB)**
- add example **ADC08XS_deltaRead.ino**
- fix select pin in **ADC08XS_read.ino**
- update readme.md


## [0.1.0] - 2024-01-13
- initial version.

