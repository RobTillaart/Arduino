
[![Arduino CI](https://github.com/RobTillaart/FRAM_I2C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FRAM_I2C.svg)](https://github.com/RobTillaart/FRAM_I2C/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FRAM_I2C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FRAM_I2C.svg?maxAge=3600)](https://github.com/RobTillaart/FRAM_I2C/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FRAM_I2C.svg)](https://registry.platformio.org/libraries/robtillaart/FRAM_I2C)


# FRAM_RINGBUFFER

Library for FRAM_RINGBUFFER to be used with the FRAM_I2C library.


## Description

**FRAM_RINGBUFFER** is a class that uses an FRAM object to implement 
a ring buffer that can be made persistent over reboots. 
The ring buffer can hold any size objects, but the user is responsible
to manage the contents. 
This means it can hold objects of different sizes, but the user should
add this size and/or type info into the object, or preceding every object.

The FRAM_RINGBUFFER is build upon the FRAM_I2C library so it is not 
expected to work with other FRAM libraries.

Types of FRAM that should work with this library:

|  TYPE      | SIZE   | TESTED |
|:----------:|-------:|:------:|
| MB85RC04   |   512  |        |
| MB85RC16   |   2 KB |        |
| MB85RC64T  |   8 KB |        |
| MB85RC128A |  16 KB |        |
| MB85RC256V |  32 KB |   Y    |
| MB85RC512T |  64 KB |        |
| MB85RC1MT  | 128 KB |        |

Please let me know if you have verified one that is not in the list.


#### Version

As the FRAM_RINGBUFFER is strongly connected to FRAM_I2C 
it has no separate version number.


## Interface

```cpp
#include "FRAM_RINGBUFFER.h"
```

### Administration

- **FRAM_RINGBUFFER()** Constructor.
- **uint32_t begin(FRAM \*fram, uint32_t size, uint32_t memAddr)** initializes 
the ring buffer. 
  - size is in bytes. 
  - memAddr is start memory address where ring buffer starts.
  - returns uint32_t == first free (next) FRAM location.
- **void flush()** resets the internal administration. 
  - Note: flush() does not wipe the content from FRAM.
- **uint32_t size()** returns size.
- **uint32_t count()** returns count == bytes used.
- **uint32_t free()** returns the number of bytes free.
- **float freePercent()** returns the number of bytes free as percentage.
- **bool full()** returns true if the ring buffer has no free bytes left.
- **bool empty()** returns true if the ring buffer has no data in it.


### Read / write (bytes)

- **int write(uint8_t value)** writes a byte to the ring buffer.
  - returns the number of bytes written (1) or **FRAM_RB_ERR_BUF_FULL**
- **int read()** returns a byte from the ring buffer.
  - returns **FRAM_RB_ERR_BUF_EMPTY** in case of an empty buffer.
- **int peek()** returns the next byte that would be read().
  - returns **FRAM_RB_ERR_BUF_EMPTY** in case of an empty buffer.


### Read / write (objects)

- **template <class T> int write(T &obj)** writes an object to the ring buffer.
  - returns the number of bytes written or **FRAM_RB_ERR_BUF_NO_ROOM**
  - see example how to use.
- **template <class T> int read(T &obj)** returns an object from the ring buffer.
  - returns bytes read or **FRAM_RB_ERR_BUF_NO_DATA** if the buffer has less 
    bytes than the object requested.
- **template <class T> int peek(T &obj)** returns the next object in the ring buffer.
  - returns bytes read or **FRAM_RB_ERR_BUF_NO_DATA** if the buffer has less 
    bytes than the object requested.


### Persistency

- **bool isSaved()** returns true if the administration of the ring buffer
is written to FRAM.
- **void save()** stores the internal administration + checksum to FRAM.
- **bool load()** retrieves the internal administration + checksum from FRAM.
  - returns true if checksum matches the stored variables. Only then the 
  variables of the ring buffer will be updated. 
- **void wipe()** removes all data from ring buffer by overwriting the FRAM.



### Error codes

|  value  |  description             |  Notes  |
|:-------:|:-------------------------|:--------|
|     0   |  FRAM_RB_OK              |
|    -1   |  FRAM_RB_ERR_BUF_FULL    |
|    -2   |  FRAM_RB_ERR_BUF_EMPTY   |
|   -21   |  FRAM_RB_ERR_BUF_NO_ROOM |  (almost) full
|   -22   |  FRAM_RB_ERR_BUF_NO_DATA |  (almost) empty


## Operational

See examples.

## Future

#### Must

#### Should

- elaborate FRAM_RINGBUFFER documentation
- add bool flag to **load(bool overrule = false)** to overrule the checksum verification.
  - default false.
- add bool flag to **wipe(bool all = true)** to overwrite all or the
  administration part only.


### Could

- example for a ring-buffer with different size objects
  - struct with size and type info.
  - preceding every object with type + size - 1..4 bytes 
- add debugging tooling
- add object count?
- create a RING_BUFFER class that can work with any type of storage.
  - SD card, EEPROM etc.

### wont

