
[![Arduino CI](https://github.com/RobTillaart/HX710AB/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HX710AB/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HX710AB/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HX710AB/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HX710AB/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HX710AB.svg)](https://github.com/RobTillaart/HX710AB/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HX710AB/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HX710AB.svg?maxAge=3600)](https://github.com/RobTillaart/HX710AB/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HX710AB.svg)](https://registry.platformio.org/libraries/robtillaart/HX710AB)


# HX710AB

Arduino library for the HX710A and HX710B 24-Bit ADC.


## Description

**Experimental**

This library provides two classes to read the HX710A and the HX710B ADC.

(from datasheet)

_The HX710(A/B) is a precision 24-bit analog-to-digital converter (ADC) with built-in
temperature sensor (HX710A) or DVDD, AVDD voltage difference detection (HX710B). 
It’s designed for weigh scales and industrial control applications to interface 
directly with a bridge sensor._

The HX710A can read the internal temperature.

THe HX710B can read the DVDD and AVDD supply voltage difference.

The HX710 has no means to detect errors, however several readings without noise
especially zero's might be an indication that something is wrong.


### Performance

Performance depends on platform used and on the time to make a measurment.
The latter is either 10 or 40 Hz, which possibly means optional 100 or 25 
milliseconds extra waiting time. (needs investigations)


### Related

- https://github.com/RobTillaart/HX710AB  this repo.
- https://github.com/RobTillaart/HX711  for load cells.
- https://github.com/RobTillaart/HX711_MP  for load celss with multipoint calibration.
- https://swharden.com/blog/2022-11-14-hx710b-arduino/  usage with pressure sensor.
- https://http://www.aviaic.com/  (manufacturer)
- https://github.com/RobTillaart/weight  conversions


### Test

TODO: Test with hardware.


## Interface

```cpp
#include "HX710AB.h"
```

### Constructor

- **HX710A(uint8_t dataPin, uint8_t clockPin)** constructor.
- **HX710B(uint8_t dataPin, uint8_t clockPin)** constructor.
- **void begin()** initialises pins.


### Read

- **int32_t read(bool differential = true)** powers up the device,
reads from the device, sets the mode for the **next** read.
The default parameter is true as differential readings are most used.
See table below. 
- **int32_t lastRead()** returns last read value, note this can be
differential or other. The user should track this.


|  differential  |  HX710A         |  HX710B         |  notes    |
|:--------------:|:---------------:|:---------------:|:---------:|
|   true         |  differential   |  differential   |  default  |
|   false        |  temperature    |  DVDD and AVDD  |


### Power

- **void powerDown()** puts the device in sleep mode (after 60 us).
- **void powerUp()** wakes up device.

Note the **read()** function automatically wakes up the device.


## Future

#### Must

- get hardware to test  (at least HX710B pressure)
- investigate blocking time read()
- improve documentation

#### Should

- refactor class hierarchy
- converting to units / temperature  (See HX711)
- async interface to circumvent the blocking wait.
  - bool request();    //  wakes up device
  - bool dataReady();  //  dataline check
  - int32_t fetch(differential = true);  //  actual fetch

#### Could

- calibration somehow.
  - zero reading?  tare()? 
- extend unit tests(?)
- more examples.
- extend performance test sketch
- AVR optimized code - see FastShiftIn.

#### Wont

- bool isPowerUp();  //  needed?
- void powerUp() not needed, as read does this.

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


