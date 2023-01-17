
[![Arduino CI](https://github.com/RobTillaart/CRC/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CRC/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CRC/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CRC/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CRC/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CRC/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CRC.svg?maxAge=3600)](https://github.com/RobTillaart/CRC/releases)


# CRC

Arduino library with CRC8, CRC12, CRC16, CRC32 and CRC64 functions.


## Description

Goal of this library is to have a flexible and portable set of generic
CRC functions and classes.

The CRCx classes have a number of added values.
Most important is that they allow one to verify intermediate CRC values.
This is useful if one sends a "train of packets" which include a CRC so far.
This detects both errors in one single packet but also optional missing packets,
or even injected packets.

Another trick one can do with the class CRCx is to change the polynome or
the reverse flag runtime during the process. This makes it harder to imitate.

Furthermore the class allows to add values in single steps and continue too.

Finally the class version gives more readable code (IMHO) as the parameters
are explicitly set.


**Note** the classes have same names as the static functions, except the class
is UPPER case. So **CRC8** is a class and **crc8()** is the function.

Deeper tech info - https://en.wikipedia.org/wiki/Cyclic_redundancy_check
and many other websites.

#### Related

- https://github.com/RobTillaart/Adler
- https://github.com/RobTillaart/CRC
- https://github.com/RobTillaart/Fletcher
- https://github.com/RobTillaart/LUHN



## Interface CRC classes

The interfaces are very similar for CRC8, CRC12, CRC16, CRC32 and CRC64 class.
The only difference is the data type for polynome, start- and end-mask,
and the returned CRC.


#### Base

Use **\#include "CRC8.h"**

- **CRC8()** default - parameterless - constructor.
- **CRC8(polynome, XORstart, XORend, reverseIn, reverseOut)** Constructor to set all parameters at once.
- **void reset()** set all internals to defaults of the **CRC8()** parameterless constructor.
- **void restart()** reset internal CRC and count only;
reuse values for other e.g polynome, XOR masks and reverse flags.
- **void add(value)** add a single value to CRC calculation.
- **void add(array, uint16_t length)** add an array of values to the CRC.
In case of a warning/error for the array type, use casting to (uint8_t \*).
- **uint8_t getCRC()** returns CRC calculated so far. This allows to check the CRC of
a really large stream at intermediate moments, e.g. to link multiple packets.
- **uint32_t count()** returns number of values added so far. Default 0.


#### Parameters

The parameters do not have defaults so the user must set them explicitly.

- **void setPolynome(polynome)** set polynome, note reset sets a default polynome.
- **void setStartXOR(start)** set start-mask, default 0.
- **void setEndXOR(end)** set end-mask, default 0.
- **void setReverseIn(bool reverseIn)** reverse the bit pattern of input data (MSB vs LSB).
- **void setReverseOut(bool reverseOut)** reverse the bit pattern of CRC (MSB vs LSB).
- **uint8_t getPolyNome()** return parameter set above or default.
- **uint8_t getStartXOR()** return parameter set above or default.
- **uint8_t getEndXOR()** return parameter set above or default.
- **bool getReverseIn()** return parameter set above or default.
- **bool getReverseOut()** return parameter set above or default.


#### Power users only

As CRC calculations of large blocks can take serious time (in milliseconds),
the classes call **yield()** after every 256 **add()** calls to keep RTOS
environments happy.

The following two calls allows one to enable and disable these calls to
**yield()** to get optimal performance. The risk is missing context switching
to handle interrupts etc. So use at own risk.

- **void enableYield()** enables the calls to **yield()**.
- **void disableYield()** disables the calls to **yield()**.

_Note: the static functions in this library also call **yield()** but this
cannot be disabled (for now)._

_Note: a parameter could be a future option to set the number of adds before
**yield()** is called. **setYield(0)** would be disable it._


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
- **uint16_t crc12(array, length, polynome = 0x080D, start = 0, end = 0, reverseIn = false, reverseOut = false)** idem with default polynome.
- **uint16_t crc16(array, length, polynome = 0x8001, start = 0, end = 0, reverseIn = false, reverseOut = false)** idem with default polynome.
- **uint16_t crc16-CCITT(array, length)** fixed polynome **0x1021**, non zero start / end masks.
- **uint32_t crc32(array, length, polynome = 0x04C11DB7, start = 0, end = 0, reverseIn = false, reverseOut = false)** idem with default polynome.
- **uint64_t crc64(array, length, polynome = 0x42F0E1EBA9EA3693, start = 0, end = 0, reverseIn = false, reverseOut = false)** - experimental version, no reference found except on Wikipedia.

Note these functions are limited to one call per block of data.
These functions will call **yield()** every 256 bytes to keep RTOS happy.
For more flexibility use the specific classes.

The static CRC functions use fast reverse functions that can be also be
used outside CRC context. Their usage is straightforward.

- **uint8_t reverse8(uint8_t in)** idem.
- **uint16_t reverse16(uint16_t in)** idem.
- **uint16_t reverse12(uint16_t in)** idem.
- **uint32_t reverse32(uint32_t in)** idem.
- **uint64_t reverse64(uint64_t in)** idem.

Reverse12 is based upon reverse16, with a final shift.
Other reverses can be created in similar way.


## CRC_polynomes.h

Since version 0.2.1 the file CRC_polynomes.h is added to hold symbolic names for certain polynomes.
These can be used in your code too to minimize the number of "magic HEX codes".
If standard polynomes are missing, please open an issue and report, with reference.


## Operational

See examples.


## Links

- https://en.wikipedia.org/wiki/Cyclic_redundancy_check - generic background.
- http://zorc.breitbandkatze.de/crc.html - online CRC calculator (any base up to 64 is supported.)
- https://crccalc.com/ - online CRC calculator to verify.
- https://www.lddgo.net/en/encrypt/crc - online CRC calculator


## Future

#### Must


#### Should

- add examples.
  - example showing multiple packages of data linked by their CRC.
    sort of "blockchain"


#### Could

- table versions for performance?  (performance - memory discussion).
- stream version - 4 classes class?
- **setCRC(value)** to be able to pick up where one left ?
  - can be done with **setStartXOR()**
  - needs **getRawCRC()**  without reverse and end mask
- Think about default parameters for constructor **CRC8(polynome, XORstart, XORend, reverseIn, reverseOut)**
  - same as reset so constructors merge? Note the CRC-functions do have defaults too.


#### Exotic CRC's ?

- **CRC1()** // parity :)
- **CRC4(array, length, polynome, start, end, reverseIn, reverseOut)** nibbles?
  - default polynome 0x03  ITU
- One CRC() with #bits as parameter?
  - up to 64 bit for all missing ones?
  - performance penalty
- One CRC() template class?


#### Won't

- add a dump(Stream = Serial) to see all the settings at once.
  user can access parameters, so no need.


