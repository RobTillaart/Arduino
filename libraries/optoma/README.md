
[![Arduino CI](https://github.com/RobTillaart/Optoma/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Optoma/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Optoma/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Optoma/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Optoma/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Optoma.svg)](https://github.com/RobTillaart/Optoma/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Optoma/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Optoma.svg?maxAge=3600)](https://github.com/RobTillaart/Optoma/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Optoma.svg)](https://registry.platformio.org/libraries/robtillaart/Optoma)


# Optoma

Arduino library to control Optoma W305ST beamer over RS232.


## Description

The Optoma library contains functions that help to control 
the beamer from an Arduino. 

The library is tested with an UNO and an Optoma W305ST Beamer. 
The commands can work on other Optoma Beamers.

Command structure
```
    ~XXnnn parameter

    ~        start command
    XX       2 digit ID
    nnn      command can be up to 3 char/digit
    space    space
    param    parameters, depend on command
    \r       end command
```


## Interface

```cpp
#include "optoma.h"
```

The following functions are implemented:

- **Optoma(HardwareSerial\* stream = &Serial)** constructor, default uses Serial, 
other HW or SW Serial are possible.
- **void init(int ID, uint32_t baudRate = 9600)** default baud rate = 9600.  
The ID is used to address a specific beamer.
In theory one could have multiple beamers on one RS232 port (never seen or tested).
- **uint32_t getBaudrate()** return set baud rate.
- **void switchOn()** idem.
- **void switchOff()** idem.
- **bool isOn()** idem.
- **void increaseVKS()** VKS - Vertical KeyStone. check datasheet.
- **void decreaseVKS()** VKS - Vertical KeyStone. check datasheet.


## Future

More functionality will be added on a need to basis.

#### Must

- documentation

#### Should

#### Could

- Create examples.
- investigate SoftWare Serial support

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

