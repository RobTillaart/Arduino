# Change Log HX711_MP
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.4] - 2025-09-16
- fix #11, HX711 rate pin code  (HX711 - #70)
- add a doReset parameter to begin() to improve start up time.
- update readme.md 
  - add details about start up time (related to RATE).
  - add **isReady()** check in calibration
  - add reference to ADAfruit breakout with RATE
- minor edits

## [0.3.3] - 2025-09-06
- update license
- implement experimental rate support.
- update keywords.txt
- update readme.md
- update the GitHub actions
- minor edits

## [0.3.2] - 2025-06-19
- fix **is_ready()** (see HX711 #65)
- add **last_time_read()** to replace **last_read()**
- minor edits

## [0.3.1] - 2024-11-08
- fix #7, sync with HX711 0.5.1
- clean up examples a bit
- minor edits

## [0.3.0] - 2024-06-17
- fix #5, reset bug
- refactor constructor
- move code to .cpp file (to match HX711)

----

## [0.2.0] - 2024-03-02
- add fastProcessor option in **begin()** (Thanks to palmerr23)
- updated license
- updated GitHub/actions to v4

----

## [0.1.1] - 2023-11-04
- update readme.md
- minor edits

## [0.1.0] - 2023-03-10
- initial release
- first version derived from 0.3.5 https://github.com/RobTillaart/HX711
  - minimized examples.
- interface is different from HX711 library as calibration is not a scale and offset any more.
  - see discussion https://github.com/RobTillaart/HX711/issues/29
  - see readme.md


