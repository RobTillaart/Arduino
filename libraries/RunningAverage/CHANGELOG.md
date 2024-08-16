# Change Log runningAverage

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.7] - 2024-08-12
- Fix #33, add **float getCoefficientOfVariation()**
- update readme.md
- update keywords.txt

## [0.4.6] - 2024-06-15
- Fix #30, add **float getSum()** (thanks to heidnerd)
- Fix #31, add **float getStandardDeviationLast(uint16_t count)** (thanks to alvaro-oliver)
- added code to detect inner array == NULL in more functions (return NAN).
  - changed return type **bool clear()**
  - changed return type **bool addValue(..)**
  - changed return type **bool fillValue(..)**
  - changed return type **bool setPartial(..)**
- moved performance.txt to performance sketch
- update unit test
- update keywords.txt
- update readme.md
- minor edits.

## [0.4.5] - 2024-01-05
- fix URL in examples
- minor edits

## [0.4.4] - 2023-10-18
- update readme.md badges
- update examples
- add two step example
- minor edits

## [0.4.3] - 2022-11-23
- add changelog.md
- add RP2040 to build-CI
- add examples
- add getAverageSubset(start, count) - experimental
- update readme.md

## [0.4.2] - 2021-12-28
- update license
- minor edits

## [0.4.1] - 2021-11-22
- updated build-CI, readme, badges
- add getAverageLast() functions.

## [0.4.0] - 2021-05-18
- increase size above 256 elements (16 bit version)

----

## [0.3.2] - 2021-01-15
- add add()
- license
- refactor

## [0.3.1] - 2020-06-19
- fix library.json
- minor refactor

## [0.3.0] - 2020-04-16
- main refactor

----

## [0.2.16] - 2020-04-16
- improve \_sum - see issue #149 (bourkemcrobbo)

## [0.2.15] - 2020-01-17
- fix overflow in getValue - see issue #139

## [0.2.14] - 2020-01-15
- added getValue(n) to retrieve elements in order of addition - see issue #132

## [0.2.13] - 2017-07-26
- revert double to float - issue #33;
- refactored a bit; marked some TODO's
- all function names to camelCase

## [0.2.12] - 2016-12-01
- add GetStandardDeviation()
- add GetStandardError()
- add BufferIsFull()  (V0v1kkk)

## [0.2.11] - 2015-09-04
- add getMaxInBuffer() getMinInBuffer() request (Antoon)

## [0.2.10] - 2015-09-01
- added getFastAverage()
- refactored getAverage()
- http://forum.arduino.cc/index.php?topic=50473

## [0.2.09] - 2015-07-12
- refactor const
- refactor constructor

## [0.2.08] - 2015-04-10
- refactor getMin() and getMax() implementation

## [0.2.07] - 2015-03-16
- added getMin() and getMax() functions (Eric Mulder)

## [0.2.06] - 2015-03-07
- all size uint8_t

## [0.2.05] - 2014-12-16
- changed float -> double

## [0.2.04] - 2014-07-03
- added memory protection

## [0.2.03] - 2013-11-31
- add getElement()

## [0.2.02] - 2012-12-30
- refactored trimValue -> fillValue

## [0.2.01] - 2012-11-21
- refactored

## [0.2.00] - 2012-??-??
- Yuval Naveh added trimValue (found on web)
- http://stromputer.googlecode.com/svn-history/r74/trunk/Arduino/Libraries/RunningAverage/RunningAverage.cpp

----

## [0.1.01] - 2011-02-28
- fixed missing destructor in .h

## [0.1.00] - 2011-01-30
- initial version

