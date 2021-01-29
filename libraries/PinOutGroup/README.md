
[![Arduino CI](https://github.com/RobTillaart/PinOutGroup/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PinOutGroup/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PinOutGroup.svg?maxAge=3600)](https://github.com/RobTillaart/PinOutGroup/releases)

# PinOutGroup

Arduino library to group up to 16 outputs into one command

## Description

A PinOutGroup is a number of output pins that can be set by means of one **write()** command.
The PinOutGroup remembers the last values set per pin and will not do a digitalWrite()
if the pin is already in the right state. Think of it as caching the state.

If a (group of) pin(s) is updated often this saves cpu cycles however this feature 
has overhead which works contra productive when you toggle the pins in a group. 
So use with care.

## Performance 

Assume that on average 50% of the pins are in the right state in a group. 
This means that on average half the pins are actually changed. By bypassing
the (relative) expensive **digitalWrite()** time is gained. 

Actual performance gains depends very much on the data written. 
It is worth to do a small investigation for this. See e.g. 7 segment demo.

**Note** that the pins are not set at the same microsecond.
A small time is needed to go through all pins. 
This is platform, group size  and pin state dependent.


## Interface


### Constructor

- **PinOutGroup()** Constructor


### Administration

- **clear()** resets all pins in the group to LOW and sets the size to zero
so one can repopulate.
- **add(size, pinArray, value)** adds a predefined array of pins to the group. Returns the number of pins added.
- **add(pin, mode)** adds a single pin to the group. Returns the number of pins added (1 or 0). value can be LOW (=0) or HIGH (1 and other values).
- **getPin(idx)** idx = 0..15; returns the pin at slot idx or 255 (0xFF) when out of range
- **getIdx(pin)** returns the (first) index of the slot with pin number. 255 (0xFF) if not found.
- **isInGroup(pin)** returns how often a pin is added to a group. Can be more than once.
- **size()** how many slots are used
- **available()** how many slots are available


### Read / Write

- **write(value)** writes a 16 bits unsigned int to max 16 pins.
- **write(idx, value)** sets a single pin of the internal array withindex 
idx to value. This one is faster than writing to the whole group for a single
change. The user must keep track of the right index nr.
- **allLOW** sets all pins to LOW (this is not same as clear)
- **allHIGH** sets all pins to HIGH
- **read()** reads back the last written value to the pins as an unsigend int.


## Future

- give **clear(skip)** a bool flag to skip setting the pins to LOW ?
- remove function? 

## Operation

See examples

