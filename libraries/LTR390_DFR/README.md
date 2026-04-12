
[![Arduino CI](https://github.com/RobTillaart/LTR390_DFR/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LTR390_DFR/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LTR390_DFR/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LTR390_DFR/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LTR390_DFR/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LTR390_DFR.svg)](https://github.com/RobTillaart/LTR390_DFR/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LTR390_DFR/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LTR390_DFR.svg?maxAge=3600)](https://github.com/RobTillaart/LTR390_DFR/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LTR390_DFR.svg)](https://registry.platformio.org/libraries/robtillaart/LTR390_DFR)


# LTR390_DFR

Arduino library for the I2C LTR390 LUX / UV sensor (DF Robotics edition).


## Warning

**Always take precautions as UV radiation can cause sunburn, eye damage and other severe problems**.

Do not expose yourself to the sun as UV source too long.

When working with UV light, natural or artificial (TL LED laser a.o.) use appropriate shielding. Do not look right into UV light sources.


## Description

**Experimental**

This library is to read the LTR390 LUX / UV sensor on the DF Robotics
break-out board.

Operating voltage range: **3.0V .. 5.0V** (tolerant).

To elaborate (when time permits and hardware)


### 0.2.0 Changes

0.2.0 major update C++, kudos to Chris0xdeadbeef.
Details see changelog.md

#### Compiler Warnings (Arduino IDE)

This library uses [[nodiscard]] to help detect ignored return values.
However, Arduino IDE disables compiler warnings by default.
To benefit from this feature, enable warnings:

> File > Preferences > Compiler warnings > Default (or higher)

#### PlatformIO

Warnings are enabled by default, no additional configuration required.


## I2C

The break-out has a fixed address of 0x1C == 28 decimal.

### I2C Speed

The device should work on 100 kHz and 400 kHz I2C bus.

To be tested.


### Multiplexing

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



### Related

UV related

- https://en.wikipedia.org/wiki/Ultraviolet
- https://en.wikipedia.org/wiki/Ultraviolet_index
- https://github.com/RobTillaart/AnalogUVSensor
- https://github.com/RobTillaart/AS7331 - profi UVA, UVB, UVC sensor.
- https://github.com/RobTillaart/LTR390_DFR  (DF Robotics variant)
- https://github.com/RobTillaart/LTR390_RT   (native LTR390)
- https://github.com/RobTillaart/ML8511

Other

- https://github.com/RobTillaart/map2colour - for a continuous colour scale


## Interface   TODO elaborate...

```cpp
#include "LTR390_DFR.h"
```

### Constructor

- **LTR390_DFR(TwoWire \* wire = &Wire)** Constructor 
with optional Wire interface.
As the device has a fixed I2C address it cannot be set.
- **bool begin()** returns true if device address 0x1C can be seen on the I2C bus.
- **bool isConnected()** returns true if device address 0x1C can be seen on I2C bus.
- **uint8_t getAddress()** returns 0x1C, fixed address, for convenience.


### Main control

- **void setALSMode()** set the Ambient Light Sensor mode.
- **void setUVSMode()** set the Ultra Violet Sensor mode.
- **void reset()** resets the sensor. This call blocks for 100 ms.


### Gain configuration

- **uint8_t setGain(uint8_t gain = 1)** gain = 0..4, values larger than 4 are
clipped to 4. Default value = 1.
Returns the gain set = 0..4.
- **uint8_t getGain()** returns set value, 0..4.


|  Gain  |  factor  |  Notes  |
|:------:|:--------:|:-------:|
|   0    |     1    |
|   1    |     3    |  default
|   2    |     6    |
|   3    |     9    |
|   4    |    18    |


### Resolution and time

- **bool setMeasurement(uint8_t resolution, uint8_t time)**
Resolution = 0..5, Time = 0..7. See table below.
Returns false if one of the parameters is out of range.
- **uint8_t getResolution()** returns set value 0..5, default 2.
- **uint8_t getTime()** returns set value 0..7, default 2.


|  reso  |  bits  |   |  time  |  millis  |  notes  |
|:------:|:------:|:-:|:------:|:--------:|:-------:|
|   0    |   20   |   |   0    |     25   |
|   1    |   19   |   |   1    |     50   |
|   2    |   18   |   |   2    |    100   |  default both.
|   3    |   17   |   |   3    |    200   |
|   4    |   16   |   |   4    |    500   |
|   5    |   13   |   |   5    |   1000   |
|   6    |   na   |   |   6    |   2000   |
|   7    |   na   |   |   7    |   2000   |

14, 15 bits is not supported.


### UV sensitivity

- **bool setUVsensitivity(float sensitivity = 1.0f)** Sets the UV sensitivity 
between 0..1. Returns false if the parameter s is out of range.
Default value = 1.0f.
- **float getUVsensitivity()** returns set value. default 1.0.


### Part and revision ID

- **uint8_t getPartID()** returns 11.
- **uint8_t getRevisionID()** returns 2.


### Get data

- **uint32_t getALSData()** returns 18 bit data.
- **float getLUX(float wFactor = 1.0f)** wFactor = window factor, typical between 0.0f and 1.0f.
Returns the ambient light in LUX.
- **uint32_t getUVSData()** returns 18 bit data.
- **float getUVI(float wFactor = 1.0f)** wFactor = window factor, typical between 0.0f and 1.0f.
Returns the UV index in ? (TODO units).


### Enable / Disable

**Experimental**

- **void enable()** idem.
- **void disable()** idem.
- **bool isEnabled()** returns current status.


### Interrupts

See datasheet for details.

- **int setInterruptConfig(uint8_t value = 0x10)**
- **uint8_t getInterruptConfig()** returns set value.


### Threshold

See datasheet for details.

- **void setHighThreshold(uint32_t value = 0x000FFFFF)**
- **uint32_t getHighThreshold()** returns set value.
- **void setLowThreshold(uint32_t value = 0)**
- **uint32_t getLowThreshold()** returns set value.

### Error

Not tested, to be elaborated (someday)

- **int lastError()** returns last low level I2C status.
Value LTR390_OK == 0 default.

|  value  |  constant            |  meaning  |
|:-------:|:---------------------|:----------|
|    0    |  LTR390_OK           |  default value.
|   -10   |  LTR390_I2C_REQUEST  |
|  other  |                      |  I2C errors, board specific.


## Future

#### Must

- Elaborate and improve documentation.
- test with right (DFR) hardware.

#### Should

- add examples
  - threshold registers
  - interrupt configuration register
  - enable/disable
  - performance measurements 
- keep in sync with LTR390_RT when possible

#### Could

- elaborate error handling
  - error codes
- unit test ==> test examples
- move code to .cpp ?


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


