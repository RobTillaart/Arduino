# Change Log MSP300

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-05-09
- Fix read bug, thanks to Gabo-Bravo
- updated readme.md
- added **uint8_t getStatus()** + defines for error codes.
- update the default I2C address to 0x28 (within range).
- rewrite **readPT()** and cache pressure, temperature and status.
- add **readP()** to read pressure and status only. (faster).
- add **getPmin()** and **getPmax()** for calibration.
- add **MSP300_performance.ino** to measure I2C read performance.
- add **MSP300_demo_pressure_only.ino** 
- add **MSP300_fast_pressure.ino** 
- update keywords.txt

----

## [0.2.0] - 2023-12-05
- refactor begin()
- update readme.md
- minor edits

----

## [0.1.2] - 2023-09-23
- add Wire1 support for ESP32
- fix keywords.txt
- update readme.md

## [0.1.1] - 2023-02-05
- update readme.md
- update GitHub actions
- update license 2023

## [0.1.0] - 2022-12-06
- initial version

