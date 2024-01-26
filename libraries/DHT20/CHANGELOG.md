# Change Log DHT20

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2024-01-26
- update readme.md
- update examples


## [0.3.0] - 2023-10-25
- simplify begin()
- updated all examples
- update readme.md

----

## [0.2.3] - 2023-07-27
- fix #12 add time out to read function

## [0.2.2] - 2022-12-21
- update keywords.txt
- add defaults to offset functions.
- update readme.md
- update GitHub actions
- update license 2023

## [0.2.1] - 2022-12-21
- first part of the **readStatus()** not part of the protocol 
  - different interpretation of datasheet page 10 section 7.4
  - the state is sent after a read command as first byte
  - see https://github.com/RobTillaart/DHT20/issues/8 + page 11 datasheet
- add **getAddress()** convenience function.

## [0.2.0] - 2022-10-30
- add changelog.md
- add rp2040 to build-CI
- add workaround for #8 to readme.md
- fix requestFrom() ambiguity
- fix #8 - embed **resetSensor()** into **read()**.
  This makes reads slightly slower.
- update readme.md

----

## [0.1.4] - 2022-09-18
- add resetSensor() code.
- add comments in .h file
- add examples
- stabilize readStatus()
- update readme.md

## [0.1.3] - 2022-09-17
- add wrapper status functions
- improve performance read()
- refactor, update readme.md

## [0.1.2] - 2022-09-16
- fix #4 DHT20_ERROR_BYTES_ALL_ZERO error condition.
- fix keywords
- add readStatus()  fix _readStatus()
- add setWireTimeout(250000, true);  //  in comments

## [0.1.1] - 2022-09-10
- add hardware schema to readme.md.
- fix async interface (first version)

## [0.1.0] - 2022-01-11
- initial version (based upon DHT20 datasheet)

