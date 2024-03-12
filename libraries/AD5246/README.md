
[![Arduino CI](https://github.com/RobTillaart/AD5246/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5246/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5246/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5246/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5246/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5246.svg)](https://github.com/RobTillaart/AD5246/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5246/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5246.svg?maxAge=3600)](https://github.com/RobTillaart/AD5246/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5246.svg)](https://registry.platformio.org/libraries/robtillaart/AD5246)


# AD5246

Arduino library for I2C single channel digital rheostat AD5246.

The library is experimental and not tested with hardware yet.


## Description

The AD5246 is a single channel digital rheostat which comes in
5 kΩ, 10 kΩ, 50 kΩ, 100 kΩ and can be set in 128 steps.

Indicative step size.

|   value  |  step size  |
|:--------:|:-----------:|
|    5 kΩ  |   39.06 Ω   |
|   10 kΩ  |   78.13 Ω   |
|   50 kΩ  |   390.6 Ω   |
|  100 kΩ  |   781.3 Ω   |


An important property is that the device defaults to the mid-scale position at startup.
One can use **AD5246_MIDPOINT** == 64 to reset to the mid-scale position.


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

This library is based upon the AD5245 library.

- https://www.analog.com/en/products/ad5246.html
- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X
- https://github.com/RobTillaart/AD5246/  rheostat


## I2C

The AD5246 has one fixed address 0x2E.

The maximum I2C speed is 400 KHz.


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


## Interface

```cpp
#include AD5246.h"
```

The library has a number of functions which are all quite straightforward.
One can get / set the value of the rheostat.

- **AD5246(TwoWire \*wire = &Wire)** constructor
- **bool begin()** for UNO.
- **bool isConnected()** See if address set in constructor is on the bus.
- **uint8_t reset()** sets rheostat to midpoint = 64. (startup default)
- **uint8_t write(uint8_t value)** set to value 0 .. 127.
Values > 127 will be mapped upon 127.
- **uint8_t read()** read value from cache.
- **uint8_t readDevice()** read value from device.

Note the AD5426 does not have a **shutdown()** command like the AD5245.


## Error codes

|  define        |  value  |
|:---------------|:-------:|
|  AD5246_OK     |   0     |
|  AD5246_ERROR  |  100    |


## Operation

The examples show the basic working of the functions.


## Future

#### Must

#### Should

- keep in sync with AD5245 library

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

