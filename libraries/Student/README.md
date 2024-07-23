
[![Arduino CI](https://github.com/RobTillaart/Student/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Student/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Student/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Student/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Student/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Student.svg)](https://github.com/RobTillaart/Student/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Student/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Student.svg?maxAge=3600)](https://github.com/RobTillaart/Student/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Student.svg)](https://registry.platformio.org/libraries/robtillaart/Student)


# Student

Arduino library for Student or T-distribution math.


## Description

**Experimental**

Student is an experimental Arduino library to estimate the mean (average) of a population
based upon a (very) small sample (selection).
Goal is to calculate the interval for which there is a certain confidence e.g. 95%, 
that the population mean lies between the estimated mean from the sample +- some intervalDelta.

The 0.1.x version of the library is limited to a maximum of 20 samples to keep RAM usage 
relative low. 
It uses a lookup table (LUT) for a sample size up to 20, and for five discrete confidence 
levels 80%, 90%, 95%, 98% and 99% ==> size table = 20 x 5 = 100 floats. 
The table encodes the 100 floats as uint16_t to save 50% of the RAM needed.

The library allows to calculate the interval after every addition until the internal buffer
of 20 samples is full. Note that at least 2 samples are needed to calculate the interval.


### StudentTable.h

The table is defined in the file **StudentTable.h** and generated from a spreadsheet.

If one need to extend the sample size, the file contains commented values for sample size 21-100.
One has to adjust **STUDENT_MAX_SIZE** in **StudentTable.h** too (max 255).
Note this will cost extra RAM.

If one wants to reduce the sample size / RAM, one can comment part of the table not needed.
One has to adjust **STUDENT_MAX_SIZE** too.


### Application example

If one wants to estimate the average temperature, one can measure it constantly and
calculate the average from all measurements. This may take up to 3600 samples per hour.
With the Student library one can measure the temperature once every 5 minutes.
This give 12 samples from which one can calculate the interval of the average temperature 
with 95% confidence.

This takes far less samples and calculation time and might meet the insights you need.
Furthermore using this method can be ideal in an low power environment (e.g. remote, 
battery powered sensor, with long sleep) to get the information you need.


### History

The T-distribution is developed by William Gosset, head experimental brewer, in 1908 while 
working for Guinness Beer. His goal was to guard a constant quality of the beer brewed.
He needed a method to determine the quality of the raw materials like grains, malt and hops,
based on small samples from the fields. 
For this he invented the t-distribution and published it under the name Student. 
Therefore this distribution is also known as the Student distribution.


### Accuracy / precision

The version 0.1.x uses float for internal storage. This means precision is at most 6-7 digits.

The version 0.1.x lookup table has 20 x 5 values with 3 decimals, coded as an uint16_t (for RAM)
This allows about 3-4 digits precision for the found interval.

The 0.1.x version does not interpolate the confidence level (yet), and only support 5 distinct levels.
This interpolation (between 80-99) is planned to be implemented in the future.
If a non supported confidence level is used, the library will use 95%.

If you need only one confidence interval you could strip the lookup table to one column.


### Character

|  parameter  |  name  |  ALT-code  |  char |
|:-----------:|:------:|:----------:|:-----:|
|  mean       |  mu    |  ALT-230   |   µ   |
|  stddev     | sigma  |  ALT-229   |   σ   |
|  CDF        |  phi   |  ALT-232   |   Φ   |  ALT-237 for lower case
|  plus minus |        |  ALT-0177  |   ±   |

- https://altcodesguru.com/greek-alt-codes.html


### Related

- https://en.wikipedia.org/wiki/Normal_distribution
- https://en.wikipedia.org/wiki/Student_distribution
- https://sphweb.bumc.bu.edu/otlt/mph-modules/bs/bs704_probability/bs704_probability9.html
- https://github.com/RobTillaart/Gauss
- https://github.com/RobTillaart/Multimap
- https://github.com/RobTillaart/Statistic  (more stat links there).
- https://github.com/RobTillaart/Student


## Interface

```cpp
#include Student.h
```

### Constructor + meta

- **Student()** constructor. 0.1.x has a fixed max sample size STUDENT_MAX_SIZE = 20.
- **uint8_t getSize()** returns STUDENT_MAX_SIZE == 20.
- **uint8_t getCount()** returns the number of samples added.
Returns value between 0 .. getSize().
- **void reset()** resets internal counter to zero.

### Add

- **bool add(float value)** adds one sample.
Returns false if internal buffer is full (count >= size).
- **bool add(float \*array, uint8_t size)** adds an array of samples.
Returns false if the internal buffer would "overflow".

### Math

- **float mean()** returns mean (average) of the samples added. 
This is the estimated mean of the population from which the samples are taken.
- **float variance()** returns variance of the samples added.
- **float deviation()** returns standard deviation of the samples added.
- **float estimatedDeviation()** returns estimated deviation of the 
estimated mean (based upon the samples).

### Interval

Confidence should be 80, 90, 95, 98 or 99. 
The confidence level is not interpolated and incorrect values are replaced by 95%.

- **float intervalDelta(int confidence)** returns the delta to be added
oor subtracted to the mean to determine the confidence interval.
- **float meanLower(int confidence)** returns mean - intervalDelta.
- **float meanUpper(int confidence)** returns mean + intervalDelta.


## Future

#### Must

- documentation
- improve upon function names.
- test test test

#### Should

- t test example.
- optimize code, e.g. cache values for performance.
- optimize lookup table, PROGMEM for footprint?
- dynamic allocation for sizes > 20
  - or derived classes, student30, student40, student50, student100?
  - linear interpolation for values > 10 (performance?)
- add interpolation to **intervalDelta()** so confidence level (0.2.x)
  could be any integer value from 80-99 (maybe even float?)

#### Could

- add examples
- add unit tests
- replace look up table with a formula? (performance drop!!)
- access function for internal array to access samples?
- template class instead of STUDENT_MAX_SIZE? (becomes different types).
- circular buffer for the samples? Running T-test?

#### Won't (unless requested)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

