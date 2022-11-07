# Change Log FastTrig

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.11] - 2022-11-02
- add changelog.md
- add rp2040 to build-CI
- moved version info from readme.md to changelog
- no functional changes


## [0.1.10  2022-04-15
- fix #12 
- split .h in .h and .cpp Needed in case of more complex projects.

## [0.1.9] - 2021-12-18  
- update Arduino-CI, badges, 
- update library.json
- minor edits

## [0.1.8] - 2021-08-10
- made % 180 conditional in itan() => performance gain
- added icot() cotangent.

## [0.1.7] - 2021-04-23
 -fix for PlatformIO

## [0.1.6] - 2020-12-23
- Arduino-CI + unit tests

## [0.1.5] - 2020-09-11
- fixed optimize
- new table
- added iasin() and iacos()

In (0.1.4) an error was found in the optimize algorithm, so for 0.1.5 
it was ran again and accuracy improved for **isin()** and **icos()**. 
However **itan()** lost a (smaller) bit. 
The gain outweighs the loss and so new table is kept.

Performance has not changed.

An initial version of a reverse lookup for **iasin(val)** and **iacos(val)** 
is added, as it uses the same **isintable16\[\]** interpolation table.

There is no **atan()** or **atan2()** replacement.


## [0.1.4] - 2020-09-08
- rewrite itan()
- cleanup
- examples

The library (0.1.4) provides an **itan()** which improved accuracy 
upon the (0.1.3) version and performance for the ESP32.  
Performance on AVR (UNO) is still an issue, accuracy is OK.


## [0.1.3] - 2020-09-07
- initial release.

## [0.1.2] - 2020-09-06
- optimize 16 bit table with example sketch

## [0.1.1] - 2020-08-30
- refactor
- create a library out of it.
- itan() approximation is bad.


_eons passed_

----

## [0.1.02] - 2011-08-20
- added interpolation

## [0.1.01] - 2011-08-18
- improved tables a bit 
- changed param to float

## [0.1.00] - 2011-08-18
- initial version

