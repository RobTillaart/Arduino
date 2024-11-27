
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
The sensor typically comes on a breakout with only GND, VCC and SIGNAL pins.
It is not a calibrated sensor however the signal is very useful for many projects.

The TEMT6000 is most sensitive at 570 nanometre (yellow/green).
The library does not compensate for wavelength (yet).

To measure the sensor must be pointed straight to the light source.
Or one should use **readLUX(times, angle)** to compensate for the angle.

Feedback is welcome, please open an issue.

### Related

- https://github.com/RobTillaart/AnalogUVSensor (typeless)analog UV sensor
- https://github.com/RobTillaart/BH1750FVI_RT lux sensor
- https://github.com/RobTillaart/LTR390_RT light + UV
- https://github.com/RobTillaart/ML8511 UV sensor
- https://github.com/RobTillaart/TEMT6000
- https://github.com/RobTillaart/TSL235R  light to frequency sensor


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
- **float readLUX(uint8_t times, float angleDegrees)** returns the average of N reads, 
converted to LUX, compensated for the angle in degrees (0..90).

The angle correction is based upon figure 4 of the datasheet.
Zero or 0 degrees is right above the sensor, maximum light.
Returns -1 if angle < 0 or angle >= 89 degrees as it cannot be calculated realistically.
Above 89 degrees the angle compensation factor "explodes" beyond 50.
IN practice angles above 85 compensates with a factor 10 or more, 
so they are affecting accuracy a lot.


## Future


#### Must

- improve documentation

#### Should

- add examples
- determine factor from calibrated lux and a readRaw.

#### Could

- unit tests
- look for optimizations
- add correction factor for wavelength (figure 5).
  - mapFloat(360-570, 0.1-1.0) + mapFloat(570-960, 1.0-0.1)
  - or example?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

