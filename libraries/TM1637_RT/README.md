[![Arduino CI](https://github.com/robtillaart/TM1637_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TM1637_RT.svg?maxAge=3600)](https://github.com/RobTillaart/TM1637_RT/releases)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TM1637_RT/blob/master/LICENSE)


# TM1637

Experimental library for TM1637 driven displays.

TO ELABORATE


## Interface

- **TM1637()** constructor
- **void init(uint8_t clockPin, uint8_t dataPin, uint8_t digits = 6)** set up the connection of the pins to the display.
As the display is only tested with a 6 digit display, this is used a s the default of the digits param.
- **void displayRaw(uint8_t \* data, uint8_t pointPos)**
- **void displayInt(long value)**
- **void displayFloat(float value)**
- **void displayHex(uint32_t value)**
- **void displayClear()** writes spaces to all positions.
- **void    setBrightness(uint8_t b)**
- **uint8_t getBrightness()**


### tuning function
To tune the timing of writing bytes.

- **void    setBitDelay(uint8_t bitDelay = 10)**
- **uint8_t getBitDelay()**



## Operation

See examples

