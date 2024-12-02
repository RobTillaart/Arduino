
[![Arduino CI](https://github.com/RobTillaart/SD2405/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SD2405/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SD2405/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SD2405/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SD2405/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SD2405.svg)](https://github.com/RobTillaart/SD2405/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SD2405/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SD2405.svg?maxAge=3600)](https://github.com/RobTillaart/SD2405/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SD2405.svg)](https://registry.platformio.org/libraries/robtillaart/SD2405)


# SD2405

Arduino library for I2C SD2405 RTC and compatibles.


## Description

This SD2405 library provides a minimalistic interface to read and write the date
and time to and from the I2C SD2405 RTC device and compatibles.

An unique feature of the SD2405 is a build in internal battery, which should 
be able to keep the RTC running for 6 months or more. The datasheet mentions
at least a 100 recharges which could be interesting for very long running projects. It is unclear how the internal battery works when temperature drops.

What is different from other RTC libraries is that it directly provides fields like
seconds, minutes etc. and not use ``` time structs``` from libraries like
```time.h``` or ```timelib.h```. This has its pros and cons of course.
Goal is to improve the ease of use for those who just need the date and time elements
and not use the alarms etc.

Furthermore the library only supports the 24 hour per day model to minimize footprint.
Subtracting 12 hours is not too difficult if one wants an "AM/PM" layout.

The current version does not support any special feature other than two generic
**readRegister()** and **writeRegister()** functions.
These two functions allows users access to all registers and to do anything possible.

The SD2405 has several functions not found on other RTC's, especially a
correction for the clock to minimize deviations (ppm). This functionality
is most interesting however not implemented in this library yet. 

Note: This SD2405 library is a refactored version of an older experimental SD2405 library
from 2022 which was never published. 
The API (base RTC functions), documentation and examples is recently (0.1.1) 
aligned with the DS3232 library.

Note: The library 0.1.1 is not tested yet with hardware.

Feedback as always is welcome, please open an issue on GitHub.

### Compatibles

No known compatible RTC's

The base time function calls are quite compatible with the DS3232 however the
I2C address differs. The DS3232 = 0x68, where the SD2405 = 0x32.

Furthermore the DS3232 has 236 bytes of SRAM, where the SD2405 has 12 bytes.


### Related

- https://github.com/RobTillaart/DS3232
- https://github.com/RobTillaart/dateTimeHelpers
- https://forum.arduino.cc/t/got-time-from-ntp-server-need-day-of-week/117799/6


## Hardware

Always check datasheet for connections.

Pull ups are needed on SDA, SCL.


## I2C

### Performance

I2C bus speeds officially supports up to 400 KHz.

Timing of UNO with SD2405 of **read()** in microseconds.

TODO

|  board   |  speed   |  time  |  notes  |
|:--------:|:--------:|:------:|:-------:|
|   UNO    |   50000  |        |
|   UNO    |  100000  |        |
|   UNO    |  200000  |        |
|   UNO    |  300000  |        |
|   UNO    |  400000  |        |  max official supported
|   UNO    |  500000  |        |
|   UNO    |  600000  |        |
|   UNO    |  700000  |        |
|   UNO    |  800000  |        |

Note that the performance can be increased a lot by keeping track
of the lastRead(). See example **SD2405_demo_read_minute.ino**
An indication averaged around 44 us per update on UNO.


### Address

The SD2405 has a fixed address of 0x32, see datasheet

### I2C multiplexing

Imagine you want multiple clocks e.g. for different time zones.
Or just to average them to be more precise, or as backup of each other
so even swapping batteries can be done without loss of availability.

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
#include "SD2405.h"
```

### Constructor

- **SD2405(TwoWire \*wire = &Wire)** Constructor and I2C bus.
- **int begin()** initializes internals.
Returns error status.
- **bool isConnected()** checks if address (0x68) can be seen on the I2C bus.
- **uint8_t getAddress()** returns address (0x68) set in constructor.

### Base RTC

- **int read()** read the current time from the RTC.
- **int write()** set the current time in the RTC.
Writes all fields, be aware that weekDay need to be set too.
- **uint32_t lastRead()** lastTime in milliseconds when RTC is read.

### Getters

Getters return the last read value, to update call **read()** first.

Note that any call to **setSeconds()** etc overwrites the internal registers
of the library.

- **uint8_t seconds()** idem.
- **uint8_t minutes()** idem.
- **uint8_t hours()** idem.
- **uint8_t weekDay()** idem.
- **uint8_t day()** idem.
- **uint8_t month()** idem.
- **uint8_t year()** idem.

### Setters

Setters set a value, to update the RTC, call **write()** after setting all fields.

Note that **read()** will overwrite all internal registers.

- **void setSeconds(uint8_t value)** 0..59
- **void setMinutes(uint8_t value)** 0..59
- **void setHours(uint8_t value)** 0..23
- **void setWeekDay(uint8_t value)** 1..7  1 = Monday .. 7 = Sunday (?)
- **void setDay(uint8_t value)** 1..31
- **void setMonth(uint8_t value)** 1..12
- **void setYear(uint8_t value)** 0..99

Note: you can also adjust just one field and keep the others.


### Temperature

Note that the temperature measurement is only refreshed every 64 (default),
128, 256 or 512 seconds.
The interval can be set with bits 5 and 4 of the CONTROL/STATUS register (0x0F).

- **float getTemperature()** return temperature in 0.25°C steps.


### Low level: Read/WriteRegister

Allows to access all functionality the library did not implement (yet).
Check datasheet for details per register.
Use with care.

- **int readRegister(uint8_t reg)**
- **int writeRegister(uint8_t reg, uint8_t value)**


### Debug

In case of an I2C error one can get the last return value
of ```wire.EndTransmission()``` to get an indication of the problem.

- **int lastRv()** values depend on platform used.


## SD2405 SRAM

**Experimental** SRAM support, needs to be tested / verified.
Feedback welcome.

SRAM is SD2405 specific, and it has 236 bytes.
The following functions use index 0..235.
The user should guard the index especially for the 16 and 32 bit versions as
the boundaries are not checked.

236 bytes can be used e.g. to hold 78 hms timestamps.

- **int SRAMwrite8(uint8_t index, uint8_t value)**
- **int SRAMwrite16(uint8_t index, uint16_t value)**
- **int SRAMwrite32(uint8_t index, uint32_t value)**
- **uint8_t SRAMread8(uint8_t index)**
- **uint16_t SRAMread16(uint8_t index)**
- **uint32_t SRAMread32(uint8_t index)**


## Future


#### Must

- improve documentation.
- get hardware to test

#### Should

- test platforms
- test performance / footprint
- test SRAM with a SD2405 (need hardware + time)
- implement more functionality (need hardware + time)
- investigate behavior internal battery at low temperature (< 0 C)

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


