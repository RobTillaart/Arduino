# Change Log pressure

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2023-11-15
- update readme.md


## [0.3.0] - 2023-02-23
- refactor getter constants
- add return value to **change()** functions.
- rename **change()** functions, more descriptive
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

----

## [0.2.2] - 2022-11-22
- add changelog.md
- add RP2040 to build-CI
- minor edits

## [0.2.1] - 2021-12-23
- update library.json
- update  license
- add experimental gas law

## [0.2.0] - 2021-11-25
- Fix formulas

----

## [0.1.0] - 2021-11-25
- Initial version


























## [0.1.1] - 2022-10-14

- add parameter to begin(float percentage)
- refactored stop()
- refactored setPercentage()
- remapped the 0-100% to 2000-2500 microseconds of servo as
  the full 1600-2500 range was only active above 50~60%
  depending on the voltage used.
- add forward(), backward() + example.
- add setInvert(flag = false)
- updated readme.md


## [0.1.0] - 2022-10-13

- initial version
- add stop(), get- and setPercentage()
- add getSeconds(), resetSeconds() for simple duration management.
- **low percentages < 50% do not work.**


