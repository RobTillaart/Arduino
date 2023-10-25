
[![Arduino CI](https://github.com/RobTillaart/DHTINT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHTINT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHTINT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHTINT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHTINT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DHTINT.svg)](https://github.com/RobTillaart/DHTINT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHTINT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHTINT.svg?maxAge=3600)](https://github.com/RobTillaart/DHTINT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DHTINT.svg)](https://registry.platformio.org/libraries/robtillaart/DHTINT)


# DHTINT

Arduino library for DHT sensors - integer only


## Description

This is an **experimental** integer only library, 
based upon - https://github.com/RobTillaart/DHTNew - version 0.4.12

Goal is to reduce footprint by using integer math only.
This way the lib becomes more usable for processors like the ATTINY 45 or 85. 

As the library only uses integer math it will not trigger the automatic including of 
the floating point math libraries. 
This will save additional memory unless other code uses floating point math.


### Compare DHTINT versus DHTNEW

Sketch: ..\example\dhtint_minimum.ino

replaced DHTINT with DHTNEW


| platform | library | sketch size | variables |
|:--------:|:--------|------------:|----------:|
|  UNO     | DHTNEW  |        5730 |       341 |
|  UNO     | DHTINT  |        3978 |       321 |
|          | delta   |        1752 |        20 |
|          |         |             |           |
|  ESP32   | DHTNEW  |      206730 |     13464 |
|  ESP32   | DHTINT  |      206110 |     13456 |
|          | delta   |         620 |         8 |
|          |         |             |           |


Gain is most substantial for the UNO platform.


## Interface

```cpp
#include "dhtint.h"
```

To elaborate


### Raw data access

To access the decimal part the following two functions are added.
These give access to the bytes that are low level communicated.
The user can decode these values to get the integer + decimal part.
This can be used for efficient storage or transmission.

- **uint16_t getRawTemperature()**
- **uint16_t getRawHumidity()**

Note these functions have no equivalent in the DHTNew library (yet).


### Integer offset

To set the decimal part of the offset the following two functions are added.

- **uint16_t setDecimalOffsetHumidity(int offset)**
- **uint16_t setDecimalOffsetTemperature(int offset)**

An offset of ```setDecimalOffsetTemperature(15);``` means +1.5 °C

Note these functions have no equivalent in the DHTNew library (yet).


## Future

No active development.

#### Must

#### Should

- Keep in sync with DHTNEW.
- Test more

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

