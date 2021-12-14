
[![Arduino CI](https://github.com/RobTillaart/CRC/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CRC/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CRC/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CRC/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CRC/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CRC/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CRC.svg?maxAge=3600)](https://github.com/RobTillaart/CRC/releases)


# CRC

Arduino library with CRC8, CRC16, CRC32 and CRC64 functions.


## Description

Goal of this library is to have a flexible and portable set of generic 
CRC functions and classes.

The CRCx classes have a number of added values. Most important is that 
they allow one to verify intermediate CRC values. This is useful if one 
sends a "train of packets" which include a CRC so far. This detects both 
errors in one packet but also missing packets, or injected packages.

Another trick one can do is change the polynome or the reverse flag during 
the process. This makes it harder to imitate.

Furthermore the class allows to add values in single steps and continue too.

Finally the class version gives more readable code (imho) as the parameters 
are explicitly set.


**Note** the classes have same names as the static functions, except the class
is UPPER case. So CRC8 is a class and **crc8()** is the function. 

Deeper tech info -https://en.wikipedia.org/wiki/Cyclic_redundancy_check
and many other websites.


## Interface CRC classes

These interfaces are very similar for CRC8, CRC16, CRC32 and CRC64 class.
The only difference is the data type for polynome, start- and end-mask, 
and the returned CRC.

Use **\#include "CRC8.h"**

- **CRC8()** Constructor
- **void reset()** set all internals to constructor defaults.
- **void restart()** reset internal CRC and count only;  reuse values for other 
e.g polynome, XOR masks and reverse flags.
- **void setPolynome(polynome)** set polynome, note reset sets a default polynome.
- **void setStartXOR(start)** set start-mask, default 0.
- **void setEndXOR(end)** set end-mask, default 0.
- **void setReverseIn(bool reverseIn)** reverse the bit pattern of input data (MSB vs LSB).
- **void setReverseOut(bool reverseOut)** reverse the bit pattern of CRC (MSB vs LSB).
- **void add(value)** add a single value to CRC calculation.
- **void add(array, uint32_t length)** add an array of values to the CRC. 
In case of a warning/error use casting to (uint8_t \*).
- **uint8_t getCRC()** returns CRC calculated so far. This allows to check the CRC of 
a really large stream at intermediate moments, e.g. to link multiple packets.
- **uint32_t count()** returns number of values added so far. Default 0.


### Example snippet

A minimal usage only needs: 
- the constructor, the add() function and the getCRC() function.

```cpp
#include "CRC32.h"
...

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
In all the examples encountered the reverse flags were set both to false or both to true. 
For flexibility both parameters are kept available. 

- **uint8_t crc8(array, length, polynome = 0xD5, start = 0, end = 0, reverseIn = false, reverseOut = false)** idem with default polynome.
- **uint16_t crc16(array, length, polynome = 0xA001, start = 0, end = 0, reverseIn = false, reverseOut = false)** idem with default polynome.
- **uint16_t crc16-CCITT(array, length)** fixed polynome **0x1021**, non zero start / end masks.
- **uint32_t crc32(array, length, polynome = 0x04C11DB7, start = 0, end = 0, reverseIn = false, reverseOut = false)** idem with default polynome.
- **uint64_t crc64(array, length, polynome, start, end, reverseIn, reverseOut)** - experimental version, no reference found except on Wikipedia.

Note these functions are limited to one call per block of data. For more flexibility use the classes.


## Operational

See examples.


## Links 

- https://en.wikipedia.org/wiki/Cyclic_redundancy_check - generic background.
- https://crccalc.com/ - online CRC calculator to verify.


## Future

- extend examples.
- table versions for performance?  (performance - memory discussion)
- example showing multiple packages of data linked by their CRC.
- stream version - 4 classes class?
- setCRC(value) to be able to pick up where one left ?
- getters, getPolynome() etc?
- 


#### Exotic CRC's ?

- **CRC1()** // parity :)
- **CRC4(array, length, polynome, start, end, reverseIn, reverseOut)** nibbles?
  - default polynome 0x03


#### Magic \#defines for "common" polynomes? verify ?

  - \#define CRC_ISO64  0x000000000000001B
  - \#define CRC_ECMA64 0x42F0E1EBA9EA3693

