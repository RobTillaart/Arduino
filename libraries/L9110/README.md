
[![Arduino CI](https://github.com/RobTillaart/L9110/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/L9110/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/L9110/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/L9110/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/L9110/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/L9110.svg)](https://github.com/RobTillaart/L9110/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/L9110/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/L9110.svg?maxAge=3600)](https://github.com/RobTillaart/L9110/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/L9110.svg)](https://registry.platformio.org/libraries/robtillaart/L9110)


# L9110

Arduino library for L9110 motor driver.


## Description

**Experimental**

This library is to use L9110 motor driver.

The L9110 is a simple motor driver which only allows forward or reverse.
For this it uses two pins of which only one can be HIGH.
If both are LOW or both are HIGH the motor stops.

In this library these pins are named forwardPin and reversePin.
The library provides a simple class to switch between the three states
and a function to read the state.

The library was written for some small tests and might be useful for
other applications. There are some ideas to extend it.

Read the datasheet for details

Feedback as always is welcome.


### Compatible

TODO
check L293, L298, HG7881 (?)
might be more or less compatible, some have ENanble pin or multiple H bridges.


### Hardware

Check datasheet

```
           TOPVIEW L9110
         +---------------+
   pin 1 | o           o |  pin 8
   pin 2 | o           o |  pin 7
   pin 3 | o           o |  pin 6
   pin 4 | o           o |  pin 5
         +---------------+
```

|  pin  |  name  |  description     |  Notes  |
|:-----:|:------:|:-----------------|:-------:|
|   1   |    OA  |  Output motor    |
|   2   |   VCC  |  Supply voltage  |  2.5-12V
|   3   |   VCC  |  Supply voltage  |  2.5-12V
|   4   |    OB  |  Output motor    |
|   5   |   GND  |  Ground          |  0
|   6   |    IA  |  Input forward   |  2.5-9.0 V
|   5   |    IB  |  Input reverse   |  2.5-9.0 V
|   6   |   GND  |  Ground          |  0


### Related

- https://www.pololu.com/category/11/brushed-dc-motor-drivers
- https://github.com/RobTillaart/AS5600 - magnetic angle measurement
- https://github.com/RobTillaart/DRV8825 - stepper motor driver.
- https://github.com/RobTillaart/L9110


### Tested

Tested on Arduino UNO R3


## Interface

```cpp
#include "L9110.h"
```

### Constructor

- **L9110(uint8_t forwardPin, uint8_t reversePin)** set the direction pins.
- **void begin()** initializes pins, and puts the state in STOP mode.
- **void swapPins()** software switching the forward and reverse pin
to prevent soldering (again).

### Motor control

- **void forward()** move the motor forward.
- **void reverse()** move the motor in reverse.
- **void stop()** stops the motor.
- **uint8_t status()** returns status, see table below.

|  value  |  define         |  notes  |
|:-------:|:----------------|:-------:|
|    0    |  L9110_STOP     |  default start after begin().
|    1    |  L9110_REVERSE  |
|    2    |  L9110_FORWARD  |


## Missing ENable pin

TODO
- needs extra hardware

## Future

#### Must

- improve documentation
- fix TODO's in documentation and code

#### Should

- investigate if a single direction (1 pin) version works?
  - keep one pin LOW.
  - derived class or own class

#### Could

- implement PWM interface
  - a first test worked (not for low PWM values) however it is not included in the library
    as there were some effects I did not understood / investigate.
  - would allow "speed adjustments", e.g. void forward(uint8_t speed);
  - only PWM pins allowed, TODO how to handle "non PWM pins"
- counters
  - how long it runs? wear indication?
  - how often switched?
- examples
  - combination with e.g. ACS712/INA228 to measure motor current.
- direction / enable API
  - seen on other devices, separate class?


#### Wont

- performance measurements as code is much faster than motor inertia.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


