
[![Arduino CI](https://github.com/RobTillaart/FRAM_I2C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FRAM_I2C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FRAM_I2C.svg?maxAge=3600)](https://github.com/RobTillaart/FRAM_I2C/releases)


# FRAM_I2C

Arduino library for I2C FRAM 


## Description

FRAM is a library to read and write (over I2C) to an FRAM module. 
FRAM is much faster than EEPROM and almost as fast as Arduino UNO RAM.
Another imaportant feature is that FRAM keeps its content after a reboot (non-volatile)

Types of FRAM the library should work with

| SIZE  |  TYPE |
|:---:|:---:|
| 8KB   | MB85RC64T  |
| 32KB  | MB85RC256V |
| 64KB  | MB85RC512T |
| 128KB | MB85RC1MT  |

Address = 0x50 (default) .. 0x57


## Interface

### Constructor

- **FRAM(TwoWire \*wire = &Wire)** Constructor with optional Wire interface.
- **int begin(address = 0x50, writeProtectPin = -1)** address and writeProtectPin is optional
- **int begin(sda, scl, address = 0x50, writeProtectPin = -1)** idem fro ESP32 a.o.
- **bool isConnected()** checks if the address is visable on the I2C bus


### Write & read

Support for basic types and 2 calls for generic object

- **void write8(memaddr, value)** uint8_t
- **void write16(memaddr, value)** uint16_t
- **void write32(memaddr, value)** uint32_t
- **void write( memaddr, \* obj, size)** other types / sizes
- **uint8_t read8(memaddr)**
- **uint16_t read16(memaddr)**
- **uint32_t read32(memaddr)**
- **void read(memaddr, uint8_t \* obj, size)** 


### Miscelaneous

- **bool setWriteProtect(b)** make the FRAM writeprotect by pulling line HIGH / LOW. 
Returns true if a writeProtectPin was defined. 
Otherwise the FRAM  cannot be write protected.
- **uint16_t getManufacturerID()** idem
- **uint16_t getProductID()** idem
- **uint16_t getSize()** returns size in KB.


## Operational
 
 See examples