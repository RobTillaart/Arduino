# Change Log INA229

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.6.0] - 2025-10-19
- fix #15, setSPISpeed()
- minor edits

----

## [0.5.0] - 2025-08-20
- Fix getKiloWattHOur() - from INA228
- update GitHub actions

----

## [0.4.1] - 2025-07-18
- Sync INA228, setADCRange() calls setMaxCurrentShunt();
- update readme.md
- update INA_comparison_table.md
- minor edits.

## [0.4.0] - 2025-03-08
- redo #8, INA.getEnergy => keep it UNsigned. Broken in 0.3.0
- update keywords.txt

----

## [0.3.0] - 2025-03-05
- fix #8,INA.getCharge => make it signed.

----

## [0.2.0] - 2025-02-15
- fix #5, Unable to set parameters, kudos to FoxRunningFromCode

----

## [0.1.1] - 2025-01-30
- fix #3, support for **int32 getShuntVoltageRAW()**
- cache ADCrange to improve **getShuntVoltage()**
- minor edits

## [0.1.0] - 2025-01-22
- initial version,
  - based upon INA228 (API) + INA239 (SPI)

