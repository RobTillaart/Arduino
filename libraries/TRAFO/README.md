
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
- RMS of an 230 or 110 Volt AC.
- detect the frequency of the line.

The library has a define **TRAFO_DEFAULT_FREQUENCY** (50 Hz) which can be overruled
by compile time command line options (or changed in the TRAFO.h file).

Note: The ZMPT101B board I have, has a potentiometer for minor adjustments.

The https://github.com/RobTillaart/map2colour library allows to map the read RMS 
voltage or the determined frequency to a colour scale of choice (RGB LED).

Feedback as always is welcome.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment, 
and any other applications that may cause personal injury due to the product's failure._


### Related

- https://github.com/RobTillaart/ACS712 - current sensor AC and DC
- https://github.com/RobTillaart/INA226 - current and voltage sensor (one of many)
- https://github.com/RobTillaart/map2colour - mapping values to colour scale.
- https://github.com/RobTillaart/printHelpers - for scientific notation

Trigger for this library
- https://forum.arduino.cc/t/using-zmpt101b-with-ads1115/1434976 



### Tested

Tested on Arduino UNO R3 with ZMPT101B transformer. Used a calibrated DMM to get
the trafoFactor right. 50 Hz and 242.3 mains were detected correctly. 
Although the mains seems high (~230 expected), this was confirmed by the DMM.

A minimal test with an UNO R3 (powered over USB) with floating internal ADC 
touched by my finger gave a frequency of around 50 Hz which is our mains.
This might come (somehow) indirectly from mains which is 50 Hz.
 

## Interface

```cpp
#include "TRAFO.h"
```

### Constructor

- **TRAFO()** constructor.
- **bool begin(int32_t (\* readADC)(), uint32_t steps, float maxVoltage, float trafoFactor = 1)** 
  - readADC is a function to read an ADC returning an int32. This can be a wrapper around any 
    internal or external ADC.
  - steps = number of ADC steps, typical power of two like 1024, 4096, etc. (Or 1023, 4095)
  - maxVoltage = conversion voltage for maximum value of the ADC used
  - trafoFactor = conversion of ADC voltage to transformer voltage (calibration). 
    The default of the trafoFactor is set to 1, which allows to read small AC voltages.

Note: the **trafoFactor** in my first hardware test (UNO R3 + ZMPT101B) had a value of 708.
This was determined by providing AC and measure it with a calibrated DMM. See below.


### Measurements

- **float detectFrequency(uint8_t times = 1)** idem. 
Typical around 50.0 or 60.0. Sample multiple times to improve accuracy.
The frequency range detectable is expected to work for 10 - 400 Hz. (to be verified).
Note it will be blocking for at least two periods.
- **void setMicrosAdjust(float factor = 1.0f)** adjust the micros timing 
to improve the accuracy of the frequency measurement.
- **float getRMS()** Returns the "main" voltage, typical around 230V or 110V.
Only works if detectFrequency() is called before as it needs the zeroPoint.
- **float getPTP()** Returns the minimum peak to maximum peak voltage. 
This can be used to determine the RMS voltage by multiplying with the 
FormFactor of the wave form (typical sine).
- **float determineFormFactor()** reverse calculating the FormFactor
from **getPTP** and **getRMS()**.

The library has a commented **getRMS()** version that is based upon the 
peak to peak value. In initial tests it was slightly less accurate.
The difference was less than 2% so it might actual be not too bad.
Cause is probably not a perfect sine wave form.

The library has a commented **determineFormFactor()** version which is 
faster and uses more program memory.


### Debugging

- **int32_t getADC()** call the readADC given in **begin()**.
returns raw units.
- **float getVoltagePerStep()** returns the ```maxVoltage x trafoFactor / steps```.
- **int32_t getZeroPoint()** last determined zero point (in ADC units).


## Calibration

First run a sketch with the trafoFactor set to 100, call getRMS() and divide 
the value expected (e.g. from DMM) by the value you got (x 100). 
This is the new trafoFactor.

Example
- Set the trafoFactor to 100, and measure the RMS
- The expected voltage is 242 Volt, and getRMS() returns 32.34
- The missing factor = 242 / 32.34 = 7.483
- So the trafoFactor should be 100 x 7.483 = 748.3
- Set the trafoFactor to 748.3 to confirm the new value.


## Future

#### Must

- improve documentation

#### Should

- investigate performance improvements.
- investigate need for yield (RTOS?)
- investigate frequency range detected.
- As detectFrequency() determines the peak2peak value, its signature might 
  need to change to **float measure(float &freq, float &RMS)** so it 
  measures all in one call might be efficient.  (0.2.0)
- test 110 Volt and other AC levels 
- test other transformers.


#### Could

- create unit tests if possible.
- other functions possible?
- add **float getSecondaryVoltage()** something ?


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


