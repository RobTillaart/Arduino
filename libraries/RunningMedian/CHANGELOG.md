# Change Log RunningMedian

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.9] - 2023-11-21
- update readme.md


## [0.3.8] - 2023-07-11
- add **getMedianAverage(nMedians)**  removing bias - #22
  - thanks to Peter Kowald
- add example **RunningMedian_getMedianAverage.ino**
- extended performance test
- update readme.md

## [0.3.7] - 2022-10-28
- Add RP2040 support to build-CI.
- Add CHANGELOG.md
- optimized binary insertion sort - see issue #20 (idea thanks to acicuc)
- add performance test sketch (to test sort efficiency)
- add setSearchMode() for selecting fastest median search mode.  
  EXPERIMENTAL, select between LINEAR or BINARY search.  

## [0.3.6} - 2022-06-06
- bump version for platformio

## [0.3.5} - 2022-06-05
- configuration options, 
- fixed static version not working

## [0.3.4} - 2021-12-28
- update library.json, 
- update readme.md, 
- license, minor edits

## [0.3.3} - 2021-01-22  
- better insertionSort (+ clean up test code)

## [0.3.2} - 2021-01-21  
- replaced bubbleSort by insertionSort
  better performance for large arrays.

## [0.3.1} - 2021-01-16
- Changed size parameter to 255 max

## [0.3.0} - 2021-01-04
- malloc() memory as default storage

----

## [0.2.2] - 2021-01-03
- add Arduino-CI + unit tests

## [0.2.1] - 2020-06-19
- fix library.json

## [0.2.0] - 2020-04-16
- refactor.

----

## [0.1.15] - 2018-08-24
- make runningMedian Configurable #110

## [0.1.14] - 2017-07-26
- revert double to float - issue #33

## [0.1.13] - 2015-10-30
- fix getElement(n) - kudos to Gdunge

## [0.1.12] - 2015-07-12
- refactor constructor + const

## [0.1.11] - 2015-03-29
- undo 0.1.10 fix clear

## [0.1.10] - 2015-03-07
- fix clear

## [0.1.09] - 2014-11-25
- float to double (support ARM)

## [0.1.08] - 2013-10-20
- add getElement(), 
- add getSottedElement() 
- add predict()

## [0.1.07] - 2013-10-19
- add correct median if \_count is even.

## [0.1.06] - 2013-10-19
- faster sort, 
- dynamic arrays, 
- replaced sorted float array with indirection array

## [0.1.05] - 2013-10-18
- fixed bug in sort; 
- removes default constructor; 
- dynamic memory

## [0.1.04] - 2013-10-17
- added getAverage(uint8_t) - kudo's to Sembazuru

## [0.1.03] - 2013-09-30
- added \_sorted flag, 
- minor refactor

## [0.1.02] - 2012-03-15  
- added ??

## [0.1.01] - 2011-02-22
- added remarks from CodingBadly

## [0.1.00] - 2011-02-16
- initial version

