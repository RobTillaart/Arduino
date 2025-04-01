
[![Arduino CI](https://github.com/RobTillaart/UUID/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/UUID/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/UUID/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/UUID/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/UUID/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/UUID.svg)](https://github.com/RobTillaart/UUID/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/UUID/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/UUID.svg?maxAge=3600)](https://github.com/RobTillaart/UUID/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/UUID.svg)](https://registry.platformio.org/libraries/robtillaart/UUID)


# UUID

Arduino library for generating UUID strings.


## Description

This library provides an **UUID** generator class.
An **UUID** is an Universally Unique IDentifier of 128 bits.
These are typically written in the following format, defined in **RFC-4122/9562**.

```
    0ac82d02-002b-4ccb-b96c-1c7839cbc4c0
                  ^    ^
```

The length is 32 hexadecimal digits + four hyphens = 36 characters.
Note that the hexadecimal digits are all lower case (by specification).
The user may convert this to upper case if needed.

The 0.1.1 version of the lib tries to follow the **RFC-4122** 
for version 4 (random generated) and variant 1.
In the format above the version 4 is indicated by the first arrow (position 14) and must be 4.
The variant 1 is at the position of the second arrow (position 19).
This nibble must be 8, 9, A or B.
All the remaining bits are random.

The basis for the **UUID** class is a Marsaglia pseudo random number generator (PRNG).
Note: This PRNG must be seeded with two real random uint32_t to get real random UUID's.
Regular reseeding with external entropy improves randomness.
Default the class will generate different sequences of UUID's as it uses the a mix of 
compile time and runtime generated seeds. 
One can overrule the default seed with fixed values to generate a known sequence as 
this is useful for testing.

Tested on Arduino UNO + ESP32.

Feedback as always is welcome.


### Breaking change in 0.2.0

The 0.2.0 version and up will be based upon **RFC-9562** as RFC-4122 is obsolete.

The setVariant4Mode() is deprecated, use **setVersion4Mode()** instead.
The return value of getMode is now more logical as version4 == 4, instead of 0.

The default behaviour is changed to have different sequences per instance based 
upon a mix of compile and runtime time generated seeds.


### GUID

Often one sees also the term **GUID** = Globally Unique Identifier.
Since 0.2.0 this library has a **GUID** derived class which is just a wrapper 
around UUID for now.


### Related

- https://en.wikipedia.org/wiki/Universally_unique_identifier
- https://www.ietf.org/rfc/rfc4122.txt (obsolete)
- https://www.ietf.org/rfc/rfc9562
- https://datatracker.ietf.org/doc/html/rfc9562 (html)
- https://github.com/RobTillaart/UUID  (this library)
- https://github.com/RobTillaart/randomHelpers

UUID is also available as ESP32 component (Kudos to KOIO5)

- https://github.com/K0I05/ESP32-S3_ESP-IDF_COMPONENTS/tree/main/components/utilities/esp_uuid


### UUID versions (OSF DCE).

Minimized summary of Wikipedia, details see RFC-9562, just a backgrounder.

- Version 1 is based upon the MAC address of the generating node (or random bits
with the multicast bit set to 1) followed by a timestamp since midnight 15 October 1582.
This date the Gregorian calendar started.
- Version 2 is reserved for DCE security and looks similar to 1 but have some drawbacks.
- Version 3 hashes a namespace using MD5. (the RFC's recommend to use version 5 instead.)
- Version 4 is using random bits == this UUID class, implements variant 1 of version 4.
This variant 1 sets the variant bits to 10 resulting in nibble (8,9,a,b)
Variant 2 has one extra bit hard set and equals legacy GUID's, therefore it only 
implements half of the variant 1 UUID's, in practice obsolete.
- Version 5 hashes a namespace using SHA1. Is very similar to version 3.
- Version 6 is similar to version 1, except the timestamp parts are MSB to LSB
which allows "generation time sorting" of the UUID's.
- Version 7 uses a timestamp since 1 jan 1970 (UNIX Epoch) followed by random bits.
It is typically used in databases. 
- Version 8 is custom, with the variant bits set to 10, the bits follow vendor specific
rules so they may encode anything or being random. 


The UUID class only implements version 4, variant 1. 
The **UUID_MODE_RANDOM** of this UUID class is not one of the 8 official 
versions. It is not even version 8. 

Interesting could be a version 8 that would have a node unique part (like 1 and 6) 
based upon the unique address of an **DS18B20** temperature sensor.
The other ~80 bits are just a sequence. Problem is to store the last number used.
Or they may be randomized, no persistent storage needed.

Also interesting IMHO is the time sorting of version 6, although I do not know 
of any application in Arduino context.


## Interface

```cpp
#include "UUID.h"
```

### Constructor

The UUID class has only a few methods.

- **UUID()** Constructor, initializes internals based upon a hash of the FILE, DATE and TIME
compile parameters, combined with the **micros()** timestamp. 
Thereafter it generates a first UUID.
This gives a different sequence of UUID's if the same code is recompiled, or when the
UUID constructor is called in a loop or function.
- **void seed(uint32_t s1, uint32_t s2 = 0)** reseeds the internal PRNG,
pseudo random number generator.
This allows to force the same / identical sequences to be generated. 
This is usable for testing and for specific applications.
Note it is mandatory to set **s1** while setting **s2** is optional.
The combination {0, 0} is not allowed and overruled by (1, 2) in software.


### Generate 

- **void generate()** generates a new UUID depending on the mode.
  - **UUID_MODE_RANDOM**: all UUID bits are random.
  - **UUID_MODE_VERSION4**: the UUID (tries to) conform to version 4 variant 1. See above. This is the default.
- **char \* toCharArray()** returns a pointer to a char buffer 
representing the last generated UUID. 
Multiple subsequent calls to **toCharArray()** will return the **same UUID**
until **generate()** is called again.

The RFC-9562 and Wikipedia tells about up to OSF DCE standard, which defines
eight versions to the standard. Historically there are even more.
The version is encoded in the version nibble 14. 


### Mode

Only two modi are supported, default is the **UUID_MODE_VERSION4**.
This is conform RFC-4122.

- **void setVersion4Mode()** set mode to **UUID_MODE_VERSION4** (== 4).
- **void setRandomMode()** set mode to **UUID_MODE_RANDOM** (== 0).
- **uint8_t getMode()** returns mode set, note these numbers have changed in 0.2.0


### Printable 

The UUID class implements the Printable interface.
This allows one to print the UUID object directly over Serial and any other
stream implementing the Print interface. Think Ethernet or SD card. 

```cpp
UUID uuid;

Serial.println(uuid);

//  gives same output as

Serial.println(uuid.toCharArray());
```


## Performance

### microSeconds per function call

Indicative performance per function measured with **UUID_test.ino**.

|  Version  |   Function    |  UNO 16 MHz  |  ESP32 240 MHz  |
|:---------:|:--------------|:------------:|:---------------:|
|   0.1.0   |  seed         |      4 us    |                 |
|   0.1.0   |  generate     |    412 us    |                 |
|   0.1.0   |  toCharArray  |      4 us    |                 |
|   0.1.1   |  seed         |      4 us    |                 |
|   0.1.1   |  generate     |    248 us    |                 |
|   0.1.1   |  toCharArray  |      4 us    |                 |
|   0.1.2   |  generate     |    156 us    |                 |
|   0.1.3   |  generate     |    120 us    |                 |
|   -       |  -            |              |                 |
|   0.1.4   |  seed         |      4 us    |       3 us      |
|   0.1.4   |  generate     |    120 us    |      14 us      |
|   0.1.4   |  toCharArray  |      4 us    |       0 us      |
|   0.1.5   |  seed         |      4 us    |       4 us      |
|   0.1.5   |  generate     |    120 us    |      15 us      |
|   0.1.5   |  toCharArray  |      4 us    |       1 us      |
|   -       |  -            |              |                 |
|   0.2.0   |  seed         |      4 us    |       5 us      |
|   0.2.0   |  generate     |    120 us    |      13 us      |
|   0.2.0   |  toCharArray  |      4 us    |       2 us      |

Note: generating the 16 random bytes already takes ~40 us (UNO).


### UUID's per second

Indicative maximum performance figures in UUID's per second, 
measured by UUID_performance.ino.
Note that 0.2.0 has become faster, especially for ESP32.

|  Version  |  mode       |  UNO 16 MHz  |  ESP32 240 MHz  |
|:---------:|:-----------:|:------------:|:---------------:|
|   0.1.0   |  both modi  |    2000++    |                 |
|   0.1.1   |  both modi  |    4000++    |                 |
|   0.1.2   |  both modi  |    6400++    |                 |
|   0.1.3   |  both modi  |    8200++    |                 |
|           |             |              |                 |
|   0.1.4   |  VARIANT4   |    8268      |     31970       |
|   0.1.4   |  RANDOM     |    8418      |     34687       |
|   0.1.5   |  VARIANT4   |    8268      |     31969       |
|   0.1.5   |  RANDOM     |    8418      |     34689       |
|           |             |              |                 |
|   0.2.0   |  VERSION4   |    8540      |     46662       |
|   0.2.0   |  RANDOM     |    8703      |     49931       |

Note that these maxima are not realistic e.g. for a server.
Other tasks need to be done too (listening, transfer etc.).

Note VARIANT4 is renamed to VERSION4 (0.2.0)

Performance on other boards welcome.


## Future

#### Must

- improve documentation
  - background
- test other platforms


#### Should

- investigate RFC-9562, for more variants.
  - versions 7 and 8 could be interesting.
  - replace VARIANT with VERSION to conform RFC-9562 naming 
    - setVersion0Mode, setVersion4Mode, setVersion8Mode  (enum)
- investigate entropy harvesting
  - micros() between calls.
  - freeRAM, timers, RAM, USB-ID, ...
  - see example
- auto reseed function?
  - e.g. micros() between calls.
- investigate thread safety
  - toCharArray(char \* buffer)?


#### Could

- add examples
  - ESP32 UUID server => using timing of the calls as entropy !
  - RTC for entropy
  - EEPROM to store last seeds? (n)
- optimize
  - reduce footprint
  - buffer as static char in generate is ~2% faster on AVR
    (not shocking, impact ?)
  - smaller / faster random generator?
- toString() interface?


### Won't (unless)

- buffer can be reduced by packing 2 values into 1 byte,
  however this need unpack() in toCharArray() == performance penalty.
- support for { and }
- add **setSeparator(char)** and **getSeparator()** ?  
  - minus is specified in the RFC's.
- move code to .h so compiler can optimize more?
- **next()** add 1 to UUID to generate a continuous sequence ?
- binary output in a byte array
  - **getBinary(uint8_t \* array)**
  - need to store them from generate.  
- add **setUpperCase()** and **setLowerCase()**, **isUpperCase()**
  - one bool flag  (user can do this)
- derived class UUID_10 which only uses digits
  - use overflow / error propagation from one byte to next.
- derived class UUID_CH which uses 'g'..'v' 
  - same algorithm guaranteed disjunct set.
- add NULL-UUID as constant? 
- add MAX-UUID as constant?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

