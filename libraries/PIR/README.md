
[![Arduino CI](https://github.com/RobTillaart/PIR/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PIR/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PIR/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PIR/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PIR/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PIR/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PIR.svg?maxAge=3600)](https://github.com/RobTillaart/PIR/releases)


# PIR

PIR library for Arduino. Supports up to 8 PIR sensors.

## Description

The PIR library implements a class to monitor 1 or more PIR sensors. 
The library supports up to 8 PIR sensors per object, which typically are added in **setup()**.
It is possible to add a sensor (pin) multiple times. 
The library accepts duplicates.

The library has two **read()** functions, one to read a specific sensor, and one to read all of them. 
The latter will return a mask indicating HIGH and LOW.
The first added PIR will have the LSB.

Instead of PIR sensors one can add other DigitalOut sensors or even switches.


## Interface

#### Base

- **PIR()** constructor. 
- **uint8_t add(uint8_t pin)** adds a PIR pin to the set of pins.
Returns the index or PIR_ARRAY_FULL (0xFE)
- **uint8_t count** returns number of PIR sensors added.

#### Read

- **uint8_t read()** read all PIR sensors in the set.
Returns a mask of HIGH / LOW values.
Not used slots will return 0.
- **uint8_t read(uint8_t index)** read a specific PIR sensor.
Faster than read() above.


## Future

#### Must
- update documentation

#### Should
- add examples
  - interrupts?

#### Could
- investigate PIR16 PIR32 class that can hold more
  - think MEGA2560.
- investigate noise
- add statistics?
  - # calls # high% # low%
  - duration
- timestamp per PIR
  - lastRead, lastTriggered?
- PIR class based upon a PCF8574?


