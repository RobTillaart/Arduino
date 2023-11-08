# Change Log M5ANGLE8

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2023-11-08
- update readme.md
- simplified begin()
- add **bool writeBrightness(channel, brightness)**

----

## [0.2.0] - 2023-08-08
- tested with hardware led to major changes.
- add reverse flag
  - add example with reverse flag
- extended analog bit range from 1..12
  - add analogRead4 and analogRead10 examples
- add **selectorRead(uint8_t channel, uint8_t steps)**
  - support for selector 0..n (n typical < 50).
  - add selectorRead example
- add **setAll(uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)**
- improved performance test
  - include I2C speed
- improved other examples
- update readme.md
- minor edits

----

## [0.1.0] - 2023-08-03
- initial version
