# Change Log LTR390

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [0.2.0] - 2026-04-08

### Added
- add `[[nodiscard]]` to critical getters to enforce return value usage.

### Changed
- refactor register definitions using namespaces and `constexpr`.
- introduce `LTR390RT` root namespace for all register and bit field definitions.
- remove internal cached state (`_gain`, `_rate`, `_resolution`) and rely on register reads.
- improve readability and maintainability by replacing magic numbers with named constants.
- explicit float literals to avoid implicit conversions.

### Fixed
- fix incorrect bit masking in `setRate()` that could overwrite resolution bits.
- fix incorrect bit mask handling in `setGain()`.
- fix type error in `getUVIndex()` causing precision loss.
- fix URL to https://github.com/RobTillaart/LTR390_RT

### Breaking Changes
- remove internal cached state. All configuration getters now read directly from hardware registers.
- register and constant definitions are now under the `LTR390RT` namespace.

----

## [0.1.4] - 2026-03-31
- fix #4, add specific status functions.
  - **bool getPowerOnStatus()**
  - **bool getInterruptStatus()**
  - **bool getDataStatus()**
- update readme.md
- update GitHub actions
- minor edits

## [0.1.3] - 2025-10-13
- update GitHub actions
- minor edits

## [0.1.2] - 2024-11-26
- add **float getLUX()**
- add **float getUVIndex()**
- add **float getIntegrationTime()**
- add **float getMeasurementTime()**
- add **uint8_t getGainFactor()**
- update readme.md, tables.

## [0.1.1] - 2024-05-09
- fix URL's

## [0.1.0] - 2024-04-29
- initial version



