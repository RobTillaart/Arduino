
[![Arduino CI](https://github.com/RobTillaart/LTR390_DFR/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LTR390_DFR/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LTR390_DFR/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LTR390_DFR/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LTR390_DFR/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LTR390_DFR.svg)](https://github.com/RobTillaart/LTR390_DFR/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LTR390_DFR/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LTR390_DFR.svg?maxAge=3600)](https://github.com/RobTillaart/LTR390_DFR/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LTR390_DFR.svg)](https://registry.platformio.org/libraries/robtillaart/LTR390_DFR)


# LTR390_DFR

Arduino library for the I2C LTR390 UV sensor (DF Robotics edition).


## Description

**Experimental**

This library is to read the LTR390 UV sensor on the DF Robotics
break-out board.

Operating voltage range: **3.0V .. 5.0V** (tolerant).


## I2C

The break-out has an address of 0x1C == 28 decimal.

#### I2C Speed

The device should work on 100 kHz and 400 kHz I2C bus.

To be tested.


#### Multiplexing

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


## Interface   TODO elaborate...

```cpp
#include "LTR390_DFR.h"
```

#### Constructor

- **LTR390_DFR(TwoWire \* wire = &Wire)** Constructor 
with optional Wire interface.
- **bool begin()** returns true if device 0x1C can be seen on the I2C bus.
- **bool isConnected()** returns true if device 0x1C can be seen on I2C bus.
- **uint8_t getAddress()** returns 0x1C, fixed address, for convenience.


#### Main control

- **void setALSMode()**
- **void setUVSMode()**
- **void reset()** blocks for 100 ms.


#### Measurement configuration

- **void setGain(uint8_t gain)** gain = 0..4,
- **uint8_t getGain()** returns set value.
- **void setMeasurement(uint8_t resolution, uint8_t time)**
- **uint8_t getResolution()**
- **uint8_t getTime()**


#### Part and revision ID

- **uint8_t getPartID()** returns 11.
- **uint8_t getRevisionID()** returns 2.


#### Get data

- **uint32_t getALSData()**
- **float getLUX(float wfac = 1)** wfac = window factor,
- **uint32_t getUVSData()**
- **float getUVI(float wfac = 1)** wfac = window factor,


## Future

#### Must

- Elaborate and improve documentation a lot.
  - add tables, ranges etc.
- test with right hardware.
- keep in sync with LTR390_RT when possible

#### Should

- add examples
- fix / elaborate TODO's in code.
  - status and error codes
  - interrupts and thresholds
- add setUVsensitivity()

#### Could

- add error handling
- unit test ==> test examples

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


