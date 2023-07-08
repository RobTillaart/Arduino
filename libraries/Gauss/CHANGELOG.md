# Change Log Gauss

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.1] - 2023-07-07
- improve performance => reciprokeSD = 1.0/stddev
- update readme.md
  - add performance section (UNO / ESP32)
  - elaborated future section
- generated a more precise lookup table (8 decimals)
- update unit tests
- add default parameters to **bool begin(float mean = 0, float stddev = 1)**
  - allow negative **stddev** but return false if stddev <= 0.
- add **float getMean()** convenience function.
- add **float getStdDev()** convenience function.
- clean up a bit



## [0.1.0] - 2023-07-06
- initial version

