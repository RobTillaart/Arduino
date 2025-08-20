# Change Log INA228

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] - 2025-08-20
- Fix #30, getKiloWattHour() (thanks to Eerth)
- update GitHub actions

----

## [0.3.2] - 2025-07-25
- change return type getADCRange()
- add getShuntVoltageRAW()
- minor edits

## [0.3.1] - 2025-07-17
- fix #26, setADCRange() calls setMaxCurrentShunt();
- update readme.md
- update INA_comparison_table.md
- minor edits.

## [0.3.0] - 2025-03-08
- redo #20, INA.getEnergy => keep it UNsigned. Broken in 0.2.0

----

## [0.2.0] - 2025-03-05
- fix #20, INA.getCharge => make it signed.
- add **getLastError()** low level (I2C) error handling

----

## [0.1.5] - 2025-01-30
- fix #17, cache ADCRange to improve getShuntVoltage()
- add **INA_comparison_table.md**
- minor edits

## [0.1.4] - 2024-10-28
- add and rename wrappers for core functions
- update all examples
- update readme.md

## [0.1.3] - 2024-10-22
- fix #10, remove limit for the Amperes, kudos to geoFrancis
- fix handling negative values for **getShuntVoltage()**
- fix handling negative values for **getCurrent()**
- update readme.md
- add **INA228_demo_two_devices.ino**
- minor edits.

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



