
[![Arduino CI](https://github.com/RobTillaart/FSLP/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FSLP/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FSLP/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FSLP/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FSLP/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FSLP.svg)](https://github.com/RobTillaart/FSLP/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FSLP/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FSLP.svg?maxAge=3600)](https://github.com/RobTillaart/FSLP/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FSLP.svg)](https://registry.platformio.org/libraries/robtillaart/FSLP)


# FSLP

Arduino library for FSLP Force Sensing Linear Potentiometer.

## Description

**Experimental**

This library is to use an FSLP, a potentiometer that can provide 
both position (like any potmeter) AND the pressure (how hard the user presses).

An FSLP is typical a strip with three or four contacts.

Library is written to better understand the working of these devices.
The code is based upon the **Force Sensing Linear Potentiometer (FSLP) Integration Guide** from InterlinkElectronics.com

Feedback as always is welcome.


### Hardware

```
           TOPVIEW FSLP                        Microprocessor
         +--------------+                   +--------------------+
         |              |                   |                    |
         |  DRIVE1  2 o |-------------------| o  GPIO            |
         |              |                   |                    |
         |   SENSE  1 o |-----------+------>| o  GPIO/ADC        |
         |              |           |       |                    |
         |              |          |R|      |                    |
         |              |          |R|      |                    |
         |              |          |R|      |                    |
         |              |           |       |                    |
         |      NC  4 o |           +-------| o  GPIO            |
         |              |                   |                    |
         |  DRIVE2  3 o |------------------>| o  GPIO/ADC        |
         |              |                   |                    |
         +--------------+                   +--------------------+
```

|  FSLP  |   name   |  Micro-proc   |  Notes  |
|:------:|:--------:|--------------:|:-------:|
|    1   |  SENSE   |  GPIO / ADC   |
|    2   |  DRIVE1  |  GPIO         |
|    3   |  DRIVE2  |  GPIO / ADC   |
|    4   |  NC      |               |
|   RRR  |          |  GPIO         |  resistor 4.7 - 10 kOhm.

See datasheet for details.


### Related

- https://github.com/RobTillaart/FSLP this library
- https://github.com/RobTillaart/FSR40X library for Force Sensing Resistors.
- https://github.com/RobTillaart/map2colour mapping a float to RGB colour spectrum.
- https://github.com/RobTillaart/pressure conversions.

Supplier of these devices (data sheets).

- https://InterlinkElectronics.com - manufacturer
- https://www.pololu.com/blog/336/new-products-and-demo-force-sensing-linear-potentiometers-and-resistors - devices


### Tested

TODO: Test on Arduino UNO and ESP32


### Performance

Figures from performance sketch, lib version 0.1.0

A call to getPressure() takes twice as long as a call to readPosition().

|  function         |  time in us  |
|:------------------|:------------:|
|  readPosition(1)  |     184      |
|  readPressure(1)  |     336      |
|  readPosition(2)  |     292      |
|  readPressure(2)  |     564      |
|  readPosition(3)  |     408      |
|  readPressure(3)  |     788      |
|  readPosition(4)  |     516      |
|  readPressure(4)  |    1008      |
|  readPosition(5)  |     628      |
|  readPressure(5)  |    1220      |


## Interface

```cpp
#include "FSLP.h"
```

constexpr float FSLP_NO_PRESSURE = 0.0f;

### Constructor

- **FSLP(uint8_t sense, uint8_t drive1, uint8_t drive2, uint8_t gpio)** See hardware
section above. The last GPIO parameter is connected to the resistor of 4.7 kOhm.

### Read

Parameter times is typical 1..5 to average multiple readings

- **float readPosition(uint8_t times = 1)** read potmeter
- **float readPressure(uint8_t times = 1)** read pressure 
- **float isPressed()** reads pressure only once to see if the device is pressed.
Returns 0 == false if not, otherwise the pressure value.
- **float getLastPosition()** returns last read position from cache.
If not read yet it returns 0.
- **float getLastPressure()** returns last read pressure from cache.
If not read yet it returns 0.

```constexpr float FSLP_NO_PRESSURE = 0.0f;``` exists for readability.


### Configuration

- **void setStabilizationDelay(uint8_t microsec = 10)** sets a delay 
before ADC can run. This may be set to zero. (do we need this?)
- **uint8_t getStabilizationDelay()** returns set value.
- **void setPressureFactor(uint8_t factor = 64)** scales readPressure()
to a project usable value. Default 64 is proposed in datasheet.
- **uint8_t getPressureFactor()** returns set value.
  
  
## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- **readForce()** better name?
  - **FSLR_NO_FORCE = 0**
- investigate if stabilization delay is needed (HW)
- investigate adding yield() somewhere
- add examples

#### Could

- set configurable threshold for pressure 
  - or a user defined pressure scale?
- investigate external ADC support (separate class?)
- add unit tests ?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


