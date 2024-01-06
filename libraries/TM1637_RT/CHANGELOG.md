# Change Log TM1637

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] - 2023-11-22
- remove init() and keyscan()
- minor edits

----

## [0.3.9] - 2023-11-22
- update readme.md
  - section about hardware performance (Kudos to SteveMicroCode #29)
  - badges to platformIO + issues
  - improve related section
- update keywords.txt
- **keyScan()** replaces keyscan() => prefer camelCase (prep 0.4.0)
  - patched examples.
- minor edits

## [0.3.8] - 2023-07-15
- fix #27
- replaced function data\[8] with a class level data\[8].
- add **hideSegment(uint8_t n)** hide a single segment
- add **hideMultiSegment(uint8_t mask)** hide multiple segments
- add **displayFahrenheit()** -9..99F
- add **displayRefresh()** to refresh last written data.
- update keywords.txt
- fix bug in **displayRaw()** (add bool hasPoint).
- update readme.md

## [0.3.7] - 2023-04-17
- move code from .h to .cpp
- add **displayTwoInt(int ll, int rr, bool colon = true)**
- add **displayCelsius(int temp, bool colon = false)**
- add '°' degree character (18)
- add examples
- update readme.md

## [0.3.6] - 2023-02-27
- add **void displayTime(uint8_t hh, uint8_t mm, bool colon)**
- add examples
- update readme.md
- update keywords.txt

## [0.3.5] - 2023-02-18
- add **void displayFloat(float value, byte fixpoint)** Thanks to marshalab
- add example TM1637_float_point.ino
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.3.4] - 2022-10-07
- added CHANGELOG.md
- added **void displayPChar(char \* data)** thanks to radionerd
- added **uint8_t asciiTo7Segment (char c)** thanks to radionerd
- updated documentation

## [0.3.3] - 2022-09-24
- added CHANGELOG.md
- added **begin()** to replace **init()** in due time.
- updated documentation

## [0.3.2] - 2022-04-16
- fix #15 support for 4 digits.
- tested on 4 digit (clock) display.

## [0.3.1] - 2021-12-29
- update library.json
- update license
- update readme.md
- minor edits
- tested on 6 digits display (with decinal point).

## [0.3.0] - 2021-10-27
- improved keyscan - kudos to wfdudley
- update documentation

----

## [0.2.1] - 2021-10-07
- add support for letters g-z; added keyscan()
- tested on ESP8266

## [0.2.0] - 2021-09-26
- add ESP32 support - kudos to alexthomazo

----

## [0.1.2] - 2021-04-16
- update readme
- fix default values

## [0.1.1] - 2021-02-15
- first release
- added examples

## [0.1.0] - 2019-10-28
- initial version

