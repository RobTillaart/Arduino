# Change Log PERIPUMP

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.2] - 2023-11-14
- update readme.md
- update keywords.txt


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


