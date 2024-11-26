
[![Arduino CI](https://github.com/RobTillaart/TEMT6000/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TEMT6000/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TEMT6000/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TEMT6000/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TEMT6000/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TEMT6000.svg)](https://github.com/RobTillaart/TEMT6000/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TEMT6000/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TEMT6000.svg?maxAge=3600)](https://github.com/RobTillaart/TEMT6000/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TEMT6000.svg)](https://registry.platformio.org/libraries/robtillaart/TEMT6000)


# TEMT6000

Arduino library for analog TEMT6000 light / LUX sensor.


## Description

**Experimental**

The library is experimental and minimalistic.

The TEMT6000 is a cheap and small analog light sensor. 
It typically comes on a breakout with only GND, VCC and SIGNAL pins.

The TEMT6000 is most sensitive at 570 nanometre (yellow/green).
To measure the sensor must be pointed straight to the light source.
Or one should apply the cos rule.

```
lux = getLUX() x 1/cos(alpha)  
//  at 60 degrees the sensor sees 50% so the real value is 2x as much.
```
where alpha is angle between light source and sensor. See datasheet figure 4.



Feedback is welcome, please open an issue.

#### Related

- https://github.com/RobTillaart/TEMT6000


## Interface

```cpp
#include "TEMT6000.h"
```

### Constructors

- **TEMT6000(uint8_t pin)** constructor
- **void setResistor(uint16_t resistor)** set resistor value in Ohm, default 10000.
This is the internal resistor, one can calibrate the device to some extend.
- **uint16_t getResistor()** returns the set resistor value..

### Read

- **uint16_t readRaw(uint8_t times = 1)** returns the average of N reads.
- **float readLUX(uint8_t times = 1)** returns the average of N reads, converted to LUX.

## Future


#### Must

- documentation

#### Should

- add examples
- determine factor from calibrated lux and a raw Read.
- **correctionFactor(angle)** angle in radians   1/cos(alpha).

#### Could

- unit tests 

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

