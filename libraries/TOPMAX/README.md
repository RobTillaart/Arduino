
[![Arduino CI](https://github.com/RobTillaart/TOPMAX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TOPMAX/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TOPMAX/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TOPMAX/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TOPMAX/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TOPMAX.svg)](https://github.com/RobTillaart/TOPMAX/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TOPMAX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TOPMAX.svg?maxAge=3600)](https://github.com/RobTillaart/TOPMAX/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TOPMAX.svg)](https://registry.platformio.org/libraries/robtillaart/TOPMAX)


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


#### 0.2.0 breaking change

Since version 0.2.0 the maxima is found with **getValue(index == 0)**.
In earlier versions the maxima was found with **index == count()**.

The advantage of this change is that independent of the size of the TOPMAX
object the true maxima will always at index == 0. So if you change your code
and the size of the TOPMAX object, far less code needs to be changed. 
It also allows to have two or more TOPMAX objects of different size and use one 
index to access both.


#### Related

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
The maximum size is currently 255, or less if there is not enough memory.
- **uint8_t count()** returns the number of elements in the internal array. 0.. size.
- **uint8_t size()** returns the maximum number of elements in the internal array. 
- **void reset()** reset the internal counter to 0, logical clearing of the system.
- **bool add(float value)** add a value to the TOPMAX object if it is in the top N of maxima.
If so the smallest element is removed.
Returns false if not added or if there was an allocation error.
- **float getValue(uint8_t index)** get an element of the internal array.
The index must be <= **count()**, if not the function currently returns **NaN**.
This may or may not be a valid value, so the user should guard the **index** parameter carefully.
- **bool fill(float value)** convenience function to fill the internal array 
with a single value e.g. 0. Returns true on success.


#### TOPMAXext

Derived from TOPMAX, extended with a tag field.

- **TOPMAXext(uint8_t size = 5)** Constructor, defines the number of elements it can hold.
Default number of elements is 5. If **size** < 3 it will be set to 3.
The maximum size is currently 255, or less if there is not enough memory.
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

- improve documentation.
- keep TOPMIN and TOPMAX functional in sync.

#### Should

- add unit tests.
  - for extended version if possible.

#### Could

- add more examples.
  - example creative use of tag field.
- add error handling
  - TOP_ERR_ALLOCATION
  - TOP_ERR_INDEX
  - TOP_NOT_ADDED
  - TOP_OK
  - int error; **int lastError()**
- create template class.
- **bool check(float value)** and **bool check(float value, uint32_t tag)**
  - if (value < getValue(0)) or so.
  - **inRange(value)**
  - checks if this value would be added to the TOP-N
- **TOP** class, in which the condition can be set as parameter.
  - a function() returning true or false when comparing 2 values.
- **bool hasValue(float value)** and **bool hasTag(uint32_t tag)**
  - or **int getIndex(...)** duplicates?

#### Wont

- how to handle double/triple etc. entries with same value
  - they are handled as unique elements, that is what I had in mind.
- optimize loops in **fill()** (maybe upon request)
  - pointer math


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

