
[![Arduino CI](https://github.com/RobTillaart/TGS2620/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TGS2620/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TGS2620/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TGS2620/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TGS2620/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TGS2620.svg)](https://github.com/RobTillaart/TGS2620/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TGS2620/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TGS2620.svg?maxAge=3600)](https://github.com/RobTillaart/TGS2620/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TGS2620.svg)](https://registry.platformio.org/libraries/robtillaart/TGS2620)


# TGS2620

Arduino library for the TGS2620 and compatibles.


## Description

**Experimental**

This library is to use the TGS2620 sensor to measure (estimate) the 
concentration of a number of gasses. 

The library is NOT tested with hardware yet.  
The accuracy is unknown / to be established.  

The sensor is sensitive for multiple gasses and the sensor cannot 
discriminate between them. So use with care.

Feedback as always is welcome.


### Hardware setup

See datasheet page 3 for details of the pins.

(simple schema, use pin 2 and 3 of sensor)

```
     5V-----[ SENSOR ]-----O------[ RL ]------ GND
                           |
                           |
                           V
                        analogRead
```

Do not forget the heater.
The heater uses 40~45 mA so cannot be sourced directly by the MCU.


### Special characters

Ω == Ohm = ALT-234 (Windows)
µ == micro = ALT-0181 (Windows)


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment, 
and any other applications that may cause personal injury due to the product's failure._


### Related

- https://github.com/RobTillaart/TGS2620 - this lib
- https://github.com/zigpot/tgs2600-on-arduino - related sensor TGS2600

Calibration story for TGS2600 sensor (close relative) - very useful
- https://zigpot.wordpress.com/2021/09/29/setting-up-gas-sensor-for-microcontroller/

Other environmental sensors
- https://github.com/RobTillaart/MTP40C - CO2 sensor
- https://github.com/RobTillaart/MTP40F - CO2 sensor
- https://github.com/RobTillaart/Cozir - CO2 sensor


### Multiplexing

Sometimes you need to control more devices. As this device uses an analog port
on can add one device per analog port or use a multiplex chip like these.

- https://github.com/RobTillaart/HC4051  (1x8 mux)
- https://github.com/RobTillaart/HC4067  (1x16 mux)


## Interface

```cpp
#include "TGS2620.h"
```

### Constructor

- **TGS2620(uint8_t analogPin, uint16_t maxSteps)** define the analogRead parameters.
- **bool configure(uint16_t RZero, uint16_t RLoad)** configure the resistor values in Ohm Ω.
Rzero is resistance of the sensor in fresh air, RLoad is the second resistor, see
hardware setup above (and datasheet).

Determine RZero.

In the absence of contaminants in the air, the resistance is called RO (RZero).
This baseline resistance (RO) has to be known prior to performing any operations. 
The calibration is performed by blowing fresh air onto the sensor (cleaning any remaining 
contaminants) and measuring the value of RS in a clean environment.

Determine RZero can be done with the example **TGS2620_determine_RZero.ino**


### Calibration I

Approximations of calibrate parameters from TGS2620 datasheet page 4
for the formula

```
PPM = a * pow(Rs/R0, b);
```

You might need to determine the numbers a and b yourself as individual sensors 
might differ slightly.
 
|  sensor   |  graph      |  a           |  b           |
|:----------|:------------|:------------:|:------------:|
|  TGS2620  |  Methane    |  40326,4527  |  -2,4245189  |
|  TGS2620  |  CO         |  1354,64785  |  -1,7801573  |
|  TGS2620  |  Iso-butane |  563,810190  |  -1,7098237  |
|  TGS2620  |  Hydrogen   |  358,088021  |  -1,8791876  |
|  TGS2620  |  Ethanol    |  320,799771  |  -1,5398176  |

Note compatible sensors like TGS2600 and TGS2610 the gasses have different 
parameters, so for these others one need to determine the parameters a and b..


- **void calibrate(float a, float b)** idem

```
Spreadsheet raw trend line formulas (more digits)

f(x) = 40326,4526622636 x^-2,42451890362475
f(x) = 1354,64785299791 x^-1,78015730335775
f(x) = 563,810189715868 x^-1,70982365658289
f(x) = 358,088020604221 x^-1,87918756975433
f(x) = 320,799770799109 x^-1,53981762140293
```

### Calibration II

Calibrating in a nutshell.

- put graph values in a spreadsheet
- create an X-Y chart
- add trend-line => select power
- get the a and b values.


### getPPM()

- **float getPPM(uint8_t reads = 1)** read the sensor with the internal analogPin configured 
in the constructor. Optional do more than one read.
Convert the raw value to PPM based upon configure and calibrate data.
- **float getPPM(uint16_t value, uint16_t maxSteps)** read the sensor with an external ADC 
and provide the value and the maxValue. Will convert the raw value to PPM.
- **uint32_t lastRead()** timestamp in milliseconds. Convenience.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- investigate temperature dependency  (T)
- investigate relative humidity dependency (%RH)
- investigate voltage dependency (V) (low)
- improve support external ADC.

#### Could

- add examples
- explain curves like startup etc.
- heater control by library?
  - IO pin with MOSFET.

#### Wont
- as formulas are known on could do "selectCO() or getPPMMethane()**
  - would break support of 2600/2610.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


