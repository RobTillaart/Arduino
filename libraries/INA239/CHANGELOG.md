# Change Log INA239

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] - 2026-09-26
- fix #13, incorrect getBusVoltage() result.
- fix shift getTemperature()
- add direct register access, readRegister() + writeRegister()
- add f suffix for float constants
- add void setBusVoltageLSB(float lsb)
- add float getBusVoltageLSB()
- add void setVoltageRatio(float ratio)
- add float getVoltageRatio()
- add INA239_voltage_divider.ino example
- update readme.md
- add output examples (test run)
- fix frameworks in library.json
- minor edits

----

## [0.3.1] - 2026-01-12
- update GitHub actions
- minor edits

## [0.3.0] - 2025-10-19
- fix #10, setSPISpeed()
- update GitHub actions
- minor edits

----

## [0.2.1] - 2025-07-22
- sync INA228, setADCRange() calls setMaxCurrentShunt();
- update readme.md
- update INA_comparison_table.md
- minor edits.

## [0.2.0] - 2025-02-15
- fix bug, Unable to set parameters in Software SPI (sync INA229, #5)

----

## [0.1.1] - 2025-01-30
- fix #4, cache ADCrange to improve **getShuntVoltage()**
- add INA_comparison_table.md
- minor edits


## [0.1.0] - 2024-12-05
- initial version, based upon INA228 stripped



