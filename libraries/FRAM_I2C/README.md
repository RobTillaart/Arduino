
[![Arduino CI](https://github.com/RobTillaart/FRAM_I2C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FRAM_I2C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FRAM_I2C.svg?maxAge=3600)](https://github.com/RobTillaart/FRAM_I2C/releases)


# FRAM_I2C

Arduino library for I2C FRAM.


## Description

FRAM is a library to read from and write to (over I2C) an FRAM module.
FRAM is much faster than EEPROM and almost as fast as Arduino UNO RAM.
Another important feature it has in common with EEPROM is that FRAM keeps
its content after a reboot (non-volatile).

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
| MB85RC1MT  | 128 KB |        |

Notes
- Not all types are tested. Pleas let me know if you have verified one.
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


### Miscellaneous

- **bool setWriteProtect(bool b)** make the FRAM write-protected by pulling line HIGH / LOW.
Returns true if a writeProtectPin was defined.
Otherwise the FRAM  cannot be write protected.
- **bool getWriteProtect()** get current status.
- **uint16_t getManufacturerID()** idem. Fujitsu = 0x00A.
- **uint16_t getProductID()** idem. Proprietary.
- **uint16_t getSize()** returns size in kiloBYTE.
If the FRAM has no device ID, the size cannot be read.
- **uint32_t getSizeBytes()** returns size in BYTES.
Convenience wrapper, useful for iterating over the whole memory,
or testing upper boundary.


## Operational

 See examples


## Future

- test more types
- new functionality
  - **clear(begin, end)** or complete clear / format only?
  - **dump(stream)** or printable interface?
  - Print interface? expensive in performance per char..
  - **getSize()** scanning FRAM like EEPROM library?
  - **write(addr obj size)** should return end + 1 == next address. 
  - remember last written address? why?
- extend examples
  - FRAM for multi language string storage
  - FRAM as linear buffer for a slow stream?
  - FRAM as ring buffer
  - FRAM logging, unequal length strings.
  - FRAM (8x) concatenated as one continuous memory.


