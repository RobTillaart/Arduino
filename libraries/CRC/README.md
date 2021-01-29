
[![Arduino CI](https://github.com/RobTillaart/CRC/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CRC/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CRC.svg?maxAge=3600)](https://github.com/RobTillaart/CRC/releases)


# CRC

Arduino library with CRC8, CRC16, CRC32 and CRC64 functions


## Description

Implements the generic CRC functions and classes.

The added value of the CRCx class is that it allows one to see intermediate CRC values calculated so far, but also 


Goal of this library is to have a flexible and portable set of functions.

**Note** the classes have same names as the static functions, except the class
is UPPER case. So CRC8 is a class and **crc8()** is the function. 

Deeper tech info -https://en.wikipedia.org/wiki/Cyclic_redundancy_check
and many other websites.


## Interface CRC classes

These interfaces are very similar for CRC8, CRC16, CRC32 and CRC64 class.
The only difference is the datatype for polynome, start- and endmask, and the returned CRC.

Use **\#include "CRC8.h"**

- **CRC8()** Constructor
- **void reset()** set all internals to constructor defaults.
- **void restart()** reset CRC and count;  use same parameters again.
- **void setPolynome(polynome)** set polynome, reset sets a default polynome.
- **void setStartXOR(start)** set startmask, default 0.
- **void setEndXOR(end)** set endmask, default 0.
- **void setReverseIn(bool reverseIn)** reverse the bitpattern of input data (MSB vs LSB).
- **void setReverseOut(bool reverseOut)** reverse the bitpattern of CRC (MSB vs LSB).
- **void add(value)** add a single value to CRC calculation.
- **void add(array, uint32_t length)** add an array of values to the CRC. In case of a warning/error use casting to (uint8_t \*).
- **uint8_t getCRC()** returns CRC calculated so far. This allows to check the CRC of a really large stream at intermediate moments, e.g. to link multiple packets.
- **uint32_t count()** returns number of values added sofar. Default 0.


### Example snippet

A minimal usage only needs 
- the constructor, the add() function and the getCRC() function.

```cpp
CRC32 crc;
  ...
  while (Serial.available())
  {
    int c = Serial.read();
    crc.add(c);
  }
  Serial.println(crc.getCRC());
```


## Interface static functions

Use **\#include "CRC.h"**

Most functions have a default polynome, same start and end masks, and default there is no reversing.
However these parameters allow one to tweak the CRC in all aspects known. 
In all the examples encountered the reverseflags were set both to false or both to true. 
For flexibility both parameters are kept available. 

- **uint8_t crc8(array, length, polynome = 0xD5, start = 0, end = 0, reverseIn = false, reverseOut = false)** idem with default polynome
- **uint16_t crc16(array, length, polynome = 0xA001, start = 0, end = 0, reverseIn = false, reverseOut = false)** idem with default polynome
- **uint16_t crc16-CCITT(array, length)** fixed polynome **0x1021**, non zero start / end masks.
- **uint32_t crc32(array, length, polynome = 0x04C11DB7, start = 0, end = 0, reverseIn = false, reverseOut = false)** idem with default polynome
- **uint64_t crc64(array, length, polynome, start, end, reverseIn, reverseOut)** - experimental version, no reference found except on Wikipedia 

Note these functions are limited to one call per block of data. For more flexibility use the classes.


## Future

- extend examples.
- table versions for performance?  (performance - memory discussion)
- example showing multiple packages of data linked by their CRC.
- stream version - 4 classes class?


#### Exotic CRC's ?

- **CRC1()** // parity :)
- **CRC4(array, length, polynome, start, end, reverseIn, reverseOut)**
  - default polynome 0x03


#### Magic \#defines for "common" polynomes? ?

  - \#define CRC_ISO64  0x000000000000001B
  - \#define CRC_ECMA64 0x42F0E1EBA9EA3693


## Operational

See examples.
