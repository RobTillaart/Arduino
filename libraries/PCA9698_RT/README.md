
[![Arduino CI](https://github.com/RobTillaart/PCA9698_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9698_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9698_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9698_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9698_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCA9698_RT.svg)](https://github.com/RobTillaart/PCA9698_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9698_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9698_RT.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9698_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCA9698.svg)](https://registry.platformio.org/libraries/RobTillaart/PCA9698)


# PCA9698

Arduino library for the PCA9698 - I2C, 40 channel IO expander.


## Description

**Experimental**

The PCA9698 is an I2C, 40 pins parallel IO expander.
These 40 pins can be configured as INPUT or OUTPUT and are addressable 
via 5 banks (groups) of 8 IO pins.
The library provides read/write access to single bit, a single bank or all
40 pins in one call.

When powered with 5 V, the outputs are capable of sourcing 10 mA 
and sinking 25 mA so the total load can go up to 1.0 Amp.
Be sure to have an adequate power supply.

The device has a RESET pin, OE (OutputEnable) pin and an INT(errupt) pin.
The library does not provide means to control these lines.

Note: Not all functionality is implemented yet.

Note: The library is not tested with hardware yet.

As always, feedback is welcome.


### Interrupts

Not implemented yet.

The PCA9698 has an interrupt output line (INT) to notify an MCU that one of the input lines has changed.
This can be used to prevent active polling of the PCA9698, which is more efficient.


### Related

- https://github.com/RobTillaart/MCP23017_RT  16 bit
- https://github.com/RobTillaart/MCP23S17 16 bit
- https://github.com/RobTillaart/PCF8575 16 bit
- https://github.com/RobTillaart/MCP23008  8 bit
- https://github.com/RobTillaart/MCP23S08  8 bit
- https://github.com/RobTillaart/PCF8574  8 bit
- https://github.com/RobTillaart/PCA9698_RT 40 bit


## I2C

### Clock

Supports clock speeds up to 1000 kHz.


### Address

|  type      |  address-range  |  notes                    |
|:-----------|:---------------:|:-------------------------:|
|  PCA9698   |  0x20 + 64      |  see datasheet Page 21  for details

One can connect up to 64 PCA9698 on one I2C bus, giving access
to 64 x 40 = 2560 IO lines in theory. 
Be sure to have a well dimensioned power supply.


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
#include "PCA9698.h"
```

### Constructor

Not tested yet.

- **PCA9698(uint8_t deviceAddress = 0x20, TwoWire \*wire = &Wire)** Constructor with optional address,
default 0x20, and the optional Wire interface as parameter.
- **bool begin()** set the initial value (default 0xFF) for the pins and masks.
- **bool isConnected()** checks if the address set in the constructor is visible on the I2C bus.
 **uint8_t getAddress()** Returns the device address.


### Read and Write 8

Parameter bank = 0..5  
Functions return error code or PCA9698_OK (0) on success.

- **uint8_t read8(uint8_t bank, uint8_t & bitmask)** reads 8 pins at once into bitmask.
- **uint8_t write8(uint8_t bank, uint8_t bitmask)** write 8 pins at once.
- **uint8_t toggle8(uint8_t bank, uint8_t bitmask)** toggles 8 pins at once.


### Read and Write 1

Parameter pin = 0..39  
Functions return error code or PCA9698_OK (0) on success.

- **uint8_t read1(uint8_t pin)** reads 1 pin.
- **uint8_t write1(uint8_t pin, uint8_t value)** writes 1 pin, 0 = LOW, other = HIGH
- **uint8_t toggle1(uint8_t pin)** toggles 1 pin.


### Read and Write 40

Use **uint8_t buf[5]** to read/write all banks in one call.
The buffer should be at least size 5. The library does not check this.
Functions return error code or PCA9698_OK (0) on success.

- **uint8_t read40(uint8_t \* buf)** reads 40 pins.
- **uint8_t write40(uint8_t \* buf)** writes 40 pins.


### Select

- **void select(uint8_t pin)** sets a single pin to HIGH, all others are set to LOW.
If pin > 39 all pins are set to LOW.
Can be used to select one of n devices.
- **void selectN(uint8_t n)** sets n pins to HIGH, all others are set to LOW.
If n >= 40 all pins are set to HIGH, if n == 0, no pin is HIGH.
This can typical be used to implement a VU meter.


### Polarity

See datasheet 7.4.3

Use **uint8_t buf[5]** to read/write all banks in one call.
The buffer should be at least size 5. The library does not check this.

- **uint8_t setPolarity40(uint8_t \* buf)**
- **uint8_t getPolarity40(uint8_t \* buf)**


### Configuration - pinMode

See datasheet 7.4.4
set input / output mode

Use **uint8_t buf[5]** to read/write all banks in one call.
The buffer should be at least size 5. The library does not check this.

- **uint8_t setPinMode40(uint8_t \* buf)**
- **uint8_t getPinMode40(uint8_t \* buf)**


### Interrupts

See datasheet 7.4.5

Use **uint8_t buf[5]** to read/write all banks in one call.
The buffer should be at least size 5. The library does not check this.

- **uint8_t setInterrupt40(uint8_t \* buf)**
- **uint8_t getInterrupt40(uint8_t \* buf)**


### All banks configuration

See datasheet 7.4.6 - 7.4.8

- **uint8_t setOutputConfig(uint8_t mask)**
- **uint8_t getOutputConfig()**
- **uint8_t setAllBank(uint8_t mask)**
- **uint8_t getAllBank()**
- **uint8_t setMode(uint8_t mask)**
- **uint8_t getMode()**


### Device ID

- **uint32_t getDeviceID()** deviceID == 12 bits manufacturer, 9 bits part, 3 bits revision


### Error handling

- **int lastError()** returns the last error from the lib. See below.


## Error codes

|  name               |  value  |  description              |
|:--------------------|:-------:|:--------------------------|
|  PCA9698_OK         |  0x00   |  no error                 |
|  PCA9698_PIN_ERROR  |  0x81   |  pin number out of range  |
|  PCA9698_I2C_ERROR  |  0x82   |  I2C communication error  |
|  PCA9698_BANK_ERROR |  0x83   |  bank out of range        |


## Future

#### Must

- elaborate documentation.
- get hardware to test library.
- test.

#### Should

- implement bit masks for All banks configuration

#### Could

- support OE pin?  ==>  outputEnable(bool OE)
- support RESET pin?
- add single bit get/set interface for pinMode, polarity and interrupt.
- make the "40" interface size aware so it can access 1,2,3,4,5 banks by parameter
  - begin(MAX_PIN); ==> derived is MAX_BANK = 1 + (MAXPIN - 1) / 8
  - would give configuration that uses less pins faster IO.
- add return value/error select() and selectN();
- should all bank get-function use references and error codes too.

#### Wont

- IN pin, => user code should handle this.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


