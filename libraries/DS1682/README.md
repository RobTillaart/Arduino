
[![Arduino CI](https://github.com/RobTillaart/DS1682/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS1682/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS1682/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS1682/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS1682/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS1682.svg)](https://github.com/RobTillaart/DS1682/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS1682/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS1682.svg?maxAge=3600)](https://github.com/RobTillaart/DS1682/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS1682.svg)](https://registry.platformio.org/libraries/robtillaart/DS1682)


# DS1682

Arduino library for the I2C DS1682 elapsed time monitor.


## Description

**Experimental, work in progress**

This library is used to communicate with the I2C DS1682 from an Arduino.

The DS1682 is an elapsed time monitor with an internal calibrated clock.
So there is no external clock needed.
The device also features an internal EEPROM to keep the data in case of a 
power loss (according to datasheet). 

The DS1682 reads the state of the EVENT pin, HIGH => clock runs, LOW => pause,
to track e.g. the total run time of a motor.
The maximum value is 32 bit in quarter seconds => ~34 year.
Furthermore the device counts the number of times the EVENT pin goes HIGH/LOW
(17 bit counter = 131.071 max).
Finally the device has an ALARM register and an ALARM pin
that signals if the defined run time in the register is reached.
The polarity of the ALARM pin can be configured.

Applications for the DS1682 include (but are not limited to) time-of-use,
getting an alarm when (re)calibration or preventive maintenance is needed.

The DS1682 library is not tested with hardware yet.  

Datasheet: 19-6835; Rev 2; 11/18

Feedback as always is welcome.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


### Hardware

See datasheet for details.

```
             TOPVIEW DS1682
         +--------------------+
         |                    |
   pin 1 | o                o |  pin 8
   pin 2 | o                o |  pin 7
   pin 3 | o                o |  pin 6
   pin 4 | o                o |  pin 5
         |                    |
         +--------------------+
```

|  pin  |   name   |  description      |  Notes  |
|:-----:|:--------:|:------------------|:-------:|
|   1   |  EVENT   |  event line       |  HIGH = time runs, LOW = pause
|   2   |  N.C.    |  not connected    |
|   3   |  ALARM   |  Alarm            |  polarity can be configured
|   4   |  GND     |  Power ground     |
|   5   |  SCL     |  I2C clock        |
|   6   |  SDA     |  I2C data         |
|   7   |  N.C.    |  not connected    |
|   8   |  VCC     |  Power 2.5 - 5 V  |


### Related

Elapse time counters:
- https://github.com/RobTillaart/DS1862 - this library
- https://github.com/RobTillaart/StopWatch_RT - idem.

Other
- https://github.com/RobTillaart/PrintHelpers


### Tested

TODO: Get hardware and test on Arduino UNO and ESP32.
A breakout board would be useful for testing different platforms.


## Compatibles

The DS1683 is an upgraded version of the DS1682 with password and more
reset options. Although the pins are the same the registers and functions
are different so a DS1683 can not be controlled with this library.

_A DS1683 library is on my backlog list, so if time permits_

No compatibles known.


## I2C

### I2C Address

The device has a fixed I2C address of 0x6A (106) so only one device per I2C bus can be used.
The I2C communication supports 2.5-5.0V so any 3.3V MCU should be able to connect.
Do not forget appropriate pull up resistors on the I2C SDA and SCL lines.

If one needs more devices there are some options.
- One could use an I2C multiplexer (see below)
- One could use an MCU with multiple I2C buses.
- One could use a (Two-Wire compatible) SW I2C (outside scope of this library).

Using the VCC as a Chip Select is not advised.
It is unclear what effect this has on the lifetime and quality of the device.


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


### I2C Performance

|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  default
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |  max datasheet


TODO: run a performance sketch on hardware.


## Interface

```cpp
#include "DS1682.h"
```

### Constructor

- **DS1682(TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the fixed address 0x2A (42).


### Configuration

Datasheet - page 10

- **int setConfiguration(uint8_t mask)**
- **uint8_t getConfiguration()**

| Bit | Mnemonic | R/W | Description |
|:---:|:---------|:----|:------------|
|  0  | ECMSB    |  R  | Event Counter MSB
|  1  | AP       | R/W | Alarm Polarity
|  2  | RE       | R/W | Reset Enabled, enables reset() command.
|  3  | AOS      | R/W | Alarm Output Select
|  4  | WMDF     | R/W | Write Memory Disable Flag
|  5  | WDF      | R/W | Write Disable Flag
|  6  | AF       | R/W | Alarm Flag
|  7  | not used |  -  | always 0

Changing the configuration implies reading the current configuration,
change the bit and write the configuration back.


### Alarm

Datasheet - page 9

For ease of use the alarm API works in seconds.

- **int setAlarm(uint32_t alarm)** sets the alarm in seconds, max 1.073.741.823
- **uint32_t getAlarm()** returns set alarm time in seconds.

See datasheet for details.


### Read Counters

Datasheet - page 9

The elapsed time counter (ETC) is controlled by the status of the EVENT pin.
When EVENT pin is HIGH the clock is running, when the EVENT line is LOW
the clock is pausing.

- **uint32_t getElapsedSeconds()** returns seconds of runtime (QSEC/4).
max 1.073.741.823 which is ~34 years.
- **uint32_t getElapsedQSEC()** returns internal quarter seconds value.
- **uint32_t getEventCounter()** returns event counter, is the number of times
the EVENT pin goes HIGH/LOW (17 bit, max 131.072).

These counters can be reset by calling **reset(true)** twice!


### EEPROM

Datasheet - page 9,11

EEPROM address = 0..9

- **int setEEPROM(uint8_t address, uint8_t value)** idem.
- **uint8_t getEEPROM(uint8_t address)** idem.


### Reset and other

Datasheet - page 9,11

These functions need to be called twice to be effective!

- **int reset(bool flag)** resets timer and event counter to zero.
- **int writeDisable(bool flag)**
- **int memoryDisable(bool flag)**


### Debug

- **uint8_t getLastError()** returns last error of low level communication.


## Future

#### Must

- improve documentation a lot
- get hardware to test

#### Should

- configuration functions
  - bool setAlarmPolarity(int mode) // LOW = 0; HIGH all others
  - int getAlarmPolarity()
  - bool getAlarmFlag();
  - other on request?

#### Could

- improve error handling
- add examples
  - alarm
  - EEPROM
  - reset
- add unit tests (if possible)

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


