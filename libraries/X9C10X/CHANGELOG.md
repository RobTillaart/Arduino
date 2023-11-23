# Change Log X9C10X

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.3] - 2023-11-23
- update readme.md


## [0.2.2] - 2022-11-27
- Add RP2040 support to build-CI.
- Add CHANGELOG.md
- update readme.md
- move getPosition() to .cpp

## [0.2.1] - 2022-07-23
- fix #9 add restoreInternalPosition(pos)
- change return type setPosition() to indicate truncation
- update readme.md and comments
- update build-CI tests

## [0.2.0  2022-07-09
- fix #7 incorrect signal during initialize
- remove position parameter from begin() to make setting position more explicit.
- update readme.md
- add uint8_t Ohm2Position()

----

## [0.1.3] - 2022-02-22
- add forced parameter to setPosition()
- update incr() and decr() return bool (made a step)

## [0.1.2] - 2022-02-16
- improve performance
- add sweeper example
- rounding in getOhm(), documentation

## [0.1.1] - 2022-02-15
- improve conditional delay

## [0.1.0] - 2022-01-26
- initial version

