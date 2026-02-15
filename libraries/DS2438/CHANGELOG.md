# Change Log DS2438

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.0] - 2026-02-05
- fix address bug in read/writeEEPROM()
- fix #5, improve demo sketch
- fix sign extension in **readCurrentOffset()**
- add DS2438_time_convert.ino
- add **enableCCAShadow()** + **disableCCAShadow()**
- add **bool setCCA(float value)** and **bool setDCA(float value)**
- add getters for status bits e.g **busyADC()**
- refactor code.
- update readme.md

----

## [0.1.2] - 2026-01-02
- update GitHub actions
- update examples
- minor edits

## [0.1.1] - 2024-01-27
- add **float readVAD()** and **float getVAD()**
- add **uint32_t readDisconnectTime()**
- add **uint32_t readEndOfChargeTime()**
- add **void enableCCA()** and **void disableCCA()**
- add **float readCCA()** and **float readDCA()**
- add **float readRemaining()**
- rename some functions
- update readme.md
- implement some optimizations
- minor edits

## [0.1.0] - 2024-01-26
- initial release (experimental, not tested with hardware)

----

## [0.0.0] - 2023-07-28
- initial version (partial)



