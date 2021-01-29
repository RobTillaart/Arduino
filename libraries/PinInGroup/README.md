
[![Arduino CI](https://github.com/RobTillaart/PinInGroup/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PinInGroup/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PinInGroup.svg?maxAge=3600)](https://github.com/RobTillaart/PinInGroup/releases)

# PinInGroup

Arduino library to group reading to 16 input pins in one command

# Description

A PinInGroup holds a number of input pins that can be read by means of a single **read()** command.
The PinInGroup makes it easier to work with a number of inputs that act as a logical unit.
Think of reading a parallel bus or read 4 lines from a matrix keyboard, or an array of switches.

One of the interesting possibilities of the pinInGroup is to add a single pin multiple times.
That allows one to read a pin e.g. in a burst of 8.

Another application of adding a pin twice could be reading a pin as first and as last of a group.
This allows you to check that state of e.g. a parallel bus has not changed during read.

## Performance

The PinInGroup is not more efficient as reading the pins in a loop yourself.
Hoewever it is less programming and can give clearer code.

**Note** that the pins are not read at the same microsecond.
A small time is needed to go through all pins. 
This is platform, group size and pin state dependent.


## Interface

### Constructor

- **PinInGroup()** Constructor

### Administration

- **clear()** sets the size to zero so one can repopulate.
- **add(size, pinArray, mode)** adds a predefined array of pins to the group. Returns the number of pins added.
- **add(pin, mode)** adds a single pin to the group. Returns the number of pins added (1 or 0). Mode can be **INPUT**(default) or **INPUT_PULLUP**.
- **getPin(idx)** idx = 0..15; returns the pin at slot idx or 255 (0xFF) when out of range
- **getIdx(pin)** returns the (first) index of the slot with pin number. 255 (0xFF) if not found.
- **isInGroup(pin)** returns how often a pin is added to a group. Can be more than once.
- **size()** how many slots are used
- **available()** how many slots are free


### Read

- **read()** reads a 16 bits unsigned int from max 16 pins. Every bit represents an input value. Note that the bits are in LSB order of the adding.
- **read(idx)** idx = 0..size-1. Reads the single pin at idx from the group. Returns 0 or 1 if OK and 0xFFFF when idx >= size.


## Future

- Optimize the low level reading e.g. reading registers only once.
- Hold register and bit info per pin. Especially for AVR this could be interesting.
- Create an analogPinGroup and a PWMGroup 
- extend to 32 bits / pins.
- Allocate dynamic memory? (fragmentation)


These ideas will be explored when time permits. 


# Operation

See examples

