# Change Log TCA9548

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-04-15
- Fix #20, **disableChannel()** bug + optimize.
- Fix **isConnected(address, channel)** bug.
- update keywords.txt
- update readme.md
- add **uint8_t find(address)** function, returns mask.
- update / add examples.

----

## [0.2.2] - 2024-01-01
- add **bool isConnected(uint8_t address, uint8_t channel)**
- minor edits

## [0.2.1] - 2023-12-09
- add derived classes
  - PCA9543 (2 channel), PCA9545 (4 channel), PCA9546 (4 channel)
- add **uint8_t getInterruptMask()**
- fix begin() : remove wire-> begin() as dependency should be outside lib
- fix readme.md

## [0.2.0] - 2023-12-09
- refactor API, begin()
- update readme.md
- add derived class PCA9548

----

## [0.1.6] - 2023-11-22
- update readme.md
- update keywords.txt

## [0.1.5] - 2023-02-12
- fix #8 ambiguity
- update keywords.txt
- add example **tca9548_search_device.ino**
- update readme.md
- prepare error handling (constants)
- some minor edits.

## [0.1.4] - 2023-01-23
- update GitHub actions
- update license 2023
- update readme.md
- update keywords.txt
- add **void disableAllChannels()**
- all channel functions return bool, true on success.
- minor edits

## [0.1.3] - 2022-11-26
- Add RP2040 support to build-CI.
- Add CHANGELOG.md
- update readme.md
- move code to .cpp

## [0.1.2] - 2021-12-28
- update license
- minor edits

## [0.1.1] - 2021-11-19
- fix reset code (from datasheet)
- implemented forced IO
- update build-CI, readme.md, badges

## [0.1.0] - 2021-03-16
- initial version

