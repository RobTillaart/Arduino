
[![Arduino CI](https://github.com/RobTillaart/PinInGroup/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PinInGroup/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PinInGroup/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PinInGroup/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PinInGroup/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PinInGroup.svg)](https://github.com/RobTillaart/PinInGroup/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PinInGroup/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PinInGroup.svg?maxAge=3600)](https://github.com/RobTillaart/PinInGroup/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PinInGroup.svg)](https://registry.platformio.org/libraries/robtillaart/PinInGroup)


# PinInGroup

Arduino library to read a group of up to 16 input pins in one command.


# Description

A PinInGroup holds a number of input pins that can be read by means of a single **read()** command.
The PinInGroup makes it easier to work with a number of inputs that act as a logical unit.
Think of reading a parallel bus or read 4 lines from a matrix keyboard, or an array of switches.

One of the interesting possibilities of the pinInGroup is to add a single pin multiple times.
That allows one to read a pin e.g. in a burst of 8.

Another application of adding a pin twice could be reading a pin as first and as last of a group.
This allows you to check that state of e.g. a parallel bus has not changed during read (or changed an even number :).

Default **PININGROUP_MAXSIZE** = 16.


#### Related

- https://github.com/RobTillaart/PinOutGroup


## Performance

The PinInGroup is not more efficient as reading the pins in a loop yourself.
However it is less programming and can give clearer code.

**Note** that the pins are not read at the same microsecond.
A small time is needed to go through all pins. 
This is platform, group size and pin state dependent.


## Interface

```cpp
#include "PinInGroup.h"
```


### Constructor

- **PinInGroup()** Constructor.

### Administration

- **void clear()** sets the size to zero so one can repopulate.
- **uint8_t add(uint8_t size, uint8_t \* pinArray, uint8_t mode)** adds a predefined array of pins to the group. 
Returns the number of pins added.
- **uint8_t add(uint8_t pin, uint8_t mode)** adds a single pin to the group. 
Returns the number of pins added (1 or 0). 
Mode can be **INPUT**(default) or **INPUT_PULLUP**.
- **uint8_t getPin(uint8_t index)** index = 0..15.
Returns the pin at slot index or 255 (0xFF) when out of range.
- **uint8_t getIndex(uint8_t pin)** returns the (first) index of the slot with pin number. 
Returns 255 (0xFF) if not found.
- **uint8_t isInGroup(uint8_t pin)** returns how often a pin is added to a group. 
Can be larger than one, max size of course.
- **uint8_t size()** how many slots are used.
- **uint8_t getMaxSize()** how many slots are there in total.
- **uint8_t available()** how many slots are free.


### Read

- **uint16_t read()** reads a 16 bits unsigned int from max 16 pins. 
Every bit represents an input value. 
Note that the bits are in LSB order of the adding.
- **uint16_t read(uint8_t index)** index = 0 .. size - 1. 
Reads the single pin at index from the group. 
Returns 0 or 1 if OK and 0xFFFF when index >= size.


#### Error codes

PININGROUP_ERROR_PIN = 0xFF = 255.


## Operation

See examples.


## Future

These ideas will be explored when time permits or needs arise.

#### Must

- improve documentation
- move code from .h to .cpp

#### Should

- add real live examples
- Allocate dynamic memory (0.2.0)
  - fragmentation?
  - would be memory efficient.

#### Could

- Optimize the low level reading e.g. reading registers only once.
  - Hold register and bit info per pin. 
  - Especially for AVR this could be interesting performance wise.
- Create a PWMGroup
- Create an analogPinGroup
  - new class
- extend to 32 bits / pins. class hierarchy. 8, 24 ?
- clear() => reset() or clearGroup() ?
- do we need yield() somewhere?
- extend unit tests
  - getIndex()
  - getPin()

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

