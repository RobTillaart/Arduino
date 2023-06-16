
[![Arduino CI](https://github.com/RobTillaart/TOPMIN/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TOPMIN/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TOPMIN/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TOPMIN/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TOPMIN/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TOPMIN/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TOPMIN.svg?maxAge=3600)](https://github.com/RobTillaart/TOPMIN/releases)


# TOPMIN

Arduino library to track the top N minima.


## Description

This experimental library tracks the top N minima of a series of values. 

The library implements two classes:
- **TOPMIN** just tracks the values. (smaller footprint).
- **TOPMINext** also tracks a user defined 32-bit tag (e.g. timestamp).

The latter is more useful as it allows to link the top N values to a certain time
or day, an index in a database, or another indirect reference.
It can even be used to store a second parameter e.g. what was the humidity for
the top N temperatures.

The library can be used for different applications:
- track top N minima temperature / humidity over a given period of time.
- track top N UV minima intensity during the day.
- track top N trading volumes or $$.
- track top N smallest fish caught in a contest.
- track top N minimum number of visitors during a day.

The 32 bit tag, can be filled with a 32 bit number like a timestamp, bit can also
be used more creatively e.g. 2x 16 bit numbers or even 32 booleans. 
Any mapping is possible (but not part of the library).


#### Links

- https://github.com/RobTillaart/TOPMAX
- https://github.com/RobTillaart/TOPMIN
- https://github.com/RobTillaart/runningAverage
- https://github.com/RobTillaart/MINMAX


## Interface

```cpp
#include "TOPMIN.h"
```

#### TOPMIN

- **TOPMIN(uint8_t size = 5)** Constructor, defines the number of elements it can hold.
Default number of elements is 5. If **size** < 3 it will be set to 3.
The maximum size is currently 255.
- **uint8_t count()** returns the number of elements in the internal array. 0.. size.
- **uint8_t size()** returns the maximum number of elements in the internal array. 
- **void reset()** reset the internal counter to 0, logical clearing of the system.
- **bool add(float value)** add a value to the TOPMIN object to check of it needs to be 
in the top N of minima.
- **float getValue(uint8_t index)** get an element of the internal array.
The index must be <= **count()**, if not the function currently returns **NaN**.
This may or may not be a valid value, so the user should guard the **index** parameter carefully.
- **bool fill(float value)** convenience function to fill the internal array 
with a single value e.g. 0.


#### TOPMINext

Derived from TOPMIN, extended with a tag field.

- **TOPMINext(uint8_t size = 5)** Constructor, defines the number of elements it can hold.
Default number of elements is 5. If **size** < 3 it will be set to 3.
The maximum size is currently 255.
- **bool add(float value, uint32_t tag)** add a value to the TOPMINext object to check if
it needs to be in the top N of minima. If so add the 32-bit **tag** too (at same index).
The 32-bit **tag** is typical an index, counter or timestamp, but any semantic is possible.
- **uint32_t getTag(uint8_t index)** get the tag from an element of the internal array.
The index must be <= **count()**, if not the function currently returns **0xFFFFFFFF**.
This may or may not be a valid value, so the user should guard the **index** parameter carefully.
- **bool fill(float value, uint32_t tag)** convenience function to fill the internal array 
with a single value e.g. 0. (tag idem).


# Future

#### Must

- keep functional in sync with TOPMAX.
- improve documentation.
- 0.2.0 
  - reverse **getValue() / getTag()** be
  - index = 0 must be the absolute minima (maxima).
  - if you change size of TOPMIN object the "winner" gets a different index
  - better would be to have to reverse ```index = count() - index```
  - then less code adaptions are needed. 

#### Should

- add unit tests.
  - for the TOPMINext version if possible
- add more examples.
  - example creative use of tag field.
  - example performance measurements (depends on size + inserted values).
    (Marsaglia PRNG, to be repeatable over platforms).

#### Could

- create template class.
- **bool check(float value)** and **bool check(float value, uint32_t tag)**
  - if (value < getValue(0)) or so.
  - checks if this value would be added to the TOP-N
- **TOP** class, in which the condition can be set as parameter.
  - a function() returning true or false when comparing 2 values. 



#### Wont

- how to handle double/triple etc. entries with same value
  - they are handled as unique elements, that is what I had in mind.
