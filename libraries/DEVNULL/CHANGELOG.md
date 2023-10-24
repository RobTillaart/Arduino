# Change Log DEVNULL

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.6] - 2023-10-24
- update readme.md


## [0.1.5] - 2022-10-31
- add changelog.md
- add rp2040 to build-CI

## [0.1.4] - 2022-09-21
- split up .h in .cpp and .h
- add **lastByte()** to check last byte written.

## [0.1.3] - 2021-12-15
- update library.json, license, minor edits

## [0.1.2] - 2021-11-24
- update build-CI
- add badges
- sets the timeout for reading to 0. No need to wait longer with DEVNULL.
  this improves the **find(...)** calls substantially.
- added **size_t write( const uint8_t \*buffer, size_t size)** for faster string processing.

## [0.1.1] - 2020-12-18
- add Arduino-CI.


## [0.1.0] - 2020-06-23
- initial version

