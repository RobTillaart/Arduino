# Change Log HX711
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.4]
- simplified changelog
- add RP2040 to build-CI
- refactored **set_gain()** to return bool to confirm valid parameter.
- add forced flag for set_gain to force a dummy read call. Default false.
- add constants for **set_gain()**
- improved unit test for **set_gain()**
- add unit test for constants.
- add delayMicroseconds(64) to power_down to enforce long enough HIGH signal.
- add power_down() power_up() cycle in **reset()**
- updated readme.md
- updated keywords.txt


## [0.3.3] - 2022-03-16
- add HX711_RAW_MODE
- update documentation

## [0.3.2] - 2022-03-16
- add example HX_set_persistent.ino. (won't work for m4)
- add CHANGELOG.md
- minor edits

## [0.3.1] - 2021-12-19
- update library.json
- license
- minor edits

## [0.3.0] - 2021-11-14
- update build-CI
- readme.md incl. badges
- fix #11 shiftIn timing

----

## [0.2.3] - 2021-05-26
- add running_average() mode

## [0.2.2] - 2021-05-10
- add read_median()
- add mode operandi
- fix typo

## [0.2.1] - 2020-12-28
- add arduino-ci
- unit test

## [0.2.0] - 2020-06-15
- add price functions
- some refactor

----

## [0.1.1] - 2019-09-09
- change long to float (reduce footprint)

## [0.1.0] - 2019-09-04
- initial version
