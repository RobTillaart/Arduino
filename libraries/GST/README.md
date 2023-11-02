
[![Arduino CI](https://github.com/RobTillaart/GST/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/GST/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/GST/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/GST/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/GST/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/GST.svg)](https://github.com/RobTillaart/GST/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/GST/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/GST.svg?maxAge=3600)](https://github.com/RobTillaart/GST/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/GST.svg)](https://registry.platformio.org/libraries/robtillaart/GST)


# GST

Arduino library for Gold Standard Test metrics.


## Description

Note: **experimental**

The GST library is an implementation of the **Gold Standard Test**.


#### Links

These sites describe the functions in more detail.

- https://en.wikipedia.org/wiki/Sensitivity_and_specificity
- https://en.wikipedia.org/wiki/Confusion_matrix


#### Related

- https://github.com/RobTillaart/Correlation
- https://github.com/RobTillaart/GST - Golden standard test metrics
- https://github.com/RobTillaart/Histogram
- https://github.com/RobTillaart/RunningAngle
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian
- https://github.com/RobTillaart/statHelpers - combinations & permutations
- https://github.com/RobTillaart/Statistic


#### Performance

The math functions are from pretty straightforward to rather complex.

It is possible to optimize functions with intermediate values if needed. 
However the right way to optimize depends on the way the library is used. 


## Interface

```cpp
#include "GST.h"
```

See .h file for all functions. Many function exist in a long descriptive name and an acronym version. Here only the long names are given.

For the definitions please check - https://en.wikipedia.org/wiki/Sensitivity_and_specificity or
https://en.wikipedia.org/wiki/Confusion_matrix


### Input functions

These four numbers should all be set before output functions make sense.
The parameter **value** is typical absolute value measured or counted.
If the parameter is omitted, the default 0 will be used to reset the value.

- **void setTruePositive(float value = 0)** set the internal TP value.
- **void setTrueNegative(float value = 0)** set the internal TN value.
- **void setFalsePositive(float value = 0)** set the internal FP value.
- **void setFalseNegative(float value = 0)** set the internal FN value.
- **void clearAll()** reset all the above to 0.

In tests one often want to increase / change the numbers.
This can be done with the **addTruePositive()** etc functions. 
After every addition all output functions can be called.

- **float addTruePositive(float value)** increases the internal TP value.
Use a negative value to decrease.
Returns the new value of TP.
- **float addTrueNegative(float value)** increases the internal TN value.
Use a negative value to decrease.
Returns the new value of TN.
- **float addFalsePositive(float value)** increases the internal FP value.
Use a negative value to decrease.
Returns the new value of FP.
- **float addFalseNegative(float value)** increases the internal FN value.
Use a negative value to decrease.
Returns the new value of FN.


### Output functions I

Basic output

- **float getTruePositive()** returns internal TP.
- **float getTrueNegative()** returns internal TN.
- **float getFalsePositive()** returns internal FP.
- **float getFalseNegative()** returns internal FN.


- **float getTotal()** returns total of four numbers.
- **float getActualPositive()**
- **float getActualNegative()**
- **float getTestedPositive()**
- **float getTestedNegative()**


- **float sensitivity()** equals truePositiveRate().
- **float specificity()** equals trueNegativeRate()


**Rate** functions can be multiplied by 100.0 to get percentage.

- **float truePositiveRate()** returns value between 0.0 and 1.0
- **float trueNegativeRate()** returns value between 0.0 and 1.0
- **float falseNegativeRate()** returns value between 0.0 and 1.0
- **float falsePositiveRate()** returns value between 0.0 and 1.0


### Output functions II

These output functions are the more 'complex' functions.
Read the Wikipedia pages for their uses.

- **float positivePredictiveValue()**
- **float negativePredictiveValue()**
- **float falseDiscoveryRate()**
- **float falseOmissionRate()**


- **float positiveLikelihoodRatio()**
- **float negativeLikelihoodRatio()**


- **float prevalenceThreshold()**
- **float threatScore()**
- **float criticalSuccessIndex()**


- **float prevalence()**
- **float accuracy()**
- **float balancedAccuracy()**
- **float F1Score()**


- **float MatthewsCorrelationCoefficient()**
- **float FowlkesMallowsIndex()**
- **float BookmakerInformedness()**


- **float markedness()**
- **float deltaP()**
- **float diagnosticOddsRatio()**


## Future

#### Must

- improve documentation

#### Should

- add functions
  - percentage functions for TP TN FP and FN?
- test
  - complete the CI test coverage.

#### Could

- examples
  - add real life examples.
  - combination with a sensor? batch testing?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

