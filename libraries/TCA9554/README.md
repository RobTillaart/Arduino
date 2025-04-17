
[![Arduino CI](https://github.com/RobTillaart/TCA9554/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TCA9554/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TCA9554/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TCA9554/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TCA9554/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TCA9554.svg)](https://github.com/RobTillaart/TCA9554/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TCA9554/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TCA9554.svg?maxAge=3600)](https://github.com/RobTillaart/TCA9554/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TCA9554.svg)](https://registry.platformio.org/libraries/robtillaart/TCA9554)


# TCA9554

Arduino library for I2C TCA9554 8 channel port expander.


## Description

**Experimental**

This library gives easy control over the 8 pins of a TCA9554 and TCA9534 device.

The pins can be used for INPUT (default) and OUTPUT, and can be set per single pin, 
or with a mask to set 8 pins in one call.

The library allow to set polarity, per pin or with a mask for 8 pins in one call.

Note: the library is not tested with hardware yet.

Feedback as always is welcome.


### TCA9534

From datasheet:

_The TCA9534 is identical to the TCA9554 except for the removal of the internal I/O 
pull-up resistors, which greatly reduces power consumption when the I/O lines are held LOW._

There is a TCA9534 class which is a (convenience) wrapper around the TCA9554 class. 
This allows one to create TCA9534 objects. 


### Compatibles

The library is expected to work for the PCA9554 / PCA9534 too for which derived 
classes are made. 

|    type   | Notes  |
|:---------:|:------:|
|  TCA9554  |  confirmed
|  TCA9534  |
|  PCA9554  |
|  PCA9534  |
|  CAT9554  |
|  CAT9534  |

Feedback of working types is welcome.


### Related

16 bit port expanders

- https://github.com/RobTillaart/MCP23017_RT
- https://github.com/RobTillaart/MCP23S17  (SPI)
- https://github.com/RobTillaart/PCA9671
- https://github.com/RobTillaart/PCF8575
- https://github.com/RobTillaart/TCA9555

8 bit port expanders

- https://github.com/RobTillaart/MCP23008
- https://github.com/RobTillaart/MCP23S08  (SPI)
- https://github.com/RobTillaart/PCF8574
- https://github.com/RobTillaart/TCA9554


## Hardware

### I2C addresses

The addresses for the TCA9554 and TCA9534 are 0x20..0x27.
These are to be set with pin A0, A1, A2.

Both the TCA9554 and TCA9534 support up to 400 kHz I2C.


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


### INT pin interrupts

The interrupt pin is not supported by the library.
Needs investigation (+ examples).


## Interface

Check the datasheet for details

```cpp
#include "TCA9554.h"
```

### Constructor

- **TCA9554(uint8_t address, TwoWire \*wire = &Wire)** constructor, with default Wire interface. 
Can be overruled with Wire0..WireN.
- **TCA9534(uint8_t address, TwoWire \*wire = &Wire)** idem.
- **PCA9554(uint8_t address, TwoWire \*wire = &Wire)** idem.
- **PCA9534(uint8_t address, TwoWire \*wire = &Wire)** idem.
- **CAT9554(uint8_t address, TwoWire \*wire = &Wire)** idem.
- **CAT9534(uint8_t address, TwoWire \*wire = &Wire)** idem.
- **uint8_t getType()** returns 34 or 54 depending on type.
- **bool begin(uint8_t mode = INPUT, uint8_t mask = 0x00)** initializes library.
Sets all the pins to INPUT (default) or to OUTPUT. 
If mode == OUTPUT the mask sets the initial value. 
If mode != OUTPUT the mode is considered INPUT.
Returns true if device can be seen on I2C bus, false otherwise.
- **bool isConnected()** returns true if device address given in the constructor can be seen 
on I2C bus, returns false otherwise.
- **uint8_t getAddress()** returns set address, (debugging).


### 1 pin interface

- **bool pinMode1(uint8_t pin, uint8_t mode)** idem.
If pin > 7 the function will return false.
The parameter mode must be INPUT or OUTPUT, other values will return false.
- **bool write1(uint8_t pin, uint8_t value)** pin = 0..7, value = LOW(0) HIGH (!0), 
returns true if successful.
- **uint8_t read1(uint8_t pin)** pin = 0..7, returns the value of the pin HIGH or LOW.
- **bool setPolarity(uint8_t pin, uint8_t value)** inverts polarity of an INPUT pin.
- **uint8_t getPolarity(uint8_t pin)** returns 1 if a pin is inverted, zero otherwise.


### 8 pin interface

mask = 0..255 (0xFF)

- **bool pinMode8(uint8_t mask)** set the mode of eight pins in one call.
1 bit = INPUT, 0 bit = OUTPUT.
- **bool write8(uint8_t mask)** returns true if successful. 
Especially useful if one needs to trigger multiple pins at the exact same time.
- **uint8_t read8()** returns a bit pattern for pins 0..7.
- **bool setPolarity8(uint8_t mask)** inverts polarity of the INPUT pins in one action.
- **uint8_t getPolarity()** returns a mask with a 1 for every INPUT pin that is inverted.


### Error codes

- **int lastError()** Above functions set an error flag that can be read with this function. 
Reading it will reset the flag to **TCA9554_OK**.

|  Description           |  Value  |
|:-----------------------|:-------:|
|  TCA9554_OK            |  0x00   |
|  TCA9554_PIN_ERROR     |  0x81   |
|  TCA9554_I2C_ERROR     |  0x82   |
|  TCA9554_VALUE_ERROR   |  0x83   |
|  TCA9554_PORT_ERROR    |  0x84   |
|  TCA9554_INVALID_READ  |  -100   |


## Future

#### Must

- update documentation
- buy TCA9554 / TCA9534 / PCA9554 / PCA9534
- test all functionality
- keep TCA9554/TCA9555 in sync

#### Should


#### Could


#### Wont (unless)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

