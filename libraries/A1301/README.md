
[![PlatformIO CI](https://github.com/RobTillaart/A1301/workflows/PlatformIO%20CI/badge.svg)](https://docs.platformio.org/en/latest/integration/ci/github-actions.html)
[![Arduino CI](https://github.com/RobTillaart/A1301/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/A1301/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/A1301/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/A1301/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/A1301/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/A1301.svg)](https://github.com/RobTillaart/A1301/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/A1301/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/A1301.svg?maxAge=3600)](https://github.com/RobTillaart/A1301/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/A1301.svg)](https://registry.platformio.org/libraries/robtillaart/A1301)

[![Commits since latest](https://img.shields.io/github/commits-since/RobTillaart/A1301/latest)](https://github.com/RobTillaart/A1301/commits/master)


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
Steps must be larger than zero.
- **void setMidPoint(float midPoint)** the value of midPoint depends on the internal ADC.
It is the value where there is no (zero) magnetic field.
Note it does not need to be a whole value. 
This allows quite precise tuning.
- **float autoMidPoint(uint8_t times = 100)** assumes zero field. 
Averages multiple (default 100) samples to set the midPoint.
Uses internal ADC.
Also returns the found midPoint.
-- **float getMidPoint()** returns the current midPoint.
- **void setSensitivity(float sensitivity)** overrule default sensitivity.
Use with care.
- **float getSensitivity()** return the set / current sensitivity.


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

- **bool isNull()** last read is zero.
- **bool isNorth()** last read is above than zero.
- **bool isSouth()** last read is below zero.
- **bool isRising()** trend (last 2 reads) is upward.
- **bool isFalling()** trend (last 2 reads) is downward.
- **float lastGauss()** returns last measurement in Gauss.
- **float prevGauss()** returns previous measurement in Gauss.
- **float deltaGauss()** returns last - previous measurement.

Experimental.

- **float determineNoise(uint8_t times = 2)** estimates noise level
around measurements. **times** will be forced to be at least 2.
Does not affect lastGauss or prevGauss values. 
- **float angle()** returns atan2(prevGauss, lastGauss).
Indicator of change.
Returns angle in radians. For degrees multiply by 180/PI.


#### Saturation.

Experimental saturation level.

- **void setMaxGauss(float maxGauss)** set the saturation level.
If maxGauss < 0 the absolute value is set.
- **float getMaxGauss()** returns the set saturation level.
- **bool isSaturated()** true when ADC (lastRead) seems to max out. 
- **float saturationLevel()** returns value between 0..100%, or beyond!


#### Tesla 

- **float Tesla(float Gauss)** convenience convertor.
- **float mTesla(float Gauss)** convenience convertor.
- **float uTesla(float Gauss)** convenience convertor.


## Future

#### Must

- improve documentation
- buy hardware A1301 / A1302 / etc...
- test with hardware (again)


#### Should 

- unit tests
- test **isSaturated()** + **saturationLevel()**
  - limits might be sensor dependant.
- investigate **atan2(prevGauss, lastGauss)**
  - angle indicates relative delta compared to magnitude and direction.
  - 45 & 315 degrees is no change.


#### Could

- Possible compatible
  - HoneyWell - SS39ET/SS49E/SS59ET
  - HoneyWell - SS490 Series
- temperature correction functions?
  - see datasheet.
- relative flux = prevGauss / lastGauss 
  - smaller 1 => increasing
  - larger  1 => decreasing
  - negative  => flipping


#### Ideas

(thinking out loud section)
- isEast() and isWest() meaning?
- influence of angle of the field-lines?
- defaults for parameters of some functions?


#### Won't

- printable interface
  - does not add much.

- can the strength of the signal be converted to distance?
  - for a given magnet maybe
  - repeatability + noise is a problem.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

