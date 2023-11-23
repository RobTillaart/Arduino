
[![Arduino CI](https://github.com/RobTillaart/WaveMix/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/WaveMix/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/WaveMix/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/WaveMix/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/WaveMix/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/WaveMix.svg)](https://github.com/RobTillaart/WaveMix/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/WaveMix/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/WaveMix.svg?maxAge=3600)](https://github.com/RobTillaart/WaveMix/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/WaveMix.svg)](https://registry.platformio.org/libraries/robtillaart/WaveMix)


# WaveMix

WaveMix is an Arduino library to mix two signals (A and B) with an adaptive weight.


## Description

WaveMix is a very simple library to mix two signals (A and B) with an adaptive weight.

Depending on the weights applied the output signal (O) looks more on signal A or on signal B. 
A gain can be applied to amplify weak signals or to be used for modulation.


Inspired by - https://www.codeproject.com/Articles/5323200/On-how-to-mix-two-signals-by-using-Spectral-Foreca

Differences
- simpler algorithm
- WaveMix works on streams of measurements too.


## Interface

```cpp
#include "WaveMix.h"
```

The main functions of the WaveMix:

- **explicit WaveMix()** Constructor
- **bool setWeight(float weight1, float weight2)** set the weight of the channels A and B. 
The weights do not need to be normalized, so one can use e.g **setWeight(7, 13)** See below.
The function returns false if the weights sum up to 0. (no changes will be made)
- **float getW1()** return the normalized weight for channel A.
- **float getW2()** return the normalized weight for channel B.
- **bool  setPercentage(float percentage)** sets the weight for channel A to percentage. 
Channel B will have 100 - percentage.
Returns false if percentage < 0 or percentage > 100. (no changes will be made)
- **void  setGain(float gain)** sets the gain factor.
An important use of gain is to amplify weak signals but one can also use it as a modulator of a signal.
See examples.
- **float getGain()** return the gain set.
- **void  setOffset(float offset)** sets the offset for the output signal. 
Typical used to align the zero level.
- **float getOffset()** return the current offset used.
- **float mix(float s1, float s2 = 0)** returns the weighted average of signal1 and signal2. 
Signal2 is made optional to allow single signal processes e.g. modulation by **setGain()**.


## Operation

See examples.


#### Weights

**setWeight()** typically uses positive weights, e.g. **setWeight(7, 13)**
counts A for 7/20 part and B for 13/20 part. 
It is also possible to use one or two negative weights. 
Using negative weights means effectively the input value is inverted before it is added. 
E.g. **setWeight(-1, 0)** would effectively invert signal A.
Only restriction to the weights is that the sum of the weights may not be zero.


#### Amplification

Weights cannot be used to amplify the signal in absolute sense, use **setGain()** for that.
By constantly updating the gain (0..max) one can implement **Amplitude Modulation**.

When the gain is negative, the output is effectively inverted.


## IDEA: N channel variant.

- add **setValue(uint8_t channel, float value)** allow update of channels at a different frequency.
- add **getValue()**, read the current output given the value of the channels. OR
- add **getValue(uint8_t mask = 0xFF)**, read the current output given the value of selected channels.
- add **setMask(uint8_t mask = 0xFF)**, select channels. ease of use?  **getValue(mask)** still needed?
- add **getMask()**, read back \_mask;
- note that **mix()** can be implemented with the above functions.
- add **setWeight(uint8_t channel, float weight)** need internal array of weights and \_sum
- add **float getWeight(uint8_t channel)** Normalized or not?
Not normalized allows easier increment per channel. Needs a **float getTotalWeight()**.
- add constructor **WaveMix(uint8_t channels = 8)** with parameter to set the number of channels? \[NO\]
- or do we need **WaveMix2()**, **WaveMix4()**, **WaveMix8()**, or even **WaveMix16()**, **WaveMix24()**, **WaveMix32()** class?

**WaveMix4()** and **WaveMix8()** seems to be realistic in terms of performance.
**WaveMix8()** can be used for 2-8 channels, using a uint8_t mask.
More channels will be much slower, so upon request the 16 and 32 variant? other variants can be obtained by masking.


## Future


#### Must

- improve documentation

#### Should

- performance test.
- investigate N channel idea.

#### Could

- think of integer version
  - performance
  - integer weights
  - math in **int32_t** with last moment float conversion 
- Templated version
  - float vs double vs int
  - maybe upon request.
- dynamic weights
  - add **increment(float)**
  - add **decrement(float)**
  - percentages? hard for multichannel?
- default parameters
  - gain = 1.0
  - percentage 50%
  - offset = 0.0
  - **reset()** needed?

#### Wont

- add top clipping
  - add **setMaximum(float)**
  - add **setMinimum(float)**
  - needs an enable/disable per limit. 
    becomes more complex than let the user constrain the output.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

