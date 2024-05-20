# Change Log DS3232

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.1] - 2024-05-17
- add **float getTemperature()**
- make DS3231 the base class as the DS3232 has EEPROM (logical)
- add experimental SRAM support 
  - **SRAMwrite8/16/32()** + **SRAMread8/16/32()**
- add example to test SRAM for DS3232.
- update readme.md.
- minor edits

## [0.4.0] - 2024-04-05
- fix #2, add **setWeekDay()**
- update examples
- update GitHub actions
- minor edits

----

## [0.3.0] - 2024-02-04
- initial release
- refactor code
- revitalize library and bring it to publish level
- add readme.md
- add changelog.md
- add library.json + library.properties
- add MIT licence
- add build infra
- add examples

----

eons ago

## [0.2.00] - 2013-11-11
- ?

## [0.1.00] - 2011-01-21
- initial version.
