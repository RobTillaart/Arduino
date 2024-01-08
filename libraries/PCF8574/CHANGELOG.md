# Change Log PCF8574

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.1] - 2023-09-23
- Update readme with advanced interrupts insights
  - kudos to ddowling for testing.
  - add example
- fix URL examples
- add Wire1 example (ESP32 + RP2040)


## [0.4.0] - 2023-09-23
- refactor API, begin()
- update readme.md
- update examples
- add examples ESP32 RP2040
- minor edits

----

## [0.3.9] - 2023-09-23
- Add Wire1 support for ESP32
- update readme.md
- minor edits

## [0.3.8] - 2023-02-04
- update readme.md
- update GitHub actions
- update license 2023

## [0.3.7] - 2022-11-16
- fix #40 - add interrupt section to readme.md

## [0.3.6] - 2022-10-19
- fix example PCF8574_rotaryEncoder.ino
- add RP2040 to build-CI
- simplified changelog.md 

## [0.3.5] - 2022-06-17
- add select(), selectN(), selectNone() and selectAll()
  convenience wrappers

## [0.3.4] - 2022-04-11
- add CHANGELOG.md
- fix **begin(int sda, int scl)** int parameters for ESP alike.

## [0.3.3] - 2021-12-23  
- update library.json, license, readme, minor edits

## [0.3.2] - 2021-07-04
- fix #25 add setAddress()

## [0.3.1] - 2021-04-23
- Fix for platformIO compatibility

## [0.3.0] - 2021-01-03
- add multiWire support - inspired by mattbue - issue #14

---

## [0.2.4] - 2020-12-17
- fix #6 tag problem 0.2.3

## [0.2.3] - 2020-12-14
- fix #6 readButton8 ambiguity

## [0.2.2] - 2020-12-07
- add Arduino-ci + start unit test + _wire->h in PCF8574.h

## [0.2.1] - 2020-06-19
- fix library.json

## [0.2.0] - 2020-05-22
- #pragma once; refactor;
- removed pre 1.0 support
- added begin(dsa, scl) for ESP32
- added reverse()

----

## [0.1.9] - 2017-02-27
- fix warning about return in readButton8()

## [0.1.08] - 2016-05-20'
-  Merged work of Septillion
- Fix/refactor ButtonRead8() - see https://github.com/RobTillaart/Arduino/issues/38
- missing begin() => mask parameter

## [0.1.07] - 2016-05-02  
- (manually merged) Septillion
- added dataOut so a write() doesn't read first,
   possibly corrupting a input pin;
- fixed shift comment, should read 1..7;
- added begin() to be sure it's in a known state,
  states could be different if uC is reset and the PCF8574 isn't;
- added buttonRead() and buttonRead8()
  which only effect the output while reading

## [0.1.06] - ??
- (intermediate) added defined errors + refactor rotate

## [0.1.05] - 2016-04-30
-  refactor, +toggleMask, +rotLeft, +rotRight

## [0.1.04] - 2015-05-09
- removed ambiguity in read8()

## [0.1.03] - 2015-03-02
- address int -> uint8_t

## [0.1.02] - ?
- replaced integers with uint8_t to reduce footprint;
- added default value for shiftLeft() and shiftRight()
- renamed status() to lastError();

## [0.1.01] - ?
- added value(); returns last read 8 bit value (cached);
  value() does not always reflect the latest state of the pins!

## [0.1.00] - 2013-02-02
- initial version
