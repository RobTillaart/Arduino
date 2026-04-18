
[![Arduino CI](https://github.com/RobTillaart/FSR40X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FSR40X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FSR40X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FSR40X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FSR40X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FSR40X.svg)](https://github.com/RobTillaart/FSR40X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FSR40X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FSR40X.svg?maxAge=3600)](https://github.com/RobTillaart/FSR40X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FSR40X.svg)](https://registry.platformio.org/libraries/robtillaart/FSR40X)


# FSR40X

Arduino library for FSR40X Force Sensing Resistors.


## Description

**Experimental**

This library is to use Force Sensing Resistors of the FSR400 series.
Main goal of the library is to convert a raw ADC voltage to Newtons, 
kilogram force (kgf) or pound force (lbf).
The accuracy of the sensors is limited (~5% ??) and thus only
gives an **indication** of the force applied.

The library has (derived) classes for the FSR400, FSR402, FSR404, FSR406, FSR408.
Currently these are wrappers and are identical to the base class FSR40X.
In the future they might have specific functions.


|  type    |  description   | notes  |
|:--------:|:---------------|:-------|
|  FSR40X  |  base class    |
|  FSR400  |  05 mm circle  |
|  FSR402  |  13 mm circle  |
|  FSR404  |  20 mm donut   |  5 mm hole
|  FSR406  |  38 mm square  |
|  FSR408  |  10 mm strip   |  length 50..500 mm


The FSR40X device needs to be in a voltage divider, with the middle connected
to the analog input of your choice.
The non actuated resistance is larger than 10 MΩ.

The library is not tested yet with hardware (need to order).

Feedback as always is welcome.


### Hardware setup

```

  Vcc ----[ FSR ]-----A------[ 10K ]------- GND
                      |
                      |
                      X
                      |
                      |
                  analogPort

```

The 10 K resistor gives a broad range of values.
See datasheet for possible other values and their range.

Essentially it is a voltage divider, optionally at X an OP-AMP.
See https://www.youtube.com/watch?v=dfGScD0UKZM


### Acceleration of gravity

This constant is used to convert Kgf to Newtons. The library use the
defined average 9.80655, although gravity is not uniform.
It varies ~0.7% due to latitude, altitude, and local density differences.
In space it varies even more.
Feel free to adjust the library to your needs.

- poles:   9.8337 m/s2
- equator: 9.7806 m/s2
- average: 9.80655 m/s2

Estimation formula for g at latitude:
```
float g = 9.7806 + sin(latitude * PI/180.0) * (9.8337 - 9.7806);
```


### Special characters

|  char  |  name       |  Windows     |
|:------:|:------------|:------------:|
|    Ω   |  Ohm        |  ALT-234     |
|    µ   |  micro      |  ALT-0181    |


### Compatibility

There are no known compatible FSR's at the moment.
Please let me know if you have one.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment, 
and any other applications that may cause personal injury due to the product's failure._


### Related

- https://github.com/RobTillaart/FSR40X - this library
- https://github.com/RobTillaart/Pressure - unit conversion
- https://github.com/RobTillaart/PrintHelpers - scientific and engineering notation.


### Tested

TODO: Test on Arduino UNO and ESP32


### Performance

The core function **readNewton()** does one or more analog reads and average them
This average is converted to newtons in a number of floating point steps.
The duration of a call depends on the ADC / board used, the number of samples to 
average and if it supports float operations in hardware.


## Interface

```cpp
#include "FSR40X.h"
```

### Constructor

- **FSR40X(uint8_t ADCpin, float voltage, uint16_t steps)** define the ADC, 
voltage range and steps. Defaults the fixed resistor to 10 kOhm.
- **bool begin(float resistor = 10000)** define the fixed resistor which together 
with the FSR forms a voltage divider. This value can be runtime adjusted, 
e.g. select different resistors for better range.
The default is 10 kOhm, which might be fine tuned e.g. use 9983.
- **bool setVoltage(float voltage)** allows runtime adjustment of the voltage
of the ADC as specified in the constructor.


### Read

- **float readRaw(uint8_t times = 1)** average read of the ADC. Allows one
to add a tailor made conversion.
- **float readNewton(uint8_t times = 1)** make one or more ADC measurements,
average them and convert them and returns the value to Newtons. 
Intermediate results are stored and can be fetched by the "getters" below.

Getters to access internal values from the last **readNewton()** measurement. 
The values do not change until a new **readNewton()** call is made.
Before first readNewton() they have no meaningful value.

- **float getVout()** returns Vout in volts.
- **float getNewton()** returns force in Newtons.
- **float getKgf()** returns force in kilogram force.
Conversion constant 1 newton = 0.101971621 kgf.
- **float getLbf()** returns force in pound force.
Conversion constant 1 newton = 0.224808943 lbf.
- **float getFSR()** return resistance of the FSR in Ohm.

Note: 1 kgf = 9.80655 Newton (gravitation constant).


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- magic formula, make it configurable?

#### Could

- add examples
- create unit tests if possible
- add readPressure as area is "known" for some derived sensors.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


