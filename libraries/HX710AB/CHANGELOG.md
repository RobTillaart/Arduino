# Change Log HX710AB

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


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

