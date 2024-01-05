# Change Log PCA9553

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.1] - 2024-01-05
- minor edits


## [0.4.0] - 2023-12-27
- Fix #6, support for Arduino ESP32 S3 - breaking change
- update readme.md
- update examples.

----

## [0.3.0] - 2023-12-11
- refactor API, begin();
- update readme.md;
- update examples

----

## [0.2.1] - 2023-09-25
- add Wire1 support for ESP32
- update readme.md

## [0.2.0] - 2023-07-17
- refactor interface (breaking)
  - for compatibility with PCA9552, PCA9551
- add **uint8_t getAddress()**
- add **void digitalWrite(led, value)**
- add **uint8_t digitalRead(led)**
- add **reset()**
- rename setLEDSource to **setOutputMode()**
- rename channelCount to **outputCount()**
- add #defines for modi
- add some error handling
- add examples
- update readme.md
- internal refactor

----

## [0.1.0] - 2023-07-16
- initial version


