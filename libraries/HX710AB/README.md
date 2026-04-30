
[![Arduino CI](https://github.com/RobTillaart/HX710AB/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HX710AB/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HX710AB/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HX710AB/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HX710AB/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HX710AB.svg)](https://github.com/RobTillaart/HX710AB/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HX710AB/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HX710AB.svg?maxAge=3600)](https://github.com/RobTillaart/HX710AB/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HX710AB.svg)](https://registry.platformio.org/libraries/robtillaart/HX710AB)


# HX710AB

Arduino library for the HX710A and HX710B 24-Bit ADC.


## Description

**Experimental**

This library provides two classes to read the HX710A and the HX710B ADC.

(from datasheet)

_The HX710(A/B) is a precision 24-bit analog-to-digital converter (ADC) with built-in
temperature sensor (HX710A) or DVDD, AVDD voltage difference detection (HX710B).
It’s designed for weigh scales and industrial control applications to interface
directly with a bridge sensor._

The HX710A can read the internal temperature.

THe HX710B can read the DVDD and AVDD supply voltage difference.

The HX710 has no means to detect errors, however several readings without noise
especially zero's might be an indication that something is wrong.

The HX710 is closely related to the HX711 which has more features.
These are not 1-to-1 replaceable devices.

If problems occur or there are questions, please open an issue at GitHub.


### Multiple devices

The library allows to have multiple devices on different pins.
When having an array of sensors the number of pins used adds up.

One way of reducing pins is to add a multiplexer e.g. HC4052,
which can select up to 4 devices allowing only 4 pins, or a 
MAX14661 which allows up to 16 devices.

- https://github.com/RobTillaart/HC4052 2 pins, 2x4 multiplexer.
- https://github.com/RobTillaart/MAX14661 I2C, 2x16 multiplexer.

Another way is to share the CLOCK pin for all devices and have an unique
DATA pin per device. This allows one to control N devices with N+1 pin.

In theory one could control (read) multiple devices in parallel,
however this library does not support such feature.
Seen a setup once having a shared CLOCK, and a 8 bit IO chip to read
up to 8 channels in parallel. There was some "bit magic" to split the
bits from the IO chips into the parallel DATA bytes.


### Breaking changes 0.2.0

Some functions have been renamed to bring the API in line with the HX711 library.

Pre-0.2.0 (experimental) versions are therefore obsolete.


### Performance

Performance depends on platform used and on the time to make a measurement.
The latter is either 10 or 40 Hz, which possibly means optional 100 or 25
milliseconds extra waiting time.

To minimize the blocking time the library implemented (0.1.2) an asynchronous 
interface to keep performance at maximum level.


### Related

- https://github.com/RobTillaart/HX710AB  this library.
- https://github.com/RobTillaart/HX711  for load cells.
- https://github.com/RobTillaart/HX711_MP  for load cells with multipoint calibration.
- https://github.com/RobTillaart/HX712  for load cells.
- https://swharden.com/blog/2022-11-14-hx710b-arduino/  usage with pressure sensor.
- https://http://www.aviaic.com/  (manufacturer)
- https://github.com/RobTillaart/weight  conversions
- https://github.com/RobTillaart/pressure  conversions


HX710B library for the MPS20N0040D pressure sensor.

- https://github.com/rppelayo/hx710B_pressure_sensor

About calibration

- https://makersportal.com/blog/2020/6/4/mps20n0040d-pressure-sensor-calibration-with-arduino


### Test

Tested HX710B with Arduino UNO.
- raw readings work
- pressure sensor drifts.
- two sensors tested have very different "zero point"


## Interface

```cpp
#include "HX710AB.h"
```

### Constructor

Two classes:

- **HX710A(uint8_t dataPin, uint8_t clockPin)** constructor.
- **HX710B(uint8_t dataPin, uint8_t clockPin)** constructor.
- **void begin(bool fastProcessor = false)** initialises pins.
The fastProcessor option adds a 1 uS delay for each clock half-cycle
to keep the time greater than 200 nS. 
If data does not makes sense, not stable one can try this flag.


### Read, synchronous

- **int32_t read(bool differential = true)** powers up the device,
reads from the device, sets the mode for the **next** read.
The default parameter is true as differential readings are most used.
See table below.
- **uint32_t last_time_read()** returns last time a value was read in milliseconds.
- **int32_t last_value_read()** returns last read value, note this can be
differential or other. The user should keep track of this.

|  differential  |  HX710A         |  HX710B         |  notes    |
|:--------------:|:---------------:|:---------------:|:---------:|
|   true         |  differential   |  differential   |  default  |
|   false        |  temperature    |  DVDD and AVDD  |


### Read, asynchronous

As the device might be blocking for up to 100 millis when using the synchronous
**read()**, the library offers an async way to read the device. 
This allows the user to do other tasks instead of active waiting.
In fact the **read()** is implemented with this async interface.

In fact the **read()** call might be blocking for an undetermined amount of time.
If the data line is not pulled LOW due to a broken device or bad connection the
**is_ready()** will never return true, causing an endless loop.
The asynchronous API gives the user a way to detect this situation and to act
in a project specific way to handle the problem.

- **void request()** wakes up the device to make a measurement.
- **bool is_ready()** checks if a measurement is ready.
- **int32_t fetch(bool differential = true)** 
reads from the device, sets the mode for the **next** read.
The default parameter is true as differential readings are most used.
See table above.


### Timeout

To prevent a blocking **read()** if a sensor is broken or due to a bad connection
the library has a timeout function (since 0.3.1).
If the timeout value is set to 0 (zero) the timeout will not be checked.
The default value is 1000 milliseconds.

Note that the sensor might need up to 100 millis to get ready, so setting the 
timeout to a too small value might result in not reading the sensor at all.
(getting series of zero's, optionally alternating, to investigate)

- **void set_timeout(uint32_t timeout)**
- **uint32_t get_timeout()** return set value.


### Calibration

The calibration for the HX710 is a two point calibration.
The reason for a two point calibration is that in contrast to the HX711 
for load cells, there is no "natural zero" per se.

One need to do two measurements M1(raw1, out1) and M2(raw2, out2).
These exists of two raw **read()** values for two known / calibrated 
**unit values**.

With these two measurements the following linear relation is derived 

```
units = (raw_in - offset) * scale;
```

After calibration one can get the parameters from the formula,
to be stored e.g. in EEPROM for a next time e.g. after reboot.


- **bool calibrate(int32_t raw1, float out1, int32_t raw2, float out2)**
calculates the scale and offset from the two measurements.
returns false if (raw1 == raw2) or (out1 == out2) as then scale and/or
offset can not be calculated.
- **float get_offset()** returns offset from the formula to store for next time.
- **float get_scale()** returns scale from the formula to store for next time.
- **void set_offset(float offset)** set offset in the formula (e.g. from EEPROM)
- **bool set_scale(float scale)** set scale in the formula (e.g. from EEPROM)
Returns false if scale is set to zero as this would make all measurements zero.

In code this could look like

```cpp
//  save calibration data
HXB.calibrate(125465, 1019.2,  159864, 1025.6);
EEPROM.set(offset_address, HXB.get_offset());
EEPROM.set(scale_address, HXB.get_scale());


//  load calibration data
HXB.set_offset(EEPROM.get(offset_address));
HXB.set_scale(EEPROM.get(scale_address));
```

The values from offset and scale should be compatible with the HX711 library.
However this is not tested (yet).


### Units

- **float get_units(uint8_t n = 1)** read the device in calibrated units.
Works only after calibration, see above.
The function can average n measurements (n = 1..255)

If the device is not calibrated, the offset == 0.0 and the scale == 1.0.
This implies that a **get_units()** call will return the raw measurement as a float.
Of course one can set these to these default values on purpose.


### Power

- **void power_down()** puts the device in sleep mode (after 60 us).
- **void power_up()** wakes up device.

Note the **read()** and **fetch()** functions automatically wake up the device.
So powerUp() is seldom needed.


## Future

#### Must

- improve documentation

#### Should

- test extensively
- add get_temperature() in HX710A
- add get_voltage() in HX710B

#### Could

- extend unit tests
- add examples.
- extend performance sketch

#### Wont

- bool isPowerUp();
- AVR optimized code - see FastShiftIn.
  (low gain as sensor blocks at 10/40 Hz)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


