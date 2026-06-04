
[![Arduino CI](https://github.com/RobTillaart/randomHelpers/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/randomHelpers/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/randomHelpers/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/randomHelpers/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/randomHelpers/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/randomHelpers.svg)](https://github.com/RobTillaart/randomHelpers/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/randomHelpers/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/randomHelpers.svg?maxAge=3600)](https://github.com/RobTillaart/randomHelpers/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/randomHelpers.svg)](https://registry.platformio.org/libraries/robtillaart/randomHelpers)


# randomHelpers

Arduino library for faster generation of random numbers.


## Description

This library contains functions that have the goal to deliver random bits faster
than the build in random function can, while still using it.

The idea is to have a buffer ( __randomBuffer) which can hold up to 32 bits.
When a number of random bits are needed, these are first fetched from the 
buffer and if the buffer gets empty, it is filled again with a call to the
random generator.

This strategy works well with a 32 bits buffer and requests for 1..16 random bits. 
However above 16 bits the overhead is larger than the gain. 
So to improve in that range too one could use a faster random function like the one 
from Marsaglia (included).

Note the gains differ per platform and are more explicit on the (slow) Arduino UNO 
platform than on a much faster ESP32.


### Related

- https://github.com/RobTillaart/DEVRANDOM
- https://github.com/RobTillaart/Prandom
- https://github.com/RobTillaart/randomHelpers
- http://www0.cs.ucl.ac.uk/staff/d.jones/GoodPracticeRNG.pdf - JKISS code


## Interface

```cpp
#include "randomHelpers.h"
```

### generators (sort of)

- **uint32_t Marsaglia()** fast PRNG.
- **bool seedMarsaglia(uint32_t a, uint32_t b)** seed the Marsaglia PRNG. a and b should not be 0. returns true on success.

### getters

- **bool getRandom1()** returns 0 or 1, false or true. 
- **uint8_t getRandom2()** returns 0 .. 3.
- **uint8_t getRandom3()** returns 0 .. 7.
- **uint8_t getRandom4()** returns 0 .. 15.
- **uint8_t getRandom5()** returns 0 .. 31.
- **uint8_t getRandom6()** returns 0 .. 63.
- **uint8_t getRandom7()** returns 0 .. 127.
- **uint8_t getRandom8()** returns 0 .. 255 typically a byte.
- **uint16_t getRandom9()** returns 0 .. 511 (2 bytes).
- **uint16_t getRandom10()** returns 0 .. 1023 (2 bytes).
- **uint16_t getRandom16()** returns 0 .. 65535 (2 bytes).
- **uint32_t getRandom24()** returns 0 .. 16777215  (3 bytes), e.g. random RGB colour.
- **uint32_t getRandom32()** returns 0 .. 2^32 - 1 (4 bytes) this is the core random generator
- **uint64_t getRandom64()** returns 0.. 2^64 - 1 (8 bytes).
- **uint32_t getRandomBits(n)** returns 0.. 2^n - 1  This works well for 1..16 bits but above 16 it is slower than the standard way. 


### Typical wrappers.

- **bool flipCoin()** A wrapper around getRandom1().
- **uint8_t throwDice()** returns 1..6.

The examples show how to use these and how their performance gain relative to
calling **random()** for every random number.


### Performance getRandom N bits

Output from randomHelpers_test.ino (UNO R3, 1.8.19, 0.2.8)

Times in micros over 10000 calls 

|  test              |  random  |  helper  |  ratio  |  notes  |
|:------------------:|:--------:|:--------:|:-------:|:-------:|
|  test_getRandom1   |  912024  |   34276  |  26.61  |
|  test_getRandom6   |  907848  |   80228  |  11.32  |
|  test_getRandom8   |  905072  |   60992  |  14.84  |
|  test_getRandom16  |  897320  |   92424  |   9.71  |
|  test_getRandom24  |  889948  |  133292  |   6.68  |
|  test_getRandom32  |  510464  |  132664  |   3.85  |
|  test_throwDice    |  912208  |  178988  |   5.10  |
|                    |          |          |         |


## JKISS

A first investigation showed JKISS was about 2x slower than Marsaglia.
So for now it will not be in this library.


## Fisher-Yates shuffle

Fast way to randomize elements of an array is this (modified) Fisher Yates.
This function uses Marsaglia() as RNG, and shuffles an array of length
in length steps.

- **template <typename T> T shuffleArrayFY(T \* arr, int length)**

```
float ar[10] = {0,1,2,3,4,5,6,7,8,9};
shuffleArrayFY <float> (ar, 10);
```

Output from randomHelpers_shuffleArray.ino (UNO R3, 1.8.19, 0.2.9)

Indicative times in micros over 1000 calls (array size 10)

|  test                          |   time   |  notes  |
|:------------------------------:|:--------:|:-------:|
| shuffleArrayFY<float>(ar, 10)  |  412224  |  RNG calls take ~90000 micros.
| shuffleArrayFY<int>(ar, 10)    |  397044  |
|                                |          |


## Future

#### Must

- wrap all up in a class (0.3.0)
  - rename getRandom64() ==> get64()  etc.
  - rename getRandomBits() ==> getN(uint8_t)  etc.
- improve/update documentation
  - add performance figures

#### Should

- improve performance **getRandomBits(n)** for n = 17..31
  - how to preserve bits if we have too few. 
  - Move them into new buffer until we have 32++? reseed?
  - performance penalty?
- test if the functions are uniform.

#### Could

- improve performance getRandomBits(n) for n = 17..31
- investigate new tricks :)

#### Wont (on request)

- RANDOM_HELPERS_LIB_VERSION?
- add JKISS and other RNG's
- add **getRandom11..16()** => 2x from 32 bits


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
