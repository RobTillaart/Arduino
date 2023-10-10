
[![Arduino CI](https://github.com/RobTillaart/AD5263/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5263/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5263/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5263/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5263/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5263.svg)](https://github.com/RobTillaart/AD5263/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5263/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5263.svg?maxAge=3600)](https://github.com/RobTillaart/AD5263/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5263.svg)](https://registry.platformio.org/libraries/robtillaart/AD5263)


# AD5263

Arduino library for I2C digital potentiometer AD5263 and compatibles.


## Description

**Experimental** needs testing with hardware.

The AD5263 is a digital potentiometer with 4 channels.
This digital potentiometers come in 20, 50 and 200 kΩ
and can be set in 256 steps.

This library only implements the I2C interface.

An important property of the device is that it defaults
to their mid position at startup.

The library also defines **AD5263_MIDPOINT** == 128.
To be used to set to defined mid-point.

(Library is based on datasheet Rev.F )


#### Related

This library is related to

- https://github.com/RobTillaart/AD524X single/dual port digital potentiometer.
- https://github.com/RobTillaart/AD5245 single port digital potentiometer.
- https://github.com/RobTillaart/AD520X multi port digital potentiometer.
- https://www.analog.com/media/en/technical-documentation/data-sheets/ad5263.pdf


#### Compatibles

The AD5280 and AD5282 are one and two channel devices that might be compatible.
Not tested yet. See future.


## I2C

#### Address

The AD5263 has two address lines to configure the I2C address. 0x2C - 0x2F

|  Addr(dec) |  Addr(Hex)  |  AD0  |  AD1  |
|:----------:|:-----------:|:-----:|:-----:|
|    44      |    0x2C     |  GND  |  GND  |
|    45      |    0x2D     |  GND  |  +5V  |
|    46      |    0x2E     |  +5V  |  GND  |
|    47      |    0x2F     |  +5V  |  +5V  |

Note the AD5263 uses the same range as the AD524X devices.


#### Performance

- TODO
- table
- test sketch


## Interface

```cpp
#include "AD5263.h"
```

The library has a number of functions which are all quite straightforward.
One can get / set the value of (both) the potentiometer(s), and the O1 and O2 output lines.


#### Constructors

- **AD5263(uint8_t address, TwoWire \*wire = &Wire)** constructor,
creates an instance with 4 potentiometer.
- **bool begin()** if connected **begin()** resets the device,
otherwise returns false.
- **bool isConnected()** See if address set in constructor is on the bus.


#### Basic IO

- **uint8_t write(uint8_t rdac, uint8_t value)** set channel rdac 0..3 to value 0..255.
- **uint8_t write(uint8_t rdac, uint8_t value, uint8_t O1, uint8_t O2)** idem + set output lines O1 and O2 too.
- **uint8_t read(uint8_t rdac)** read back set value.
rdac should be 0..3.
- **uint8_t setO1(uint8_t value = HIGH)**  value = HIGH (default) or LOW.
- **uint8_t setO2(uint8_t value = HIGH)**  value = HIGH (default) or LOW.
- **uint8_t getO1()** read back O1 line.
- **uint8_t getO2()** read back O2 line.


#### Misc

- **uint8_t zeroAll()** sets potentiometer's to 0 and I/O to LOW.
- **uint8_t reset()** sets potentiometer's to midpoint == 127 and I/O to LOW. (startup default)
- **uint8_t midScaleReset(uint8_t rdac)** resets one potentiometer to midpoint == 127.
- **uint8_t readBackRegister()** read register back, for debugging.


#### Experimental

- **uint8_t shutDown()** check datasheet, not tested, use at own risk.


## Error codes

|  define        |  value  |
|:---------------|:-------:|
|  AD5263_OK     |   0     |
|  AD5263_ERROR  |   100   |


## Future

#### Must

- update documentation.
- get hardware (breakout or so).
- test with hardware.


#### Should


#### Could

- investigate AD5280/82 compatibility.
- improve error handling.
- sync with AD520X / AD524X library
- optimize footprint **write()** and **midScaleReset()**


#### Wont



## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

