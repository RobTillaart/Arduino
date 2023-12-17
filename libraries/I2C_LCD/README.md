
[![Arduino CI](https://github.com/RobTillaart/I2C_LCD/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_LCD/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_LCD/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_LCD/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_LCD/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_LCD.svg)](https://github.com/RobTillaart/I2C_LCD/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_LCD/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_LCD.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_LCD/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_LCD.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_LCD)


# I2C_LCD

Arduino library for I2C_LCD  LCD displays.


## Description

Experimental library for the I2C LCD display, typical 20 x 4 characters.

The goal of the library is to minimize footprint and improve performance.
This is partly done by dedicate the library to I2C only.

The library is inspired by the excellent LiquidCrystel_I2C library of F. Malpartida.
- https://github.com/fmalpartida/New-LiquidCrystal

The library implements the print interface, so all data types are printable.


#### Compatibility

Not 100% compatible with F. Malpartida's I2C library, however the differences are 
not that large.
Furthermore the 0.1.0 version does not support all functionality so there is still
a lot to implement.
So if you need such functionality, you still should use the **New-liquidCrystal** library.


#### Tests

Only tested on an UNO and a 20 x 4 character LCD.


## Performance

The most important optimization is to send a byte in a single I2C transaction.
This takes 5 bytes to transport, which is 3 less than the reference.

Furthermore there is an optimization if the pins are in order, as then
it is far easier to get the nibble (half bytes).

First performance tests are good. See example **I2C_LCD_performance.ino**.

The performance measurement is done on an UNO, pins are in order.

|  I2C clock  |  time (us)  |  notes  |
|:-----------:|:-----------:|:-------:|
|  100000     |     4316    |
|  200000     |     2440    |
|  300000     |     1780    |
|  400000     |     1496    |  recommended 
|  500000     |     1308    |
|  600000     |     1176    |
|  700000     |     1076    |
|  800000     |     1024    |


#### Related

- https://github.com/fmalpartida/New-LiquidCrystal



## Interface

```cpp
#include "I2C_LCD.h"
```

#### Constructor

- **I2C_LCD(uint8_t address, TwoWire \* wire = &Wire)** Constructor, 
mandatory address and optional alternative I2C bus.
- **void config(uint8_t address, uint8_t enable, uint8_t readwrite, uint8_t registerselect, 
                   uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7, 
                   uint8_t backlight)** pin configuration.
Will change in the future.
- **void begin(uint8_t cols = 20, uint8_t rows = 4)** initializes library size.


#### Other

- **void setBacklight(bool on)** not implemented yet
- **void display()** set display on
- **void noDisplay()** set display off
- **void clear()** clear the screen and set cursor to 0, 0.
- **void home()** set cursor to 0, 0.
- **void setCursor(uint8_t col, uint8_t row)** set cursor to given position.
There is no check yet if this is out of range.


#### Print interface

- **size_t write(uint8_t c)**

Array writing not supported.


#### Low level API

In the first version these are public, however they probably should be private.

- **void sendData(uint8_t value)**
- **void sendCommand(uint8_t value)**
- **void write4bits(uint8_t value)**


## Future

#### Must

- update documentation

#### Should

- fix TODO's in code
- implement functional range
- test with other platforms
- test with other display sizes
- test more
- make a PR for New-LiquidCrystal library to implement there too.


#### Could

- implement unit tests (possible?)
- add examples
  - Wire1, Wire2 etc
- solve MAGIC numbers (defaults)
- add timestamp last print
- position control in write().


#### Wont



## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

