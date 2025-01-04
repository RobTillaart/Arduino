
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

**Experimental**

This SD2405 library provides a interface to read and write the date
and time to and from the I2C SD2405 RTC device and compatibles (SD2405AL).
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

The library supports two generic **readRegister()** and **writeRegister()** functions.
These two functions allows users access to all registers and to do anything possible.
In time these might move to the protected section of the library.

The SD2405 has several functions not found on other RTC's, especially a
correction for the clock to minimize deviations (ppm). 
Check out **int adjustClockFrequency(int32_t oscillator, int32_t target)** below.

Another important functionality is the option to enable and disable writing to the RTC.
be sure to **enableWriteRTC()** before **write()**.

**Note:** This SD2405 library is a refactored version of an older experimental 
SD2405 library from 2022 which was never published. 
The API (base RTC functions), documentation and examples is recently (dec 2024) 
aligned with my DS3232 library.

**Note:** not all functionality is tested yet. 
This will take several releases as my time is limited.

Feedback as always is welcome, please open an issue on GitHub.


### AM/PM

The library only supports the 24 hour per day model.
Subtracting 12 hours is not to difficult if one needs an **AM/PM** layout.

```
00:00 => 00:00 AM
11:00 => 11:00 AM
12:00 => 12:00 PM
13:00 => 01:00 PM
23:00 => 11:00 PM
```

### Breaking changes 0.2.0

The library is tested with hardware resulting in a 0.2.0 version with a lot
of code fixes in the library. Therefore the **pre 0.2.0 versions are obsolete**.

- disableWriteRTC() + enableWriteRTC() works as intended.
- read() + write() works as intended.
- SRAM functions work as intended.

Other functions, alarms, interrupts etc, are still to be verified.

Feedback as always is welcome, please open an issue on GitHub.


### Compatibles

There are no known compatible RTC's, if you encounter one please let me know.

Not compatible, the DS3232 has 236 bytes of SRAM, where the SD2405 has (only) 12 bytes.


### Related

- https://github.com/RobTillaart/DS3232
- https://github.com/RobTillaart/dateTimeHelpers
- https://forum.arduino.cc/t/got-time-from-ntp-server-need-day-of-week/117799/6


## Hardware

Always check datasheet for the connections.

Pull up resistors are needed on SDA, SCL. Value depend on length of wires.


## I2C

### Performance

Max I2C bus speed in the datasheet is 400 kHz, however 800 kHz still worked. 
However the gain above the official speed of 400 kHz is relative small.

Timing of UNO with SD2405 of **read()** in microseconds. Version 0.2.0.

|  board   |  speed   |  time  |  notes  |
|:--------:|:--------:|:------:|:-------:|
|   UNO    |   50000  |  2011  |
|   UNO    |  100000  |  1078  |  default bus speed
|   UNO    |  200000  |   606  |
|   UNO    |  300000  |   445  |
|   UNO    |  400000  |   377  |  max official supported
|   UNO    |  500000  |   341  |
|   UNO    |  600000  |   315  |
|   UNO    |  700000  |   299  |
|   UNO    |  800000  |   289  |

Use **SD2405_demo_performance.ino** to test your platform.

Note that the performance can be increased a lot by keeping track
of the **lastRead()**. See example **SD2405_demo_read_minute.ino**
If only read once per minute at 100 kHz would result in an **average**
read time of less than 20 us (still the peak time is 1078).


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
what your project needs.


### Enable disable writing

To enable write access to the device.

- **int enableWriteRTC()** enable writing to the date time registers.
- **int disableWriteRTC()** disable writing to the date time registers.


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

Note that **read()** will overwrite the internal variables. So use with care.

The ranges of the values are not checked, this might change in the future.

- **void setSeconds(uint8_t value)** 0..59
- **void setMinutes(uint8_t value)** 0..59
- **void setHours(uint8_t value)** 0..23
- **void setWeekDay(uint8_t value)** 0..6  0 = Sunday  6 = Saturday
- **void setDay(uint8_t value)** 1..31
- **void setMonth(uint8_t value)** 1..12
- **void setYear(uint8_t value)** 0..99

Note: you can call **read()** and adjust only one or two fields 
(typical seconds minutes) and keep the others as they are.


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

To be investigated.

- **int setFOBAT(bool flag)** enable / disable the INT output when
running on batteries. See datasheet for details.
- **bool getRCTF()** read only status of power (something).
See datasheet for details.


### SD2405 SRAM

The SD2405 has 12 bytes of SRAM. The following functions use index 0..11 (or less).
The user must guard the index especially for the 16 and 32 bit versions as
the boundaries are not checked. The behaviour of writing outside SRAM is unknown.

Note: 12 bytes can be used e.g. to hold about 3 timestamps.

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
- clean up code

#### Should

- add missing getters
  - control registers.
- test more with hardware (need time)
- investigate INTerrupts
  - check duration of INT pulses.
  - add examples
- test platforms


#### Could

- optimize read
  - fetch only needed fields e.g. only S or HHMMSS or YYMMDD or (possible?)
  - would reduce communication time.
  - int read(register, count = 1);
- add examples
  - AM/PM example.
- investigate behaviour internal battery at low temperature ( < 0 C)
- cache control registers to improve performance.
  - only after confirmed with hardware.
- optimized bcd2dec (from fast math)
- add error handling
  - last value rv?
- make read/writeRegister() protected.


#### Wont

- support AM/PM mode 12/24
- optimize write is not supported (datasheet)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


