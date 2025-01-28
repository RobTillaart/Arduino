
[![Arduino CI](https://github.com/RobTillaart/PIR8575/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PIR8575/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PIR8575/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PIR8575/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PIR8575/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PIR8575.svg)](https://github.com/RobTillaart/PIR8575/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PIR8575/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PIR8575.svg?maxAge=3600)](https://github.com/RobTillaart/PIR8575/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PIR8575.svg)](https://registry.platformio.org/libraries/robtillaart/PIR8575)


# PIR8575

Arduino library for 16 channel PIR detection system based upon PCF8575.


## Description

**Experimental**

The library gives control over up to 16 parallel working PIR devices over I2C.

The idea for this library came up in a discussion about how to fully cover an
area with PIR sensors without blind spots and how to check them.
The existing PIR library (see below) uses the pins of a processor, which is fast.
However there are only so many free pins for IO, so then the idea for this
library popped up.

The library is based upon the well tested PCF8575 library (stripped version)
and is expected to work to some extend with the PCF8574. (to be verified).

To connect the PIR units (especially 16 ones) one has to connect a separate
power supply as these cannot be powered directly by a typical microprocessor.

The library is not tested with many PIR sensors yet.

As always, feedback is welcome.


### I2C address

The base address of teh PCF8575 = 0x20 + 0..7 depending on address pins A0..A2.


### Interrupts intro

The PIR8575 (PCF8575) has an interrupt output line (INT) to notify an MCU
that one of the input lines has changed its status.
This can be used to prevent active polling of the PCF8575, which can be
more efficient.

See datasheet PCF8575 for details.


### Related

- https://github.com/RobTillaart/PIR
- https://github.com/RobTillaart/PCF8575  16 bit IO expander.


## Interface

```cpp
#include "PIR8575.h"
```

### Constructor

- **PIR8575(uint8_t address, TwoWire \* wire = &Wire)** Constructor with
I2C device address, and the optional Wire interface as parameter.
- **bool begin()** returns true if device address is seen on I2C bus.
- **bool isConnected()** checks if the address is visible on the I2C bus.
- **uint8_t getAddress()** returns the device address.

### Read

- **uint16_t read16()** reads all 16 pins at once. This one does the actual reading.
- **uint8_t read(uint8_t pir)** reads a single PIR device; parameter pir = 0..15.
- **int lastError()** returns the last error from the lib. (see .h file).


## Error codes

|  name               |  value  |  description              |
|:--------------------|:-------:|:--------------------------|
|  PIR8575_OK         |  0x00   |  no error                 |
|  PIR8575_PIN_ERROR  |  0x81   |  pin number out of range  |
|  PIR8575_I2C_ERROR  |  0x82   |  I2C communication error  |


## Future

#### Must

- update documentation.
- test with hardware

#### Should

- add examples 
  - PIR scanner 360 degrees, "clock"
  - corridor ?
- polarity of all pins - in begin()?  (conditional XOR in read).

#### Could

- move code to .cpp
- use of mask during read
- configure number of PIR's (1..16) in begin()?.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


