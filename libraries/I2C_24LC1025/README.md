
[![Arduino CI](https://github.com/RobTillaart/I2C_24LC1025/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_24LC1025/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_24LC1025.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_24LC1025/releases)


# I2C_24FC1025 - I2C 1MB EEPROM

Arduino library for for external I2C EEPROM - 24LC1025 and equivalents.


## Description

This library is to access external I2C EEPROM of 128 KB in size, 
typically the 24LC1025 and equivalents.

**Warning**
A2 = Non-Configurable Chip Select.
This pin must be connected to VCC (+5V). 
The device will **NOT** work when this pin floats or is connected to GND (0V).


## Interface

The interface is kept quite identical to the I2C_EEPROM library.
https://github.com/RobTillaart/I2C_EEPROM

Most important change is 32 bit memory addresses.


### Constructor

- **I2C_24LC1025(uint8_t deviceAddress, TwoWire \*wire = &Wire)** constructor, optional Wire interface
- **bool begin()** initializes the I2C bus and checks if the device is available on the I2C bus.
- **bool begin(uint8_t sda, uint8_t scl)** idem for ESP32 / ESP8266 and alike.
- **bool isConnected()** test to see if device is on the bus.


### Core functions

- **int writeByte(uint32_t memoryAddress, uint8_t value)** write a single byte to the specified memory address.
- **int updateByte(uint32_t memoryAddress, uint8_t value)** write a single byte, but only if changed. Returns 0 if value was same or write succeeded.
- **int writeBlock(uint32_t memoryAddress, uint8_t \* buffer, uint32_t length)** write a buffer starting at the specified memory address. 
- **int updateBlock(uint32_t memoryAddress, uint8_t \* buffer, uint32_t length)** write a buffer starting at the specified memory address, but only if changed
- **int setBlock(uint32_t memoryAddress, uint8_t value, uint32_t length)** writes the same byte to length places starting at the specified memory address. Returns 0 if OK.
- **uint8_t readByte(uint32_t memoryAddress)** read a single byte from a given address
- **uint16_t readBlock(uint32_t memoryAddress, uint8_t \* buffer, uint32_t length)** read length bytes into buffer starting at specified memory address. Returns the number of bytes read, which should be length.


### Other

- **uint32_t getDeviceSize()** idem
- **uint8_t  getPageSize()** idem
- **uint32_t getLastWrite()** idem


#### UpdateBlock()

(new since 0.1.3)

The function **updateBlock()** reads the block of data and compares it with the new values 
to see if it needs rewriting.

As the function reads/writes the data in blocks with a maximum length of **I2C_TWIBUFFERSIZE** 
(== 30 AVR limitation; 128 for ESP32) it does this comparison in chuncks if the length exceeds this number. 
The result is that an **updateBlock()** call can result e.g. in 4 reads and only 2 writes under the hood. 

If data is changed often between writes, **updateBlock()** is slower than **writeBlock()**.
So you should verify if your sketch can make use of the advantages of **updateBlock()**


## Limitation

The library does not offer multiple EEPROMS as one continuous storage device.


## Future

- See I2C EEPROM as this library is following.


## Operation

See examples

