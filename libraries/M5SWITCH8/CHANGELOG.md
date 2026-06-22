# Change Log M5SWITCH8

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.2] - 2026-06-19
- add **M5BUTTON8.h** file wrapper. (now for real)
- replaced magic register nr's with named constants.
- minor edits

## [0.1.1] - 2026-06-18
- add **void setColor(uint8_t led, uint8_t R, uint8_t G, uint8_t B)**
- add **void setColor233(uint8_t led, uint8_t value)**
- add **uint8_t getColor233(uint8_t led)**
- change **readSwitch(uint8_t sw)** out of range ==> return 255
- add **M5BUTTON8.h** file wrapper.
- M5BUTTON8 class only
  - add **uint8_t readButton(uint8_t button)** 
  - add **bool isPressed(uint8_t button)**
- update readme.md
- minor edits

## [0.1.0] - 2026-06-16
- initial version

