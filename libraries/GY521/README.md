
[![Arduino CI](https://github.com/RobTillaart/GY521/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/GY521/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/GY521/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/GY521/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/GY521/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/GY521.svg)](https://github.com/RobTillaart/GY521/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/GY521/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/GY521.svg?maxAge=3600)](https://github.com/RobTillaart/GY521/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/GY521.svg)](https://registry.platformio.org/libraries/robtillaart/GY521)


# GY521

Arduino library for I2C GY521 accelerometer-gyroscope sensor a.k.a. MCU-6050.


## Description

Experimental library for GY521 a.k.a. MCU-6050.

Library is work in progress, in fact it is extracted and extended from an old project.
It needs to be tested a lot more.

See changelog.md for latest updates.


#### Examples

- **GY521_angle** read angleX, angleY, angleZ.
- **GY521_performance** measure performance.
- **GY521_pitch_roll_yaw** to get pitch roll yaw.
- **GY521_readCalibration_1** read calibration values / errors for a flat sensor.
- **GY521_readCalibration_2** generate calibration code snippet.
- **GY521_test_1** test working of the sensor.
- **GY521_test_2** test set/get functions.


## Breakout board

From left to right

|  pin  |  pinName  |  description      |  notes  |
|:-----:|:---------:|:------------------|:-------:|
|   0   |    VCC    |  +5V              |
|   1   |    GND    |  ground           |
|   2   |    SCL    |  I2C clock        |
|   3   |    SDA    |  I2C data         |
|   4   |    XDA    |  auxiliary data   | see datasheet
|   5   |    XCL    |  auxiliary clock  | see datasheet
|   6   |    AD0    |  address          | 
|   7   |    INT    |  interrupt        |


#### Address

AD0 connected to GND => 0x68 
AD0 connected to VCC => 0x69


## Calibration (short version for now)

1. load and run calibration example  
   it shows a header containing 6 numbers and 10 lines of 8 numbers
1. wait until the middle 6 of the longer lines stabilize (should all be 0)
1. copy the 6 numbers above the axe aye aze as these are the numbers needed.


## Interface

```cpp
#include "GY521.h"
```

### Constructor

- **GY521(uint8_t address = 0x69, , TwoWire \*wire = &Wire)** Constructor with default address. 
0x68 is also a valid address. The wire argument is optional to select Wire1 Wire2 etc. on some boards.
- **bool begin(uint8_t sda, uint8_t scl)** begin for ESP32 et al. Returns true if address can be found on I2C bus.
- **bool begin()** Returns true if address can be found on I2C bus.
- **bool isConnected()** returns true if device can be found on I2C bus.
- **void reset()** set all internal values to 0 and throttle time to 10 ms.
- **bool wakeUp()** idem.


### Throttle

- **void setThrottle(bool throttle = true)** throttle to force "delay" between reads.
- **bool getThrottle()** returns true if throttle mode is set.
- **void setThrottleTime(uint16_t ti )** throttle time in milliseconds, max = 65535 = 1++ minute
- **uint16_t getThrottleTime()** returns throttle time set.


### Read

#### Set before read

- **bool setAccelSensitivity(uint8_t as)** as = 0, 1, 2, 3 ==> 2g 4g 8g 16g
- **uint8_t getAccelSensitivity()** returns 0, 1, 2, 3
- **bool setGyroSensitivity(uint8_t gs)** gs = 0,1,2,3  ==>  250, 500, 1000, 2000 degrees/second
- **uint8_t getGyroSensitivity()** returns 0, 1, 2, 3  
= **void setNormalize(bool normalize = true)** normalizes pitch roll yaw or not. Default true.
= **bool getNormalize()** returns flag.


#### Actual read

- **int16_t read()** returns status = GY521_OK on success.
- **int16_t readAccel()** read accelerometer only to speed up interaction. This call does update the throttle timer.
returns status = GY521_OK on success.
- **int16_t readGyro()** read gyroscope only to speed up interaction. This call does update the throttle timer.
returns status = GY521_OK on success.
Note: for pitch roll yaw you need to call **read()**.
- **int16_t readTemperature()** read temperature only, does **not** update the throttle timer.
returns status = GY521_OK on success.
- **uint32_t lastTime()** last time sensor is actually read. In milliseconds. Not updated by readTemperature().

Since version 0.3.8 the **read()** and **readGyro()** function is updated to keep the range of **getPitch()**,
 **getRoll()** and **getYaw()** in the range 0..359.999 degrees. (Issue #36). 
Problem is that with continuous rotation in a same direction internal variables will overflow and new 
movements (angles) will get lost as insignificant digits.

In version 0.4.0 the normalization of pitch, roll and yaw is fixed and made conditional. (Issue #42).


#### Calls after read

Note that multiple calls will return the same value. One must explicitly call **read()** to get new values. 

- **float getAccelX()** idem.
- **float getAccelY()** idem.
- **float getAccelZ()** idem.
- **float getAngleX()** idem.
- **float getAngleY()** idem.
- **float getAngleZ()** idem.
- **float getTemperature()** idem.
- **float getGyroX()** idem.
- **float getGyroY()** idem.
- **float getGyroZ()** idem.
- **float getPitch()** idem. May return any number.
If **setNormalize(true)** return value will be 0-359.999
- **float getRoll()** idem. May return any number.
If **setNormalize(true)** return value will be 0-359.999
- **float getYaw()** idem. May return any number.
If **setNormalize(true)** return value will be 0-359.999


### Register access

Read the register PDF for the specific value and meaning of registers.

- **uint8_t setRegister(uint8_t reg, uint8_t value)**
- **uint8_t getRegister(uint8_t reg)**


## documents

- check details - MPU-6000-Register-Map1.pdf


## Operation

See examples, use with care 


## Future

#### Must

- improve documentation
  - add tables where appropriate
  - sensitivity, error codes etc
- test test and test ...(ESP too)

#### Should

- add performance sketch

#### Could

- calibrate sketch could print code snippet to include...
- add examples
- improve unit tests?

#### Wont

- look for maths optimizations  (atan, hypot, performance)
  - ==> hypot optimized (fastTrig?)
  - other ideas affect accuracy, so unless new ideas arise.
- calibrate function in the lib
  - not as lib will grow too large.

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

