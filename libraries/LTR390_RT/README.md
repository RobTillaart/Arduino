
[![Arduino CI](https://github.com/RobTillaart/LTR390_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LTR390_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LTR390_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LTR390_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LTR390_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LTR390_RT.svg)](https://github.com/RobTillaart/LTR390_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LTR390_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LTR390_RT.svg?maxAge=3600)](https://github.com/RobTillaart/LTR390_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LTR390.svg)](https://registry.platformio.org/libraries/robtillaart/LTR390)


# LTR390

Arduino library for the I2C LTR390 UV sensor.


## Warning

**Always take precautions as UV radiation can cause sunburn, eye damage and other severe problems**.

Do not expose yourself to the sun as UV source too long.

When working with UV light, natural or artificial (TL LED laser a.o.) use appropriate shielding. Do not look right into UV light sources.


## Description

**Experimental**

This library is to read the LTR390 UV sensor directly.

The library was written after ordering a LTR390 sensor (breakout) from DFRobotics.
However that one had its own processor and its own interface. 
So the result was two libraries for the "same" product.

**Warning:** Operating voltage range: **1.7V .. 3.6V**  
So the LTR390 will not work on directly 5V boards.


## I2C

The LTR390 has a fixed address of 0x53 == 83 decimal according to datasheet.

### I2C Speed

The device should work on 100 kHz and 400 kHz I2C bus.

To be tested.


### I2C Multiplexing

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

## Interface

```cpp
#include "LTR390.h"
```

### Constructor

- **LTR390(TwoWire \* wire = &Wire)** Constructor 
with optional Wire interface.
- **bool begin()** returns true if device 0x53 can be seen on the I2C bus.
- **bool isConnected()** returns true if device 0x53 can be seen on I2C bus.
- **uint8_t getAddress()** returns 0x53, fixed address, for convenience.


### Main control

- **void setALSMode()** ALS is visible light mode.
- **void setUVSMode()** UVS is UV mode.
- **void reset()** resets the device, will block for 100 ms.
- **void enable()** enable device, active.
- **void disable()** disable device, standby.
- **bool isEnabled()** returns current device status.


### Resolution

- **void setResolution(uint8_t resolution)** resolution = 0..5 (default 2)
- **uint8_t getResolution()**
- **float getIntegrationTime()**

|  resolution  |  value   |  integration  |  notes  |
|:------------:|:--------:|:-------------:|:-------:|
|       0      |  20 bit  |   400.0 ms    |
|       1      |  19 bit  |   200.0 ms    |
|       2      |  18 bit  |   100.0 ms    |  default
|       3      |  17 bit  |    50.0 ms    |
|       4      |  16 bit  |    25.0 ms    |
|       5      |  13 bit  |    12.5 ms    |


### Rate

- **void setRate(uint8_t rate)** rate = 0..7 (default 2)
- **uint8_t getRate()**
- **float getMeasurementTime()**

|  rate  |  measurement  |  notes  |
|:------:|:-------------:|:-------:|
|   0    |     25.0 ms   |
|   1    |     50.0 ms   |
|   2    |    100.0 ms   |  default
|   3    |    200.0 ms   |
|   4    |    500.0 ms   |
|   5    |   1000.0 ms   |
|   6    |   2000.0 ms   |
|   7    |   2000.0 ms   |


### Gain

- **void setGain(uint8_t gain)** gain = 0..4 (default 1)
- **uint8_t getGain()**
- **uint8_t getGainFactor()**

|  gain  |  value   |  notes  |
|:------:|:--------:|:-------:|
|   0    |    1x    |
|   1    |    3x    |  default
|   2    |    6x    |
|   3    |    9x    |
|   4    |   18x    |


### Part and revision ID

Returned values might differ.

- **uint8_t getPartID()** returns 11.
- **uint8_t getRevisionID()** returns 2.


### Main status

- **uint8_t getStatus()** need split? or masks? table?


### Get data

- **uint32_t getALSData()** returns raw ALS data.
- **uint32_t getUVSData()** returns raw UV data.

Conversions, see https://esphome.io/components/sensor/ltr390.html  
These functions are not verified (yet).

- **float getLUX(float windowsFactor)** convert raw ALS data to LUX.
- **float getUVIndex(float windowsFactor)** convert raw UVS data to UV index.


### Interrupt

- **int setInterruptConfig(uint8_t value)**
- **uint8_t getInterruptConfig()**
- **int setInterruptPersist(uint8_t value)**
- **uint8_t getInterruptPersist()**


### Threshold

- **void setHighThreshold(uint32_t value)**
- **uint32_t getHighThreshold()**
- **void setLowThreshold(uint32_t value)**
- **uint32_t getLowThreshold()**


## Future

#### Must

- improve documentation
  - add tables, ranges, descriptions etc.
- test with right hardware.

#### Should

- keep in sync with DFRobotics where possible.
- add examples.
  - test example
  - performance example
- fix / elaborate TODO's in code.
  - status and error codes
  - interrupts and thresholds

#### Could

- add error handling
- unit test or test example?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


