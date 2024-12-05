
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

This SD2405 library provides a interface to read and write the date
and time to and from the I2C SD2405 RTC device and compatibles.
Furthermore one can set alarms in many formats.

An unique feature of the SD2405 is the **internal battery**, which should 
be able to keep the RTC running for 6 months or more. The datasheet mentions
at least a 100 recharges which could be interesting for very long running projects. 
It is unclear how well the internal battery works when temperature drops.

What is different from other RTC libraries is that it directly provides fields like
seconds, minutes etc. and not use ``` time structs``` from libraries like
```time.h``` or ```timelib.h```. This has its pros and cons of course.
Goal is to improve the ease of use for those who just need the date and time 
elements.

The library only supports the 24 hour per day model to minimize footprint.
Subtracting 12 hours is not difficult if one needs an **AM/PM** layout.

The library supports two generic **readRegister()** and **writeRegister()** functions.
These two functions allows users access to all registers and to do anything possible.

The SD2405 has several functions not found on other RTC's, especially a
correction for the clock to minimize deviations (ppm). 
Check out **int adjustClockFrequency(int32_t oscillator, int32_t target)** below.

Note: This SD2405 library is a refactored version of an older experimental 
SD2405 library from 2022 which was never published. 
The API (base RTC functions), documentation and examples is recently (0.1.1) 
aligned with my DS3232 library.

Note: The current library is not tested yet with hardware.

Feedback as always is welcome, please open an issue on GitHub.


### Compatibles

No known compatible RTC's.

The base time function calls are similar to those of the DS3232, only the
I2C address differs. The DS3232 = 0x68, where the SD2405 = 0x32.
However the (extended) control and alarm registers differ. 

Furthermore the DS3232 has 236 bytes of SRAM, where the SD2405 has (only) 12 bytes.


### Related

- https://github.com/RobTillaart/DS3232
- https://github.com/RobTillaart/dateTimeHelpers
- https://forum.arduino.cc/t/got-time-from-ntp-server-need-day-of-week/117799/6


## Hardware

Always check datasheet for connections.

Pull ups are needed on SDA, SCL.


## I2C

### Performance

I2C bus speed is not mentioned in the datasheet.
However it is expected to supports up to 400 KHz.  (feedback welcome).

Timing of UNO with SD2405 of **read()** in microseconds.

|  board   |  speed   |  time  |  notes  |
|:--------:|:--------:|:------:|:-------:|
|   UNO    |   50000  |        |
|   UNO    |  100000  |        |
|   UNO    |  200000  |        |
|   UNO    |  300000  |        |
|   UNO    |  400000  |        |  max official supported ??
|   UNO    |  500000  |        |
|   UNO    |  600000  |        |
|   UNO    |  700000  |        |
|   UNO    |  800000  |        |

Note that the performance can be increased a lot by keeping track
of the **lastRead()**. See example **SD2405_demo_read_minute.ino**
An indication averaged around 44 us per update on an Arduino UNO.
(measured on a DS3232 which is quite compatible).


### Address

The SD2405 has a fixed address of **0x32** or 50 decimal, see datasheet.

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

- **SD2405(TwoWire \*wire = &Wire)** Constructor and optional set the I2C bus, e.g. to Wire1.
- **int begin()** initializes internals.
Returns error status.
- **bool isConnected()** checks if address (0x32) can be seen on the I2C bus.
- **uint8_t getAddress()** returns fixed address (0x32).

### Base RTC

- **int read()** read the current day and time fields from the DS2405 RTC.
- **int write()** write the current day and time fields to the DS2405 RTC.
Writes all fields, be aware that weekDay need to be set too. 
- **uint32_t lastRead()** lastTime in milliseconds when RTC is read.


The **lastRead()** value allows e.g. to track the seconds in the MCU using
millis() and only reread the RTC once every minute. 
Even longer periods before rereading the RTC are possible depending on 
what the project needs.


### Getters

Getters return the last value read, to update these fields call **read()** first.

Note that any call to **setSeconds()** etc. overwrites the internal variables
of the library. So use with care. 

- **uint8_t seconds()** returns 0..59.
- **uint8_t minutes()** returns 0..59.
- **uint8_t hours()** returns 0..23.
- **uint8_t weekDay()** returns 0..6  0 = Sunday  6 = Saturday
- **uint8_t day()** return 1..31 (depending on month of course).
- **uint8_t month()** returns 1..12.
- **uint8_t year()** return 0..99.


### Setters

Setters set a value, to update the RTC, call **write()** after setting all 
fields that need to be updated. E.g. month or year is less expected to need 
an update.

Note that **read()** will overwrite all internal registers. So use with care. 

The ranges of the values are not checked, this might change in the future.

- **void setSeconds(uint8_t value)** 0..59
- **void setMinutes(uint8_t value)** 0..59
- **void setHours(uint8_t value)** 0..23
- **void setWeekDay(uint8_t value)** 0..6  0 = Sunday  6 = Saturday
- **void setDay(uint8_t value)** 1..31
- **void setMonth(uint8_t value)** 1..12
- **void setYear(uint8_t value)** 0..99

Note: you can also adjust just one field and keep the others as they are.
E.g. if you only need the year month day and are not interested in the time.


### Configure interrupts

See datasheet for details.

The INT pin can generate interrupts from three sources. 
The duration of a pulse is ~250 ms according to the datasheet.

- **int configureInterrupt(uint8_t source, bool repeat, bool autoReset)**
  - source: disable = 0, 1 = alarm, 2 = frequency, 3 = timer
  - repeat: single = false, repeat = true until INTAF is reset
  - autoReset: ARST = 0 = false, ARST = 1 = true.
