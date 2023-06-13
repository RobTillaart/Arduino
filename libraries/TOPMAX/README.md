
[![Arduino CI](https://github.com/RobTillaart/TOPMAX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TOPMAX/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TOPMAX/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TOPMAX/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TOPMAX/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TOPMAX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TOPMAX.svg?maxAge=3600)](https://github.com/RobTillaart/TOPMAX/releases)


# TOPMAX

Arduino library to track the top N maxima.

## Description

This experimental library tracks the top N maxima of a series of values. 

The library implements two classes:
- **TOPMAX** just tracks the values. (smaller footprint).
- **TOPMAXext** also tracks a user defined 32-bit tag (e.g. timestamp).

The latter is more useful as it allows to link the top N values to a certain time
or day, an index in a database, or another indirect reference.
It can even be used to store a second parameter e.g. what was the humidity for
the top N temperatures.

The library can be used for different applications:
- track top N peak temperature / humidity over a given period of time.
- track top N UV peak intensity during the day.
- track top N trading volumes or $$.
- track top N largest fish caught in a contest.
- track top N number of visitors during a day.
- track top N of time-outs, e.g. to monitor production loss. 

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
#include "TOPMAX.h"
```

#### TOPMAX

- **TOPMAX(uint8_t size = 5)** Constructor, defines the number of elements it can hold.
Default number of elements is 5. If **size** < 3 it will be set to 3.
The maximum size is currently 255.
- **uint8_t count()** returns the number of elements in the internal array. 0.. size.
- **uint8_t size()** returns the maximum number of elements in the internal array. 
- **void reset()** reset the internal counter to 0, logical clearing of the system.
- **bool add(float value)** add a value to the TOPMAX object to check of it needs to be 
in the top N of maxima.
- **float getValue(uint8_t index)** get an element of the internal array.
The index must be <= **count()**, if not the function currently returns **NaN**.
This may or may not be a valid value, so the user should guard the **index** parameter carefully.
- **bool fill(float value)** convenience function to fill the internal array 
with a single value e.g. 0.


#### TOPMAXext

Derived from TOPMAX, extended with a tag field.

- **TOPMAXext(uint8_t size = 5)** Constructor, defines the number of elements it can hold.
Default number of elements is 5. If **size** < 3 it will be set to 3.
The maximum size is currently 255.
- **bool add(float value, uint32_t tag)** add a value to the TOPMAXext object to check if
it needs to be in the top N of maxima. If so add the 32-bit **tag** too (at same index).
The 32-bit **tag** is typical an index, counter or timestamp, but any semantic is possible.
- **uint32_t getTag(uint8_t index)** get the tag from an element of the internal array.
The index must be <= **count()**, if not the function currently returns **0xFFFFFFFF**.
This may or may not be a valid value, so the user should guard the **index** parameter carefully.
- **bool fill(float value, uint32_t tag)** convenience function to fill the internal array 
with a single value e.g. 0. (tag idem).


# Future

#### Must

- keep functional in sync with TOPMIN.
- improve documentation.

#### Should

- add unit tests.
- add more examples.
- add performance measurements.
  - depends on size / and inserted values.

#### Could

- create template class.

#### Wont

