
[![Arduino CI](https://github.com/RobTillaart/AD5245/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5245/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5245/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5245/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5245/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5245.svg)](https://github.com/RobTillaart/AD5245/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5245/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5245.svg?maxAge=3600)](https://github.com/RobTillaart/AD5245/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5245.svg)](https://registry.platformio.org/libraries/robtillaart/AD5245)


# AD5245

Arduino library for I2C single channel digital potentiometer AD5245.

The library is experimental and not tested with hardware yet.


## Description

The AD5245 is a single channel digital potentiometer which comes in
5 kΩ, 10 kΩ, 50 kΩ, 100 kΩ and can be set in 256 steps.

Indicative step size.

|   value  |  step size  |
|:--------:|:-----------:|
|    5 kΩ  |   19.53 Ω   |
|   10 kΩ  |   39.06 Ω   |
|   50 kΩ  |   195.3 Ω   |
|  100 kΩ  |   390.6 Ω   |


An important property of the device is that it defaults
to the mid-scale position at startup.
One can use **AD5245_MIDPOINT** == 128 to reset to the mid-scale position.


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

This library is based upon the AD524X library, and triggered by this issue:
- https://github.com/RobTillaart/AD524X/issues/11

- https://www.analog.com/en/products/ad5245.html
- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X
- https://github.com/RobTillaart/AD5246/  rheostat


## I2C address

The AD5245 has one address line to configure the I2C address.

| Address(dec)| Address(Hex) |  AD0  |
|:-----------:|:------------:|:-----:|
|     44      |     0x2C     |  GND  |
|     45      |     0x2D     |  +5V  |

The maximum I2C speed is 400 KHz.


## Interface

```cpp
#include AD5245.h"
```

The library has a number of functions which are all quite straightforward.
One can get / set the value of the potentiometer.

- **AD5245(uint8_t address, TwoWire \*wire = &Wire)** constructor
- **bool begin()** initializes internals. Returns true on success.
- **bool isConnected()** See if address set in constructor is on the bus.
- **uint8_t reset()** sets potentiometer to midpoint = 128. (startup default)
- **uint8_t write(uint8_t value)** set to value 0 .. 255.
- **uint8_t read()** read value from cache.
- **uint8_t readDevice()** read value from device.
- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Error codes

|  define        |  value  |
|:---------------|:-------:|
|  AD5245_OK     |   0     |
|  AD5245_ERROR  |  100    |


## Operation

The examples show the basic working of the functions.


## Future

#### Must

#### Should

- sync with AD520X library
- sync with AD524X library

#### Could

#### Wont

- midScaleReset() ?  AD524X alike
  ==> user can do **write(AD5245_MIDPOINT)**.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

