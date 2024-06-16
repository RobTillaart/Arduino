# Change Log M5ROTATE8

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] 2024-06-15
- add **uint32_t readRGB(uint8_t channel)**
- add firmware V2 functions
  - **void setButtonToggleCount(uint8_t channel, uint8_t value = 0)**
  - **uint8_t getButtonToggleCount(uint8_t channel)**
  - **uint8_t getButtonRegister()**
  - **uint8_t getEncoderChangeFlag()**
- improved **setAddress()**
- add examples
- update readme.md
- minor edits

----

## [0.3.0] 2023-12-05
- refactor API
- update readme 
- update examples

----

## [0.2.1] 2023-09-23
- add Wire1 support for ESP32
- update readme.md
- update keywords.txt

## [0.2.0] 2023-08-08
- testing with hardware led to a major upgrade
- fix keyPressed
- fix read32
- add setAbsCounter example.
- update examples
- fix **writeRGB(8...)**
- add **setAll(R,G,B)**
- update readme.md
- minor edits

----

## [0.1.0] - 2023-08-03
- initial version
