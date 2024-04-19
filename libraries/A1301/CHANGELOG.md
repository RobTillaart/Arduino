# Change Log A1301

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.3] - 2024-04-19
- update GitHub actions
- experimental PlatformIO build-CI
- add PlatformIO build badge in readme.md
- add Commits since last release badge in readme.md
- experimental Teensy build (no success yet)
- minor edits in examples.


## [0.2.2] - 2024-01-01
- add **float autoMidPoint(times)**
- add examples 
- update readme.md

## [0.2.1] - 2023-09-19
- add **bool isRising()** and **bool isFalling()**
- add **float deltaGauss()**
- add **float determineNoise(uint8_t times = 2)**
- add **angle()** experimental.
- add / update examples.
- replaced internal mVGauss by GaussmV to improve math performance.
- update readme.md

## [0.2.0] - 2023-04-24
- add **isNull()** is no magnetic field is detected.
- add **saturationLevel()** returns 0..100%
- update examples (plotter + test)
- fix midPoint in **begin()**
- fix constructor **maxGauss**
- update readme.md
- update unit test
- update keywords.txt
- minor edits

----

## [0.1.2] - 2023-03-01
- update GitHub actions
- update license
- minor edits

## [0.1.1] - 2022-12-02
- update keywords.txt
- boolean => bool
- add **isSaturated()**
- update readme.md
- add A1324/A1325/A1326 derived classes.
- update unit test

## [0.1.0] - 2022-12-01
- initial version
- rewrite whole class.

----

## [0.0.1] - 2010-07-22
- first light (not released)
