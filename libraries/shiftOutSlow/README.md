
[![Arduino CI](https://github.com/RobTillaart/ShiftOutSlow/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ShiftOutSlow/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ShiftOutSlow/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ShiftOutSlow/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ShiftOutSlow/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ShiftOutSlow.svg)](https://github.com/RobTillaart/ShiftOutSlow/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ShiftOutSlow/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ShiftOutSlow.svg?maxAge=3600)](https://github.com/RobTillaart/ShiftOutSlow/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ShiftOutSlow.svg)](https://registry.platformio.org/libraries/robtillaart/ShiftOutSlow)


# ShiftOutSlow

Arduino library for shiftOut with build-in delay - e.g. for 74HC595


## Description


ShiftOutSlow is an experimental library that has a build in delay (in microseconds) that allows tuning the time per bit.
This allows one to improve reliability e.g. when using longer lines.

The data pin and clock pin are set in the constructor, the delay can be set per byte send to be able to optimize runtime.

ShiftOutSlow implements the print interface.


#### Related

- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow


## Performance

The performance of **write()** with a delay of 0 microseconds is slower than the default Arduino
**shiftOut()** due to some overhead.

The delay requested is divided by two to minimize disruption of the duty cycle of the clock pulse,
resulting in "better" pulses.

Performance measurements are meaningless, as the purpose of this library is to 
slow the pulse train to a working level.


## Interface

```cpp
#include "ShiftOutSlow.h"
```

#### Functions

The interface exists of the following functions:

- **ShiftOutSlow(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder = LSBFIRST)** constructor.
- **size_t write(uint8_t data)** writes a new value. 
Returns the bytes written.
- **size_t write(const uint8_t \*buffer, size_t size)** writes an array of size over shift out. 
Uses **write(uint8_t)** so expect about equal performance.
Returns the bytes written.
- **uint8_t lastWritten()** returns last value written.
- **void setDelay(uint16_t microSeconds = 0)** set delay per **bit** from 0 .. 65535 microseconds. 
Note: the delay is not the time per bit but an additional time per bit.
Note: the delay can be set runtime per write / print call.
- **uint16_t getDelay()** returns the set delay in microseconds.
- **bool setBitOrder(uint8_t bitOrder = LSBFIRST)** set LSBFIRST or MSBFIRST.
Returns false for other values.
Note: bit order can be changed runtime per write / print call.
- **uint8_t getBitOrder()** returns LSBFIRST or MSBFIRST (typical 0 and 1).


### Print interface

As this library implements the print interface one can use:

- **size_t print(any)** print any data type.
- **size_t println(any)** print any data type followed by a newline "\n".


## Operation

See examples.


## Future

#### Must

- improve documentation

#### Should

- Add a select pin to be more SPI alike?
  - would allow SPI debugging?
- increase max delay uint32_t ?
  - would allow pulses in "second" domain.

#### Could

- add examples
  - adaptive speed example?

#### Wont

- delay/2 is not exact half when delay is odd.
  - no big issue.
  - del_before and del_after could prepare for duty cycle.
- set delay in terms of frequency - delay is 'wave length'
- set delay in terms of max total time the read may cost.
- get set dutyCycle(0 .. 99%)
- optimize the place to yield() ?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

