# PinInGroup

Arduino library to group reading to 16 input pins in one command

# Description

A PinInGroup holds a number of input pins that can be read by means of a single **read()** command.
The PinInGroup makes it easier to work with a number of inputs that are a logical unit,
e.g. think of reading a parallel bus or read 4 lines from a matrix keyboard, or just 
read an array of switches.

### Performace

The PinInGroup is not much more efficient as reading the pins in a loopyourself.
Hoewever it is less programming and gives clearer code.

There exist some ideas to optimize the low level reading e.g. only reading
the registers only once, or hold register and bit info per pin.
These ideas will be explored when time permits. 

Note: The current ideas are platform specific.

### interface

**clear()** sets the size to zero so one can repopulate.

**add()** adds a predefined array of pins of a single pin to the group. 
Note one can set a 2nd parameter mode to **INPUT**(default) or **INPUT_PULLUP**.

**read(value)** reads a 16 bits unsigned int from max 16 pins.

**size()** and **free()** give information about the group.

# Operation

See examples

