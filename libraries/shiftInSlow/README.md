
[![Arduino CI](https://github.com/RobTillaart/ShiftInSlow/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ShiftInSlow/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ShiftInSlow/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ShiftInSlow/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ShiftInSlow/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ShiftInSlow.svg)](https://github.com/RobTillaart/ShiftInSlow/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ShiftInSlow/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ShiftInSlow.svg?maxAge=3600)](https://github.com/RobTillaart/ShiftInSlow/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ShiftInSlow.svg)](https://registry.platformio.org/libraries/robtillaart/ShiftInSlow)


# ShiftInSlow

Arduino library for shiftIn with build-in delay - e.g. for 74HC165.


## Description

**Experimental**

shiftInSlow is a library which has a build in delay (in microseconds) 
that allows tuning the time per bit. 
This can help to improve reliability e.g. when using long lines.

The dataPin and clockPin and bitOrder are set in the constructor.
The (bit) delay is configurable before every byte send to be able 
to optimize runtime. 
Default there is no delay.

Feedback as always is welcome.


### Related

- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow


## Performance

The performance of **read()** with a delay of 0 microseconds is slower
 than the default Arduino **shiftIn()** due to some overhead. 

The delay requested is split in two (expect rounding errors) to have 
"nice" looking pulse with the duty cycle around 50%.

Performance measurements are meaningless, as the purpose of this library
is to slow down the pulse train to a working level.


## Interface

```cpp
#include "ShiftInSlow.h"
```

### Constructor

- **ShiftInSlow(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder = LSBFIRST)** constructor, 
bit order is default set to LSBFIRST.
Default there is no delay (0 us).

### Read

- **int read()** reads a new value.
- **int lastRead()** returns last value read from cache.

### Delay

- **void setDelay(uint16_t microseconds = 0)** set delay per bit 
from 0 .. 65535 microseconds. 
Note that the delay is split in two parts to keep the duty cycle around 50%.
Note that odd delays will get a truncating error.
- **uint16_t getDelay()** returns the set delay in microseconds.

### BitOrder

- **bool setBitOrder(uint8_t bitOrder = LSBFIRST)** set LSBFIRST or MSBFIRST. 
Returns false for other values (so bitOrder is not changed).
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST.

### Invert

(new in 0.1.6)

- **void setInvert(bool invert = false)** invert the data read.
- **uint16_t getInvert()**

If the byte read is inverted, the **lastRead()** will return 
the inverted value too.


## Operation

See examples.


## Future

#### Must

- improve documentation

#### Should

- Add a select pin to be more SPI alike?
  - would allow SPI debugging?
- fix odd delays rounding error
  - get uneven duty cycle is result.

#### Could

- add examples
  - adaptive speed example?
- reverse flag to change "BitOrder in software"?
  - parameter for read(bool reverse) or lastRead(reverse)
  - faster than rereading (if possible)

#### Wont

- delay/2 is not exact half when delay is odd.
  - no big issue.
  - del_before and del_after could prepare for duty cycle.
- get set dutyCycle(0 .. 99%)
- set delay in terms of frequency - delay is 'wave length'
- set delay in terms of max total time the read may cost.
- read16/24/32 to read more bytes is a user task.
- increase max delay uint32_t ?
  - would allow pulses in "second" domain.
  - and blocking for long time.
  - millis() clock instead of micros()

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
