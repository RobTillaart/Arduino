
[![Arduino CI](https://github.com/RobTillaart/DHT2pin/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHT2pin/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHT2pin/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHT2pin/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHT2pin/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DHT2pin.svg)](https://github.com/RobTillaart/DHT2pin/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHT2pin/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHT2pin.svg?maxAge=3600)](https://github.com/RobTillaart/DHT2pin/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DHT2pin.svg)](https://registry.platformio.org/libraries/robtillaart/DHT2pin)


# DHT2pin

Arduino library for experimental 2 pin DHT library.


## Credits & testing

Maria Emanuella Moura Silva for testing and verifying this experimental
code on a Galileo.


## Description

**NOTE: THIS LIB IS NOT TESTED EXTENSIVELY YET SO USE WITH CARE**

This library is an **experimental** version of the DHT library that uses **two** data pins.
One pin for all read actions and one pin for all write actions.
This way one does not need to switch a pin between **INPUT** and **OUTPUT**.

Note:
It needs a diode between the input pin of the MCU and the data pin of the DHT sensor.
The output pin of the MCU is directly connected to the data pin of the DHT sensor.

This library was made after a request which also referred to the links below.

https://web.archive.org/web/20150912065850/https://communities.intel.com/thread/53869

https://web.archive.org/web/20180510215445/http://bigdinotech.com/tutorials/galileo-tutorials/using-1-wire-device-with-intel-galileo
(there might be later versions)

**NOTE: THIS LIB IS NOT TESTED EXTENSIVELY YET SO USE WITH CARE**


## interface

```cpp
#include "DHT2pin.h"
```

- **DHT2pin(uint8_t rpin, uint8_t wpin)** constructor.
- **void begin()** set pinModes correctly, must be called before read().
- **int read11()** read a DHT11.
- **int read()** read a DHT22 and equivalents.
- **float humidity()** get last humidity read.
- **float temperature()** get last temperature read.


## Operation

See example


## Future

- no active development planned


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

