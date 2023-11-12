# Change Log Temperature

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.7] - 2023-11-12
- update readme.md
- renamed TEMPERATURE_VERSION => TEMPERATURE_LIB_VERSION
- updated examples to show LIB version
- update keywords.txt
- minor edits


## [0.3.6] - 2023-02-17
- add **absoluteHumidity(TC, RH)** from relative humidity
- add **boilingFahrenheit(feet)** boiling temperature Fahrenheit at height in feet.
- add **boilingCelsius(meter)** boiling temperature Celsius at height in meter.
- add **boilingMeter(Celsius)** inverse function of above.
- add example
- update keywords.txt
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.3.5] - 2022-11-26
- added RP2040 to build-CI
- simplified changelog
- optimized Steadman's formula (HeatIndex).
- update readme.md

## [0.3.4] - 2022-04-15
- fix #16 Split .h in .h and .cpp 

## [0.3.3] - 2022-01-09
- added working limits to windChill() and heatIndex()

## [0.3.2] - 2022-01-08
- added a TempConvertor class for more exotic scales.
- added baroToSeaLevel() - kudos to RobertDB59
- Renamed Celcius to Celsius.

## [0.3.1] - 2022-01-07
- fix adjustments which were incorrectly added.

## [0.3.0] - 2022-01-05
- fix #10 update HeatIndex function
 compared with https://www.calculator.net/heat-index-calculator.html

----

## [0.2.5] - 2021-12-28
- Arduino-CI, library.json, readme.md, license, minor edits

## [0.2.4] - 2021-01-08
- Arduino-CI + unit tests

## [0.2.3] - 2020-08-27
- fix #5 order of functions, typo, fixed 1 example

## [0.2.2] - 2020-06-19
- fix library.json

## [0.2.1] - 2020-05-26
- added wind-chill formulas

## [0.2.0] - 2020-04-04
- #pragma once, removed WProgram.h, readme.md, comments
- replaced obsolete links with new ones,
- tested and removed some code

----

## [0.1.1] - 2017-07-26
- double to float (issue #33)

## [0.1.0] - 2015-03-29
-  initial version


