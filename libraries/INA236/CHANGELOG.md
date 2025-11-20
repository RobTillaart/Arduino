# Change Log INA236

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.5] - 2025-11-17
- sync INA226, 0.6.5
- improvements on ALERT register functions
- removed FC00 mask in **bool setAlertRegister()**
- add **uint16_t getAlertRegister()** to get all register bits.
  - obsoletes getAlertFlag().
- add **void setAlertLatchEnable(bool latch = false)**
- add **void setAlertPolarity(bool inverted = false)**
- add **void getAlertLatchEnable()**
- add **void getAlertPolarity()**
- update readme.md
- minor edits

## [0.1.4] - 2025-08-18
- update GitHub actions
- allow overrule INA236_MINIMAL_SHUNT on command line.
- update reference in readme.md (fix #8)
- minor edits.

## [0.1.3] - 2025-07-21
- Sync INA228, setADCRange() calls setMaxCurrentShunt();
- update readme.md
- update INA_comparison_table.md
- minor edits.

## [0.1.2] - 2025-05-06
- add **getLastError()** low level (I2C) error handling
- update readme.md

## [0.1.1] - 2025-01-30
- fix #2, cache ADCRange to improve getShuntVoltage()
- add **INA_comparison_table.md**
- align INA228/INA229
- minor edits

## [0.1.0] - 2024-05-27
- initial version ported from INA226 to INA236 by Josef Tremmel



