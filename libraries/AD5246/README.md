
[![Arduino CI](https://github.com/RobTillaart/AD5246/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD5246/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD5246/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD5246/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD5246/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5246/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5246.svg?maxAge=3600)](https://github.com/RobTillaart/AD5246/releases)


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


#### Related

This library is based upon the AD5245 library.

- https://www.analog.com/en/products/ad5246.html
- https://github.com/RobTillaart/AD520X/
- https://github.com/RobTillaart/AD524X/
- https://github.com/RobTillaart/AD5245/
- https://github.com/RobTillaart/AD5246/


## I2C address

The AD5246 has one fixed address 0x2E.
If one needs more AD5426 on one I2C bus one need a I2C multiplexer 
- https://github.com/RobTillaart/TCA9548

The maximum I2C speed is 400 KHz.


## Interface

```cpp
#include AD5246.h"
```

The library has a number of functions which are all quite straightforward.
One can get / set the value of the rheostat.

- **AD5246(TwoWire \*wire = &Wire)** constructor
- **bool begin(uint8_t sda, uint8_t scl)** ESP32 a.o initializing of Wire.
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

- keep in sync with AD5245 library

