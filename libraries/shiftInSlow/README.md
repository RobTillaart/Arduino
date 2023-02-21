
[![Arduino CI](https://github.com/RobTillaart/ShiftInSlow/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ShiftInSlow/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ShiftInSlow/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ShiftInSlow/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ShiftInSlow/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ShiftInSlow/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ShiftInSlow.svg?maxAge=3600)](https://github.com/RobTillaart/ShiftInSlow/releases)


# ShiftInSlow

Arduino library for shiftIn with build-in delay - e.g. for 74HC165.

Related libraries
- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow


## Description

shiftInSlow is an experimental library that has a build in delay (in microseconds) that allows tuning the time per bit. 
This allows one to improve reliability e.g. when using longer lines.

The dataPin and clockPin are set in the constructor, the delay is configurable per byte send to be able to optimize runtime.


## Performance

The performance of **read()** with a delay of 0 microseconds is slower than the default Arduino 
**shiftIn()** due to some overhead. 

The delay requested is split in two (expect rounding errors) to have "nice" looking pulse
with the duty cycle around 50%.

Performance measurements are meaningless, as the purpose of this library is to 
slow the pulse train to a working level.


## Interface

```cpp
#include "ShiftInSlow.h"
```

#### Functions

The interface exists of the following functions:
- **ShiftInSlow(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder = LSBFIRST)** constructor, 
bit order is default set to LSBFIRST.
- **int read()** reads a new value.
- **int lastRead()** returns last value read.
- **void setDelay(uint16_t microseconds = 0)** set delay per bit from 0 .. 65535 microseconds. 
Note that the delay is split in two parts to keep the duty cycle around 50%.
- **uint16_t getDelay()** returns the set delay in microseconds.
- **bool setBitOrder(uint8_t bitOrder = LSBFIRST)** set LSBFIRST or MSBFIRST. Returns false for other values.
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST.


## Operation

See examples.


## Future

#### Must

- improve documentation

#### Should

- add examples
  - adaptive speed example?

#### Could

- Add a select pin to be more SPI alike?
- increase max delay uint32_t ?

#### Wont

- get set dutyCycle(0 .. 99%)
- set delay in terms of frequency - delay is 'wave length'
- set delay in terms of max total time the read may cost.
- read16/24/32 to read more bytes is a user task.

