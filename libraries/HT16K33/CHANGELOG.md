# Change Log HT16K33

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.1] - 2024-01-04
- add constants for individual segments, kudos to DeflateAwning
- add **demo_scrolling.ino**
- update readme.md


## [0.4.0] - 2023-12-05
- refactor API, begin()
- update readme.md
- remove obsolete getAddr() => **getAddress()**
- rename brightness() => **setBrightness()**
- add **getBrightness()**
- rename blink() ==> **setBlink()**
- add **getBlink()**
- minor edits

----

## [0.3.9] - 2023-09-22
- add Wire1 support for ESP32
- update readme.md

## [0.3.8] - 2023-02-26
- add **getBrightness()**
- moved code to .cpp file (prep 0.4.0)
- update readme.md
- added OBSOLETE section (prep 0.4.0)
- update GitHub actions
- update license 2023
- minor edits

## [0.3.7] - 2022-11-19
- add displayUnit(float, char);
- add top c symbol
- add degree symbol
- moved code to .cpp file (prep 0.4.0)

## [0.3.6] - 2022-11-09
- add changelog.md
- add rp2040 to build-CI
- update readme.md

## [0.3.5] - 2022-09-23
- fix #21 additional LEDs on the display
  used in a special layout   :88:8'8
  
## [0.3.4] - 2021-12-19
- update library.json
- update license
- minor edits

## [0.3.3] - 2021-05-26
- fix #17 add leadingZero flag in displayTIme() (Kudos to OwenDuffy)

## [0.3.2] - 2021-01-14
- add WireN support,
- add refresh(),                  // experimental
- add getOverflow();              // experimental
- add displayFloat(f, decimals);  // experimental

## [0.3.1] - 2020-12-28
- Arduino-CI, unit test (framework only)

## [0.3.0] - 2020-10-12
- negative float
- cache control
- extend displayRaw()

----

## [0.2.4] - 2020-10-10
- refactor #5 setDigits() iso suppressLeadingZeroPlaces()

## [0.2.3] - 2020-10-09
- issue #4 add negative values for displayInt()

## [0.2.2] - 2020-10-04
- add displayDate() thanks to bepitama

## [0.2.1] - 2020-07-15
- fix #160 - decimal point
## [0.2.0] - 2020-06-13
- ESP32 support
- fix brightness bug

----

## [0.1.5] - 2019-11-30
- refactor

## [0.1.4] - 2019-11-28
- add displayRaw()
- add displayVULeft(), displayVURight()

## [0.1.3] - 2019-10-07
- fix clear
- add suppressLeadingZeroPlaces()

## [0.1.2] - 2019-02-11
-- optimized performance

## [0.1.1] - 2019-02-07
- first stable version

## [0.1.0] - 2019-02-07
- initial version


