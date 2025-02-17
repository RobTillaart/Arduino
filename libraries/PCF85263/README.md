
[![Arduino CI](https://github.com/RobTillaart/PCF85263/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCF85263/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCF85263/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCF85263/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCF85263/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCF85263.svg)](https://github.com/RobTillaart/PCF85263/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCF85263/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCF85263.svg?maxAge=3600)](https://github.com/RobTillaart/PCF85263/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCF85263.svg)](https://registry.platformio.org/libraries/robtillaart/PCF85263)


# PCF85263

Arduino library for the PCF85263 RTC (I2C).


## Description

**Experimental**

This library is written to use the NXP PCF85263 RTC.

The functionality implemented is just basic date time retrieval.

More functionality upon request (if time permits)

#### Not implemented but interesting:

The device can run in a stop-watch mode. The range goes up to 999 999 hours,
which is about 41666 days is about 114 years.


### Related

- https://github.com/RobTillaart/PCF85263 this library
- https://github.com/RobTillaart/DS3232 high precision RTC
- https://github.com/RobTillaart/stopWatch_RT SW stopwatch
- https://github.com/RobTillaart/CountDown SW count down timer


## I2C

The device has a fixed I2C address of 0x51 (81) so only one RTC per I2C bus can be used.
The I2C communication supports 0.9-5.0 V so any 3.3V MCU should be able to connect.
Do not forget appropriate pull up resistors on the I2C SDA and SCL lines.

If one needs more sensors there are some options.
- One could use an I2C multiplexer (see below)
- One could use an MCU with multiple I2C buses.
- One could use a (Two-Wire compatible) SW I2C (outside scope of this library).


### I2C multiplexing

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

See example **TCA9548_demo_PCF85263.ino**


### I2C clock

The PCF85263 support max 400 KHz.


## Interface

```cpp
#include "PCF85263.h"
```

### Constructor

- **PCF85263(TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the fixed address 0x51 (81).


### Base RTC

- **int readDateTime()** read the current time from the RTC.
- **int writeDateTime()** set the current time in the RTC.
Writes all fields, be aware that weekDay need to be set too.
- **uint32_t lastRead()** lastTime in milliseconds when RTC is read.

### Getters

Getters return the last read value, to update call **read()** first.

- **uint8_t seconds()**
- **uint8_t minutes()**
- **uint8_t hours()**
- **uint8_t weekDay()**
- **uint8_t day()**
- **uint8_t month()**
- **uint8_t year()**

### Setters

Setters set a value, to update the RTC call **write()** after.

- **void setSeconds(uint8_t value)** 0..59
- **void setMinutes(uint8_t value)** 0..59
- **void setHours(uint8_t value)** 0..23
- **void setWeekDay(uint8_t value)** 0..6  0 = Sunday, 1 = Monday .. 6 = Saturday
- **void setDay(uint8_t value)** 1..31
- **void setMonth(uint8_t value)** 1..12
- **void setYear(uint8_t value)** 0..99

Note: you can also adjust just one field and keep the others.


### Function

- **void setRTCmode(uint8_t mode = 0)** 0 => RTC mode (default,
1 = Stopwatch mode, other ignored.


### Start Stop RTC

- **void startRTC()** idem.
- **void stopRTC()** idem.


### Low level: Read/WriteRegister

Allows to access all functionality the library did not implement (yet).
Check datasheet for details per register.
Use with care.

- **int readRegister(uint8_t reg)**
- **int writeRegister(uint8_t reg, uint8_t value)**


### Debugging

- **int getLastI2Cstate()** returns last low level I2C status. 0 == OK.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- investigate stopwatch mode as it is unique.

#### Could

- extend functionality upon request.
  - alarms
  - extended controls
- add examples
- add unit test

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


