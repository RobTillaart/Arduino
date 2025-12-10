
[![Arduino CI](https://github.com/RobTillaart/DS1804/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS1804/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS1804/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS1804/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS1804/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS1804.svg)](https://github.com/RobTillaart/DS1804/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS1804/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS1804.svg?maxAge=3600)](https://github.com/RobTillaart/DS1804/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS1804.svg)](https://registry.platformio.org/libraries/robtillaart/DS1804)


# DS1804

Arduino library for DS1804 Nonvolatile Trimmer Potentiometer.


## Description

**Experimental**

The library implements a class for the DS1804 potentiometer.
These devices come in 10K, 50K and 100K and allows control in 100 steps.

The DS1804 has a simple pulse interface and can **not** be read back
so the library can not provide the current position of the wiper.

The DS1804 has an EEPROM to save the current position (writeable for 50000 times)
and uses that value as start position at power up.

Feedback as always is welcome.


### Power up / down

(from datasheet)  
On **power-up**, wiper position will be loaded within a maximum time
period of **500 µs** once the power-supply is stable.
Additionally, the three-terminal interface port will be active after **50 ms**. 

On **power-down**, the wiper position register data will be **lost**. 
On the next device power-up, the value of
EEPROM memory will be loaded into the wiper position register.

There is no defined factory default, expect the value to be random.
As the device has no feedback, one must send 100 pulses to move the trimmer to the begin or end point.


### Alternative use

One could use the UP/ DOWN pins of the device to read signals from an 
external system. The microprocessor could monitor the state by means of an
ADC measurement (and optional act upon it).

This is not implemented in the library, just worth to mention.
 

### Related

Other digipots (not all)

- https://github.com/RobTillaart/AD520x
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5248 (also AD5243)
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X
- https://github.com/RobTillaart/DS1804


## Interface

```cpp
#include "DS1804.h"
```

### Constructor

- **DS1804(uint8_t csPin, uint8_t incPin, uint8_t udPin)** constructor.
- **void begin(bool b = false)** initializes pins, 
default the device is not selected.


### Base

- **void select(bool b)** enable / disable device.
- **bool selected()** returns current status (csPin).
- **void moveUp(uint8_t steps = 1)** if enabled move position n steps up (steps is clipped to 0..100)
- **void moveDown(uint8_t steps = 1)** if enabled move position n steps down (steps is clipped to 0..100)

Duration of moveUp/Down depends linearly on the parameter steps, expect less than half a millisecond.

Note: One must send 100 pulses to move the trimmer to the begin or end point. (no feedback).


### EEPROM power up value

- **void saveEEPROM()** saves the current position to internal EEPROM.
Note the library cannot read this EEPROM value.

To set a value for sure, you might go 100x down and P times up to get 
at the requested position.

See **DS1804_save_EEPROM.ino**


## Future

#### Must

- improve documentation
- test with hardware

#### Should


#### Could

- default true for select() / begin()?

#### Wont

- void mute();  (depends on 3 pins if up or down is mute)

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

