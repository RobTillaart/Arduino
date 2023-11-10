
[![Arduino CI](https://github.com/RobTillaart/MATRIX7219/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MATRIX7219/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MATRIX7219/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MATRIX7219/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MATRIX7219/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MATRIX7219.svg)](https://github.com/RobTillaart/MATRIX7219/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MATRIX7219/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MATRIX7219.svg?maxAge=3600)](https://github.com/RobTillaart/MATRIX7219/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MATRIX7219.svg)](https://registry.platformio.org/libraries/robtillaart/MATRIX7219)


# MATRIX7219

Arduino Library for controlling one or more 8x8 LED MATRIX with a MAX7219 / MAX7221.


## Description

This experimental library provides an easy control to 8x8 MATRIX boards.
It is pretty minimalistic for now as the user still has to do bit math 
to get the right lights on as one can only set 8 LEDS at a time.

For the future two (derived) classes are planned: 
- a class that is optimized to use for a single 8x8 matrix.
- a class that buffers the state of the LEDS, allowing more functionality.

MAX7221 derived class is identical (for now).


#### Tests

It is tested with an UNO and a single 8x8 matrix and a 4x 8x8 matrix-chain.
During tests it became clear that the orientation of the matrices I used, 
seen from the IN connector was different. These insights lead to the 
implementation of the **inverse, reverse** and **swap** functions.


#### Related

- https://embed.plnkr.co/3VUsekP3jC5xwSIQDVHx Sprite Generator by Miro Božík


#### Tested

Tested on Arduino UNO.


## Interface

```cpp
#include "MATRIX7219.h"
```

Not all functionality works, matrix parameter et al.

- **MATRIX7219(uint8_t dataPin, uint8_t selectPin, uint8_t clockPin, uint8_t matrices)** 
Constructor, initializes IO pins and the number of 8x8 matrices on same pins.
- **MATRIX7221(uint8_t dataPin, uint8_t selectPin, uint8_t clockPin, uint8_t matrices)** 
Constructor (derived class) idem as above.
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

#### 0.1.0 UNO

MATRIX7219_performance.ino with UNO 16 MHz

|  board  |  function     |  time (us)  |  notes  |
|:-------:|:-------------:|:-----------:|:--------|
|   UNO   | begin         |     796     |
|   UNO   | clear         |    1572     |
|   UNO   | count         |       4     |
|   UNO   | setRow(255)   |     204     | setReverse has minimal influence
|   UNO   | setRow(0)     |     200     |
|   UNO   | setBrightness |     208     |


#### 0.1.1 UNO

Optimized registers for UNO  (for AVR from FastShiftOut).
2.5 to 4.2 times faster. (price: a few bytes storage).


|  board  |  function     |  time (us)  |  notes  |
|:-------:|:-------------:|:-----------:|:--------|
|   UNO   | begin         |     196     |  2.5x
|   UNO   | clear         |     368     |  4.2x
|   UNO   | count         |       4     |  idem
|   UNO   | setRow(255)   |      56     |  3.5x
|   UNO   | setRow(0)     |      56     |  3.5x
|   UNO   | setBrightness |      56     |  3.5x


#### 0.1.1 ESP32

First test ESP32

|  board  |  function     |  time (us)  |  notes  |
|:-------:|:-------------:|:-----------:|:--------|
|  ESP32  | begin         |      37     |
|  ESP32  | clear         |      47     |
|  ESP32  | count         |       2     |
|  ESP32  | setRow(255)   |      12     |
|  ESP32  | setRow(0)     |       8     |
|  ESP32  | setBrightness |       8     |


## Future

#### Must

- improve documentation

#### Should

- create a derived class with a buffer => 8 bytes per Matrix.
  - goal is to have **setPixel(x,y)** and **clearPixel(x,y)**
  - design first (performance)

#### Could

- examples
  - 8x8 as debugger (dump variables)
- add unit tests
  - need simulator / mock-up
- defaults for invert, reverse, swap?  (false).

#### Wont (unless requested)

- create a derived class for a single 8x8 matrix.
  - if performance gain is enough?
- store last set brightness.
  - **uint8_t getBrightness()**
  - not needed yet


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

