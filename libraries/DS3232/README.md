
[![Arduino CI](https://github.com/RobTillaart/DS3232/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS3232/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS3232/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS3232/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS3232/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS3232.svg)](https://github.com/RobTillaart/DS3232/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS3232/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS3232.svg?maxAge=3600)](https://github.com/RobTillaart/DS3232/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS3232.svg)](https://registry.platformio.org/libraries/robtillaart/DS3232)


# DS3232

Arduino library for I2C DS3232 real time clock and compatibles.


## Description

This DS3232 library provides a minimalistic interface to read and write the date 
and time to and from the I2C DS3232 RTC device and compatibles.

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
However for people who need a full function DS3232 library check the excellent 
library at https://github.com/JChristensen/DS3232RTC


Note: This DS3232 library is a refactored version of an old experimental DS3232 library 
from 2011 which was never published.


#### Tests

All examples are tested with Arduino UNO with 100KHz I2C.


#### Compatibles

The DS3231 RTC is compatible for the date and time keeping part.
The only difference found is that the DS3231 does not have the 
236 bytes of **battery backupped** SRAM the DS3232 has.


#### Related

- https://github.com/JChristensen/DS3232RTC  (full featured DS3232 lib)
- https://github.com/RobTillaart/dateTimeHelpers


## Hardware

Always check datasheet for connections.

Pull ups are needed on SDA, SCL and other pins (datasheet).


## I2C 

#### Performance

I2C bus speeds officially supports up to 400 KHz.

Timing of UNO with DS3232 of **read()** in microseconds.

|  board   |  speed   |  time  |  notes  |
|:--------:|:--------:|:------:|:-------:|
|   UNO    |   50000  |  2011  |
|   UNO    |  100000  |  1072  |
|   UNO    |  200000  |   608  |
|   UNO    |  300000  |   442  |
|   UNO    |  400000  |   374  |  max official supported 
|   UNO    |  500000  |   328  |  indicative
|   UNO    |  600000  |   296  |  indicative
|   UNO    |  700000  |   280  |  indicative
|   UNO    |  800000  |   272  |  indicative

Note that the performance can be increased a lot by keeping track 
of the lastRead(). See example **DS3232_demo_read_minute.ino**
An indication averaged around 44us per update on UNO.


#### Address

Fixed address 0x68, both for DS3232 and DS3231, see datasheet

#### I2C multiplexing

Imagine you want multiple clocks e.g. for different time zones.
Or just to average them to be more precise, or as backup of each other
so even swapping batteries can be doen without loss of availability.

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
#include "DS3232.h"
```

#### Constructor

- **DS3231(TwoWire \*wire = &Wire)** Constructor and I2C bus.
- **DS3232(TwoWire \*wire = &Wire)** Constructor and I2C bus.
- **int begin()** initializes internals.
Returns error status.
- **bool isConnected()** checks if address (default 0x68) can be seen on the I2C bus.
- **uint8_t getAddress()** returns address (0x68) set in constructor.
- **uint16_t getType()** returns 3232 or 3231, depending on constructor.

#### Base RTC

- **int read()** read the current time from the RTC.
- **int write()** set the current time in the RTC.
Writes all fields.
- **uint32_t lastRead()** lastTime in milliseconds when RTC is read.

#### Getters

Getters return the last read value, to update call **read()** first.

- **uint8_t seconds()**
- **uint8_t minutes()**
- **uint8_t hours()**
- **uint8_t weekDay()**
- **uint8_t day()**
- **uint8_t month()**
- **uint8_t year()**

#### Setters

Setters set a value, to update the RTC call **write()** after.

- **void setSeconds(uint8_t value)**
- **void setMinutes(uint8_t value)**
- **void setHours(uint8_t value)**
- **void setDay(uint8_t value)**
- **void setMonth(uint8_t value)**
- **void setYear(uint8_t value)**

Note: weekDay cannot be set.

Note: you can also adjust just one field and keep the others.


#### Low level: Read/WriteRegister

Allows to access all functionality the library did not implement (yet).
Check datasheet for details per register.
Use with care.

- **int readRegister(uint8_t reg)**
- **int writeRegister(uint8_t reg, uint8_t value)**


#### Debug

In case of an I2C error one can get the last return value 
of ```wire.EndTransmission()``` to get an indication of the problem.

- **int lastRv()** values depend on platform used.


## Future

#### Must

- improve documentation.

#### Should

- test platforms
- test performance / footprint
- can the trick from the example be included in the library?
  - extra footprint?

#### Could

- add readDate() + readTime()
  - less IO
  - as date is not read so often?
- int getTemperature();
- SRAM 236 bytes
  - int SRAMwrite8(uint8_t index, uint8_t value);
  - int SRAMwrite16(uint8_t index, uint16_t value);
  - int SRAMwrite32(uint8_t index, uint32_t value);
  - int SRAMread8(uint8_t index, uint8_t value);
  - int SRAMread16(uint8_t index, uint16_t value);
  - int SRAMread32(uint8_t index, uint32_t value);
  - float and char array support?
- AM/PM support could be done in software.
  - simpler than decoding RTC?


#### Wont

Other extended functionality (or in derived class)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


