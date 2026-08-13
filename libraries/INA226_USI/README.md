
[![Arduino CI](https://github.com/RobTillaart/INA226_USI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA226_USI/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA226_USI/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA226_USI/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA226_USI/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA226_USI.svg)](https://github.com/RobTillaart/INA226_USI/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA226_USI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA226_USI.svg?maxAge=3600)](https://github.com/RobTillaart/INA226_USI/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA226_USI.svg)](https://registry.platformio.org/libraries/robtillaart/INA226)


# INA226_USI

Arduino library for INA226 power sensor for ATtiny.

Derived class developed by Peter.Simoons, 2026-08-08


## Description

**Experimental** 

The INA226_USI implements the INA226 library (based upon 0.6.6) for the Atmel ATtiny85 et al. 
The INA226 library was adapted to implement a small voltage and current monitor for a power supply, and works well.

The ATtiny85 et al uses TinyWireM and USI_TWI_Master for I2C. 
These replaces the TwoWire I2C API in the code.

Detailed description see https://github.com/RobTillaart/INA226 as that is the
leading library for developments.

Feedback as always is welcome.


### Testing

The INA226_USI library is only tested and confirmed to work with ATtiny85 hardware.
A test sketch compiled well for the ATtiny44/45/64/65/84, although
not tested on actual hardware.

The library is too big for the ATtiny24/25, so the idea popped up to 
make an integer only derived library with a minimal API to keep footprint
as small as possible.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

