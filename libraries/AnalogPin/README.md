
[![Arduino CI](https://github.com/RobTillaart/AnalogPin/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AnalogPin/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AnalogPin/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AnalogPin/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AnalogPin/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AnalogPin.svg)](https://github.com/RobTillaart/AnalogPin/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AnalogPin/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AnalogPin.svg?maxAge=3600)](https://github.com/RobTillaart/AnalogPin/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AnalogPin.svg)](https://registry.platformio.org/libraries/robtillaart/AnalogPin)


# AnalogPin

Arduino library to add functionality on top of analogRead().


## Description

AnalogPin is an Arduino class that adds noise filtering and smoothing to analogRead().
Furthermore it can speed up the analogRead() function by tuning the pre-scaler.
This latter is AVR only.


## Interface

```cpp
#include "AnalogPin.h"
```

- **AnalogPin(uint8_t pin)** constructor with analogue pin as parameter.
- **void setPrescaler(uint8_t prescaler = 7)** AVR only pre-scaler.
- **uint8_t getPrescaler()** return pre-scaler set.
- **void  setNoiseThreshold(uint8_t noise = 0)** set noise level that should be ignored. 
Typical 0..2.
- **uint8_t getNoiseThreshold()** return set value.
- **void setSmoothWeight(uint8_t alpha = 0)** alpha = 0..31, parameter for low pass filter.
- **uint8_t getSmoothWeight(void)** returns set alpha.
- **int read(bool twice = false)** read function, optional read twice to stabilize.
- **int readSmoothed()** read version that uses low pass filter.
- **int readPrevious()** returns previous read value.
- **int readLast()** returns last read value without reading a new one.


## Operation

**get/setPrescaler(uint8_t prescaler)** can be used to speed up analogRead().  
The effect is that both the accuracy and precision are affected.
You should verify if this is acceptable for your project.
***Works only for AVR based boards***

**get/setNoiseThreshold(uint8_t noise)** is used to set the noise threshold to be used by the **read()** function.

**read(bool twice)** implements an **analogRead()** that suppresses small noise fluctuations.
The parameter twice is used to force analogRead() to be executed twice to reduce noise from the multiplexing.

Example: if the previous read has the value 300 and you
want to interpret all subsequent readings between 290
and 310 as 300 (the same) your code should look like:
```
    AP.setNoiseThreshold(10);
    AP.read();
```

**get/setSmoothWeight(uint8_t alpha)** is used to set the weight factor for the **readSmoothed()** function.

The weight of the previous read is **alpha/32**.
A higher alpha will dampen the signal more, a lower alpha
will follow the actual signal better.
This can be used to suppress noise too.

```
    AP.setSmoothWeight(4);   // weight = 4/32 = 1/8 = 12.5%
    AP.readSmoothed();
```

**readSmoothed()** implements an analogRead with a running average build in.


## Future

#### Must

- update documentation
  - advantage of certain functions, when to use

#### Should

- more examples

#### Could

- move code to .cpp

#### Wont

- **volts()** + get/setFactor(float f)
  - any other unit would make equal sense?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


