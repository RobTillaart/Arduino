
[![Arduino CI](https://github.com/RobTillaart/DHT12/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHT12/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHT12/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHT12/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHT12/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DHT12.svg)](https://github.com/RobTillaart/DHT12/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHT12/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHT12.svg?maxAge=3600)](https://github.com/RobTillaart/DHT12/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DHT12.svg)](https://registry.platformio.org/libraries/robtillaart/DHT12)


# DHT12

Arduino library for I2C DHT12 temperature and humidity sensor.


## Description

The DHT12 is an I2C temperature and humidity sensor.

The constructor is called only with a TwoWire object (Wire, Wire1 etc) as the device 
has a fixed address. The user should call **Wire.begin()** in setup before calling
the **begin()** function.

Thereafter one has to call the **read()** function to do the actual reading,
and with **getTemperature()** and **getHumidity()** to get the read values.
Calling these latter again will return the same values until a new **read()** is called.


#### I2C

The DHT12 has a fixed I2C address of 0x5C. To use multiple DHT12's one need an
I2C multiplexer like PCA9548 or TCA9548.

The DHT12 should work up to 400 KHz however this is not tested (yet).


## Interface

```cpp
#include "DHT12.h"
```


#### Constructor

- **DHT12(TwoWire \*wire = &Wire)** constructor, using a specific Wire (I2C bus).
Default is set to Wire.
- **bool begin()** initializer for non ESP32. Returns true if connected.
- **bool isConnected()** returns true if the address of the DHT12 can be seen on the I2C bus. (since 0.3.2)


#### Core

- **int8_t read()** read the sensor and store the values internally. It returns the status of the read which should be 0.
- **float getHumidity()** returns last Humidity read, or -999 in case of error.
- **float getTemperature()** returns last Temperature read, or -999 in case of error.
- **uint32_t lastRead()** returns the timestamp of the last successful read in milliseconds since startup.
If zero there has been no **read()** called yet.


#### Offset

- **void setHumOffset(float offset = 0)** set an offset to calibrate (1st order) the sensor.
Default offset is 0.
- **float getHumOffset()** return current humidity offset, default 0.
- **void setTempOffset(float offset = 0)** set an offset to calibrate (1st order) the sensor.
Default offset is 0.
- **float getTempOffset()** return current temperature offset, default 0.


## Future

#### Must

- documentation 
  - related?

#### Should

- test at different I2C speeds 
  - 400 KHz should be possible.
- add examples.


#### Could

- check for optimizations. although I2C overhead is much more.
- add **void setIgnoreChecksum(bool = false)** ignore checksum flag speeds up communication a bit
- add **bool getIgnoreChecksum()** get status. For completeness.
- investigate if it is possible to extract temp and hum separately
  - faster?
- add **void suppressErrorReads(bool)** prevents the -999, returns previous value
- add **bool getSuppressError()**


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


