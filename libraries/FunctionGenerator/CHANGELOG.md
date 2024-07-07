# Change Log functionGenerator

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-07-05
- add **float sinusDiode(float t)**
- add **float sinusRectified(float t)**
- add **float trapezium1(float t)** with duty cycle.
- add **float trapezium2(float t)** with duty cycle.
- add **float heartBeat(float t)**
- add **float freeWave(float t, int16_t arr, int size)** arbitrary wave generator.
- update **functionGeneratorPerformance.ino**
- add examples for **freeWave()**
- fix Arduino-lint.yml (long library name error)
- update readme.md
- minor edits

----

## [0.2.6] - 2023-11-02
- update readme.md
- update keywords.txt (align)

## [0.2.5] - 2023-03-25
- add **setDutyCycle()**, **getDutyCycle()**
- implement duty cycle for square(), triangle() and random()
- add **seedRandom(a, b)**
- add some optimizations
- move code from .h to .cpp
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.2.4] - 2022-11-07
- add changelog.md
- add rp2040 to build-CI
- update readme.md

## [0.2.3] - 2021-12-18
- update library.json, license, minor edits

## [0.2.2] - 2021-11-02
- update Arduino-CI, badges
- add mode for sawtooth and stair.

## [0.2.0] - 2020-06-10
- main refactoring and cleanup

## [0.2.1] - 2020-12-24
- add Arduino-CI + unit tests

----

## [0.1.5] - 2017-07-29
- Fix issue #33 (dbl -> float)

## [0.1.04] - 2015-01-03
- add integer versions - to be used with 8 bit DAC

## [0.1.03] - 2015-01-02
- add stair
- more refactoring

## [0.1.02] - 2015-01-01
- refactor and research

## [0.1.01] - 2015-01-01
- initial class version

## [0.1.00] - 2015-01-01
- initial version


