# Change Log SHT4x

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.3]
- add derived class SHT4xAutomotive, see #20
- add SHT4xAutomotive.ino example (just test code).
- add getCelsius() for completeness.
- minor edits

## [0.1.2] - 2026-07-06
- fix #18, warning in setHeatInterval()
- add derived classes SHT40, SHT41, SHT43 and SHT45 (wrappers)
- minor edits

## [0.1.1] - 2026-04-21
- merge #16,
- minor edits

## [0.1.0] - 2026-04-03
- Merge #12, modernize code + unit tests
- Merge #13, make _heatInterval consistent
- improve readme.md
- Merge #14, add example SHT4x_advanced.ino
- update GitHub actions
- minor edits

----

## [0.0.3] - 2025-09-27
- add heat interval protection
- add enum measType to replace defines
- add SHT4x_ERR_INVALID_ADDRESS
- move code to .cpp file
- checked I2C performance range
- constrain humidity between 0..100%
- merged PR #6 force float math instead of double- kudos to Chris0xdeadbeef
- optimized getDelay() usage.
- add fast parameter to reset(), default false
- update readme.md
- update keywords.txt
- minor edits

## [0.0.2] - 2025-09-23
- created https://github.com/RobTillaart/SHT4x

## [0.0.1] - 2025-08-11
- initial version,
- forked from https://github.com/RobTillaart/SHT31

