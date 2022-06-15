
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
These are typically written in the following format, defined in RFC 4122.

```
    0ac82d02-002b-4ccb-b96c-1c7839cbc4c0
                  ^    ^
```

The length is 32 hexadecimal digits + four hyphens = 36 characters.
Note that the hexadecimal digits are lower case.

The 0.1.1 version of the lib tries to follow the RFC4122, 
for version 4 (random generated) and variant 1.
In the format above the version 4 is indicated by the first arrow and must be 4.
The variant 1 is at the position of the second arrow. 
This nibble must be 8,9, a or b.
All the remaining bits are random.

The basis for the UUID class is a Marsaglia pseudo random number generator.
This PRNG must be seeded with two real random uint32_t to get real random UUID's.

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


| Version |  Function   | UNO 16 MHz | ESP32 240 MHz |
|:-------:|:------------|:----------:|:-------------:|
| 0.1.0   | seed        |      4 us  |               |
| 0.1.0   | generate    |    412 us  |               |
| 0.1.0   | toCharArray |      4 us  |               |
| 0.1.1   | seed        |      4 us  |               |
| 0.1.1   | generate    |    248 us  |               |
| 0.1.1   | toCharArray |      4 us  |               |
| 0.1.2   | generate    |    156 us  |               |



UUID's per second

| Version |  UNO 16 MHz  |  ESP32 240 MHz  | notes  |
|:-------:|:------------:|:---------------:|:------:|
| 0.1.0   |    2000++    |                 |
| 0.1.1   |    4000++    |                 | generate both modes
| 0.1.2   |    6400++    |                 | generate both modes


Note that this maximum is not realistic e.g. for a server where also
other tasks need to be done (listening, transfer etc).


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

### Won't

- support for { and }
- add **setSeparator(char)** and **getSeparator()** ?  
  - minus is the specification.


