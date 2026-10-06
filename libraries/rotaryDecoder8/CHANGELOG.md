# Change Log rotaryDecoder8

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.5] - 2026-10-02
- fix #9, support for setting rotation direction
- add bool setDirection(uint8_t re, uint8_t dir = 0)
- add uint8_t getDirection(uint8_t re)
- add section about pull up resistors.
- fix frameworks in library.json
- minor edits

## [0.1.4] - 2026-09-16
- fix #7,
- add getClicks(), setClicks()
- add setStepsPerClick(), getStepsPerClick()
- add example rotaryDecoder8_getClicks.ino
- update readme.md
- improve rotaryDecoder_demo_interrupt.ino
- fix internal state after reset()
- add reset(re) to reset a single rotary encoder.
- reduce build-CI platforms.
- minor edits

## [0.1.3] - 2026-01-22
- fix #5, update example interrupt
- update examples
- update readme.md
- minor edits

## [0.1.2] - 2026-01-08
- update GitHub actions
- minor edits

## [0.1.1] - 2025-01-08
- fix library.properties

## [0.1.0] - 2025-01-06
- initial version, based upon rotaryDecoder 0.4.0
  - kudos to e11aprope11a for testing!


