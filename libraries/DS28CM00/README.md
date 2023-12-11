
[![Arduino CI](https://github.com/RobTillaart/DS28CM00/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS28CM00/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS28CM00/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS28CM00/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS28CM00/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS28CM00.svg)](https://github.com/RobTillaart/DS28CM00/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS28CM00/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS28CM00.svg?maxAge=3600)](https://github.com/RobTillaart/DS28CM00/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS28CM00.svg)](https://registry.platformio.org/libraries/robtillaart/DS28CM00)


# DS28CM00

Arduino library for I2C DS28CM00 unique identification chip.  \[48 bit\]


## Description

THe DS28CM00 IC has a 64 bit address consisting of one type byte, 0x50, 6 bytes unique serial and a CRC
over the previous 7 bytes. This results in an 48 bits unique ID giving 281.474.976.710.656 combinations.
If that number is not unique enough, you could use 2 or more of them with an I2C multiplexer.

Since version 0.3.0 the library supports reading only the first n bytes from the serial.
Sometimes less bytes are sufficient, and less bytes takes less time.

The DS28CM00 IC has the same addressing scheme as the better known DS18B20, except for the type byte.
Therefore one could use an DS18B20 as an unique ID chip in a similar way and getting a temperature sensor
as bonus. 

The DS28CM00 can work in 2 modes, I2C and SMBus mode. Check datasheet for details.


#### 0.4.0 Breaking change

Version 0.4.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/UUID


## Interface

```cpp
#include "DS28CM00.h"
```

- **DS28CM00(TwoWire \*wire = &Wire)** Constructor, with default Wire as I2C bus.
The device has a fixed address of 0x50.
- **bool begin()** initializes library, sets default DS28CM00_I2C_MODE.
Returns false if mode cannot be set or if device cannot be found.
- **bool isConnected()** returns true if device can be found on I2C bus.
- **bool getUID(uint8_t \* buffer, uint8_t size = 8)** copy unique serial number into buffer.
Size is default 8, maximum size, size = 0 returns false. 
Less unique bytes can be enough sometimes.
Returns false if action failed.
- **bool setI2CMode()** set DS28CM00_I2C_MODE (0x00). Returns false if action failed.
- **bool setSMBusMode()** set DS28CM00_SMBUS_MODE (0x01). Returns false if action failed.
- **bool getMode(uint8_t &mode)** returns mode set above. Returns false if action failed.


|  value  |  mode                   |
|:-------:|:-----------------------:|
|  0x00   |  DS28CM00_I2C_MODE      |
|  0x01   |  DS28CM00_SMBUS_MODE    |
|  0xFF   |  DS28CM00_MODE_UNKNOWN  |


## Operation

See examples.

The class is not tested extensively e.g. with ESP32 / ESP8266.
An example sketch for ESP32 exist and compiles. Feedback welcome.


## Future

#### Must

- test with ESP32 and other platforms. (feedback welcome).

#### Should

- only extend on request / bugs
- measure performance I2C 400 500 600 kHz ...

#### Could

- cache the serial? (costs 8 bytes) + one flag.
  - If (cached filled) => faster!

#### Wont

- **uint8_t getError()** add error handling? - I2C; #bytes; mode; ...(too much for simple device)
- **bool setMode()** public? no.

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

