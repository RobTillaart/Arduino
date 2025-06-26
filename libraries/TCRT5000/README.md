
[![Arduino CI](https://github.com/RobTillaart/TCRT5000/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TCRT5000/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TCRT5000/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TCRT5000/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TCRT5000/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TCRT5000.svg)](https://github.com/RobTillaart/TCRT5000/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TCRT5000/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TCRT5000.svg?maxAge=3600)](https://github.com/RobTillaart/TCRT5000/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TCRT5000.svg)](https://registry.platformio.org/libraries/robtillaart/TCRT5000)


# TCRT5000

Arduino library for the TCRT5000 reflective optical sensor (IR).


## Description

**Experimental**

The TCRT5000 sensor is an infrared reflective sensor. 
This library is written to use with a TCRT5000 breakout's analog output
and handle a threshold in software. 

These breakouts have typical two outputs, a digital and an analog one.
The analog output returns a "raw" signal strength.
The digital output has a threshold level depending on a potentiometer
which is typically set once.

The library allows to set a threshold in software and compare if the 
raw signal is either above or below this set threshold.
As the threshold is set in software it can be changed runtime.
This can be useful to adapt e.g. to changing lighting conditions.

As always feedback is welcome.


Uses analog output.


### Related

- https://github.com/RobTillaart/PIR


## Interface

```cpp
#include "TCRT5000.h"
```

### Base

- **TCRT5000(uint8_t analogPin)** 
- **int read()**
- **int lastRead()**

### Threshold

Default threshold **TCRT5000_DEFAULT_THRESHOLD (500)**.
This is about 50% of the UNO R3 ADC, so you might need to change this.

- **void setThreshold(int threshold)** idem
- **int getThreshold()** returns set value or the default.
- **bool aboveThreshold()** reads the sensor and returns true is above 
the set (or default) threshold.
- **bool belowThreshold()**  reads the sensor and returns true is below
or equal to the set (or default) threshold.


## Future

#### Must

- improve documentation

#### Should

- add examples

#### Could

- compare to threshold, (use case?)
  - **int absoluteTH()**  == read() - threshold;
  - **float relativeTH()**  == ((read() - threshold) x 1.0)/ threshold;
  - **float percentageTH()**  == 100 x relativeTH();

#### Wont

- convert to distance
  - depends on a lot of factors.

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


