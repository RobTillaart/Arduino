
[![Arduino CI](https://github.com/RobTillaart/tinySHT2x/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/tinySHT2x/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/tinySHT2x/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/tinySHT2x/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/tinySHT2x/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/tinySHT2x.svg)](https://github.com/RobTillaart/tinySHT2x/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/tinySHT2x/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/tinySHT2x.svg?maxAge=3600)](https://github.com/RobTillaart/tinySHT2x/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/tinySHT2x.svg)](https://registry.platformio.org/libraries/robtillaart/tinySHT2x)


# tinySHT2x

Arduino library specific for AVR tiny processors. 


## Description

The tinySHT2x is an **Experimental** Arduino library to read the SHT2X sensor.
This sensor provides temperature and humidity.

The library is meant for AVR only, tiny platform, so it is minimal (not?) portable.


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
Wire parameter has moved from **begin()** to the Constructor.
The user has to call **Wire.begin()** before calling **begin()**.


#### Related

- https://github.com/RobTillaart/SHT2x (based upon).


## Interface

```cpp
#include "tinySHT2x.h"
```

#### Functions

- **tinySHT2x(TwoWire \* wire = &Wire)** Constructor
- **bool begin()** initializes internals. Returns true if device can be found.
- **bool isConnected()** Returns true if device can be found.
- **bool reset()** sends SOFT_RESET command to sensor.
returns false if I2C failed to send it.


#### Async interface

With the Async interface the user must watch keep track of the appropriate
delay between the request and read. 
For temperature this is typical around 70 millis and for humidity 30 millis().

- **void requestTemperature()** sends GET_TEMPERATURE command to sensor.
- **void requestHumidity()** sends GET_HUMIDITY command to sensor.
- **float readTemperature()** fetches data from the sensor.
- **float readHumidity()** fetches data from the sensor.
  
#### Sync interface

- **float getTemperature(uint8_t del = 70)** requests and read the temperature.
It uses a delay of 70 milliseconds which can be tuned by the user.
- **float getHumidity(uint8_t del = 30)**  requests and read the humidity.
It uses a delay of30 milliseconds which can be tuned by the user.
  
- see https://github.com/RobTillaart/SHT2x


## Future

#### Must

- test test test test (Viktor)
- improve documentation

#### Should

#### Could

- investigate async interface
  - splitting requestHumidity() and getHumidity().
  - idem for temperature. 
- Can a tiny have another Wire than Wire?
- Check the status bit (temperature / humidity flag) 
  - datasheet page 8, LSB bit 1 - bit 0 not used)
  - needed?
- Move Wire parameter to constructor?


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
