# Change Log AM232X

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.4] - 2022-10-12

- Add RP2040 support to build-CI.
- Add CHANGELOG.md

## [0.4.3] - 2022-06-17
- add get/setSuppressError()
- add AM232X_HUMIDITY_OUT_OF_RANGE
- add AM232X_TEMPERATURE_OUT_OF_RANGE
- fix return -0.0 (from AM2315 lib)
- major rewrite readme.md (sync AM2315)

## [0.4.2] - 2022-06-17  add derived classes
- added some unit tests
- fix _lastRead bug
- minor edits.

## [0.4.1] - 2022-01-28
- fix ERROR_CONNECT, minor edits
- fix #19 support Wire1 on ESP

## [0.4.0] - 2022-01-06
- add offset(), lastRead() and readDelay()
- refactor examples, 
- update readme.md

----

## [0.3.4] - 2021-12-11
- add unit test
- update library.json
- update license

## [0.3.3] - 2021-10-19
- update build-CI

## [0.3.2] - 2021-03-30
- #13 - timeout to isConnected()
- add wakeUp()
- readme.md

## [0.3.1] - 2021-01-28
- fix TODO's in code

## [0.3.0] - 2021-01-12
- add isConnected()
- add Wire0..Wire5 support

----

## [0.2.0] - 2020-05-03
-  made temperature + humidity private, 
- add wrapper functions.
## [0.2.1] - 2020-05-06
-  fix temperature function (thanks Chade)
## [0.2.2] - 2020-05-12
-  added ESP32 support
## [0.2.3] - 2020-05-27
-  update library.json
## [0.2.4] - 2020-12-09
-  Arduino-CI

----

## [0.1.5] - 2020-03-25
- refactor, 
- add read() to begin()

## [0.1.4] - 2018-10-24
- fixed temperature formula - #114
- thanks to 9a4gl

## [0.1.3] - 2017-12-19
-  added ESP8266 - issue #86
- tested by Viktor Balint

## [0.1.2] - 2017-12-12
-  get and set functions.

## [0.1.1] - 2017-12-12
-  added CRC checking

## [0.1.0] - 2017-12-11
-  initial version

