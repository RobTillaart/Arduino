
[![Arduino CI](https://github.com/RobTillaart/UUID/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/UUID/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/UUID/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/UUID/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/UUID/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/UUID/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/UUID.svg?maxAge=3600)](https://github.com/RobTillaart/UUID/releases)


# UUID

Arduino library for generating UUID strings.


## Description

This **experimental** library provides a UUID generator.
A UUID is an Universally Unique IDentifier of 128 bits.
These are typically written in the following format, defined in RFC-4122.

```
    0ac82d02-002b-4ccb-b96c-1c7839cbc4c0
                  ^    ^
```

The length is 32 hexadecimal digits + four hyphens = 36 characters.
Note that the hexadecimal digits are lower case.

The 0.1.1 version of the lib tries to follow the RFC-4122, 
for version 4 (random generated) and variant 1.
In the format above the version 4 is indicated by the first arrow and must be 4.
The variant 1 is at the position of the second arrow. 
This nibble must be 8, 9, A or B.
All the remaining bits are random.

The basis for the UUID class is a Marsaglia pseudo random number generator.
This PRNG must be seeded with two real random uint32_t to get real random UUID's.
Regular reseeding with external entropy improves randomness.

Often one sees also the term GUID = Globally Unique Identifier.

Tested on Arduino UNO only.

- https://en.wikipedia.org/wiki/Universally_unique_identifier
- https://www.ietf.org/rfc/rfc4122.txt


## Interface


### UUID class

Use **\#include "UUID.h"**

The UUID class has only a few methods.

- **UUID()** Constructor, initializes internals an generates a default UUID.
- **void seed(uint32_t s1, uint32_t s2 = 0)** reseeds the internal 
pseudo random number generator.
It is mandatory to set s1 while s2 is optional.
The combination {0, 0} is not allowed and overruled in software.
- **void generate()** generates a new UUID depending on the mode.
  - **UUID_MODE_RANDOM**: all UUID bits are random.
  - **UUID_MODE_VARIANT4**: the UUID (tries to) conform to version 4 variant 1. See above.
- **char \* toCharArray()** returns a pointer to a char buffer 
representing the last generated UUID. 
Multiple subsequent calls to **toCharArray()** gives the same UUID 
until **generate()** is called again.


### Mode

Only two modi are supported. Default is the **UUID_MODE_VARIANT4**.
This is conform RFC-4122.

- **void setVariant4Mode()** set mode to **UUID_MODE_VARIANT4**.
- **void setRandomMode()** set mode to **UUID_MODE_RANDOM**.
- **uint8_t getMode()** returns mode set.


### Printable 

The UUID class implements the printable interface.
This allows one to print the UUID object directly over Serial and any other
stream implementing the Print interface. Think Ethernet or SD card. 

```cpp
UUID uuid;

Serial.println(uuid);

// gives same output as

Serial.println(uuid.toCharArray());
```


## Performance

Not tested ESP32 (and many other platforms) yet.

Performance measured with **UUID_test.ino** shows the following times:


#### microseconds per byte

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
|           |               |              |                 |
|   0.1.4   |  seed         |      4 us    |       3 us      |
|   0.1.4   |  generate     |    120 us    |      14 us      |
|   0.1.4   |  toCharArray  |      4 us    |       0 us      |

Note: generating the 16 random bytes already takes ~40 us (UNO).


#### UUID's per second

indicative maximum performance (see example sketch)

|  Version  |  UNO 16 MHz  |  ESP32 240 MHz  |  notes      |
|:---------:|:------------:|:---------------:|:-----------:|
|   0.1.0   |    2000++    |                 |  both modi  |
|   0.1.1   |    4000++    |                 |  both modi  |
|   0.1.2   |    6400++    |                 |  both modi  |
|   0.1.3   |    8200++    |                 |  both modi  |
|           |              |                 |             |
|   0.1.4   |    8268      |     31970       |  VARIANT4   |
|   0.1.4   |    8418      |     34687       |  RANDOM     |


Note that these maxima are not realistic e.g. for a server.
Other tasks need to be done too (listening, transfer etc.).


## Operation

See examples.


## Future

### General

- improve documentation
  - external random input needed
  - background
- test other platforms
- investigate entropy harvesting
  - freeRAM, micros, timers, RAM, USB-ID, ...
  - compile constants __DATE__ and __TIME__
  - see example
- GUID as derived class?
  - (further identical?)


### Functions

- add **setUpperCase()** and **setLowerCase()**, **isUpperCase()**
  - one bool flag
- binary output in a byte array
  - **getBinary(uint8_t \* array)**
  - need to store them from generate.  


### Examples

- ESP32 UUID server 
  - using timing of the calls as entropy !
- RTC for entropy
- EEPROM to store last seeds?

### Fixes / optimizations

- reduce footprint
  - can the buffer be reduced?
  - smaller random generator?
- move code to .h so compiler can optimize more?

### Won't

- support for { and }
- add **setSeparator(char)** and **getSeparator()** ?  
  - minus is the specification.


