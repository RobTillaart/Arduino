# Change Log I2C_LCD

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


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

