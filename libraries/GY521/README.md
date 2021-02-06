
[![Arduino CI](https://github.com/RobTillaart/GY521/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/GY521/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/GY521.svg?maxAge=3600)](https://github.com/RobTillaart/GY521/releases)

# GY521

Arduino library for I2C GY521 accelerometer-gyroscope sensor a.k.a. MCU-6050


## Description

Experimental library for GY521 a.k.a. MCU-6050

Library is work in progress, in fact extracted and extended from an old project.
It needs to be tested a lot more.

It has three examples
- calibration example to determine the offsets needed
- example to read values.
- test sketch to test get / set values.


## Breakout board

left to right

|  pin | pinname | description     |
|:----:|:--------|:----------------|
|  0   |  VCC    | +5V             |
|  1   |  GND    | ground          |
|  2   |  SCL    | I2C clock       |
|  3   |  SDA    | I2C data        |
|  4   |  XDA    | auxiliary data  | see datasheet
|  5   |  XCL    | auxiliary clock | see datasheet
|  6   |  AD0    | address         | 
|  7   |  INT    | interrupt       |

#### Address
AD0 connected to GND => 0x68 
AD0 connected to VCC => 0x69


## Calibration (short version for now)

1. load and run calibration example  
   it shows a header containing 6 numbers and 10 lines of 8 numbers
1. wait until the middle 6 of the longer lines stabilize (should all be 0)
1. copy the 6 numbers above the axe aye aze as these are the numbers needed.


## Interface


### Constructor

- **GY521(uint8_t address = 0x69)** Constructor with default address. 0x68 is also valid.
- **bool begin()**
- **bool isConnected()** device can be found on I2C bus.
- **bool wakeUp()**


### Throttle

- **void setThrottle(bool throttle = true)** throttle to force delay between reads.
- **bool getThrottle()** idem
- **void     setThrottleTime(uint16_t ti )** milliseconds, max = 65535 = 1++ minute
- **uint16_t getThrottleTime()** idem


### Read

#### SET BEFORE READ
  // as = 0,1,2,3 ==> 2g 4g 8g 16g
- **bool setAccelSensitivity(uint8_t as)** as = 0, 1, 2, 3 ==> 2g 4g 8g 16g
- **uint8_t getAccelSensitivity()** returns 0, 1, 2, 3
- **bool setGyroSensitivity(uint8_t gs)** gs = 0,1,2,3  ==>  250, 500, 1000, 2000 degrees/second
- **uint8_t  getGyroSensitivity()** returns 0, 1, 2, 3  


#### Actual read

- **int16_t read()** returns ...
- **uint32_t lastTime()** last time sensor is actually read. In millis().


#### Call after read

- **float getAccelX()** idem
- **float getAccelY()** idem
- **float getAccelZ()** idem
- **float getAngleX()** idem
- **float getAngleY()** idem
- **float getAngleZ()** idem
- **float getTemperature()** idem
- **float getGyroX()** idem
- **float getGyroY()** idem
- **float getGyroZ()** idem
- **float getPitch()** idem
- **float getRoll()** idem
- **float getYaw()** idem


### Register access

Read the register PDF for the specific 

- **uint8_t setRegister(uint8_t reg, uint8_t value)**
- **uint8_t getRegister(uint8_t reg)**


## Future

**Should**
- test test and test ...(ESP too)
- improve documentation
- look for math optimizations  (atan, hypot, performance)

**Could**
- calibrate function in the lib ?  (think not as lib might grow?)
- calibrate sketch could print code snippet to include...


## documents

- check details - MPU-6000-Register-Map1.pdf


## Operation

See examples, use with care 

