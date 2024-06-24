# Change Log rotaryDecoder

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2024-06-20
- changed **uint8_t readInitialState()** to return the read state.
- changed **bool setValue(uint8_t re, int32_t value = 0)** to return false 
if parameter re is out of range, prevent possible bug.
- changed **int32_t getValue(uint8_t re)** to return 0 
if parameter re is out of range, prevent possible bug.
- add example **rotaryDecoder_demo_RE_IO.ino**
- update readme.md, interface section.
- minor edits

## [0.3.0] - 2024-02-14
- Fix #10, add read and write for free IO pins.
- add **read1(pin)**
- add **write1(pin, value)** experimental see #10
- made **read8()** and **write8()** public for faster multi pin access
- update readme.md

----

## [0.2.1] - 2024-01-06
- Fix URL in examples
- minor edits


## [0.2.0] - 2023-11-21
- simplify begin() interface - breaking change
- update readme.md

----

## [0.1.4] - 2023-09-22
- add Wire1 support for ESP32
- moved code from .h to .cpp
- update readme.md
- minor edits

## [0.1.3] - 2022-11-23
- add changelog.md
- add RP2040 to build-CI
- fix version number .cpp
- minor edits

## [0.1.2] - 2021-12-27
- update library.json
- update readme.md
- update license
- minor edits

## [0.1.1] - 2021-11-15
- update build-CI, readme.md
- improve readability of code

## [0.1.0] - 2021-05-08
- initial version


