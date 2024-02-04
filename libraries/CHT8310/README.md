
[![Arduino CI](https://github.com/RobTillaart/CHT8310/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CHT8310/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CHT8310/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CHT8310/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CHT8310/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/CHT8310.svg)](https://github.com/RobTillaart/CHT8310/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CHT8310/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CHT8310.svg?maxAge=3600)](https://github.com/RobTillaart/CHT8310/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/CHT8310.svg)](https://registry.platformio.org/libraries/robtillaart/CHT8310)


# CHT8310

Arduino library for CHT8310 temperature and humidity sensor.


## Description

This library is **EXPERIMENTAL** and implements a minimal subset of the functionality of the sensor.
Version 0.1.0 includes reading the temperature and humidity register and the manufacturer-ID register.
Furthermore one can set an offset for temperature and humidity.

Version 0.1.0 does support reading or writing other registers by generic wrappers.
Read the datasheet for the register details.

|  sensor       |  range        |  accuracy\*  |  resolution  |
|:-------------:|:-------------:|:------------:|:------------:|
|  temperature  |  -40°..125°C  |  max 0.5°C   |  0.03125°C   |
|  humidity     |  0%..100% RH  |  max 2% RH   |  0.02% RH    |

\* Accuracy for full range.
More exact details for smaller ranges, see datasheet.

The library is based upon https://github.com/RobTillaart/CHT8305
which is a simpler and unfortunately not an compatible sensor.

If you are able to test this library, please share your experiences.


#### Tests

- not done yet.


#### Related

-  https://github.com/RobTillaart/CHT8305


## Hardware

Always check datasheet for connections.

```cpp
//
//             +---------------+
//     VCC ----| VCC           |
//     SDA ----| SDA  CHT8310  |
//     GND ----| GND           |
//     SCL ----| SCL           |
//      ?  ----| AD0           |   ? depends on address see table below.
//             |               |
//      x  ----| ALERT         |   x not suppported yet
//             +---------------+
//
//  check datasheet
//  VCC     RED
//  GND     BLACK
//  SDA     YELLOW
//  SCL     WHITE
```

Pull ups are needed on SDA, SCL.


## I2C 

#### performance

I2C bus speeds is supported up to 400 KHz.


#### Addresses

Check datasheet

|  AD0  |   Address  |  Notes  |
|:-----:|:----------:|:--------|
|  GND  |    0x40    |  CHT8310_DEFAULT_ADDRESS
|  VCC  |    0x44    |
|  SDA  |    0x48    |
|  SCL  |    0x4C    |

Pull ups are needed on SDA, SCL and optional to ALERT.


#### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up 
to eight channels (think of it as I2C subnets) which can use the complete 
address range of the device. 

Drawback of using a multiplexer is that it takes more administration in 
your code e.g. which device is on which channel. 
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices 
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


## Interface

```cpp
#include "CHT8310.h"
```

#### Constructor

- **CHT8310(const uint8_t address = CHT8310_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** Constructor 
with default address (0x40) and I2C bus.
- **int begin()** initializes internals.
Returns error status.
- **bool isConnected()** checks if address (default 0x40) can be seen on the I2C bus.
- **uint8_t getAddress()** returns address set in constructor.


#### Core

- **int read()** reads both the temperature and humidity.
Can be called once per second.
- **int readTemperature()** read only temperature (slightly faster than read)
- **int readHumidity()** read only humidity (slightly faster than read)
- **uint32_t lastRead()** returns lastRead in MilliSeconds since start sketch.
Useful to check when it is time to call **read()** again, or for logging.
- **float getHumidity()** returns last humidity read.
Will return the same value until **read()** or **readTemperature()** is called again.
- **float getTemperature()** returns last temperature read.
Will return the same value until **read()** or **readHumidity()** is called again.

Note: read(), readTemperature() and readHumidity() blocks each other,
so you can call only one of them every second.


#### Conversion delay

- **void setConversionDelay(uint8_t cd = 11)** default is 11 milliseconds (datasheet P8).
Not tested what is the optimum.
- **uint8_t getConversionDelay()** returns set value.


#### Offset

Adding offsets works well in the "normal range" but might introduce 
under- or overflow at the ends of the sensor range.
These are not handled for temperature by the library (humidity since 0.1.7).
  
- **void setHumidityOffset(float offset)** idem.
- **void setTemperatureOffset(float offset)** idem.
- **float getHumidityOffset()** idem.
- **float getTemperatureOffset()** idem.

If the offset is not the same over the operational range, 
consider a mapping function for temperature and humidity.
e.g. https://github.com/RobTillaart/MultiMap


#### Meta data

- **uint16_t getManufacturer()** returns 0x5959.


#### Register Access

Temporary wrappers to access the registers.
Read the datasheet for the details.

- **uint16_t readRegister(uint8_t reg)**
- **int writeRegister(uint8_t reg, uint16_t value)**


## Future

#### Must

- elaborate documentation.
- test with hardware 

#### Should


#### Could

- implement more functionality
  - keep in sync with CHT8305 where possible
  - (unit) test where possible
  - refactor.
- test different platforms
  - AVR, ESP32, ESP8266, STM32, RP2040, ...
- add examples
  - performance.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


