
[![Arduino CI](https://github.com/RobTillaart/I2C_EEPROM/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_EEPROM/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_EEPROM/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_EEPROM/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_EEPROM/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_EEPROM/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_EEPROM.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_EEPROM/releases)


# I2C_EEPROM

Arduino Library for external I2C EEPROM - 24LC512, 24LC256, 24LC64/32/16/08/04/02/01.


## Description

This library is to access external I2C EEPROM up to 64KB (= 512 Kbit) in size.
MicroChip 24LC512, 24LC256, 24LC64, 24LC32, 24LC16, 24LC08, 24LC04, 24LC02, 24LC01 and equivalents.


The **I2C_eeprom_cyclic_store** interface is documented [here](README_cyclic_store.md)


## Interface

### Constructor

- **I2C_eeprom(uint8_t deviceAddress, TwoWire \*wire = &Wire)** constructor, optional Wire interface.
- **I2C_eeprom(uint8_t deviceAddress, uint32_t deviceSize, TwoWire \*wire = &Wire)** constructor, with optional Wire interface.
- **bool begin()** initializes the I2C bus and checks if the device is available on the I2C bus.
- **bool begin(uint8_t sda, uint8_t scl)** idem for ESP32 / ESP8266 and alike.
- **bool isConnected()** test to see if deviceAddress is found on the bus.


### Core functions

- **int writeByte(uint16_t memoryAddress, uint8_t value)** write a single byte to the specified memory address.
- **int updateByte(uint16_t memoryAddress, uint8_t value)** write a single byte, but only if changed.
Returns 0 if value was same or write succeeded.
- **int writeBlock(uint16_t memoryAddress, uint8_t \* buffer, uint16_t length)** write a buffer starting at the specified memory address.
- **int updateBlock(uint16_t memoryAddress, uint8_t \* buffer, uint16_t length)** write a buffer starting at the specified memory address, but only if changed.
- **int setBlock(uint16_t memoryAddress, uint8_t value, uint16_t length)** writes the same byte to length places starting at the specified memory address. Returns 0 if OK.
- **uint8_t readByte(uint16_t memoryAddress)** read a single byte from a given address
- **uint16_t readBlock(uint16_t memoryAddress, uint8_t \* buffer, uint16_t length)** read length bytes into buffer starting at specified memory address.
Returns the number of bytes read, which should be length.


### Other

- **uint32_t getDeviceSize()** idem
- **uint8_t  getPageSize()** idem
- **uint8_t  getPageSize(uint32_t deviceSize)** idem
- **uint32_t getLastWrite()** idem
- **uint32_t determineSize(bool debug = false)**
function that determines the size of the EEPROM by detecting when a memory address is folded upon memory address 0.
It is based upon the observation that memory wraps around.
The debug flag gives some output to Serial.

**Warning**: this function has changed (again) in 1.4.0

Test results

| Type    | returns |  Memory  | Page Size | Notes |
|:--------|:--------|:---------|:---------:|:------|
|  -      |    0    |          |           | connect error, check device address / wiring |
| 24LC512 |  65536  |  64 KB   |  128      |       |
| 24LC256 |  32768  |  32 KB   |   64      |       |
| 24LC128 |  16384  |  16 KB   |   64      |       |
| 24LC64  |   8192  |   8 KB   |   32      |       |
| 24LC32  |   4096  |   4 KB   |   32      | not tested with hardware |
| 24LC16  |   2048  |   2 KB   |   16      |       |
| 24LC08  |   1024  |   1 KB   |   16      |       |
| 24LC04  |    512  |  512 b   |   16      |       |
| 24LC02  |    256  |  256 b   |    8      |       |
| 24LC01  |    128  |  128 b   |    8      |       |

The function cannot detect smaller than 128 bit EEPROMS.


#### UpdateBlock()

(new since 1.4.2)

The function **updateBlock()** reads the block of data and compares it with the new values to see if it needs rewriting.

As the function reads/writes the data in blocks with a maximum length of **I2C_BUFFERSIZE** (== 30 on AVR limitation).
It does this comparison in chunks if the length exceeds this number.
The result is that an **updateBlock()** call can result e.g. in 4 reads and only 2 writes under the hood.

If data is changed often between writes, **updateBlock()** is slower than **writeBlock()**.
So you should verify if your sketch can make use of the advantages of **updateBlock()**


#### ExtraWriteCycleTime (experimental)

(new since 1.5.1)

To improve support older I2C EEPROMs e.g. IS24C16 two functions were added to increase
the waiting time before a read and/or write as some older devices have a larger timeout
than 5 milliseconds which is the minimum.

- **void     setExtraWriteCycleTime(uint8_t ms)** idem
- **uint8_t  getExtraWriteCycleTime()** idem


## Limitation

The library does not offer multiple EEPROMS as one continuous storage device.


## Future

- improve error handling, write functions should return bytes written or so.
- what can we do with the print interface? (investigate)
- investigate multi-EEPROM storage,
- investigate smarter strategy for updateBlock() => find first and last changed position could possibly result in less writes.
- can setBlock use strategies from update


## Operational

See examples

