# Change Log Gauss

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.1] - 2023-11-02
- update readme.md
- minor edits.


## [0.2.0] - 2023-07-10
- improve performance => faster lookup.
  - removed __z[] saves 136 bytes RAM
- remove MultiMap dependency.
- - remove **\_stddev** as **\_reciprokeSD** holds same information.
- add **float P_outside(float f, float g)** 
  - returns **P(x < f) + P(g < x)** under condition (f < g).
- add **float denormalize(float value)** (reverse normalize).
- add examples DS18B20 and HX711 and BMI
- update readme.md
- minor edits.

----

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

