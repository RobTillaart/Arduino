
[![Arduino CI](https://github.com/RobTillaart/A1301/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/A1301/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/A1301/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/A1301/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/A1301/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/A1301/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/A1301.svg?maxAge=3600)](https://github.com/RobTillaart/A1301/releases)


# A1301

Arduino library for A1301 and A1302 magnetometer.


## Description

The A1301 and A1302 are continuous-time, Ratio-metric, linear Hall-effect sensors. 
They are optimized to accurately provide a voltage output that is proportional to 
an applied magnetic field. 
These devices have a quiescent output voltage that is 50% of the supply voltage. 
This voltage level is a.k.a. the midPoint.

Two output sensitivity options are provided: 2.5 mV/G typical for the A1301, 
and 1.3 mV/G typical for the A1302. (from datasheet)

The following 5 classes are supported:

|  sensor  |  sensitivity    |  support  |
|:---------|:---------------:|:---------:|
|  A1301   |  2.5   mV/Gauss |     Y     |
|  A1302   |  1.3   mV/Gauss |     Y     |
|  A1324   |  5.000 mV/Gauss |     Y     |
|  A1325   |  3.125 mV/Gauss |     Y     |
|  A1326   |  2.500 mV/Gauss |     Y     |

Other, more or less, compatible sensors are welcome.
(see future below.)

The library is experimental and need more testing.
Feedback, issues and improvements are welcome, 
Please open an issue on GitHub.


## Connection

```
//  always check datasheet.
//
//    PIN    A1301
//    ===============
//     1     GND
//     2     DATA
//     3     VDD +5V
```


## Interface

```cpp
#include "A1301.h"
```


#### Constructor

- **HALL(uint8_t pin)** base class constructor.
pin is the analogPin to read from.
- **A1301(uint8_t pin)** constructor.
- **A1302(uint8_t pin)** constructor.
- **A1324(uint8_t pin)** constructor.
- **A1325(uint8_t pin)** constructor.
- **A1326(uint8_t pin)** constructor.


#### Configuration

- **void begin(float voltage, uint16_t steps)**
Sets the parameters voltage and number of steps of the internal ADC.
Note this allows to update the voltage runtime.
- **void setMidPoint(float midPoint)** the value of midPoint depends on the internal ADC.
It is the value where there is no (zero) magnetic field.
Note it does not need to be a whole value. 
This allows quite precise tuning.
- **float getMidPoint()** returns the current midPoint.
- **void setSensitivity(float sensitivity)** overrule default sensitivity.
Use with care.
- **float getSensitivity()** return current sensitivity.


#### Read

- **float raw(uint8_t times = 1)** raw analog measurement.
- **float read(uint8_t times = 1)** raw measurement converted to Gauss.
Can be positive (North) or negative (South).
Returns Gauss.
- **float readExt(float raw)** to be used with external ADC.
Note: **raw** is an ADC measurement, not a voltage.
Can be positive (North) or negative (South).
Returns Gauss.
Can also be used for testing, e.g. replay of a series of data.


#### Analyse

- **bool isNorth()** idem.
- **bool isSouth()** idem.
- **float lastGauss()** returns last measurement in Gauss.
- **float prevGauss()** returns previous measurement in Gauss.


#### Saturation.

Experimental saturation level.

- **void setMaxGauss(float maxGauss)** set the saturation level.
If maxGauss < 0 the absolute value is set.
- **float getMaxGauss()** returns the set saturation level.
- **bool isSaturated()** true when ADC (lastRead) seems to max out. 
- **float saturationLevel()** returns value between 0..100%.


#### Tesla 

- **float Tesla(float Gauss)** convenience convertor.
- **float mTesla(float Gauss)** convenience convertor.
- **float uTesla(float Gauss)** convenience convertor.


## Operation

The examples show the basic working of the functions.
(to elaborate more examples)


## Future

#### Must

- improve documentation
- buy hardware A1301 / A1302 / etc...
- test with hardware (again)


#### Should 

- unit tests
- test **isSaturated()** + **saturationLevel()**
  - limits might be sensor dependant.
- optimize math
  - multiplications instead of divisions.
  - other constants needed?


#### Could

- **float findZero()** how exactly => ACS712 **autoMidPoint()**
- investigate **float determineNoise()** (set/get)
- add examples.
  - performance read()
- Possible compatible
  - HoneyWell - SS39ET/SS49E/SS59ET
  - HoneyWell - SS490 Series
- temperature correction functions?
  - see datasheet.


#### Ideas

(thinking out loud section)
- isEast() and isWest() meaning?
  - **isEast()** field strength is "rising" ==> lastGauss > prevGauss
  - **isWest()** field strength is "sinking" ==> lastGauss < prevGauss
  - should that be absolute or not? or just **bool isRising()**
- **float readDelta(uint8_t times = 1)** returns the relative change.
- atan2(prevGauss, lastGauss)?
  - angle indicates relative delta compared to magnitude and direction.
  - 45 135 degrees is no change. 
- can the strength of the signal be converted to distance?
  - for a given magnet
  - repeatability + noise.
- influence of angle of the field-lines?
- defaults for parameters of some functions?


#### Won't

- printable interface
  - does not add much.
