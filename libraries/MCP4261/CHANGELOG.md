# Change Log MCP4261

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.0] - 2024-07-09
- refactor 0.1.0 implementation
  - use less magic numbers
  - reimplement protected functions
- remove parameter from **begin()** reads value from device. (breaking)
- fix the supported range to 0..256 (was 255).
- add **uint16_t getValueDevice(uint8_t pm)**
- add **uint16_t getValueNV(uint8_t pm)**
- add **void setTCONMask(uint16_t mask)**
- add **uint16_t getTCONMask()**
- add **uint16_t getStatusMask()**
- add **bool setEEPROM(uint8_t index, uint16_t value)**
- add **uint16_t getEEPROM(uint8_t index)**
- update readme.md
- minor edits.


## [0.1.0] - 2024-02-21
- initial version
