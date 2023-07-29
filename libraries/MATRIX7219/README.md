
[![Arduino CI](https://github.com/RobTillaart/MATRIX7219/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MATRIX7219/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MATRIX7219/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MATRIX7219/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MATRIX7219/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MATRIX7219/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MATRIX7219.svg?maxAge=3600)](https://github.com/RobTillaart/MATRIX7219/releases)


# MATRIX7219

Arduino Library for controlling one or more 8x8 LED MATRIX with a MAX7219.


## Description

This experimental library provides an easy control to 8x8 MATRIX boards.
It is pretty minimalistic for now as the user still has to do bit math 
to get the right lights on as one can only set 8 LEDS at a time.

For the future two (derived) classes are planned: 
- a class that is optimized to use for a single 8x8 matrix.
- a class that buffers the state of the LEDS, allowing more functionality.


#### Tests

It is tested with an UNO and a single 8x8 matrix and a 4x 8x8 matrix-chain.
During tests it became clear that the orientation of the matrices I used, 
seen from the IN connector was different. These insights lead to the 
implementation of the **inverse, reverse** and **swap** functions.


#### Related

- TODO


#### Tested

Tested on Arduino UNO.


## Interface

**\#include "MATRIX7219.h"**

Not all functionality works, matrix parameter et al.

- **MATRIX7219(uint8_t dataPin, uint8_t selectPin, uint8_t clockPin, uint8_t matrices)** 
Constructor, initializes IO pins and the number of 8x8 matrices on same pins.
- **void begin()** resets the internals of the connected device.
- **uint8_t  getMatrixCount()** returns number of matrices set in constructor.
Convenience function.
- **void setBrightness(uint8_t bright = 2)** set bright = 0..15 for all matrices. 
Default is a relative low intensity.
- **void displayOff()** switches on low power mode == all LEDs off.
Leaves all registers the same. 
Can be used to blink the display, get attention.
- **void displayOn()** switches display on again.  
- **void displayTest(bool on = false)** sets all LEDs on full brightness.
Used to verify all LEDS still work. 
Or to implement a flashy alarm.
Default value is false ==> normal mode.
- **void clear()** clear all matrices.
- **void setRow(uint8_t row, uint8_t value, uint8_t matrix)** set a value to a certain row of a certain matrix.


#### Invert, reverse and swap.

For adapting the layout if needed.

- **void setInvert(bool invert)** invert the output. Default = false.
- **bool getInvert()** get current setting.
- **void setReverse(bool rev)** reverse the output. Default = false.
- **bool getReverse()** get current setting.
- **void setSwap(bool swap)** swaps row n with (8-n).
- **bool getSwap()** get current setting.


## Performance 

Preliminary tests - MATRIX7219_performance.ino

|  version  |  function     |  time (us)  |  notes  |
|:---------:|:-------------:|:-----------:|:--------|
|   0.1.0   | begin         |    796      |
|   0.1.0   | clear         |    1572     |
|   0.1.0   | count         |    4        |
|   0.1.0   | setRow(255)   |    204      | setReverse has minimal influence
|   0.1.0   | setRow(0)     |    200      |
|   0.1.0   | setBrightness |    208      |


## Future

#### Must

- improve documentation
- Buffering version => 8 bytes per Matrix.
- Single matrix version (faster)
- 

#### Should

- test other platforms
- performance testing
  - increase.
- add unit tests
- create a derived class for a single 8x8 matrix.
  - if performance gain is enough?
- create a derived class with a buffer
  - goal is to have **setPixel(x,y)** and **clearPixel(x,y)**
- reverse from CRC for real reverse


#### Could

- examples
  - 8x8 as debugger (dump variables)
  - clock ? binary - other?
- store last set brightness. 
  - **uint8_t getBrightness()**
  

#### Wont

