# Change Log LTR390_DFR

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [0.2.0] - 2026-04-01

### Added
- [[nodiscard]] attribute to critical methods to prevent ignored return values

### Changed
- Replaced register macros with constexpr inside LTR390Reg namespace
- Modernized constructor using member initializer list
- Improved type safety (explicit casts, consistent types)
- Simplified gain handling using lookup table
- Constructor rewritten using initializer list
- Improved type safety and consistency across the codebase

### Fixed
- Fixed potential overflow when assembling 32-bit ALS/UVS data from 16-bit registers

## [0.2.0] - 2026-04-02
- merged #6,#8,#10 major refactor, kudos to Chris0xdeadbeef
- add **void enable()**, **void disable()**, **bool isEnabled()**
- add **int lastError()** to read last I2C low level error (experimental)
- update readme.md
- update keywords.txt
- update examples
- minor edits

----

## [0.1.3] - 2026-03-31
- update GitHub actions
- minor edits

## [0.1.2] - 2025-10-14
- update GitHub actions
- update examples
- minor edits

## [0.1.1] - 2024-09-23
- extend functionality and documentation
- add return value in **setGain()** 0..4
- add param check in **bool setMeasurement(resolution,time)**
- refactored code for readability (e.g. magic numbers).
- add **bool setUVsensitivity(float s)** and **float getUVsensitivity()()**
- update keywords.txt (prepare)

## [0.1.0] - 2024-04-29
- initial version



