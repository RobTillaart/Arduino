# Change Log SHT2x

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.1] - 2022-11-24
- Add RP2040 support to build-CI.
- Add CHANGELOG.md


## [0.2.0] - 2022-07-10
- Fix #11 RawTemp + rawHum (kudos to theandy94)
- add experimental getResolution() + setResolution()
- adjust read delay
- add experimental batteryOK()
- add CRC in read() - no fail.

----

## [0.1.4] - 2022-06-21
- Fix #9 ESP32 wire.begin()
- Fix getEIDB() bug.

## [0.1.3] - 2021-12-28
- update library.json 
- update license
- minor edits

## [0.1.2] - 2021-09-29  
- Add Si70xx derived classes
- add getEIDA(), getEIDB(), getFirmwareVersion()
- update build-CI, readme.md badges

## [0.1.1] - 2021-09-28  
- Add HTU2x derived classes,
- update readme.md + add some status info

## [0.1.0] - 2021-09-25
- initial version

