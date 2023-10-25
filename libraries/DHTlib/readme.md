
[![Arduino CI](https://github.com/RobTillaart/DHTlib/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHTlib/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHTlib/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHTlib/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHTlib/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DHTlib.svg)](https://github.com/RobTillaart/DHTlib/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHTlib/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHTlib.svg?maxAge=3600)](https://github.com/RobTillaart/DHTlib/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DHTlib.svg)](https://registry.platformio.org/libraries/robtillaart/DHTlib)


# DHTlib

Arduino library for DHT temperature and humidity sensor. AVR optimized


## Description

The DHT11, 21, 22, 33 and 44 are relative inexpensive sensors for measuring temperature and humidity.

This library can be used for reading both values from these DHT sensors.
The DHT11 only returns integers (e.g. 20) and does not support negative values.
The others are quite similar and provide one decimal digit (e.g. 20.2)
The hardware pins of the sensors and handshake are identical so ideal to combine in one lib.

The library (0.1.13 version) is confirmed to work on:

- UNO (tested myself)
- 2009 (tested myself)
- MEGA2560
- DUE
- attiny85 @8MHz
- Digistump Digix @ 84 MHz

Later 0.1.xx versions are optimized for AVR only.

More information - http://playground.arduino.cc/Main/DHTLib -

For latest version for the DHT, check https://github.com/RobTillaart/DHTNEW


## DHT PIN layout from left to right

| Front |      | Description   |
|:------|:----:|:--------------|
| pin 1 |      | VCC           |
| pin 2 |      | DATA          |
| pin 3 |      | Not Connected |
| pin 4 |      | GND           |


## Interface

```cpp
#include "dht.h"
```


#### Constructor

- **dht()** Constructor


#### Read functions per type

- **int8_t read11(uint8_t pin)**
- **int8_t read(uint8_t pin)**
- **int8_t read12(uint8_t pin)**

- **inline int8_t read21(uint8_t pin)**
- **inline int8_t read22(uint8_t pin)**
- **inline int8_t read33(uint8_t pin)**
- **inline int8_t read44(uint8_t pin)**
- **inline int8_t read2301(uint8_t pin)**
- **inline int8_t read2302(uint8_t pin)**
- **inline int8_t read2303(uint8_t pin)**
- **inline int8_t read2320(uint8_t pin)**
- **inline int8_t read2322(uint8_t pin)**

- **float humidity** public class variable to access last read humidity.
- **float temperature** public class variable to access last read temperature.


#### Enable / disable interrupts

- **bool getDisableIRQ()**
- **void setDisableIRQ(bool b )**


## Operational

See examples


## Versions

- See changelog.md
- See DHTNEW or DHTStable library for latest stable version for all platforms.


## Future

#### Must

- improve documentation

#### Should

- separate history versions CHANGELOG.md file ?

#### Could

- improve unit tests
  - constants
- move non public part of #defines to .cpp

#### Wont

- updates only on request basis (bugs)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

