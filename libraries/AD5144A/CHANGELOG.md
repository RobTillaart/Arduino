# Change Log AD5144A
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2024-01-25
- update readme.md (multiplexer)


## [0.3.0] - 2023-11-24.
- simplify **begin()**, remove setting Wire pins from library.
- add **getAddress()**
- update readme.md

----

## [0.2.1] - 2023-01-11
- add support for Wire1 for ESP32
- update readme.md
- minor edits

## [0.2.0] - 2023-01-11
- update GitHub actions
- update license
- removed mid() ==> use midScale() instead
- moved code from .h to .cpp

----

## [0.1.9] - 2022-12-02
- fix #21
- update readme.md + comments
- add read back cache in reset()
- move part of code to .cpp file (prep 0.2.0)
- update keywords.txt
- minor refactor

## [0.1.8] - 2022-10-25
- add rp2040 to build
- redo comments
- clean up examples

## [0.1.7] - 2022-06-21
- fix ESP32 Wire.begin datatype

## [0.1.6] - 2022-04-25
- extra comments on **sync()**
- fixed issue #14, preloading values should not change cached values

## [0.1.5] - 2022-03-14
- CHANGELOG.md: moved history from AD5144A.cpp to this file.
- fix #12 always call reset in begin().
- add flag to **begin(bool doReset = true)** to explicitly disable the reset
call. The default is true ==> backwards compatibility / normal use.
- updated readme.md

## [0.1.4] - 2021-12-10
- add check for maxValue in code.
- remove experimental from version string.
- add headers to library.json,
- minor edits readme, license,

## [0.1.3] - 2021-10-17
- update build-ci
- improve readme.md

## [0.1.2] - 2021-05-12
- add increment()
- add decrement()

## [0.1.1] - 2021-05-12
- add topScale()
- add bottomScale()

## [0.1.0] - 2021-04-30
- initial version


