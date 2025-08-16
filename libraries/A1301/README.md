
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

Arduino library for the A1301, A1302 and compatible magnetometers.


## Description

**Experimental**

The A1301 and A1302 are continuous-time, Ratio-metric, linear Hall-effect sensors.
They are optimized to accurately provide a voltage output that is proportional to
an applied magnetic field.
These devices have a quiescent output voltage that is 50% of the supply voltage.
This voltage level is a.k.a. the midPoint.

Two output sensitivity options are provided: 2.5 mV/G typical for the A1301,
and 1.3 mV/G typical for the A1302. (from the datasheet).
This sensitivity can be overridden to fine tune the library.

The following 5 classes are supported:

|  sensor  |  sensitivity    |  support  |
|:---------|:---------------:|:---------:|
|  A1301   |  2.5   mV/Gauss |     Y     |
|  A1302   |  1.3   mV/Gauss |     Y     |
|  A1324   |  5.000 mV/Gauss |     Y     |
|  A1325   |  3.125 mV/Gauss |     Y     |
|  A1326   |  2.500 mV/Gauss |     Y     |

The library needs more testing.
Feedback, issues and improvements are welcome,
also if compatible devices are missing.
Please open an issue on GitHub.


### 0.3.0 breaking change

The 0.3.0 version improved some function names and added more return types.
See changelog.md for details. Functional there are no changes.


### Connection

```
//  always check datasheet.
//
//    PIN    A1301
//    ===============
//     1     GND
//     2     DATA
//     3     VDD +5V
```

### Related

- https://github.com/RobTillaart/AS5600
- https://github.com/RobTillaart/AngleConvertor


## Interface

```cpp
#include "A1301.h"
```

### Constructor

- **HALL(uint8_t pin)** base class constructor.
The parameter pin is the analogPin to read from.
- **A1301(uint8_t pin)** constructor, other sensitivity, see table above.
- **A1302(uint8_t pin)** constructor, other sensitivity, see table above.
- **A1324(uint8_t pin)** constructor, other sensitivity, see table above.
- **A1325(uint8_t pin)** constructor, other sensitivity, see table above.
- **A1326(uint8_t pin)** constructor, other sensitivity, see table above.


### Configuration

- **bool begin(float voltage, uint16_t steps)**
Sets the parameters voltage and number of steps of the internal ADC, typical 5.0 V
and 1023 steps for a 10 bit ADC.
Note this function allows to update the voltage runtime.
Voltage and Steps must be larger than zero, otherwise the function returns false.
- **bool setMidPoint(float midPoint)** the value of midPoint depends on the internal ADC.
It is the value where there is no (zero) magnetic field.
Note it does not need to be a whole value.
This allows quite precise tuning.
midPoint should be larger than zero, otherwise the function returns false.
- **float autoMidPoint(uint8_t times = 100)** assumes a zero magnetic field.
Averages multiple (default 100) samples to determine and set the midPoint.
Uses the internal ADC specified in the constructor.
The function returns the found midPoint.
-- **float getMidPoint()** returns the current midPoint.
- **bool setSensitivity(float sensitivity)** overrules the default sensitivity.
Sensitivity must be larger than zero, otherwise the function returns false.
Use with care!
- **float getSensitivity()** return the set / current sensitivity.


### Read

- **float raw(uint8_t times = 1)** returns the average of times raw analog measurements.
Times must be larger than zero.
- **float read(uint8_t times = 1)** returns the average of times raw measurements converted to Gauss.
The value can be positive (== North) or negative (== South) or zero.
Returns Gauss.
- **float readExt(float raw)** to be used with external ADC.
Note: **raw** is an raw external ADC measurement, not a voltage.
Can be positive (== North) or negative (== South) or zero.
Returns Gauss.
Note this function can also be used for testing, e.g. replay of a series of data.


### Analyse

- **bool isNull()** last read is zero.
- **bool isNorth()** last read is above zero.
- **bool isSouth()** last read is below zero.
- **bool isRising()** trend (last 2 reads) is upward.
- **bool isFalling()** trend (last 2 reads) is downward.
- **float lastGauss()** returns last measurement in Gauss.
- **float prevGauss()** returns previous measurement in Gauss.
- **float deltaGauss()** returns last - previous measurement.

**Experimental**

- **float determineNoise(uint8_t times = 2)** estimates the noise level
around measurements. The parameter **times** will be forced to be at least 2.
Does not affect the lastGauss() or prevGauss() values.
- **float angle()** returns the atan2(prevGauss, lastGauss).
The angle indicates a relative change.
Returns angle in radians. For an angle in degrees multiply by **(180.0/PI)**.
An angle of 45 or 225 degrees means no change, where an angle of 135 or 315
degrees implies maximum change.


### Saturation level

**Experimental**

- **bool setMaxGauss(float maxGauss)** set the saturation level.
If maxGauss < 0 the absolute value is set.
The function returns false if maxGauss == 0.
- **float getMaxGauss()** returns the set saturation level.
- **bool isSaturated()** true when ADC (lastRead) seems to max out.
- **float saturationLevel()** returns value between 0..100%, or beyond!


### Tesla (conversion)

- **float Tesla(float Gauss)** convenience convertor.
- **float mTesla(float Gauss)** convenience convertor.
- **float uTesla(float Gauss)** convenience convertor.


## Future

#### Must

- improve documentation
- buy hardware A1301 / A1302 / etc...
- test with hardware

#### Should

- test **isSaturated()** + **saturationLevel()**
  - limits might be sensor dependant.
- add and improve unit tests

#### Could

- Possible compatible
  - HoneyWell - SS39ET/SS49E/SS59ET
  - HoneyWell - SS490 Series
- temperature correction functions?
  - see datasheet.
- relative flux() = prevGauss / lastGauss
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
  - field strength ~~ (C/distance)^3 ==> distance ~~ C/thirdRoot(field)
  - how to determine C constant, for a given magnet maybe
  - repeatability + noise is a problem.

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

