# Change Log MS5611_SPI

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2024-06-03
- add support for ARDUINO_ARCH_MBED

## [0.3.0] - 2024-01-19
- fix #11, improve SPI dependency
  - solves #6 in a better way.

----

## [0.2.0] - 2023-11-30
- refactor constructor interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- update readme.md
- update examples

----

## [0.1.3] - 2023-11-14
- update readme.md
- update keywords

## [0.1.2] - 2022-12-14
- fix #6 support for Nano33, 
  - adding extra **begin()**
- minor edits readme.md
- move code from .h to .cpp
- commented debug Serial.print() statements from code.

## [0.1.1] - 2022-10-27
- sync with MS5611
- add RP2040 support to build-CI
- add CHANGELOG.md
- add isConnected() ==> read() should return MS5611_READ_OK
- add getManufacturer()
- add getSerialCode()
- add parameter mathMode to **reset()** to switch between pressure math.
  - see readme for details.
- minor edits.

## [0.1.0] 2022-01-18 (15-okt-2014)
- initial version, based upon MS5611 0.3.6