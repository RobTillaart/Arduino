# Change Log I2C_LCD

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.2] - 2023-12-21
- implement polarity backlight (and removed policy)
- add **size_t center(uint8_t row, const char \* message)**
- add **size_t right(uint8_t col, uint8_t row, const char \* message)**
- merged low level code reducing footprint.
- optimized low level code when pins are not in ascending order (minor).
- add examples
- fix keywords.txt
- update readme.md


## [0.1.1] - 2023-12-18
- add blink() and noBlink()
- add cursor() and noCursor()
- add on() and off()
- refactor **config()** => breaking change
- add backlight code
- add **clearEOL()** - clear from current pos to end of line
- add position control to prevent writing beyond EOL
- add bool return type for **setCursor()** fail ==> out of range
- add clear() and display() to **begin()**
- add default pins
- update keywords.txt
- add examples
- add **I2C_LIB_special_chars.h**
- and more


## [0.1.0] - 2023-12-16
- initial version 
- goal is to optimize footprint & performance

