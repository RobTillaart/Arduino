
[![Arduino CI](https://github.com/RobTillaart/LTR390_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LTR390_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LTR390_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LTR390_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LTR390_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LTR390_RT.svg)](https://github.com/RobTillaart/LTR390_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LTR390_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LTR390_RT.svg?maxAge=3600)](https://github.com/RobTillaart/LTR390_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LTR390.svg)](https://registry.platformio.org/libraries/robtillaart/LTR390)


# LTR390

Arduino library for the I2C LTR390 UV sensor.


## Description

**Experimental**

This library is to read the LTR390 UV sensor directly.

It was written after I ordered a LTR390 sensor (breakout) from DFRobotics.
However that one had its own processor and its own interface. 
So the result was two libraries for the same product.

**Warning:** Operating voltage range: **1.7V .. 3.6V**  
So it will not work on 5V devices


## I2C

The device has a fixed address of 0x53 == 83 decimal according to datasheet.

#### I2C Speed

The device should work on 100 kHz and 400 kHz I2C bus.

To be tested.


#### I2C Multiplexing

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


#### Related

- https://github.com/RobTillaart/LTR390_RT   (native LTR390)
- https://github.com/RobTillaart/LTR390_DFR  (DF Robotics variant)


## Interface

```cpp
#include "LTR390.h"
```

#### Constructor

- **LTR390(TwoWire \* wire = &Wire)** Constructor 
with optional Wire interface.
- **bool begin()** returns true if device 0x53 can be seen on the I2C bus.
- **bool isConnected()** returns true if device 0x53 can be seen on I2C bus.
- **uint8_t getAddress()** returns 0x53, fixed address, for convenience.


#### Main control

- **void setALSMode()**
- **void setUVSMode()**
- **void reset()** blocks for 100 ms.
- **void enable()** idem.
- **void disable()** idem.
- **bool isEnabled()** returns current status.


#### Measurement configuration

- **void setResolution(uint8_t resolution)** resolution = 0..5
- **uint8_t getResolution()**
- **void setRate(uint8_t rate)** rate = 0..7
- **uint8_t getRate()**
- **void setGain(uint8_t gain)** gain = 0..4
- **uint8_t getGain()**


#### Part and revision ID

- **uint8_t getPartID()** returns 11.
- **uint8_t getRevisionID()** returns 2.


#### Main status

- **uint8_t getStatus()** need split? or masks?


#### Get data

- **uint32_t getALSData()**
- **uint32_t getUVSData()**


#### Interrupt

- **int setInterruptConfig(uint8_t value)**
- **uint8_t getInterruptConfig()**
- **int setInterruptPersist(uint8_t value)**
- **uint8_t getInterruptPersist()**


#### Threshold

- **void setHighThreshold(uint32_t value)**
- **uint32_t getHighThreshold()**
- **void setLowThreshold(uint32_t value)**
- **uint32_t getLowThreshold()**


## Future

#### Must

- Elaborate and improve documentation a lot.
  - add tables, ranges etc.
- test with right hardware.

#### Should

- add examples.
  - test example
  - performance example
- fix / elaborate TODO's in code.
  - status and error codes
  - interrupts and thresholds
- add **float getLUX(float wfac = 1)**
- add **float getUVI(float wfac = 1)**

#### Could

- add error handling
- unit test or test example?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


