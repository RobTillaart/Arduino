
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

**Experimental** library for GY521 a.k.a. MCU-6050.

Library is work in progress, in fact it is extracted and extended from an old project.
It needs to be tested a lot more.

See changelog.md for latest updates.


#### 0.6.1

Improved **calibrate()** to support any angle.


#### 0.6.0

Fixed a bug in calibration function, making previous versions obsolete.


#### 0.5.0 Breaking change

Version 0.5.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Examples

- **GY521_angle** read angleX, angleY, angleZ.
- **GY521_performance_calibrate.ino** determine calibration performance.
- **GY521_performance** measure performance.
- **GY521_pitch_roll_yaw** to get pitch roll yaw.
- **GY521_raw_cooked** make a table of raw measurements and derived data 
for analysis e.g. in a spreadsheet.
- **GY521_readCalibration_1** read calibration values / errors for a "flat" sensor.
- **GY521_readCalibration_2** generate calibration code snippet.
- **GY521_test_1** test working of the sensor.
- **GY521_test_2** test set/get functions (sort of unit test).
- **GY521_two_sensors** demo for two sensors.


#### Related

- https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
- https://cdn.sparkfun.com/datasheets/Sensors/Accelerometers/RM-MPU-6000A.pdf  register map.
- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/AngleConverter


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

Since version 0.5.2 the library has a build in **void calibrate(times)** function which
can be called instead of manual calibration.
This function overwrites the values of axe aye aze gxe gye gze.
**calibrate()** must be called after **setAccelSensitivity(as)** and **setGyroSensitivity(gs)**.

Note the **calibrate()** function takes time, depending on the number of times.

Since version 0.6.1 the calibrate function is extended with optional parameters so the
sensor can be calibrated in any angle. 
**bool calibrate(times, angleX = 0, angleY = 0, inverted = false)**


#### Manual calibration

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
- **bool begin()** Returns true if address can be found on I2C bus.
Note call **Wire.begin()** before **begin()**.
- **bool isConnected()** returns true if device can be found on I2C bus.
- **void reset()** set all internal values to 0 and throttle time to 10 ms.
- **bool wakeUp()** idem.


### Calibrate

- **bool calibrate(uint16_t times, float angleX = 0, float angleY = 0, bool inverted = false)** 
This function overwrites the values of axe aye aze and gxe gye gze.
To improve the quality of the error offsets, the GY521 sensor should not move during the calibration.
The parameter times determines the number of measurements the calibration function should make.
Note that the actual number of samples can be less if a read of the sensor fails.
If there is no good read at all the function returns **false**.
Typical values for times are 100 or more. 
If times is set to 0, it will be forced to 1.
Please note this call will be very time consuming.

Ideal the function **calibrate()** should continue until it is stable (how to define) for n reads.
Drawback is that this would make the duration unpredictable.

New since 0.6.1 (experimental)  
The optional parameters **float angleX = 0, float angleY = 0** should be between -90 .. +90.
These can be used if the sensor is not lying flat during calibration. 
The optional parameter **bool inverted = false** should be set to true if the sensor is 
upside down. 


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
- **void setNormalize(bool normalize = true)** normalizes pitch roll yaw or not. Default true.
- **bool getNormalize()** returns flag.


#### Actual read

- **int16_t read()** reads all core measurements.
returns status = GY521_OK on success.
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

Note that multiple calls will return the same value. 
One must explicitly call **read()** to get new values. 

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


#### Experimental Pitch Roll and Yaw

Pitch Roll and Yaw is work in progress and should not be used for projects yet.

- **float getPitch()** idem. May return any number.
If **setNormalize(true)** return value will be 0-359.999
- **float getRoll()** idem. May return any number.
If **setNormalize(true)** return value will be 0-359.999
- **float getYaw()** idem. May return any number.
If **setNormalize(true)** return value will be 0-359.999


#### Digital Low Pass Filter

See datasheet P13-reg26

- **bool setDLPFMode(uint8_t mode)** mode = 0..6, returns false if mode > 6.
- **uint8_t getDLPFMode()** returns the current (set) mode.

| Mode | Acc bandwidth | delay  | Gyro bandwidth | delay  |   Fs  |
|:----:|:-------------:|:------:|:--------------:|:------:|:-----:|
|   0  |     260 Hz    |   0.0  |      256 Hz    |   1.0  | 8 kHz |
|   1  |     184 Hz    |   2.0  |      188 Hz    |   1.9  | 1 kHz |
|   2  |      94 Hz    |   3.0  |       98 Hz    |   2.8  | 1 kHz |
|   3  |      44 Hz    |   4.9  |       42 Hz    |   4.8  | 1 kHz |
|   4  |      21 Hz    |   8.5  |       20 Hz    |   8.3  | 1 kHz |
|   5  |      10 Hz    |  13.8  |       10 Hz    |  13.4  | 1 kHz |
|   6  |       5 Hz    |  19.0  |        5 Hz    |  18.6  | 1 kHz |


#### Generic Register Access

Read the register PDF for the specific value and meaning of registers.

- **uint8_t setRegister(uint8_t reg, uint8_t value)**
- **uint8_t getRegister(uint8_t reg)**


## Documents

- check details registers - MPU-6000-Register-Map1.pdf


#### Error codes

|  Error code                 |  value  |  notes  |
|:----------------------------|:-------:|:-------:|
|  GY521_OK                   |    0    |  not an error
|  GY521_THROTTLED            |    1    |  not an error
|  GY521_ERROR_READ           |   -1    |
|  GY521_ERROR_WRITE          |   -2    |
|  GY521_ERROR_NOT_CONNECTED  |   -3    |


#### Sensitivity Acceleration

The strength of Earth's gravity varies with latitude (equator = 0°, poles = 90°).
The standard value for gravity (gn) is 9.80665 m/s^2 (often 9.81 m/s^2)
At the equator the gravity (ge) is 9.78033 m/s^2.

The library provides the constant GRAVITY = 9.80655


|  value  | Acceleration  |    m/s2    |  notes  |
|:-------:|:--------------|:----------:|:-------:|
|    0    |      2 g      |   19.6131  |  default
|    1    |      4 g      |   39.2262  |
|    2    |      8 g      |   78.4524  |
|    3    |     16 g      |  156.9048  |


#### Sensitivity Gyroscope

unit dps = degrees per second.

|  value  |  Gyroscope  |  radians/sec  |  notes  |
|:-------:|:------------|:-------------:|:-------:|
|    0    |   250 dps   |   4.36332313  |  default
|    1    |   500 dps   |   8.72664626  |
|    2    |  1000 dps   |  17.45329252  |
|    3    |  2000 dps   |  34.90658504  |


## Operation

See examples, use with care.


## Future

There is no intention to implement getters and setters for all registers.
However if one specific is needed, please open an issue.

#### Must

- time
- improve documentation
- investigate Pitch Roll and Yaw math in detail.
  - investigate math needed.
  - implementation.
  - when?
- test test and test ...(ESP too)

#### Should

- test **calibrate()** function 
  - for different sensitivities.
  - for different angles.

#### Could

- add examples
- improve unit tests?
- reorder code in read(), would that save some micros.?
  - first all ax, then ay etc
  - footprint / performance gain?
- make enum for sensitivity Accel?
- make enum for sensitivity Gyro?

#### Wont

- look for maths optimizations  (atan, hypot, performance)
  - ==> hypot optimized (fastTrig?)
  - other ideas affect accuracy, so unless new ideas arise.
- calibrate function in the lib
  - not as lib will grow too large.
- defaults value for functions?
  - user must set function parameters explicit


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

