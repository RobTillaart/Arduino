# Change Log DHTStable

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [1.1.2] - 2023-10-25
- update readme.md
- add changelog.md


## [1.1.1] - 2021-12-16
- update library.json
- update license
- minor edits

## [1.1.0] - 2021-11-06
- fix DHTNew-#67 negative temperature

## [1.0.1] - 2021-06-01
- change architecture to fix incompatible flag.

## [1.0.0] - 2021-05-26
- rename files and class to DHTStable to fix incompatible flag.
- changed temperature and humidity to private
- breaking change!

----

## [0.2.9] - 2021-02-27
- fix URL in library.json

## [0.2.8]   2021-02-01
- fix negative temperature (from DHTStablenew)

## [0.2.7]   2020-12-20
- add Arduino-CI, unit test,
- reset(), getTemperature(), getHumidity()

## [0.2.6]   2020-07-20
- update URL in .cpp

## [0.2.5]   2020-06-30
- move to own repository; update headers mainly.

## [0.2.4]   2018-04-03
- add get-/setDisableIRQ(bool b)

## [0.2.3]   2018-02-21
- change #defines in const int to enforce return types.
  https://github.com/RobTillaart/Arduino/issues/94

## [0.2.2]   2017-12-12
- add support for AM23XX types more explicitly

## [0.2.1]   2017-09-20
- fix https://github.com/RobTillaart/Arduino/issues/80

## [0.2.0]   2017-07-24
- fix https://github.com/RobTillaart/Arduino/issues/31 + 33

----

## older

//  0.1.13  fix negative temperature
//  0.1.12  support DHT33 and DHT44 initial version
//  0.1.11  renamed DHTLIB_TIMEOUT
//  0.1.10  optimized faster WAKEUP + TIMEOUT
//  0.1.09  optimize size: timeout check + use of mask
//  0.1.08  added formula for timeout based upon clock speed
//  0.1.07  added support for DHT21
//  0.1.06  minimize footprint (2012-12-27)
//  0.1.05  fixed negative temperature bug (thanks to Roseman)
//  0.1.04  improved readability of code using DHTLIB_OK in code
//  0.1.03  added error values for temp and humidity when read failed
//  0.1.02  added error codes
//  0.1.01  added support for Arduino 1.0, fixed typos (31/12/2011)
//  0.1.0   by Rob Tillaart (01/04/2011)
//
// inspired by DHT11 library

