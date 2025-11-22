# Change Log CHT832X

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2025-11-21
- fix #7, update readme.md about **getNIST()**
- add **CHT8320** and **CHT8325** as derived classes (convenience).
- add example CHT832X_plotter.ino
- minor edits

## [0.3.0] - 2025-10-03
- fix #5, temperature above ~40C flipped to negative
- made all floats explicit (0.0f iso 0.0)
- minor edits

----

## [0.2.0] - 2025-09-10
- fix #3, reading T&H failed (kudos to NetForces)
- implementing ASYNC interface (refactor private part)
- add example **CHT832X_asynchronous.ino**
- improve error handling
- add **int getError()**
- add CRC8 check for receiving data
- add **CHT832X_ERROR_CRC**
- add **CHT832X_READ_DELAY** as a configurable const in .h file
- add constants for the COMMANDS in .cpp (readability)
- add example CHT832X_crc8_check.ino (debug version).
- update GitHub actions
- minor edits

----

## [0.1.0] - 2024-12-29
- initial version.

