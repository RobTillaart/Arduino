
[![Arduino CI](https://github.com/RobTillaart/PCA9671/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9671/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9671/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9671/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9671/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCA9671.svg)](https://github.com/RobTillaart/PCA9671/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9671/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9671.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9671/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCA9671.svg)](https://registry.platformio.org/libraries/robtillaart/PCA9671)


# PCA9671

Arduino library for the PCA9671, I2C 16-bit I/O expander.


## Description

**Experimental**

The library gives easy control over the 16 pins of the PCA9671 chips.
It is a replacement product for the PCF8575, so this library is based
upon the PCF8575 library to make replacement as easy as possible.

The PCA9671 can have 64 I2C addresses, see datasheet.

The PCA9671 does not have an interrupt pin, but a reset pin.
This external reset pin is not (yet) supported by the library.

Having 64 devices on one I2C bus would allow you to connect up to
64 x 16 = 1024 IO lines.

The library allows to read and write both single pins or 16 pins at once.
Furthermore some additional functions are implemented that are playful and useful.

Not tested with hardware yet.

Feedback as always is welcome.


### Comparison PCF8575

Based upon data sheets.

|  device   |  address  |  max I2C  |  interrupt  |  reset  |
|:---------:|:---------:|:---------:|:-----------:|:-------:|
|  PCF8575  |    8      |  400 KHz  |     Y       |    N    |
|  PCA9671  |    64     |    1 MHz  |     N       |    Y    |


### Related

16 bit port expanders

- https://github.com/RobTillaart/MCP23017_RT  I2C 16 IO LINES
- https://github.com/RobTillaart/MCP23S17  SPI 16 IO LINES
- https://github.com/RobTillaart/PCF8575  I2C 16 IO LINES
- https://github.com/RobTillaart/PCA9671  I2C 16 IO LINES - successor PCF8575


8 bit port expanders

- https://github.com/RobTillaart/MCP23008  I2C 8 IO lines
- https://github.com/RobTillaart/MCP23S08  SPI 8 IO lines
- https://github.com/RobTillaart/PCF8574  I2C 8 IO lines


## I2C

The device has 64 possible addresses.

See datasheet.

### Performance

TODO:

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
#include "PCA9671.h"
```

**PCA9671_INITIAL_VALUE** is a define that can be set compile time or before
the include of "PCA9671.h" to overrule the default value used with the 
**begin()** call.


### Constructor

- **PCA9671(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with the optional 
I2C device address, default 0x20, and the optional Wire interface as parameter.
- **bool begin(uint8_t value = PCA9671_INITIAL_VALUE)** set the initial value for the pins and masks.
Returns true if device address is visible on the I2C bus.
- **bool isConnected()** checks if the address is visible on the I2C bus.
- **bool setAddress(const uint8_t deviceAddress)** sets the device address after construction. 
Can be used to switch between PCA9671 modules runtime. Note this corrupts internal buffered values, 
so one might need to call **read16()** and/or **write16()**. 
Returns false if address is out of range or if the address could not be found on I2C bus.
Returns true if address can be found on I2C bus.
- **uint8_t getAddress()** Returns the address set in the constructor or by **setAddress()**.


### Read and Write

- **uint16_t read16()** reads all 16 pins at once. This one does the actual reading.
- **uint8_t read(uint8_t pin)** reads a single pin; pin = 0..15.
- **uint16_t value()** returns the last read inputs again, as this information is buffered 
in the class this is faster than reread the pins.
- **void write16(uint16_t value)** writes all 16 pins at once. This one does the actual reading.
- **void write(uint8_t pin, uint8_t value)** writes a single pin; pin = 0..15; value is HIGH(1) or LOW (0).
- **uint16_t valueOut()** returns the last written data.


### Button

The **"button"** functions are to be used when you mix input and output on one IC.
It does not change / affect the pins used for output by masking these.
Typical usage is to call **setButtonMask()** once in setup as pins do not (often) change
during program execution. 

- **void setButtonMask(const uint16_t mask)** sets the (bit) mask which lines are input.
- **uint16_t getButtonMask()** returns the set buttonMask.
- **uint16_t readButton16()** use the mask set by setButtonMask to select specific input pins.
- **uint16_t readButton16(uint16_t mask)** use a specific mask to select specific input pins.
Note this can be a subset of the pins set with **setButtonMask()** if one wants to process not all.
- **uint8_t readButton(uint8_t pin)** read a singe input pin.


### Special

- **void toggle(uint8_t pin)** toggles a single pin.
- **void toggleMask(uint16_t mask)** toggles a selection of pins, 
if you want to invert all pins use 0xFFFF (default value).
- **void shiftRight(uint8_t n = 1)** shifts output channels n pins (default 1) pins right (e.g. LEDs ).
Fills the higher lines with zero's.
- **void shiftLeft(uint8_t n = 1)**  shifts output channels n pins (default 1) pins left (e.g. LEDs ).
Fills the lower lines with zero's.
- **void rotateRight(uint8_t n = 1)** rotates output channels to right, moving lowest line to highest line.
- **void rotateLeft(uint8_t n = 1)** rotates output channels to left, moving highest line to lowest line.
- **void reverse()** reverse the "bit pattern" of the lines, swapping pin 15 with 0, 14 with 1, 13 with 2 etc..


### Select

Some convenience wrappers.

- **void select(const uint8_t pin)** sets a single pin to HIGH, all others are set to LOW.
If pin > 15 all pins are set to LOW.
Can be used to select one of n devices.
- **void selectN(const uint8_t pin)** sets pins 0..pin to HIGH, all others are set to LOW.
If pin > 15 all pins are set to LOW.
This can typical be used to implement a VU meter.
- **void selectNone()** sets all pins to LOW.
- **void selectAll()** sets all pins to HIGH.


### Miscellaneous

- **int lastError()** returns the last error from the lib. (see .h file).


## Error codes


|  name               |  value  |  description              |
|:--------------------|:-------:|:--------------------------|
|  PCA9671_OK         |  0x00   |  no error                 |
|  PCA9671_PIN_ERROR  |  0x81   |  pin number out of range  |
|  PCA9671_I2C_ERROR  |  0x82   |  I2C communication error  |


## Future

#### Must

- improve documentation
- get hardware to test
- keep in sync with PCF8575.

#### Should


#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


