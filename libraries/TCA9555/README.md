
[![Arduino CI](https://github.com/RobTillaart/TCA9555/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TCA9555/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TCA9555/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TCA9555/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TCA9555/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TCA9555.svg)](https://github.com/RobTillaart/TCA9555/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TCA9555/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TCA9555.svg?maxAge=3600)](https://github.com/RobTillaart/TCA9555/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TCA9555.svg)](https://registry.platformio.org/libraries/robtillaart/TCA9555)


# TCA9555

Arduino library for TCA9555 16 channel I2C port expander.


## Description

This library gives easy control over the 16 pins of a TCA9555 chip.

The pins can be used for INPUT (default) and OUTPUT, and allow to set polarity.

The pins can be set per single pin, or with a mask to set either 8 or 16 pins
in one call.
Note that for the 16 bit interface settings are not perfectly simultaneous 
as the 16 bit interface does in fact 2 calls to the 8 bit interface.  


#### TCA9535

From datasheet:

_The TCA9535 is identical to the TCA9555, except that the TCA9535 does not include the internal I/O
pull-up resistor, which requires pull-ups and pull-downs on unused I/O pins when configured as an
input and not driven. This reduces power consumption when the I/O is held low._

There is a TCA9535 class which is a (convenience) wrapper around the TCA9555 class. 
This allows one to create TCA9535 objects. 


#### 0.3.0 Breaking change

The version 0.3.0 has breaking changes in the interface. 
The rationale is that the programming environment of the **Arduino ESP32 S3** 
board uses a remapping by means of the include file **io_pin_remap.h**.
This file remaps the pins of several core Arduino functions. 
The remapping is implemented by #define macros and these implement "hard" text 
replacements without considering context. 
The effect is that methods from this class (and several others) which have the same 
name as those Arduino core functions will be remapped into something not working.

The following library functions have been renamed:

|  old name        |  new name    |  notes  |
|:-----------------|:-------------|:--------|
|  analogRead()    |  read()      |
|  analogWrite()   |  write()     |
|  pinMode()       |  pinMode1()  |
|  digitalRead()   |  read1()     |
|  digitalWrite()  |  write1()    |



#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

16 bit port expanders

- https://github.com/RobTillaart/MCP23017_RT
- https://github.com/RobTillaart/MCP23S17
- https://github.com/RobTillaart/PCF8575

8 bit port expanders

- https://github.com/RobTillaart/MCP23008
- https://github.com/RobTillaart/MCP23S08
- https://github.com/RobTillaart/PCF8574


## Hardware

#### I2C addresses

The addresses for the TCA9555 and TCA9535 are 0x20..0x27.
These are to be set with pin A0, A1, A2.

Both the TCA9555 and TCA9535 support up to 400 kHz I2C.


#### I2C multiplexing

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


#### INT

The interrupt pin is not supported by the library.
Needs investigation (+ examples).


## Interface

Check the datasheet for details

```cpp
#include "TCA9555.h"
```

#### Constructor

- **TCA9555(uint8_t address, TwoWire \*wire = &Wire)** constructor, with default Wire interface. 
Can be overruled with Wire0..WireN.
- **TCA9535(uint8_t address, TwoWire \*wire = &Wire)** idem.
- **uint8_t getType()** returns 35 or 55 depending on type.
- **bool begin()** initializes library.
Returns true if device can be seen on I2C bus, false otherwise.
- **bool isConnected()** returns true if device can be seen on I2C bus, false otherwise.
- **uint8_t getAddress()** returns set address, (debugging).


#### 1 pin interface

- **bool pinMode1(uint8_t pin, uint8_t mode)** idem.
- **bool write1(uint8_t pin, uint8_t value)** pin = 0..15, value = LOW(0) HIGH (!0), returns true if successful.
- **uint8_t read1(uint8_t pin)** pin = 0..15, returns the value of the pin HIGH or LOW.
- **bool setPolarity(uint8_t pin, uint8_t value)** inverts polarity of an INPUT pin.
- **uint8_t getPolarity(uint8_t pin)** returns 1 if a pin is inverted.


#### 8 pin interface

port = 0..1  
mask = 0..255

- **bool pinMode8(uint8_t port, uint8_t mask)** set the mode of eight pins in one call.
- **bool write8(uint8_t port, uint8_t mask)** returns true if successful. 
Especially useful if one needs to trigger multiple pins at the exact same time.
- **uint8_t read8(uint8_t port)** returns a bit pattern for pins 0..7 or pins 8..15.
- **bool setPolarity8(uint8_t port, uint8_t mask)** inverts polarity of the 8 INPUT pins in one action.
- **uint8_t getPolarity(uint8_t port)** returns a mask with a 1 for every INPUT pin that is inverted.


#### 16 pin interface

Be aware that the 16 pins interface does two calls to the 8 pins interface. 
So it is impossible to switch pins from the 2 groups of 8 at exactly the same time 
without additional hardware.

- **bool pinMode16(uint16_t mask)** set the mode of sixteen pins in one call. 
- **bool write16(uint16_t mask)**  mask = 0x0000 .. 0xFFFF, returns true if successful.
- **uint16_t read16()** Returns a bit pattern for pins 0..15.
- **bool setPolarity16(uint16_t mask)** inverts polarity of the 8 INPUT pins in one action. 
Returns true upon success.
- **uint16_t getPolarity()** returns a mask of 16 bits with a 1 for every INPUT pin that is inverted.


#### Error codes

- **int lastError()** Above functions set an error flag that can be read with this function. 
Reading it will reset the flag to **TCA9555_OK**.


|  Description           |  Value  |
|:-----------------------|:-------:|
|  TCA9555_OK            |  0x00   |
|  TCA9555_PIN_ERROR     |  0x81   |
|  TCA9555_I2C_ERROR     |  0x82   |
|  TCA9555_VALUE_ERROR   |  0x83   |
|  TCA9555_PORT_ERROR    |  0x84   |
|  TCA9555_INVALID_READ  |  -100   |


## Future


#### Must

- update documentation
- buy TCA9555 / TCA9535
- test all functionality
  - library is written without hardware


#### Should

- investigate INT = interrupt pin
- investigate map INPUT_PULLUP on INPUT (pinMode ?)
- investigate internal pull up etc.
- investigate TCA9535 differences
  - pull up resistors
  - elaborate derived class
- **setPolarity()** ==> **setPolarity1()** ? get idem.
  - uniformity


#### Could

- rethink class hierarchy
  - TCA9535 has less functions so should be base class
- add performance example for I2C.
- investigate optimizing the "16 pins" interface.
  - read /write multiple bytes in one call, is it supported?


#### Wont (unless)

- add TCA9535 error codes
  - better reuse them?  ==> TCA95X5 codes


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

