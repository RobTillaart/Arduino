
[![Arduino CI](https://github.com/RobTillaart/A1301/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/A1301/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/A1301/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/A1301/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/A1301/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/A1301/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/A1301.svg?maxAge=3600)](https://github.com/RobTillaart/A1301/releases)


# A1301

Arduino library for A1301 and A1302 magnetometer.


## Description

The A1301 and A1302 are continuous-time, ratiometric, linear
Hall-effect sensors. They are optimized to accurately provide
a voltage output that is proportional to an applied magnetic
field. These devices have a quiescent output voltage that is
50% of the supply voltage. Two output sensitivity options are
provided: 2.5 mV/G typical for the A1301, and 1.3 mV/G
typical for the A1302. (from datasheet)


|  sensor  |  sensitivity    |  support  |
|:---------|:---------------:|:---------:|
|  A1301   |  2.5   mV/Gauss |     Y     |
|  A1302   |  1.3   mV/Gauss |     Y     |
|  A1324   |  5.000 mV/Gauss |     N     |
|  A1325   |  3.125 mV/Gauss |     N     |
|  A1326   |  2.500 mV/Gauss |     N     |

Other, more or less, compatible sensors are welcome.
(see future)

The library is experimental and need more testing.
Feedback, issues and improvements are welcome, 
Please open an issue on GitHub.


## Connection

```
//  always check datasheet.
//    PIN    A1301
//    ===============
//     1     GND
//     2     DATA
//     3     VDD +5V
```


## Interface

#### Constructor

- **HALL(uint8_t pin)** base class constructor.
pin is the analogPin to read from.
- **A1301(uint8_t pin)** constructor.
- **A1302(uint8_t pin)** constructor.

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
- **float readExt(float raw)** to be used with external ADC.
Can be positive (North) or negative (South).


#### Analyse

- **boolean isNorth()** idem.
- **boolean isSouth()** idem.
- **float lastGauss()** returns last measurement in Gauss.
- **float prevGauss()** returns previous measurement in Gauss.
- **float Tesla(float Gauss)** convenience convertor.
- **float mTesla(float Gauss)** convenience convertor.
- **float uTesla(float Gauss)** convenience convertor.


## Operation

The examples show the basic working of the functions.


## Future

#### Must
- improve documentation
- buy hardware A1301 / A1302 / ...
- test with hardware (again)

#### Should 
- plotter example
- unit tests

#### Could
- **boolean isSaturated()**
- **float findZero()** how exactly.
- printable interface
- Possible compatible
  - HoneyWell - SS39ET/SS49E/SS59ET
  - HoneyWell - SS490 Series
- add derived classes for - A1324/25/26 ?

#### Won't

