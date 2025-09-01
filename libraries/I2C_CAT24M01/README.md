
[![Arduino CI](https://github.com/RobTillaart/I2C_CAT24M01/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_CAT24M01/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_CAT24M01/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_CAT24M01/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_CAT24M01/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_CAT24M01.svg)](https://github.com/RobTillaart/I2C_CAT24M01/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_CAT24M01/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_CAT24M01.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_CAT24M01/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_CAT24M01.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_CAT24M01)


# I2C_CAT24M01 - I2C 1Mbit EEPROM

Arduino library for CAT24M01 1Mbit I2C EEPROM.


## Description

This library is to access the external CAT24M01 I2C EEPROM of 128 KB = 1 Mbit in size.

The user is responsible to verify the used memoryAddress (range) exists in the used EEPROM. 
(read / write / verify functions).
The library does not check this. If the address is larger than the EEPROM size, 
the address used will probably be memoryAddress % deviceSize.

This library follows the I2C_EEPROM and I2C_24LC1025 libraries, see links below.

The main difference with the I2C_24LC1025 is the place where the 16th bit of the 
memory address is inserted in the device address. 

Power-up to Ready Mode = 100 usec, so one has to wait 0.1 msec or more before using the EEPROM.

The library is not tested (extensively) with hardware yet.

Feedback, as always, is welcome.


### Related

- https://github.com/RobTillaart/I2C_24LC1025
- https://github.com/RobTillaart/I2C_CAT24M01
- https://github.com/RobTillaart/I2C_EEPROM


## Schematic

Verify the datasheet for your specific EEPROM.

```cpp
              +---U---+
          NC  | 1   8 |  VCC = +5V
          A1  | 2   7 |   WP = write protect pin
          A2  | 3   6 |  SCL = I2C clock
   (VSS) GND  | 4   5 |  SDA = I2C data
              +-------+
```


## I2C 

I2C address = 0x50, 0x52, 0x54, 0x56 depending on A1 and A2 address lines.
Bit 0 of the I2C address is used for the MSB of the memory address.

Read the datasheet, section device addressing.


### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up
to eight channels (think of it as I2C subnets) which can use the complete
address range of the device.

Drawback of using a multiplexer is that it takes more administration in
your code e.g. which device is on which channel.
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


## Interface

```cpp
#include "I2C_CAT24M01.h"
```

The interface is kept quite identical to the I2C_EEPROM library.
https://github.com/RobTillaart/I2C_EEPROM / I2C_24LC1025

Most important difference is 32 bit memory addresses.


### Constructor

- **I2C_CAT24M01(uint8_t deviceAddress, TwoWire \*wire = &Wire)** constructor,
to set the device address and optional Wire interface.
The address = 0x50, 0x52, 0x54, 0x56 depending on A1 and A2 address lines, see above.
- **bool begin(uint8_t writeProtectPin = -1)** Optionally one can set the **WP**
writeProtect pin. (see section below).
If the **WP** pin is defined, the default behaviour will be to **not** allow writing.
Furthermore it checks if the deviceAddress given in the constructor is available 
on the defined I2C bus.
Returns true if deviceAddress is found on the I2C bus, false otherwise.
- **bool isConnected()** returns true if the address given in the constructor is
available on the defined I2C bus.
- **uint8_t getAddress()** returns deviceAddress set in the constructor.
Convenience.


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

Using update instead of write functions does not write if the value is the same.
The price is an extra read() call, but if there is no change the gain is performance.

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
The user is responsible that the used buffer can hold length bytes.


### Verify functions

Same as write and update functions above. Returns true if successful, false indicates an error.
The user is responsible that the used buffer can hold length bytes.

- **bool writeByteVerify(uint32_t memoryAddress, uint8_t value)**
- **bool writeBlockVerify(uint32_t memoryAddress, uint8_t \* buffer,  uint32_t length)**
- **bool setBlockVerify(uint32_t memoryAddress, uint8_t value, uint32_t length)**
- **bool updateByteVerify(uint32_t memoryAddress, uint8_t value)**
- **bool updateBlockVerify(uint32_t memoryAddress, uint8_t \* buffer, uint32_t length)**
Returns true is buffer equals memoryAddress for length bytes.


### Other

- **uint32_t getDeviceSize()** returns the current set deviceSize.
- **uint16_t getPageSize()** returns the current set pageSize.
- **uint32_t getLastWrite()** returns timestamp in millis since start of program.


### UpdateBlock()

The function **updateBlock()** reads the block of data and compares it with the new values to see if it needs rewriting.

As the function reads/writes the data in blocks with a maximum length of **I2C_TWIBUFFERSIZE** 
(== 30 AVR limitation; 128 for ESP32) 
It does this comparison in chunks if the length exceeds the length of the I2C buffer.
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


## Future

- See I2C EEPROM as this library is following.
- add examples
- sync _pageSize with I2C_24LC1025


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

