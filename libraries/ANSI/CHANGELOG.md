# Change Log ANSI

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.2] - 2024-04-06
- update GitHub actions
- minor edits


## [0.3.1] - 2023-11-13
- added experimental functions (to get feedback)
  - if these work depends on terminal (app) used.
  - feedback welcome.
- updated readme.md with above functions
- add initial version of **supportMatrix.md**
- updated keywords.txt

## [0.3.0] - 2023-11-09
- fix missing 0 in normal (#19, Kudos to d0m1n1qu3)
- fix basic escape strings write length (normal, bold etc  eating one char).
- add **getScreenSize()** (#16, Kudos to chlordk)
- add **readCursorPosition()** (#16, Kudos to chlordk)
- add example, (#16, Kudos to chlordk)
- add **screenWidth()** call getScreenSize() before use
- add **screenHeight()** call getScreenSize() before use
- refactor **deviceType()** size.
- add **blinkFast()**
- update readme.md
- update keywords.txt

----

## [0.2.1] - 2023-10-17
- update readme.md (badges)
- fix version in ansi.cpp
- add a derived VT100 class (wrapper for now).
- minor edits

## [0.2.0] - 2023-02-26
- fix #13 gotoXY(column, row)
- add ansi_gotoXY example.
- update all examples with new gotoXY
- improve performance - replace print() => write()
- move all (non experimental) code from .h to .cpp
- update readme.md
- minor edits

----

## [0.1.8] - 2023-01-31
- update readme.md
- update GitHub actions
- update license 2023
- minor edit unit test
- add example ansi_clock.ino
- add example ansi_132_columns.ino
- minor edits

## [0.1.7] - 2022-10-28
- add RP2040 to build-CI
- minor edits
- start simplifying changelog
- minor change unit test

## [0.1.6] - 2022-04-11
- add CHANGELOG.md
- add **int deviceType()** 
- edit README.md

## [0.1.5] - 2021-12-13
- add write(array, length)
- update library.json, license, minor edits

## [0.1.4] - 2021-10-18
- update build-CI (e.g. ESP32)
- update examples

## [0.1.3] - 2020-12-11
- add Arduino-CI
- add unit test (minimal)

## [0.1.2] - 2020-07-08
- add clearLine 
= add color support (thanks to airbornemint)

## [0.1.1] - 2020-05-27
- update library.json

## [0.1.0] - 2020-04-28
- initial release
  Based upon my VT100 library (from 2013) which is now obsolete.
  This vt100 lib had just a list of escape sequences #defined. 


