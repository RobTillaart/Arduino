
[![Arduino CI](https://github.com/RobTillaart/I2C_24LC1025/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_24LC1025/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_24LC1025/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_24LC1025/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_24LC1025/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_24LC1025.svg)](https://github.com/RobTillaart/I2C_24LC1025/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_24LC1025/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_24LC1025.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_24LC1025/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_24LC1025.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_24LC1025)


# I2C_24LC1025 - I2C 1MB EEPROM

Arduino library for for external I2C EEPROM - 24LC1025 and equivalents e.g. 24AA1025/24FC1025.


## Description

This library is to access external I2C EEPROM of 128 KB in size, 
typically the 24LC1025 and equivalents e.g. 24AA1025/24FC1025.

**Warning**
A2 = Non-Configurable Chip Select.
This pin must be connected to VCC (+5V). 
The device will **NOT** work when this pin floats or is connected to GND (0V).

This library follows the I2C_EEPROM library, see links below.

#### Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/I2C_EEPROM


## Schematic

```cpp
        +---U---+
    A0  | 1   8 |  VCC = +5V
    A1  | 2   7 |   WP = write protect pin
    A2  | 3   6 |  SCL = I2C clock
   GND  | 4   5 |  SDA = I2C data
        +-------+

default address = 0x50 .. 0x53 depending on A0 and A1 address lines.
A2 must be connected to VCC (5V).

Read the datasheet, section device addressing, about A2 and B0 (block bit)
```


## Interface

```cpp
#include "I2C_24LC1025.h"
```

The interface is kept quite identical to the I2C_EEPROM library.
https://github.com/RobTillaart/I2C_EEPROM

Most important difference is 32 bit memory addresses.


### Constructor

- **I2C_24LC1025(uint8_t deviceAddress, TwoWire \*wire = &Wire)** constructor, optional Wire interface.
- **bool begin(uint8_t writeProtectPin = -1)** initializes the I2C bus with the default pins.
Furthermore it checks if the deviceAddress is available on the I2C bus.
Returns true if deviceAddress is found on the bus, false otherwise.
Optionally one can set the **WP** writeProtect pin. (see section below).
If the **WP** pin is defined the default will be to **not** allow writing.
- **bool isConnected()** test to see if deviceAddress is found on the bus.
- **uint8_t getAddress()** returns device address set in constructor.

### Write functions

- **int writeByte(uint32_t memoryAddress, uint8_t value)** write a single byte to 
the specified memory address.
Returns I2C status, 0 = OK.
- **int writeBlock(uint32_t memoryAddress, uint8_t \* buffer, uint32_t length)** 
write a buffer starting at the specified memory address. 
Returns I2C status, 0 = OK.
- **int setBlock(uint32_t memoryAddress, uint8_t value, uint32_t length)** writes 
the same byte to length places starting at the specified memory address. 
Returns I2C status, 0 = OK.


### Update functions

- **int updateByte(uint32_t memoryAddress, uint8_t value)** write a single byte,
but only if changed. 
Returns 0 if value was same or write succeeded.
- **uint32_t updateBlock(uint32_t memoryAddress, uint8_t \* buffer, uint32_t length)** 
write a buffer starting at the specified memory address, but only if changed.
Returns bytes written.


### Read functions

- **uint8_t readByte(uint32_t memoryAddress)** read a single byte from a given address
- **uint32_t readBlock(uint32_t memoryAddress, uint8_t \* buffer, uint32_t length)** 
read length bytes into buffer starting at specified memory address.
Returns the number of bytes read, which should be length.


### Verify functions

Since 0.2.0 - experimental, needs extensive testing.

Same as write and update functions above. Returns true if successful, false indicates an error.

- **bool writeByteVerify(uint32_t memoryAddress, uint8_t value)**
- **bool writeBlockVerify(uint32_t memoryAddress, uint8_t \* buffer,  uint32_t length)**
- **bool setBlockVerify(uint32_t memoryAddress, uint8_t value, uint32_t length)**
- **bool updateByteVerify(uint32_t memoryAddress, uint8_t value)**
- **bool updateBlockVerify(uint32_t memoryAddress, uint8_t \* buffer, uint32_t length)**


### Other

- **uint32_t getDeviceSize()** idem
- **uint8_t  getPageSize()** idem
- **uint32_t getLastWrite()** idem


### UpdateBlock()

(new since 0.1.3)

The function **updateBlock()** reads the block of data and compares it with the new values to see if it needs rewriting.

As the function reads/writes the data in blocks with a maximum length of **I2C_TWIBUFFERSIZE** 
(== 30 AVR limitation; 128 for ESP32) 
It does this comparison in chunks if the length exceeds this number.
The result is that an **updateBlock()** call can result e.g. in 4 reads and only 2 writes under the hood.

If data is changed often between writes, **updateBlock()** is slower than **writeBlock()**.
So you should verify if your sketch can make use of the advantages of **updateBlock()**


### ExtraWriteCycleTime (experimental)

To improve support older I2C EEPROMs e.g. IS24C16 two functions were 
added to increase the waiting time before a read and/or write as some 
older devices have a larger timeout 
than 5 milliseconds which is the minimum.

- **void     setExtraWriteCycleTime(uint8_t ms)** idem
- **uint8_t  getExtraWriteCycleTime()** idem

It is also possible to adjust the **I2C_WRITEDELAY** in the .h file
or overrule the define on the command line.


### WriteProtectPin WP (experimental)

(since 0.2.5)

The library can control the **WP** = WriteProtect pin of the EEPROM.
To do this one should connect a GPIO pin of the MCU to the **WP** pin of the EEPROM.
Furthermore the **WP** should be defined as a parameter in **begin()**.
If the **WP** pin is defined the default will be to **not** allow writing.
The user has to enable writing either by manual or automatic control.

In the automatic mode the library only allows writing to the EEPROM when it
actually writes to the EEPROM. 
So it keeps the EEPROM in a read only mode as much as possible.
This prevents accidental writes due to (noisy) signals on the I2C bus. (#57)


Status
- **bool hasWriteProtectPin()** returns true if **WP** has been set.

Automatic control
- **void setAutoWriteProtect(bool b)** if set to true, the library enables writing
only when the EEPROM is actually written. This setting **overrules** the manual control.
If **setAutoWriteProtect()** is set to false (== default) the manual control is leading.
- **bool getAutoWriteProtect()** get current setting.

Manual control
- **void allowWrite()** allows writing by setting **WP** to LOW.
- **void preventWrite()** disables writing by setting **WP** to HIGH.



## Limitation

The library does not offer multiple EEPROMS as one continuous storage device.


## Operation

See examples


## Future

- See I2C EEPROM as this library is following.
- add examples


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

