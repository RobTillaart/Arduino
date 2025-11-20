# Change Log INA260

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [0.1.2] - 2025-11-16
- sync INA226 - 0.6.5
- improvements on ALERT register functions
- removed FC00 mask in **bool setAlertRegister()**
- add **uint16_t getAlertRegister()** to get all register bits.
  - obsoletes getAlertFlag().
- add **void setAlertLatchEnable(bool latch = false)**
- add **void setAlertPolarity(bool inverted = false)**
- add **void getAlertLatchEnable()**
- add **void getAlertPolarity()**
- update GitHub actions
- update readme.md
- minor edits

## [0.1.1] - 2025-05-06
- add **getLastError()** low level (I2C) error handling
- update readme.md
- update examples

## [0.1.0] - 2025-02-18
- initial version



