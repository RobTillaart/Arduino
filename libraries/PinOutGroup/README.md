# PinOutGroup

Arduino library to group up to 16 outputs into one command

# Description

A PinOutGroup is a number of output pins that can be set by means of one **write()** command.
The PinOutGroup remembers the last values set per pin and will not do a digitalWrite()
if the pin is already in the right state. Think of it as caching the state.

If a (group of) pin(s) is updated often this saves cpu cycles however this feature 
has overhead which works contra productive when you toggle the pins in a group. So use with care.

### performance intermezzo
Assume that on average 50% of the pins are in the right state in a group. 
This means that on average half the pins are actually changed. By bypassing
the (relative) expensive **digitalWrite()** time is gained. 

Actual performance gains depends very much on the data written. 
It is worth to do a small investigation for this. See e.g. 7 segment demo.

### interface

**clear()** resets all pins in the group to LOW and sets the size ot zero
so one can repopulate.

**add()** adds a predefined array of pin numbers of a single pin to the group.

**write(value)** writes a 16 bits unsigned int to max 16 pins.

**write(idx, value)** sets a single pin of the internal array withindex 
idx to value. This one is faster than writing to the whole group for a single
change. The user must keep track of the right index nr.

**read()** reads back the last written value to the pins as an unsigend int.

**size()** and **free()** give information about the group.


# Operation

See examples

