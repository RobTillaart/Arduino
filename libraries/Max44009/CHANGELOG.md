# Change Log MAX44009

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.6.1] - 2024-05-17
- add **getCurrentDivisorRatio()**
- add **getAddress()** convenience
- add **max44009_performance.ino**.
- add **max44009_test_manual_mode.ino**.
- update readme.md
- update keywords.txt
- minor edits.

## [0.6.0] - 2023-10-02
- refactor constructor around I2C interface (simpler)
- remove **configure()**
- update readme.md
- update examples

----

## [0.5.3] - 2022-11-16
- add RP2040 in build-CI
- add changelog.md
- minor edit readme.md

## [0.5.2] - 2022-01-05
- minor edits after creating Max44007 library

## [0.5.1] - 2021-12-21
- update library.json
- update license
- minor edits

## [0.5.0] - 2021-06-04
- fix exponent math.

----

## [0.4.4] - 2021-05-27
- add Arduino-lint

## [0.4.3] - 2020-12-30
- Arduino-CI, unit test

## [0.4.2] - 2020-06-19
- fix library.json

## [0.4.1] - 2020-03-21
- add #pragma
- update readme.md
- license.md

## [0.4.0] - 2020-01-30
- remove automatic mode from constructors;
- added example code

----

## [0.3.3] - 2020-01-27
- fix #140 refactor constructors / configure

## [0.3.2] - 2020-01-21
- solve #132 cannot read full range in manual mode.
- set automatic mode explicitly in constructors;
- added some error checks

## [0.3.1] - 2020-01-21
- fix #133 overflow of the exponent.

## [0.3.0] - 2020-01-20
- fix #141 Kudos to Moritz89

## [0.2.0] - 2019-08-23
- solve #127 == redo #118

----

## [0.1.10] - 2018-12-08
- issue #118 Fix constructor esp8266 (thanks to Bolukan)

## [0.1.9] - 2018-07-01
- issue #108 Fix shift math (thanks Roland vandecook)

## [0.1.8] - 2018-05-13
- issue #105 Fix read register (thanks morxGrillmeister)

## [0.1.7] - 2018-04-02
- issue #98 extend constructor for ESP8266

## [0.1.6] - 2017-07-26
- revert double to float 

## [0.1.5]
- update history

## [0.1.4]
- added setAutomaticMode() to max44009.h (thanks debsahu)

## [0.1.03] 
- added configuration

## [0.1.02]
- added threshold code

## [0.1.01]
- added interrupt code

## [0.1.00] - 2010-??-??
- initial version.

