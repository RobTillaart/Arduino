
[![Arduino CI](https://github.com/RobTillaart/SMC/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SMC/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SMC/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SMC/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SMC/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SMC.svg)](https://github.com/RobTillaart/SMC/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SMC/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SMC.svg?maxAge=3600)](https://github.com/RobTillaart/SMC/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SMC.svg)](https://registry.platformio.org/libraries/robtillaart/SMC)


# SMC

Arduino library for a Sliding Mode Controller (SMC).


## Description

**Experimental**

This library implements a Sliding Mode Controller class and was triggered by 
the chapter in the Elektor book **Control Engineering with Fuzzy Logic** from 
Josef Bernhardt (See related section below).
The book is well written, and offers a good introduction or refresh in the matter.

A Sliding Mode Controller (SMC) is an algorithm to control processes including
but not limited to control the heating process of an oven. 
This oven example is used to describe the working below.

**Warning** 

This library is mainly implemented to understand the way this type of process 
control works, so to say educational purpose.
It should not be used for mission critical or medical processes et al, see license.
Use at your own risk.


### SMC introduction

The SMC uses four parameters
- the setPoint, the target one want to reach (e.g. 80°C)
- the maxValue that can be send to the process (e.g. heater, max PWM or voltage)
- weight1 => for the 1st order error (how far is current value from setPoint)
- weight2 => for the 2nd order error (how much has the error itself changed)

The SMC class can work in three different modi, SMC_SIMPLE, SMC_LINEAR (default) 
and SMC_EXPONENTIAL.
- SMC_SIMPLE mode only uses the error. If the setPoint has not been reached,
it will set the heater to the maximum value. It is essentially just ON/OFF.
- SMC_LINEAR mode uses a weighted value of the 1st and 2nd order error.
If that is positive it will set the heater to the maximum value.
- SMC_EXPONENTIAL mode uses a weighted value of the 1st and 2nd order error.
It will control the heater to a value between 0 and maximum value.

Feedback as always is welcome.


### Related

E-book Josef Bernhardt
- https://www.elektor.nl/products/control-engineering-with-fuzzy-logic
- https://github.com/RobTillaart/PID_RT
- https://github.com/RobTillaart/Temperature


## Interface

```cpp
#include "SMC.h"
```

### Constructor

- **SMC()** constructor
- **void begin(float setPoint, float maxValue, float weight1, float weight2)** 
Sets the initial values for 
  - setPoint, the target one wants to reach (e.g. temperature)
  - the maximum level of the control signal, (e.g. heater)
  - weight1 == weight for the error between setPoint and measured value (1st order).
  - weight2 == weight for the delta error compared to previous error (2nd order).

The function **begin()** can be called multiple times with different parameters 
to adjust all settings at once.
There also exist functions to set and get these parameters on an individual basis.
See getters and setters below.


### Control

Essential two similar values, use the one that matches your setup.

- **float outValuePercentage(float inValue)** returns the control signal value 
between 0 and 100%.
- **float outValue(float inValue)** returns above % times the maxValue.
This function needs to be called in a (tight) loop.


### Mode

- **void setMode(uint8_t mode)** set the control mode, see table below.
- **uint8_t getMode()** returns current mode (0, 1)

|  mode  |  define           |  description  |
|:------:|:------------------|:--------------|
|   0    |  SMC_LINEAR       |  ON/OFF based on 1st and 2nd order error (default)
|   1    |  SMC_EXPONENTIAL  |  Continuous 0..100%
|   2    |  SMC_SIMPLE       |  ON/OFF only based on 1st order error (no weight)

Note: the SMC_SIMPLE is not discussed in the book.


### Getters and Setters

The process parameters can be changed and monitored continuously runtime.
This allows to e.g. increase or decrease the temperature one wants to guard.

The setter functions have no or minimal parameter range verification.

-**void setSetPoint(float setPoint)** the level one wants to reach / keep. 
Also known as the SOLL value.
-**float getSetPoint()** returns current setPoint.
-**void setNaxValue(float maxValue)** set the signal level to control the process.
-**float getMaxValue()** returns current maxValue.
-**void setWeights(float weight1, float weight2)** set the weights for the process.
-**float getWeight1()** get process weight for error
-**float getWeight2()** get process weight for delta error.


### Offset

The process might need adjustment in the form of an offset upon the **inValue**
parameter of the **outValue()** function to improve the control process.
This might help to bring over- and undershoot a bit in balance.

-**void setOffset(float offset)** set the offset
-**float getOffset()** returns set offset.


## Future

#### Must

- improve documentation
- build a test setup (e.g. DHT22 fan control)

#### Should

- implement example
  - DHT22 fan control.
  - MCP4725 - DAC
- parameter verification for setter functions
  - bool begin() too?
- need normal (heater) / inverted (cooler) flag  (100 - percentage)
  - could this also be done with negative weights?
  - SIMPLE does not use weights. (use sign??)

#### Could

- do we need two outValues?  (ON level OFF level)
- investigate -100% .. 100% model.
  - bool flag 
  - outValue() need to handle 
  - will it work for EXPONENTIAL ? how ?
- SMC_SIMPLE_ADAPT mode
  - evaluate error as percentage of the setPoint range (100% - 0%)

```
    //  something like this
    if (_mode == SMC_SIMPLE_ADAPT)
    {
      if (_error >= 0)
      {
        return 100 - 100 * (error / setPoint);
      }
      return 0;
    }
```


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


