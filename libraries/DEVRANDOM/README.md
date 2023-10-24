
[![Arduino CI](https://github.com/RobTillaart/DEVRANDOM/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DEVRANDOM/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DEVRANDOM/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DEVRANDOM/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DEVRANDOM/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DEVRANDOM.svg)](https://github.com/RobTillaart/DEVRANDOM/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DEVRANDOM/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DEVRANDOM.svg?maxAge=3600)](https://github.com/RobTillaart/DEVRANDOM/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DEVRANDOM.svg)](https://registry.platformio.org/libraries/robtillaart/DEVRANDOM)


# DEVRANDOM

Arduino library to wrap a random generator in a stream.


## Description

The library implements a stream class that mimics the /dev/random
device of a Linux system. It can be used for testing with streams.


#### Related

- https://github.com/RobTillaart/DEVFULL
- https://github.com/RobTillaart/DEVNULL
- https://github.com/RobTillaart/DEVRANDOM


## Interface

```cpp
#include "DEVRANDOM.h"
```

### Constructor

- **DEVRANDOM()** Constructor.
- **DEVRANDOM(char \* str)** Constructor, seeding with a string of characters.
- **DEVRANDOM(uint32_t value)** Constructor, seeding with a integer value.
- **DEVRANDOM(float value)** Constructor, seeding with a float value.


### Streeam interface

To read and to reseed the random generator.

- **int available()** There is always 1 next byte available.
- **int peek()** will give you next byte.
- **int read()** will give you next byte and generate a new one.
- **size_t write(uint8_t data)** data will be used for reseeding the random number generator (RNG), mode 0 and 3.
In digitalRead and analogRead mode the seed is used to XOR
the value, so it does have some effect.
- **size_t write(uint8_t \* buffer, size_t size)** speeds up reseeding 
for some print / println calls.
- **void flush()** to keep the CI happy.

As **write()** reseeds the RNG, printing to **DEVRANDOM** will also reseed the RNG. 
E.g. **dr.println("Hello world");** or **dr.println(3.45678);** will reseed DEVRANDOM too.
See examples.

If footprint is an issue one could remove the **size_t write(uint8_t \* buffer, size_t size)**
from the library and implement a stripped version in **write()**.
Reseeding will become slower but as reseeding is not used that often
this might be a good trade off.


### Random generator selection

- **void useRandom()** use the build in software random number generator. This is the default, but platform dependant.
- **void useDigitalRead(uint8_t pin)** use digitalRead to read 8 bits from a defined pin.
One can build a hardware RNG that flips between 0 and 1 very rapidly and unpredictably.
Connect this signal to the pin and it will be read and generate a random byte.
The seed value from the write is used as an XOR byte.
- **void useAnalogRead(uint8_t pin)** use the analogRead to read 8 bits
This can be fed with any analogue noise source.
The seed value from the write is used as a XOR byte.
- **void useMarsaglia()** uses the Marsaglia pseudo random generator.
This one is quite fast and good, and more important portable.
- **uint8_t getMode()** returns the source of randomness.

|  Mode   |  DEVRANDOM_MODE  | Type                   |
|:-------:|:----------------:|:-----------------------|
|    0    | build in random  | depends on platform    |
|    1    | digitalRead      | hardware external      |
|    2    | analogRead       | hardware external      |
|    3    | Marsaglia        | software portable PRNG |


There might be other RNG's in the future. 
If you have an interesting and fast PRNG to be included please let me know. 


### Obsolete

- **useSW()** replaced by **useRandom()**. 
- **useHW(uint8_t pin)** replaced by **useDigitalRead()**.
- **useAR(uint8_t pin)** replaced by **useAnalogRead()**.


## Operation

See example sketches.


### Example

As shown in the example one can use fscanf() to read larger data types, 

```cpp
  DEVRANDOM dr;
  uint32_t x;
  fscanf((FILE*) &dr, "%lu", &x);
  Serial.println(x);
```

However float is not supported standard in the fscanf() by UNO and strings (%s) generate garbage.
So a password generator is a bit more difficult (and a good exercise).


## Future

#### Must

- improve documentation.

#### Should

#### Could

- add examples.
- add other (portable) PRNG.
- **available()** returns 1, 
  - should that be more e.g. INT_MAX
  - a random number > 0 ?
  - ?
- when changing mode should \_next == **peek()** be reset?
  - yes, think so ```_next = _rnd();```
  - when already in that mode? (=> complex)

#### Wont

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

