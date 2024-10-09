# Change Log INA228

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.2] - 2024-09-29
- merge fix for temperature - kudos to xkachya!
- fix for getShuntVoltage() - kudos to markliquid1 (PR #8)
- refactored many functions.
- add INA228_CFG_REGISTER defines (register 0).
- add INA228_ADC_REGISTER defines (register 1).
- fix ADC functions.
- optimize **xxxDiagnoseAlertBit()** functions
- rename **clearDiagnoseAlertBit()**
- fix **getDieID()**
- add **INA228_performance.ino**
- change return type **getEnergy()** and **getCharge()** to double.
- update readme.md

## [0.1.1] - 2024-05-15
- add limit functions
- add threshold functions
- add constants for DiagnoseAlert register
  - check them in unit test
- move register constants to .cpp
- make readRegister() and writeRegister() private
- update readme.md, keywords.txt
- minor edits


## [0.1.0] - 2024-05-10
- initial version



