
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

The library holds the last read value and the previous value. These are needed for the
smoothing and allows the users to implement their own smoothing functions.

Furthermore it can speed up the analogRead() function by tuning the pre-scaler.
This latter is AVR only.

Feedback as always is welcome.

## Interface

```cpp
#include "AnalogPin.h"
```

### Constructor

- **AnalogPin(uint8_t pin)** constructor with analogue pin as parameter.

### Read

- **int read(bool twice = false)** read function, optional read twice to stabilize the
internal ADC after multiplexing.
- **int readSmoothed()** read version that uses a low pass filter, see **setSmoothWeight()** below.
- **int readPrevious()** returns previous read value.
- **int readLast()** returns the last read value (cache) without reading a new one.


**read(bool twice)** implements an **analogRead()** that suppresses small noise fluctuations.
The parameter twice is used to force analogRead() to be executed twice to reduce the noise from the multiplexing of the internal ADC.


### Prescaler, AVR only

- **void setPrescaler(uint8_t prescaler = 7)** AVR only pre-scaler.
- **uint8_t getPrescaler()** return pre-scaler set.

**get/setPrescaler(uint8_t prescaler)** can be used to speed up analogRead().
The effect is that both the accuracy and precision are affected.
You should verify if this is acceptable for your project.


### Noise suppression

- **void  setNoiseThreshold(uint8_t noise = 0)** set the noise level that
should be ignored in the read() function. Typical value 0..2 but can be set
larger in noisy environments.
Default value = 0, no noise suppression.
- **uint8_t getNoiseThreshold()** return the value set or default zero.

Example: if the previous read has the value 300 and you
want to interpret all subsequent readings between 290
and 310 as 300 (the same) your code should look like:
```
    AP.setNoiseThreshold(10);
    AP.read();
```

### Smooth averaging

- **void setSmoothWeight(uint8_t alpha = 0)** alpha = 0..31, set the weight factor for the
low pass filter used in **readSmoothed()**. Default the low pass filter is disabled, (alpha = 0).
- **uint8_t getSmoothWeight(void)** returns set alpha, or the default zero.


The weight of the previous read is **alpha/32**.
A higher alpha will dampen the signal more,
a lower alpha will follow the actual signal better.
An alpha of zero will ignore the previous read.

This parameter can be used to suppress noise too.

```
    AP.setSmoothWeight(4);   // weight = 4/32 = 1/8 = 12.5%
    AP.readSmoothed();
```

## Future

#### Must

- update documentation
  - advantage of certain functions, when to use

#### Should

- more examples

#### Could

- move code to .cpp / .h?

#### Wont

- **volts()** + get/setFactor(float f)
  - any other unit would make equal sense => user must handle this.
  - example added.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


