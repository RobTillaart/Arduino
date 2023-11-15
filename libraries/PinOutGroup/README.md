
[![Arduino CI](https://github.com/RobTillaart/PinOutGroup/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PinOutGroup/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PinOutGroup/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PinOutGroup/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PinOutGroup/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PinOutGroup.svg)](https://github.com/RobTillaart/PinOutGroup/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PinOutGroup/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PinOutGroup.svg?maxAge=3600)](https://github.com/RobTillaart/PinOutGroup/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PinOutGroup.svg)](https://registry.platformio.org/libraries/robtillaart/PinOutGroup)


# PinOutGroup

Arduino library to group up to 16 outputs into one command.


## Description

A PinOutGroup is a number of output pins that can be set by means of one **write()** command.
The PinOutGroup remembers the last values set per pin and will not do a digitalWrite()
if the pin is already in the right state. Think of it as caching the state.

If a (group of) pin(s) is updated often this saves CPU cycles however this feature 
has overhead which works contra productive when you toggle the pins in a group. 
So use with care.

Default **PINOUTGROUP_MAXSIZE** = 16.


#### Related

- https://github.com/RobTillaart/PinInGroup


## Performance 

Assume that on average 50% of the pins are in the right state in a group. 
This means that on average half the pins are actually changed. By bypassing
the (relative) expensive **digitalWrite()** time is gained. (at least on AVR).

Actual performance gains depends very much on the data written. 
It is worth to do a small investigation for this. See e.g. 7 segment demo.

**Note** that the pins are not set at the same microsecond.
A small time is needed to go through all pins. 
This is platform, group size and pin state dependent.


## Interface

```cpp
#include "PinOutGroup.h"
```

### Constructor

- **PinOutGroup()** Constructor.

### Administration

- **void clear()** resets all pins in the group to LOW and sets the size to zero.
so one can repopulate.
- **uint8_t add(uint8_t size, uint8_t \* pinArray, uint8_t value = LOW)** adds a predefined array of pins to the group. 
Returns the number of pins added. Default the pins are set to LOW.
- **uint8_t add(uint8_t pin, uint8_t mode = LOW)** adds a single pin to the group. 
Returns the number of pins added (1 or 0). value can be LOW (=0, default) or HIGH (1 and other values).
- **uint8_t getPin(uint8_t index)** index = 0..15; returns the pin at slot index or 255 (0xFF) when out of range.
- **uint8_t getIndex(uint8_t pin)** returns the (first) index of the slot with pin number. 255 (0xFF) if not found.
- **uint8_t isInGroup(uint8_t pin)** returns how often a pin is added to a group. Can be more than once.
- **uint8_t size()** how many slots are used.
- **uint8_t getMaxSize()** how many slots are there in total.
- **uint8_t available()** how many slots are available.


### Read / Write

- **uint8_t write(uint16_t value)** writes a 16 bits unsigned int to max 16 pins.
- **uint8_t write(uint8_t index, uint8_t value)** sets a single pin of the internal array with index  to value. 
This one is faster than writing to the whole group for a single change. 
The user must keep track of the right index number.
- **void allLOW** sets all pins to LOW (this is not same as clear).
- **void allHIGH** sets all pins to HIGH.
- **uint16_t read()** reads back the last written value to the pins as an unsigned int.


## Operation

See examples


## Future

#### Must

- update documentation

#### Should 

- move code from .h to .cpp
- should clear() have a flag to set to LOW/HIGH/NOCHANGE when clearing?

#### Could

- Optimize the low level writing
  For AVR this could be interesting (performance).
- extend to 32 bits / pins. class hierarchy. 8, 24 ?
- give **clear(skip)** a bool flag to skip setting the pins to LOW ?
- remove function? 
- check PinInGroup to stay in "sync" API wise.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

