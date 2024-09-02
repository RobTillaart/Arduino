# Change Log MHZCO2

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.1] - 2024-09-02
- merge #11, update lastMeasurement only if read is successful (kudos JonNelson)
- add **void setTimeOut(uint16_t timeout = 1000)** to configure timeout
- add **uint16_t getTimeOut()**
- add example **MHZCO2_sw_serial_timeout.ino**.
- update unit tests
- update readme.md
- minor edits

## [0.2.0] - 2023-12-29
- Fix #9 bug in **setPPM()**
- fix race condition in **receive()**
- update readme.md
- minor edits

----

## [0.1.4] - 2023-11-14
- update readme.md
- add plotter example (MEGA)
- update keywords.
- minor edits

## [0.1.3] - 2023-07-27
- remove MTP40F as it is not compatible
- update examples.
- minor edits.

## [0.1.2] - 2023-01-18
- fix build - SoftwareSerial problem
- fix version in .cpp
- fix date in changelog
- minor edit in readme.md

## [0.1.1] - 2023-01-06
- rename to MHZCO2
- create derived classes
- move code from .h to .cpp
- add lastMeasurement()
- improve documentation
- refactor, rewrite, optimize

## [0.1.x] - 2020-09-01
- add PWM and analog examples for MHZ19B

## [0.1.0] - 2020-05-05
- initial version (MHZ19B)


