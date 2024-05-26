# Change Log Histogram

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.7] - 2024-05-25
- add examples **hist_pointer.ino** and **hist_array.ino**
- issue #10 spin off library https://github.com/RobTillaart/Kurtosis
- minor edits

## [0.3.6] - 2024-01-03
- add **float saturation()**
- fix examples
- minor edits

## [0.3.5] - 2023-11-04
- update readme.md
- minor fix in changelog.md
- update keywords.txt

## [0.3.4] - 2023-06-30
- change return type **uint8_t clear()**, return status bucket
- change return type **uint8_t setBucket(value)**, return status bucket
- change return type **uint8_t add(value)**, return status bucket
- change return type **uint8_t sub(value)**, return status bucket
- add **uint8_t status()** last known status.
- add **int32_t sum()**, adds up all buckets.
- made **setBucket()** virtual.
- update / clean up readme.md
- minor improvements derived classes - still experimental

## [0.3.3] - 2023-02-21
- optimize loops
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.3.2] - 2022-11-09
- add changelog.md
- add rp2040 to build-CI
- update readme.md
- clean-up code
- update documentation

## [0.3.1] - 2021-12-19
- update library.json
- update license,
- minor edits

## [0.3.0] - 2021-11-02
- update build-CI
- add badges
- refactor readability
- add parameter for clear(value = 0)
- add findMin(), findMax()
- add countAbove(), countLevel(), countBelow().
- add setBucket(),
- change length to uint16_t ==> 65534

----

## [0.2.1] - 2020-12-24
- add Arduino-CI + unit tests

## [0.2.0] - 2020-06-12
- #pragma once
- removed pre 1.0 support

----

## [0.1.6] - 2017-07-27
- revert double to float (issue #33)

## [0.1.5] - 2017-07-16
- refactor
- support for > 256 buckets
- prevent alloc() errors

## [0.1.4] - 2015-03-06
- stricter interface

## [0.1.3] - 2013-09-29
- testing a lot
- refactoring

## [0.1.2] - 2012-12-23
- changed float to double
- some comments

## [0.1.1] - 2012-11-10
- added PMF() and CDF()

## [0.1.0] - 2012-11-10
- initial version

