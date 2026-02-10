# Change Log BL0942_SPI

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.2] - 2026-01-28
- fix negative values getWatt(), getVWave(), getIWave().
- add **float getMaxCurrent()** **float getMaxCurrentRMS()**
- add **float getMaxVoltage()** **float getMaxVoltageRMS()**
- update calibration examples to include **getMax...()**
- add **uint32_t errorCount()** to count readRegister CRC errors. (debug).
- update readme.md
- minor edits

## [0.1.1] - 2026-01-06
- fix setUserMode() to force bit 0 and 1 to b1
- add bit masks to getters and setters to get only valid bits.
- add **resetSPI()**
- improve example output (bit masking)
- improve documentation / code comments
- added conversion formulas
- many small edits / fixes.

## [0.1.0] - 2026-01-06
- initial release

## [0.0.0] - 2025-12-29
- initial version (not functional complete!)



