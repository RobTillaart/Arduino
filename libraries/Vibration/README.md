
[![Arduino CI](https://github.com/RobTillaart/Vibration/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Vibration/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Vibration/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Vibration/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Vibration/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Vibration.svg)](https://github.com/RobTillaart/Vibration/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Vibration/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Vibration.svg?maxAge=3600)](https://github.com/RobTillaart/Vibration/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Vibration.svg)](https://registry.platformio.org/libraries/robtillaart/Vibration)


# Vibration

Arduino library for a vibration / tilt sensor e.g. SW-420, SW-18010P.


## Description

**Experimental**

This library is to interact with an analog vibration sensor. 
Goal is to detect if there is movement or tilt.

Vibration sensors, a.k.a. tilt switches can work in different ways so they are 
meant for different applications.
Some have a conducting ball that has a home position and when vibrations occur
or when tilted it will move out of this position, connecting a switch.
If the sensor stays tilted the switch can stay connected for longer times. 
Some of the sensors e.g. SW-18010P, have a spring connected to the ball that forces
the ball to the home position if there is no vibration. Even in a tilted position.

The library assumes that the sensor connects to VCC when connected, so not connected 
reads as zero (0).
However the library uses analogReads so the sensor can e.g. also "load" a capacitor
which slowly increases the voltage (RC). 
This allows measuring a first order (relative) magnitude of a vibration.

The different functions of the library might fit more (or less) to your needs.
If functionality is missing, please open an issue.


### Interrupts

The library does not use interrupts to count the pulses of the vibration
 / tilt sensor. 
 For now it supports only polling to  see if there is any vibration. 
As vibrations are relative long in CPU clock cycles, polling a few times
per second worked well for my needs.


### Related

TODO


### Tested

Arduino UNO.


## Interface

```cpp
#include "Vibration.h"
```

### Constructor

- **VibrationSensor(uint8_t analogPin)** constructor, set the analogPin to use.
- **bool begin()** place holder for now.

### Measurements

- **float zeroCount(uint32_t duration, uint16_t noise = 10)** read the sensor, 
count the times the value is zero.
Returns the percentage reads as below or equal to noise level.
This noise level has a default value of 10.
- **uint16_t average(uint32_t duration)** reads the sensor for a defined duration,
but at least once. Returns the average of multiple reads.
- **uint16_t poll(uint32_t duration)** polls the sensor for a given duration
(in millis), with a minimum of one sample. 
The function returns the maximum value sampled.
Note this code is blocking for at least duration milliseconds.


## Future


#### Must

- improve documentation

#### Should


#### Could

- **bool isVibrating(uint8_t samples)** ?
- use (fast) external ADC.
  - https://github.com/RobTillaart/ADS1x15
  - https://github.com/RobTillaart/MCPADC
- add delay between average reads (option, blocks even longer).
- default values parameters?
- investigate interrupts.
  - platform specific probably
- investigate the acquisition time ==> differs per board.
- refactor interface - 0.2.0
  - measure(duration);
  - result functions.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


