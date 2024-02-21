# Change Log MTP40F

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.0] - 2024-02-20
- add CRC check in **request()**, thanks to DaveDavenport
  - failing CRC indicates communication error.
- added **MTP40F_INVALID_CRC** 
- update unit test
- add section about multi device / multiplexer to readme.md
- minor edits examples

-----

## [0.1.2] - 2023-11-14
- update readme.md


## [0.1.1] - 2023-08-02
- fix **getGasConcentration()** status handling
- update readme.md
- improve readability some parameters
- add (SoftwareSerial) schema to several examples
- add **MTP40F_REQUEST_FAILED** (error handling is still to do)
- add default value to **setAirPressureReference(apr = 1013)**
- add default value to **setSelfCalibrationHours(hours = 168)**
- update examples

## [0.1.0] - 2023-07-25
- initial version.

