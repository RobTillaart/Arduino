
[![Arduino CI](https://github.com/RobTillaart/AD5248/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5248/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5248/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5248/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5248/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD5248.svg)](https://github.com/RobTillaart/AD5248/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5248/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5248.svg?maxAge=3600)](https://github.com/RobTillaart/AD5248/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD5248.svg)](https://registry.platformio.org/libraries/robtillaart/AD5248)


# AD5248

Arduino library for I2C digital potentioMeter AD5243 and rheostat AD5248


## Description

The AD5243 is a digital potentiometer, the AD5248 is a digital rheostat.


|  device  |  channels  |  steps |  ranges KΩ         |  notes  :|
|:--------:|:----------:|:------:|:------------------:|:--------:|
|  AD5243  |     2      |  256   |  2.5, 10, 50, 100  |  potentioMeter
|  AD5248  |     2      |  256   |  2.5, 10, 50, 100  |  rheostat


Both IC's have two "channels" and they do not have the output lines
some other IC's in these series have e.g. like the AD5242.

The AD5243 has a fixed address (0x2F = 47 decimal) while the AD5248 has 
two address pins giving 4 possible addresses. See table below.


| Addr(dec)| Addr(Hex) |  AD1  |  AD0  |  Notes  |
|:--------:|:---------:|:-----:|:-----:|:-------:|
|    44    |   0x2C    |  GND  |  GND  |
|    45    |   0x2D    |  GND  |  +5V  |
|    46    |   0x2E    |  +5V  |  GND  |
|    47    |   0x2F    |  +5V  |  +5V  |  fixed address of AD5243  |


An important property of the devices is that they defaults
to their mid position at startup.

The library defines **AD5248_MIDPOINT == 127**.
To be used to set to defined mid-point.


#### Related

- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5248
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X


#### Compatibles

If you know compatible devices please let me know.


## Interface

```cpp
#include "AD5248.h"
```

The library has a number of functions which are all quite straightforward.
One can get / set the value of (both) the potentiometer(s), and the O1 and O2 output lines.


#### Constructors

- **AD5243(TwoWire \*wire = &Wire)** constructor base class,
creates an instance with 2 potentiometers.
- **AD5248(uint8_t address, TwoWire \*wire = &Wire)** create an instance with 2 rheostats.
- **bool begin()** initialization of the object. 
Note the user must call **wire.begin()** or equivalent before calling **begin()**.
- **bool isConnected()** See if the address set in constructor is on the I2C bus.
- **uint8_t getAddress()**  Returns address set in the constructor, or fixed 0x2F for the AD5243.

#### Read write

- **uint8_t read(uint8_t channel)** read back the set value.
- **uint8_t write(uint8_t channel, uint8_t value)** set channel 0/1 to value 0..255.
- **uint8_t zeroAll()** sets all potentiometer's to 0 and I/O to LOW.
- **uint8_t reset()** sets all potentiometer's to midpoint == 127. (startup default)
- **uint8_t midScaleReset(uint8_t channel)** resets one potentiometer to midpoint == 127.
- **uint8_t readBackRegister()** read register back, for debugging.


#### Experimental

- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Error codes

|  define        |  value  |
|:---------------|:-------:|
|  AD5248_OK     |   0     |
|  AD5248_ERROR  |   100   |


## Future

#### Must

- improve documentation.
- buy hardware
- test

#### Should

- sync with AD524X library.

#### Could


#### Wont



## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

