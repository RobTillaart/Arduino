
[![Arduino CI](https://github.com/RobTillaart/DS1683/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS1683/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS1683/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS1683/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS1683/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS1683.svg)](https://github.com/RobTillaart/DS1683/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS1683/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS1683.svg?maxAge=3600)](https://github.com/RobTillaart/DS1683/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS1683.svg)](https://registry.platformio.org/libraries/robtillaart/DS1683)


# DS1683

Arduino library for the I2C DS1683 elapsed time monitor.


## Description

**Experimental, work in progress**

This library is used to communicate with the I2C DS1683 from an Arduino.

The DS1683 is an elapsed time monitor with an internal calibrated clock.
So there is no external clock needed.
The device also features an internal EEPROM to keep the data in case of a 
power loss (according to datasheet). 

The DS1683 reads the state of the EVENT pin, when the pin is pulled HIGH,
the value of the event time counter (ETC) is fetched from the EEPROM and 
the clock continues. When the pin goes to LOW, the event counter (EC) is 
incremented and the ETC is stored in EEPROM again.

When the EVENT pin changes, I2C is unavailable for up to 300 milliseconds.

The maximum value of the event time counter is 32 bit in quarter seconds => ~34 year.
The maximum value of the Event Counter is 16 bit => 65.535.
Both counters can be reset to zero if needed.

Furthermore the device has two ALARM registers, one for Event Time and one 
for Event Count.
If one or both these values are reached or exceeded the ALARM pin will trigger.
The polarity of the ALARM pin can be configured.

Finally the device has a PASSWORD function to control write access to the device.

Applications for the DS1683 include (but are not limited to) time-of-use,
getting an alarm when (re)calibration or preventive maintenance is needed.

The DS1683 library is not tested with hardware yet.  

Datasheet: 19-6388; Rev 0; 6/12

Feedback as always is welcome.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


### Hardware

See datasheet for details.

```
             TOPVIEW DS1683
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
- https://github.com/RobTillaart/DS1682
- https://github.com/RobTillaart/DS1683
- https://github.com/RobTillaart/StopWatch_RT - idem.

Other
- https://github.com/RobTillaart/PrintHelpers


### Tested

TODO: Get hardware and test on Arduino UNO and ESP32.
A breakout board would be useful for testing different platforms.


## Compatibles

The DS1682 and DS1683 have the same pin layout, however they have
a complete different internal register layout. 
So this library cannot be used for a DS1683.

The DS1683 has additional password and reset options. 

No compatibles known.


## I2C

### I2C Address

The device has a fixed I2C address of 0x6B (107) so only one device per I2C bus can be used.
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
#include "DS1683.h"
```

### Constructor

- **DS1683(TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the fixed address 0x2A (42).


### Configuration

Datasheet - page 10

- **int setConfiguration(uint8_t mask)**
- **uint8_t getConfiguration()**

| BIT | NMEMONIC | DESCRIPTION |
|:---:|:---------|:------------|
|  0  | ALRM POL | Alarm Polarity
|  1  | EC ENAB  | Event Counter Alarm Enable
|  2  | ETC ENAB | Event Timer Alarm Enable
| 3-7 | not used | always 0

Changing the configuration implies reading the current configuration,
change the bit and write the configuration back.


### Command

| BIT | NMEMONIC | DESCRIPTION |
|:---:|:---------|:------------|
|  0  | CLR-ALM  | Clear Alarm
| 1-7 | not used |
- **int setCommand(uint8_t command)**
- **uint8_t getCommand()**


### Status

| BIT | NMEMONIC | DESCRIPTION |
|:---:|:---------|:------------|
|  0  | ETC AF   | Event Timer Flag
|  1  | EC AV    | Event Counter Flag
|  2  | EVENT    | status EVENT pin
| 3-7 | not used |
- **uint8_t getStatus()**


### Alarm

Datasheet - page 9

For ease of use the alarm API works in seconds.

- **int setEventTimeAlarm(uint32_t alarm)** sets the alarm in seconds, max 1.073.741.823
- **uint32_t getEventTimeAlarm()** returns set alarm time in seconds.
- **int setEventCountAlarm(uint16_t alarm)** sets the alarm in counts
- **uint16_t getEventCountAlarm()**


### Read Counters

Datasheet - page 9

The elapsed time counter (ETC) is controlled by the status of the EVENT pin.
When EVENT pin is HIGH the clock is running, when the EVENT line is LOW
the clock is pausing.

- **uint32_t getElapsedSeconds()** returns seconds of runtime (QSEC/4).
max 1.073.741.823 which is ~34 years.
- **uint32_t getElapsedQSEC()** returns internal quarter seconds value.
- **uint32_t getEventCounter()** returns event counter, is the number of times
the EVENT pin goes HIGH/LOW (16 bit, max 65.535).


### Reset Counters

The EC and ETC registers can be reset to zero if and only if the 
EVENT pin is LOW. The library supports only a reset to zero (for now).

- **int resetEventTime()** set Event Time Counter to zero.
- **int resetEventCounter()** set Event Counter to zero.


### EEPROM

Datasheet - page 9,11

EEPROM address = 0..15

- **int setEEPROM(uint8_t address, uint8_t value)** idem.
- **uint8_t getEEPROM(uint8_t address)** idem.


### Password

Datasheet - page 12,15

**USE WITH CARE**

- **int setPasswordEntry(uint32_t value)** enter a password to unlock 
write permissions for the device.
- **int setPasswordValue(uint32_t value)** change the password of the device.

The DS1683 has a uint32_t password (4 bytes). 
If you enter the right password you get write permissions to the device.
This includes write permission to change the password with **setPasswordValue()**.

Notes:
- **USE WITH CARE**
- The password registers return zero when read, not supported.
- The default password = 0xFFFFFFFF
- There is no known way for factory reset. 
- To disable write access to the device, enter an invalid entry.


### Debug

- **uint8_t getLastError()** returns last error of low level communication.


## Future

#### Must

- improve documentation
- get hardware to test
- sync DS1682/DS1683

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
  - password
- add unit tests (if possible)


#### Wont

- support reset to other values, why?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


