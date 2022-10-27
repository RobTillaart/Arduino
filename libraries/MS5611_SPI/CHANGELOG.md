# Change Log MS5611

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.1] - 2022-10-27
- sync with MS5611
- add RP2040 support to build-CI
- add CHANGELOG.md
- add isConnected() ==> read() should return MS5611_READ_OK
- add getManufacturer()
- add getSerialCode()
- add parameter mathMode to **reset()** to switch between pressure math.
  - see readme for details.
- minor edits.


## [0.1.0] 2022-01-18
- initial version, based upon MS5611 (15-okt-2014)