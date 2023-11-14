
# Release Notes MultiSpeedI2CScanner

https://github.com/RobTillaart/MultiSpeedI2CScanner


## Version 

0.1.17


### 0.1.17  2023-11-14
- update readme.md

### 0.1.16  2023-01-20

- update build-ci
- add link to I2C scanner class in readme.md

### 0.1.15  2021-12-22

- change Khz =>KHz
- update license

### 0.1.14  2021-11-10

- update Arduino-CI build process
- add badges to readme.md
- updated readme.md
- support up to 5 Wire buses
- added an I2C bus counter sketch (very minimal)
- minor edits release notes.

### 0.1.13  2020-12-12

- Add Arduino-CI build process.
- Added a dummy examples folder with the same .ino source.
- This shows that the sketch compiles well.

### 0.1.12  2020-12-12

- Fix #4, default address range = 08...119 (0-7 and 120-127 are special)

### 0.1.11  2018-07-20

- Fix failing TWBR setting
- added yield() during scan to improve ESP behaviour.
- added disable interrupts flag
- refactor / clean up

### 0.1.10  2018-04-02

- Fix #152
- improved support for ESP32
- changed multispeed ranges a bit (option 0 and 9)
- refactor
- added experimental high speeds 1000, 3400, 5000 KHz.

verified on UNO and ESP32,
note the latter one must adjust the pins in the code.

### 0.1.9   2018-04-02

- '9' command to scan up to 400 KHz only to prevent blocking
- changed "scan up to 400 KHz" as default at startup

### 0.1.8   2017-08-03

- DUE support

### 0.1.7   2017-07-17

- TEENSY support - multiple I2C ports
- '@' command to select I2C Port
- changed # speeds steps of 100

### 0.1.6   2015-03-29

- Wire.setClock as more portable way to set I2C clock

### 0.1.5   2014-07-06

- void setSpeed()   - more control about what is scanned
- void setAddress() - address range
- extended help

### older versions not documented
(started 2013-11-05 ?)


//  -- END OF FILE --

