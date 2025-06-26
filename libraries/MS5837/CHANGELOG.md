# Change Log MS5837

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.0] - 2025-06-13
- fix #4, read() error after test with hardware
- change API to **int read()** for better debugability
- improve demo sketch - add getLastError()
- redo getAltitude() formula 
- add sketch MS5837_performance.ino
- redo 2nd order compensation
- improve error handling
- add getCRC(), getProduct(), getFactorySettings(), getPromZero()
- add sketch MS5837_demo_meta_data.ino
- update readme.md
- update keywords
- minor edits

----

## [0.1.1] - 2025-04-07
- update GitHub actions
- update readme.md
- add **int lastError()** to prepare error handling
- add **uint32_t lastRead()**
- add derived class **MS5803** to be able to set address.
- minor edits

## [0.1.0] - 2023-12-24
- initial release

## [0.0.0] - 2023-11-12
- initial version



