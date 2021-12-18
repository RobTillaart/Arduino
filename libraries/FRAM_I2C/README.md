
[![Arduino CI](https://github.com/RobTillaart/FRAM_I2C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FRAM_I2C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FRAM_I2C.svg?maxAge=3600)](https://github.com/RobTillaart/FRAM_I2C/releases)


# FRAM_I2C

Arduino library for I2C FRAM 


## Description

FRAM is a library to read and write (over I2C) to an FRAM module. 
FRAM is much faster than EEPROM and almost as fast as Arduino UNO RAM.
Another important feature is that FRAM keeps its content after a reboot (non-volatile)

FRAM stands for Ferroelectric RAM - https://en.wikipedia.org/wiki/Ferroelectric_RAM

Types of FRAM the library should work with

| SIZE  |  TYPE      |
|:-----:|:----------:|
| 8KB   | MB85RC64T  |
| 32KB  | MB85RC256V |
| 64KB  | MB85RC512T |
| 128KB | MB85RC1MT  |

Address = 0x50 (default) .. 0x57


## Interface

### Constructor

- **FRAM(TwoWire \*wire = &Wire)** Constructor with optional Wire interface.
- **int begin(uint8_t address = 0x50, int8_t writeProtectPin = -1)** address and writeProtectPin is optional.
- **int begin(uint8_t sda, uint8_t scl, uint8_t address = 0x50, int8_t writeProtectPin = -1)** idem fro ESP32 a.o.
- **bool isConnected()** checks if the address is visible on the I2C bus.


### Write & read

Support for basic types and 2 calls for generic object

- **void write8(uint16_t memaddr, uint8_t value)** uint8_t
- **void write16(uint16_t memaddr, uint16_t value)** uint16_t
- **void write32(uint16_t memaddr, uint32_t value)** uint32_t
- **void write(uint16_t memaddr, uint8_t \* obj, uint16_t size)** other types / sizes
- **uint8_t read8(uint16_t memaddr)**
- **uint16_t read16(uint16_t memaddr)**
- **uint32_t read32(uint16_t memaddr)**
- **void read(uint16_t memaddr, uint8_t uint8_t \* obj, uint16_t size)** 


### Miscellaneous

- **bool setWriteProtect(bool b)** make the FRAM write-protected by pulling line HIGH / LOW.  
Returns true if a writeProtectPin was defined. 
Otherwise the FRAM  cannot be write protected.
- **bool getWriteProtect()** get current status.
- **uint16_t getManufacturerID()** idem.
- **uint16_t getProductID()** idem.
- **uint16_t getSize()** returns size in KB.


## Operational
 
 See examples
 
## Future

- test 
- extend examples
- example in which FRAM is used as buffer for some stream?
- example FRAM ring buffer
- 

