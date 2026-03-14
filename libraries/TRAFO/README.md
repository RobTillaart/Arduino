
[![Arduino CI](https://github.com/RobTillaart/TRAFO/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TRAFO/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TRAFO/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TRAFO/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TRAFO/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TRAFO.svg)](https://github.com/RobTillaart/TRAFO/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TRAFO/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TRAFO.svg?maxAge=3600)](https://github.com/RobTillaart/TRAFO/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TRAFO.svg)](https://registry.platformio.org/libraries/robtillaart/TRAFO)


# TRAFO

Arduino library for AC line voltage and frequency measurement.


## Description

**Experimental, work in progress**

This library is to use a transformer (TRAFO) like the ZMPT101B to measure the 
AC line voltage.

The library was inspired by a discussion on the forum about using 
an external ADC for the ZMPT101B library. 
This library tries to generalize the concept so it can be used for different
transformers and with both internal as external ADC's.

The library supports
- RMS of an 230 or 110 V AC.
- detect the frequency of the line.

Feedback as always is welcome.

The library is not tested with hardware yet.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment, 
and any other applications that may cause personal injury due to the product's failure._


### Related

- https://github.com/RobTillaart/ACS712 - current sensor AC and DC
- https://github.com/RobTillaart/INA226 - current and voltage sensor (one of many)
- https://github.com/RobTillaart/printHelpers - for scientific notation

Trigger for this library
- https://forum.arduino.cc/t/using-zmpt101b-with-ads1115/1434976 



### Tested

TODO: 
- Test on Arduino UNO et al with transformer.
- order hardware - e.g. ZMPT101B module.

Note:
A minimal test with an UNO R3 (powered USB) with floating internal ADC 
touched by my finger gave a frequency of around 50 Hz which is our mains.
 

## Interface

```cpp
#include "TRAFO.h"
```

### Constructor

- **TRAFO()**
- **bool begin(int32_t (\* readADC)(), uint32_t steps, float maxVoltage)** 
  - readADC is a function to read an ADC returning an int32.
  - steps = nr of ADC steps, typical power of two like 1024, 4096, etc.
  - maxVoltage = conversion voltage for max value of ADC


### Measurements

- **float detectFrequency(uint8_t times = 1)** idem. 
Typical around 50.0 or 60.0. Sample multiple times to improve accuracy.
- **void setMicrosAdjust(float factor = 1.0f)** adjust the micros timing 
to improve the accuracy of the frequency
- **float getRMS()** idem. Typical around 230V or 110V.
Only works if detectFrequency() is called before.


### Debugging

- **int32_t getADC()** call the readADC given in constructor.
- **int32_t getZeroPoint()** last determined zero point.


## Future

#### Must

- improve documentation
- get hardware to test
- calibration routine

#### Should

- investigate performance

#### Could

- create unit tests if possible
- flag if detectFrequency is called for getRMS().

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