- **int resetInterruptFlags()** reset both INTAF (alarm) INTDF (count down) manually.


### Alarm interrupts

See datasheet for details.

Setters, most are similar to the setters of the day/time, except **setAlarmWeek()**.
This one uses bit mask of all 7 days of the week and multiple can be selected.


- **int setAlarmSecond(uint8_t value)**
- **int setAlarmMinute(uint8_t value)**
- **int setAlarmHour(uint8_t value)**
- **int setAlarmWeek(uint8_t value)** value == bit mask of weekdays.
  - bit_mask == { 0 sat fri thu wed tue mon sun } == LSB oriented list.
- **int setAlarmDay(uint8_t value)**
- **int setAlarmMonth(uint8_t value)**
- **int setAlarmYear(uint8_t value)**

Getters, return the last set value.

- **int getAlarmSecond()**
- **int getAlarmMinute()**
- **int getAlarmHour()**
- **int getAlarmWeek()** returns a bit mask of weekdays.
  - bit_mask == { 0 sat fri thu wed tue mon sun } == LSB oriented list.
- **int getAlarmDay()**
- **int getAlarmMonth()**
- **int getAlarmYear()**

Enable which alarm interrupts:

- **int setAlarmInterrupt(uint8_t bit_mask)** The bit mask represents which 
alarms are checked. 
There can be multiple in parallel, check datasheet for detailed behaviour.
  - bit_mask == { 0 Y M W D H Min S }


### Frequency interrupts

See datasheet for details.

- **int setFrequencyMask(uint8_t bit_mask)** values of the bit mask see table below.

|  value  |     Hz  |  |  value  |     Hz  |
|:-------:|--------:|--|:-------:|--------:|
|    0    |      0  |  |    8    |      4  |
|    1    |  32768  |  |    9    |      2  |
|    2    |   4096  |  |   10    |      1  |
|    3    |   1024  |  |   11    |    1/2  |
|    4    |     64  |  |   12    |    1/4  |
|    5    |     32  |  |   13    |    1/8  |
|    6    |     16  |  |   14    |   1/16  |
|    7    |      8  |  |   15    |     1S  |


### CountDown interrupts

See datasheet for details.

With **setCountDown()** one can set a countdown timer in 0..255 units.
The size of the unit is defined by **setCountDownMask()**. 
One can make an alarm that goes off every 5 minutes.
See ranges in table below.

- **int setCountDownMask(uint8_t bit_mask)** 0..3, values see table below.
- **int setCountDown(uint8_t value)** 0..255

|  value  |  Source Hz  |  range                  |  notes  |
|:-------:|:-----------:|:-----------------------:|:--------|
|    0    |     4096    |  1 - 255/ 4096 seconds  |  1/100 ~~ 41/4096
|    1    |       64    |  1 - 255/64 seconds     |
|    2    |        1    |  1 - 255 seconds        |
|    3    |      1/60   |  1 - 255 minutes        |


### Time Trimming

Read datasheet section (twice).

This is IMHO a great feature of the SD2405 is the option to tune the oscillator
or crystal with a few ppm to be even more precise.
Internally it adds or skips clock beat to run a bit faster or slower.

- **int adjustClockFrequency(int32_t oscillator, int32_t target)**
  - oscillator is the actual clock (IST = e.g. 32760).
  - target is the wanted clock (SOLL = e.g.32768).


### Other functions

- **int enableWriteRTC()** enable writing to the date time registers.
- **int disableWriteRTC()** disable writing to the date time registers

- **int setFOBAT(bool flag)** enable / disable the INT output when
running on batteries. See datasheet for details.
- **bool getRCTF()** read only status of power (something).
See datasheet for details.


### SD2405 SRAM

SRAM support, needs to be tested / verified.
Feedback welcome.

SRAM has 12 bytes.
The following functions use index 0..11.
The user should guard the index especially for the 16 and 32 bit versions as
the boundaries are not checked.

12 bytes can be used e.g. to hold about 3 timestamps.

- **int SRAMwrite8(uint8_t index, uint8_t value)**
- **int SRAMwrite16(uint8_t index, uint16_t value)**
- **int SRAMwrite32(uint8_t index, uint32_t value)**
- **uint8_t SRAMread8(uint8_t index)**
- **uint16_t SRAMread16(uint8_t index)**
- **uint32_t SRAMread32(uint8_t index)**


### Low level: readRegister - writeRegister

Allows to access all functionality the library does not implement.
Check datasheet for details per register.
Use with care.

- **int readRegister(uint8_t reg)**
- **int writeRegister(uint8_t reg, uint8_t value)**


## Future


#### Must

- improve documentation.
- get hardware to test

#### Should

(need hardware + time)

- test performance / footprint / I2C clock speed.
  - fill table
- investigate INTerrupts
  - check duration of INT pulses.
- test SRAM with a SD2405 
- investigate behaviour internal battery at low temperature ( < 0 C)
- test platforms
- verify weekday need to be written too (as it can be calculated from others)

#### Could

- optimize read / write
  - fetch only needed fields e.g. only S or HHMMSS or YYMMDD or ...
  - would reduce communication time.
  - int read(register, count = 1);
  - int write(register, count = 1);
- add examples
- cache control registers to improve performance.
  - only after confirmed with hardware.
- optimized bcd2dec (from fast math)
- register names instead of numbers?
- add error handling
  - last value rv?


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


