
[![Arduino CI](https://github.com/RobTillaart/TSL260R/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TSL260R/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TSL260R/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TSL260R/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TSL260R/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TSL260R.svg)](https://github.com/RobTillaart/TSL260R/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TSL260R/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TSL260R.svg?maxAge=3600)](https://github.com/RobTillaart/TSL260R/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TSL260R.svg)](https://registry.platformio.org/libraries/robtillaart/TSL260R)


# TSL260R

Arduino library for the TSL260R IR to voltage convertor


## Description

The TSL260R (TSL261R, TSL262R) is a IR sensor that outputs a voltage depending on the irradiation.

This library does convert the output voltage to uW/cm2.

As the type sensor differ by sensitivity the library has three distinct classes.
The table below is an approximation for the max irradiation at 3.3 Volt (output).
For an Arduino UNO 3.3 V is about 650 ADC steps. 
When using e.g. an external 16 bit ADS1115, one definitely has far more steps.

|  Type     |  max uW/cm2  |
|:---------:|:------------:|
|  TSL260R  |     30       |
|  TSL261R  |     70       |
|  TSL262R  |    125       |


**Warning** this library is experimental so you should use it with care.
It is written on the datasheet as I have no hardware yet to test it. 
Of course I am very interested in your experiences and feedback to improve
the library.


#### Related

- https://github.com/RobTillaart/TSL235R pulse based irradiance variant.
- https://github.com/RobTillaart/TSL260R analog IR irradiance variant.
- https://github.com/RobTillaart/AnalogUVSensor
- https://github.com/RobTillaart/ML8511  UV sensor


## Hardware Connection

#### Power supply

The maximum output voltage depends on the power supply voltage.
This implies that the output range (uW/cm2) depends on power supply voltage.
To maximize the measurement range a voltage of at leat 4.5 V is advised.

See datasheet figure 14: Maximum Output Voltage vs Supply Voltage


#### Schema

Always check datasheet 

```
//  Front view 
//
//  PIN 1 - GND
//  PIN 2 - VDD      2.7 V .. 5.5 V
//  PIN 3 - SIGNAL   voltage out
```


## Interface

```CPP
#include "TSL260R.h"
```

#### Internal ADC

- **TSL260R(uint8_t pin, uint16_t maxADC, float voltage)** Constructor when using an 
internal ADC and just one sample to measure the output voltage of the sensor.
  - pin = analogRead() pin
  - maxADC = max value of the internal ADC, UNO = 1023.
  - voltage = max voltage of the internal ADC.
- **TSL261R(uint8_t pin, uint16_t maxADC, float voltage)** idem for TSL261R.
- **TSL262R(uint8_t pin, uint16_t maxADC, float voltage)** idem for TSL262R.
- **float irradiance()** returns the irradiance in uW/cm2.
Uses the analogRead() of the internal ADC. 
**Fails** by returning 0 when object is created with the other constructor.


#### External ADC

- **TSL260R()** constructor when using an external ADC or more than one internal samples
to measure the voltage.
When using this constructor one cannot use the parameterless **irradiance()**, see above.
- **TSL261R()** idem for TSL261R.
- **TSL262R()** idem for TSL262R.
- **float irradiance(float voltage)** returns the irradiance in uW/cm2 based upon voltage 
parameter. Does not use an internal analogRead(). 
Note the user can average 8 internal ADC measurements to reduce noise and then use 
this function based upon the average voltage.


#### WaveLength

- **void setWaveLength(uint16_t waveLength = 940)** sets the wave length so the conversion 
can use a correction factor. 
At 900 - 940 nm the wave length correction factor == 1.0.
Wave length should be between 830 and 1100.
- **uint16_t getWaveLength()** returns the configured wave length.
- **float getWaveLengthFactor()** returns the wave length correction factor. 
Note the sensor is most sensitive around 940 nm. See datasheet.
- **calculateWaveLengthFactor(uint16_t waveLength)** calculates the factor to compensate 
for less sensitivity at other wave lengths.
E.g. if the sensor is 0.5 x as sensitive at a given wave length the factor should be 2. 


#### Calibration

Since version 0.1.2 the following functions are added to calibrate the irradiance formula
to some extend. The formula is ```irradiance = AA * voltage + BB```.

See datasheet figure 12: Output Voltage vs Irradiance

Use with care.

- **void setAA(float aa)** set a new value for AA.
- **float getAA()** return the current value.
- **void setBB(float bb)** set a new value for BB.
- **float getBB()** return the current value.


## Operations

See examples.


## Future

#### Must

- improve documentation
- buy hardware (where)
- test test test test

#### Should

- extend unit tests
- write examples
- fix the dependency of **irradiance()**
  - derived class?
- optimize code

#### Could

- test with different IR LEDS (e.g. remote)
- Normalized Output Voltage vs Angular Displacement correction
  - figure 11
- temperature correction

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

