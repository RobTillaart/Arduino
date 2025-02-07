
[![Arduino CI](https://github.com/RobTillaart/I2C_SOFTRESET/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_SOFTRESET/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_SOFTRESET/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_SOFTRESET/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_SOFTRESET/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_SOFTRESET.svg)](https://github.com/RobTillaart/I2C_SOFTRESET/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_SOFTRESET/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_SOFTRESET.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_SOFTRESET/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_SOFTRESET.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_SOFTRESET)


# I2C_SOFTRESET

Arduino library for the I2C_SOFTRESET, to reset stuck devices.\n Sends a soft reset over the I2C bus.",


## Description

**Experimental**

The I2C_SOFTRESET is a library to reset some stuck devices on the I2C bus.

After an error during the I2C handshake, power problem or reset an I2C device can get stuck.
Some devices can get unstuck after an I2C bus reset.

The I2C specification defines a I2C bus reset as follows:

A START pulse, followed by 9 pulses, followed by a START and STOP pulse on the SCL line.


```
SCL   H L   H L   H L   H L   H L   H L   H L   H L   H L   H L   H L   H L   H L
     START   1     2     3     4     5     6     7     8     9   STOP  START  STOP

SDA    L H                                                               L     H
```

Feedback, issues, improvements are welcome. 
Please file an issue on GitHub.


### Related

- https://www.puyasemi.com/  datasheet P24C02C/P24C04C/P24C08C/P24C16C
- https://github.com/RobTillaart/I2C_SOFTRESET
- https://github.com/RobTillaart/I2C_SCanner
- https://github.com/RobTillaart/MultiSpeedI2CScanner


## Interface

```cpp
#include "I2C_SOFTRESET.h"
```

- **I2C_SOFTRESET(uint8_t SDA, uint8_t SCL)**
- **void reset()** sends the I2C reset pulse.
- **uint32_t lastReset()** returns timestamp of last reset if one was not enough.

There is also a function that does all in one call.

- **void I2CSoftReset(uint8_t SDA, uint8_t SCL)** sends the I2C reset pulse.


## Future

#### Must

- improve documentation
- test the library with hardware (how to get a device stuck?)

#### Should

- add examples
- optimize where possible.
- parameter for the delayMicroseconds();

#### Could

- class I2C_BUS(SDA, SCL)
  - generic calls too into class?  I2C_GENCAL class?

#### Wont



## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

