# Change Log I2C_LCD

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.2] - 2024-08-26
- fix #11, add dice example
- add single pixel example
- update spectrum_column example
- fix special chars, LCD_SQROOT + LCD_SIGMA + LCD_SUM
- add custom chars +- and euro
- fix version in .cpp

## [0.2.1] - 2024-01-08
- add ESP8266 performance figures.
- update readme.md
- clean up examples

## [0.2.0] - 2024-01-02
- Fix #6, clean up code
- rewrote the bitsInOrder optimization
- optimized send() a bit.
- add clear() measurement to performance sketch.
- update readme.md
- minor edits 

----

## [0.1.4] - 2023-12-28
- changed return type of **begin()**. Returns false if LCD not found on I2C bus.
- made initialization delay(100) in **begin()** a bit smarter.
- add **repeat(c, times)**
- fix **center()** for non 20x4 LCD.
- add **I2C_LCD_custom_chars.h** with examples.
- add examples

## [0.1.3] - 2023-12-22
- add support for **16x4** and **10x4** display.
- minimized footprint **setCursor()**
- add parameter to **moveCursorLeft(uint8_t n = 1)**
- add parameter to **moveCursorRight(uint8_t n = 1)**
- improve timing
- update examples
- minor edits

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

