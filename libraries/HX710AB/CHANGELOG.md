# Change Log HX710AB

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2026-04-28
- fix #9, add timeout handling
- add **void set_timeout(uint32_t timeout)**
- add **uint32_t get_timeout()**
- add two sensor example
- minor edits

## [0.3.0] - 2026-04-03
- fix #7, **get_units(n = 1)** parameter default value
- add **get_units(n)** parameter check (>=1)
- add example HX710A_get_units.ino example
- add get_units() to performance test
- update readme.md
- fixed return type last_value_read()
- fixed keywords.txt
- update GitHub actions
- minor edits

----

## [0.2.2] - 2025-09-06
- update license
- update the GitHub actions
- fix readme.md.
- minor edits

## [0.2.1] - 2025-06-19
- fix **is_ready()** (see HX711 #65)

## [0.2.0] - 2024-11-17
- breaking change, aligned function names with HX711 where possible
- implement base class HX710AB (reduce source duplication)
- implement async interface, three functions
  - **void request()**, **bool is_ready()**, **fetch()**
- implement two point calibration **void calibrate()**
- add unit tests
- add examples
- update keywords.txt
- update readme.md

----

## [0.1.1] - 2024-11-13
- fix #2, add fastProcessor flag.
- changed **lastRead()** into **lastValueRead()**
- added **lastTimeRead()**
- update readme.md
- minor edits

## [0.1.0] - 2024-11-08
- initial version

