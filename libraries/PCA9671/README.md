
[![Arduino CI](https://github.com/RobTillaart/PCA9671/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9671/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9671/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9671/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9671/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCA9671.svg)](https://github.com/RobTillaart/PCA9671/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9671/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9671.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9671/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCA9671.svg)](https://registry.platformio.org/libraries/robtillaart/PCA9671)


# PCA9671

Arduino library for the PCA9671 and PCA9673, I2C 16-bit I/O expander.


## Description

**Experimental**

The library gives easy control over the 16 pins of the PCA9671 devices.
The PCA9671 is a replacement product for the PCF8575, so this library is based
upon the PCF8575 library to make the transition as easy as possible.

The PCA9671 can have 64 I2C addresses, see datasheet how to connect.

The PCA9671 is not 100% compatible as it does not have an interrupt pin, 
but a reset pin instead.
Note: hardware pin 1 == interrupt (OUT) or reset (IN).
The external reset pin is not (yet) supported by the library, use it with care.


Having 64 devices on one I2C bus would allow you to connect up to
64 x 16 = 1024 input or output lines. 
Be aware that you might need an appropriate power supply to have all of them
working properly.

The library allows to read and write both single pins or 16 pins in one call.
Be aware that the 16 bits interface actually writes 2 times 8 pins.
Furthermore some additional functions are implemented that are playful and useful.

Warning: Not all functionality is tested with hardware, so use with care.

Feedback as always is welcome.


### PCA9673

The library should work with the PCA9673 device, which is nearly identical.
The difference is that the PCA9673 has both an interrupt pin AND a RESET pin. 
What is missing is address pin 2, and thus it has less addresses. 

So not 100% replacement compatible but close enough if one takes care of
the interrupt an reset pins.


### Comparison PCF8575, PCA9671 and PCA9673

Based upon data sheets.

|             |  PCF8575  |  PCA9671  |  PCA9673  |  Notes  |
|:------------|:---------:|:---------:|:---------:|:-------:|
|  address    |     8     |    64     |    16     |
|  max I2C    |  400 KHz  |   1 MHz   |   1 MHz   |
|  interrupt  |   Y (1)   |     N     |   Y (1)   |  (1) = pin nr
|  reset-pin  |     N     |   Y (1)   |   Y (3)   |  (3) = pin nr
|  SW-reset   |     N     |     Y     |     Y     |  see section below.
|  deviceID   |     N     |     Y     |     Y     |  see section below.
|             |           |           |           |

The library does not implement the SW-reset call.


### Related

16 bit port expanders

- https://github.com/RobTillaart/MCP23017_RT  I2C 16 IO lines.
- https://github.com/RobTillaart/MCP23S17  SPI 16 IO lines.
- https://github.com/RobTillaart/PCF8575  I2C 16 IO lines.
- https://github.com/RobTillaart/PCA9671  I2C 16 IO lines. - successor PCF8575


8 bit port expanders

- https://github.com/RobTillaart/MCP23008  I2C 8 IO lines.
- https://github.com/RobTillaart/MCP23S08  SPI 8 IO lines.
- https://github.com/RobTillaart/PCF8574  I2C 8 IO lines.


## I2C

The device has 64 possible addresses.

See datasheet page 6, section 7.1.1 Address maps.


### Performance

TODO: test to fill the table

| clock speed |  Read  |  Write  |  Notes              |
|:-----------:|:------:|:-------:|:--------------------|
|    100000   |        |         |
|    200000   |        |         |
|    300000   |        |         |
|    400000   |        |         |
|    500000   |        |         |
|    600000   |        |         |
|    700000   |        |         |
|    800000   |        |         |
|    900000   |        |         |
|   1000000   |        |         |


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


## Reset

The PCA9671 and PCA9673 have a reset pin (pin 1 or 3) to reset the device 
to power on state.

To reset the device one needs to set the reset pin LOW for at least 4 us.
The reset process itself takes about 100us, see datasheet page 20 and fig 22.

The reset can / will change the internal state of the device compared to the 
(cached) inner state as hold by the library. 
So you need to call e.g. **read16()** or **select()** after reset to restore
the alignment of the inner states.


### Software Reset Call

All PCA9671's on an I2C bus will respond to the **Software Reset Call** 
(SWRST = 0x0006). So they will react if a SWRST is sent to other devices too.
Details see data sheet, page 9.

TODO: test SWRST with https://github.com/RobTillaart/I2C_SCANNER

The SWRST can / will change the internal state of the device compared to the 
(cached) inner state as hold by the library. 
So you need to call e.g. **read16()** or **select()** after reset to restore
the alignment of the inner states.


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
- **PCA9673(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor.
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
- **void write16(uint16_t value)** writes all 16 pins at once. This one does the actual writing.
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

- **int lastError()** returns the last error from the library. (see .h file).


### DeviceID

- **uint32_t deviceID()** experimental. Datasheet page 10.
Returns 24 bits, see table or 0xFFFFFFFF (-1) on error.

Use **PCA9671_deviceId.ino** to see how to split the fields.

|   bits   |  meaning       |  notes  |
|:--------:|:---------------|:--------|
|  00..02  |  Revision      |
|  03..08  |  Feature       |  datasheet uses P and F
|  09..15  |  Category      |  no details known
|  16..23  |  Manufacturer  |  no details known

The first and only test gave the following output, (see #4).

```
Manufacturer = 0x00  (NXP?)
Category     = 0x01
Feature      = 0x20  (== address?, coincidence?)
Revision     = 0x00
```

There is no info how to interpret the bits further (yet), feedback welcome.


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
- test more platforms
- keep in sync with PCF8575.

#### Should


#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


