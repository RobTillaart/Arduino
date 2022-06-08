
[![Arduino CI](https://github.com/RobTillaart/GST/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/GST/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/GST/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/GST/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/GST/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/GST/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/GST.svg?maxAge=3600)](https://github.com/RobTillaart/GST/releases)


# GST

Arduino library for Gold Standard Test metrics.


## Description

Note: **experimental**

The GST library is an implementation of the **Gold Standard Test**.


#### Links

These sites describe the functions in more detail.

- https://en.wikipedia.org/wiki/Sensitivity_and_specificity
- https://en.wikipedia.org/wiki/Confusion_matrix


#### Performance

The math functions are from pretty straightforward to rather complex.

It is possible to optimize functions with intermediate values if needed. 
However the right way to optimize depends on the way the library is used. 


#### Related libraries

- https://github.com/RobTillaart/Statistic


## Interface

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


- **float truePositiveRate()**
- **float trueNegativeRate()**
- **float falseNegativeRate()**
- **float falsePositiveRate()**


### Output functions II

These are the more 'complex' functions.
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

- improve documentation
- add functions
  - percentage functions for TP TN FP and  FN?
- test
  - complete the CI test coverage.
- examples
  - add real life examples.
  - combination with a sensor? batch testing?
