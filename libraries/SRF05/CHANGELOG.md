# Change Log SRF05

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-02-08
- add support for single pin operation (echo == trigger) Kudos to RobertPHeller!
- add **float getYards()** wrapper.
- add **void setSampleInterval(uint16_t microSeconds = 1000)** (for average & median)
- add **uint16_t getSampleInterval()**
- reduced pulseIn timeout to 200000 (30+ meter)
- minor edits.

----

## [0.2.0] - 2024-01-28
- add **float calculateSpeedOfSound(float temperature, float humidity)**
- redo lookup table SOS temperature humidity
- redo **float determineSpeedOfSound(float distance, uint8_t count = 64)**
- removed the **Out** pin as it is non functional yet.
- update readme.md
- update examples

----

## [0.1.5] - 2023-11-22
- update readme.md

## [0.1.4] - 2023-03-15
- add **uint32_t lastTime()**
- changed return type **bool setCorrectionFactor()**
- add experimental **get- setTriggerLength()**
- redo **determineSpeedOfSound()**
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.1.3] - 2022-11-25
- Add RP2040 support to build-CI.
- Add CHANGELOG.md
- update readme.md
- update **determineSpeedOfSound()** with default parameter = 1 meter
- add mode constants
- update unit test
- move code from .h to .cpp

## [0.1.2] - 2021-12-28
- update library.json
- update license
- minor edits

## [0.1.1] - 2021-11-18
- update build-CI
- update readme.md
- minor edits

## [0.1.0] - 2021-05-17
- initial version

