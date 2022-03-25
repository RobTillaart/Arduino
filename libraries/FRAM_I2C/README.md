
[![Arduino CI](https://github.com/RobTillaart/FRAM_I2C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FRAM_I2C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FRAM_I2C.svg?maxAge=3600)](https://github.com/RobTillaart/FRAM_I2C/releases)


# FRAM_I2C

Arduino library for I2C FRAM.


## Description

FRAM is a library to read from and write to (over I2C) an FRAM module.
FRAM is much faster than EEPROM and almost as fast as (Arduino UNO) RAM.
Another important feature it has in common with EEPROM is that FRAM keeps
its content after a reboot as it is non-volatile.
That makes it ideal to store configuration or logging
data in a project.

FRAM stands for Ferroelectric RAM - https://en.wikipedia.org/wiki/Ferroelectric_RAM

Types of FRAM the library should work with

|  TYPE      | SIZE   | TESTED | NOTES                |
|:----------:|-------:|:------:|:---------------------|
| MB85RC04   |   512  |        | no deviceID register |
| MB85RC16   |   2 KB |        | no deviceID register |
| MB85RC64T  |   8 KB |    Y   |
| MB85RC128A |  16 KB |        | no deviceID register |
| MB85RC256V |  32 KB |        |
| MB85RC512T |  64 KB |    Y   |
| MB85RC1MT  | 128 KB |        | 16 bit address problem? to be tested |

Notes
- Not all types of FRAM are tested. Please let me know if you have verified one.
- If there is no deviceID **getSize()** will not work correctly.

Address = 0x50 (default) .. 0x57, depends on the lines A0..A2.


## Interface


### Constructor

- **FRAM(TwoWire \*wire = &Wire)** Constructor with optional Wire interface.
- **int begin(uint8_t address = 0x50, int8_t writeProtectPin = -1)** address and writeProtectPin is optional.
- **int begin(uint8_t sda, uint8_t scl, uint8_t address = 0x50, int8_t writeProtectPin = -1)** idem for ESP32 a.o.
- **bool isConnected()** checks if the address is visible on the I2C bus.


### Write & read

Support for basic types and 2 calls for generic object, use casting if needed.

- **void write8(uint16_t memaddr, uint8_t value)** uint8_t
- **void write16(uint16_t memaddr, uint16_t value)** uint16_t
- **void write32(uint16_t memaddr, uint32_t value)** uint32_t
- **void write(uint16_t memaddr, uint8_t \* obj, uint16_t size)** other types / sizes.
- **uint8_t read8(uint16_t memaddr)**
- **uint16_t read16(uint16_t memaddr)**
- **uint32_t read32(uint16_t memaddr)**
- **void read(uint16_t memaddr, uint8_t uint8_t \* obj, uint16_t size)**
One needs to allocate memory as the function won't.

(0.3.4 added template functions, see issue #13 )
- **uint16_t writeObject(uint16_t memaddr, T &obj)** writes an object to memaddr (and following bytes). Returns memaddr + sizeof(obj) to get the next address to write to.
- **uint16_t readObject(uint16_t memaddr, T &obj)** reads an object from memaddr and next bytes. Returns memaddr + sizeof(obj) to get the next address to read from.

(0.3.5 added)
- **uint32_t clear(uint8_t value = 0)** clears the whole FRAM by writing value to all addresses - default zero's.
Returns the number of bytes written..


### Miscellaneous

- **bool setWriteProtect(bool b)** make the FRAM write-protected by pulling line HIGH / LOW.
Returns true if a writeProtectPin was defined.
Otherwise the FRAM cannot be write protected.  
Note the pin should be defined in **begin()**.
- **bool getWriteProtect()** get current write protect status.
- **uint16_t getManufacturerID()** idem. Fujitsu = 0x00A.
- **uint16_t getProductID()** idem. Proprietary.
- **uint16_t getSize()** returns size in kiloBYTE.
If the FRAM has no device ID, the size cannot be read.
- **uint32_t getSizeBytes()** returns size in BYTES.
Convenience wrapper, useful for iterating over the whole memory,
or testing the upper boundary.
- **void setSizeBytes(uint32_t value)** sets size in bytes for **getSizeBytes()**.
To be used only if **getSize()** cannot determine the size.
See also remark in Future section below. 



## Operational

 See examples


## Future

### high
- 32 bits addresses to support MB85RC1MT.
  - no explicit request yet (0.4.0)

### medium
- **write()** and **writeBlock()** might write beyond the end of FRAM
  - now it is responsibility user.
  - testing would degrade performance?
  - error flag ?
- extend examples
  - FRAM for multi language string storage
  - FRAM as linear buffer for a slow stream?
  - FRAM as ring buffer
  - FRAM logging, unequal length strings.
  - FRAM (8x) concatenated as one continuous memory.

### low
- test more types of FRAM
- **getSize()** scanning FRAM like EEPROM library?
- remember last written address? why?

### wont
- extend current **clear()** with partial **clear(begin, end, value)**?
  - can be done by **writeBlock()** calls by user too
  - would need more complex end checking
  - ==> wont for now
- **dump(stream)** or printable interface?
  - Print interface? expensive in performance per char..

