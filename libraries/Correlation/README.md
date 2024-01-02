
[![Arduino CI](https://github.com/RobTillaart/Correlation/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Correlation/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Correlation/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Correlation/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Correlation/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Correlation.svg)](https://github.com/RobTillaart/Correlation/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Correlation/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Correlation.svg?maxAge=3600)](https://github.com/RobTillaart/Correlation/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Correlation.svg)](https://registry.platformio.org/libraries/robtillaart/Correlation)


# Correlation

Arduino Library to determine linear correlation between X and Y datasets.


## Description

This library calculates the coefficients of the linear correlation
between two (relative small) datasets. The size of these datasets is
20 by default. The size can be set in the constructor.

Please note that the correlation uses about ~50 bytes per instance,
and 2 floats == 8 bytes per pair of elements.
So ~120 elements will use up 50% of the RAM of an UNO.

The formula of the correlation is expressed as **Y = A + B \* X**.

If all points are on a vertical line, the parameter B will be NAN,
This will happen if the **sumXi2** is zero or very small.

Use with care.


#### Related

- https://github.com/RobTillaart/Correlation
- https://github.com/RobTillaart/GST - Golden standard test metrics
- https://github.com/RobTillaart/Histogram
- https://github.com/RobTillaart/RunningAngle
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian
- https://github.com/RobTillaart/statHelpers - combinations & permutations
- https://github.com/RobTillaart/Statistic


## Interface

```cpp
#include "Correlation.h"
```

#### Constructor

- **Correlation(uint8_t size = 20)** allocates the array needed and resets internal admin.
Size should be between 1 and 255. Size = 0 will set the size to 20.
- **~Correlation()** frees the allocated arrays.


#### Base functions

- **bool add(float x, float y)** adds a pair of **floats** to the internal storage array's.
Returns true if the value is added, returns false when internal array is full.
When running correlation is set, **add()** will replace the oldest element and return true.
Warning: **add()** does not check if the floats are NAN or INFINITE.
- **uint8_t count()** returns the amount of items in the internal arrays.
This number is always between 0 ..**size()**
- **uint8_t size()** returns the size of the internal arrays.
- **void clear()** resets the data structures to the start condition (zero elements added).
- **bool calculate()** does the math to calculate the correlation parameters A, B and R.
This function will be called automatically when needed.
You can call it on a more convenient time.
Returns false if nothing to calculate **count == 0**
- **void setR2Calculation(bool)** enables / disables the calculation of Rsquared.
- **bool getR2Calculation()** returns the flag set.
- **void setE2Calculation(bool)** enables / disables the calculation of Esquared.
- **bool getE2Calculation()** returns the flag set.


After the calculation the following functions can be called to return the core values.
- **float getA()** returns the A parameter of formula **Y = A + B \* X**
- **float getB()** returns the B parameter of formula **Y = A + B \* X**
- **float getR()** returns the correlation coefficient R which is always between -1 .. 1
The closer to 0 the less correlation there is between X and Y.
Correlation can be positive or negative.
Most often the Rsquared **R x R** is used.
- **float getRsquare()** returns **R x R** which is always between 0.. 1.
- **float getEsquare()** returns the error squared to get an indication of the
quality of the correlation.
- **float getAverageX()** returns the average of all elements in the X dataset.
- **float getAverageY()** returns the average of all elements in the Y dataset.
- **float getEstimateX(float y)** use to calculate the estimated X for a given Y.
- **float getEstimateY(float x)** use to calculate the estimated Y for a given X.


#### Correlation Coefficient R

Indicative description of the correlation value.

|  R             |  correlation  |
|:--------------:|:--------------|
|  +1.0          |  Perfect      |
|  +0.8 to +1.0  |  Very strong  |
|  +0.6 to +0.8  |  Strong       |
|  +0.4 to +0.6  |  Moderate     |
|  +0.2 to +0.4  |  Weak         |
|   0.0 to +0.2  |  Very weak    |
|   0.0 to -0.2  |  Very weak    |
|  -0.2 to -0.4  |  Weak         |
|  -0.4 to -0.6  |  Moderate     |
|  -0.6 to -0.8  |  Strong       |
|  -0.8 to -1.0  |  Very strong  |
|  -1.0          |  Perfect      |


#### Running correlation

- **void setRunningCorrelation(bool rc)** sets the internal variable runningMode
which allows **add()** to overwrite old elements in the internal arrays.
- **bool getRunningCorrelation()** returns the runningMode flag.

The running correlation will be calculated over the last **count** elements.
If the array is full, count will be size.
This running correlation allows for more adaptive formula finding e.g. find the
relation between temperature and humidity per hour, and how it changes over time.


#### Statistical

These functions give an indication of the "trusted interval" for estimations.
The idea is that for **getEstimateX()** the further outside the range defined
by **getMinX()** and **getMaxX()**, the less the result can be trusted.
It also depends on **R** of course. Idem for **getEstimateY()**

- **float getMinX()** idem
- **float getMaxX()** idem
- **float getMinY()** idem
- **float getMaxY()** idem


#### Debugging / educational

Normally not used. For all these functions index should be < count!

- **bool setXY(uint8_t index, float x, float y)** overwrites a pair of values.
Returns true if succeeded.
- **bool setX(uint8_t index, float x)** overwrites single X.
- **bool setY(uint8_t index, float y)** overwrites single Y.
- **float getX(uint8_t index)** returns single value.
- **float getY(uint8_t index)** returns single value.
- **float getSumXY()** returns sum(Xi \* Yi).
- **float getSumX2()** returns sum(Xi \* Xi).
- **float getSumY2()** returns sum(Yi \* Yi).


#### Obsolete since 0.3.0

To improve readability the following functions are replaced.

- **float getAvgX()**    ==> **getAverageX()**
- **float getAvgY()**    ==> **getAverageY()**
- **float getSumXiYi()** ==> **getSumXY()**
- **float getSumXi2()**  ==> **getSumX2()**
- **float getSumYi2()**  ==> **getSumY2()**


## Future

#### Must

- improve documentation

#### Should

- examples
  - real world if possible.

#### Could

- Template version?
The constructor should get a TYPE parameter, as this
allows smaller data types to be analysed taking less memory.
- move code from .h to .cpp

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

