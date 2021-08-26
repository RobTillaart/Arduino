
[![Arduino CI](https://github.com/RobTillaart/Correlation/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Correlation/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Correlation/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Correlation/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Correlation/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Correlation/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Correlation.svg?maxAge=3600)](https://github.com/RobTillaart/Correlation/releases)


# Correlation

Arduino Library to determine linear correlation between X and Y datasets.


## Description

This library calculates the coefficients of the linear correlation 
between two (relative small) datasets. The size of these datasets is 
20 by default. The size can be set in the constructor. 

The formula of the correlation is expressed as **Y = A + B \* X**,

Please note that the correlation uses about ~50 bytes per instance,
and 2 floats == 8 bytes per pair of elements.
So ~120 elements will use up 50% of the RAM of an UNO.

Use with care.


## Interface


### Constructor

- **Correlation(uint8_t size = 20)** allocates the array needed and resets internal admin.
- **~Correlation()** frees the allocated arrays.


### Base functions

- **bool add(float x, float y)** adds a pair of **floats** to the internal storage. 
Returns true if the value is added, returns false when internal array is full.
When running correlation is set, it will replace the oldest element and return true.
- **uint8_t count()** returns the amount of items in the internal arrays.
- **uint8_t size()** returns the size of the internal arrays.
- **void clear()** resets the datastructure to start condition (zero elements added)
- **bool calculate()** does the math to calculate the correlation parameters A, B and R. 
This function will be called automatically when needed.
You can call it on a more convenient time. 
Returns false if nothing to calculate **count == 0**
- **float getA()** returns the A parameter of formula **Y = A + B \* X**
- **float getB()** returns the B parameter of formula **Y = A + B \* X**
- **float getR()** returns the correlation coefficient R. 
The closer to 0 the less correlation there is between X and Y. 
Correlation can be positive or negative. 
Most often the R squared **sqr(R)** is used.
- **float getRsquare()** returns the **sqr(R)** which is always between 0.. 1.
- **float getEsquare()** returns the error squared to get an indication of the
quality of the relation.
- **float getAvgX()** returns the average of all elements in the X dataset.
- **float getAvgY()** returns the average of all elements in the Y dataset.
- **float getEstimateX(float y)** use to calculate the estimated X for a given Y.
- **float getEstimateY(float x)** use to calculate the estimated Y for a given X.


### Running correlation

- **void setRunningCorrelation(bool rc)** sets the internal variable 
runningMode which allows **add()** to overwrite old elements in the
internal arrays. 
- **bool getRunningCorrelation()** returns the runningMOde flag.

The running correlation will be calculated over the last **count** elements. 
This allows for more adaptive formula finding e.g. find the relation between
temperature and humidity per hour.


### Statistical

These functions give an indication of the "trusted interval" for estimations.
The idea is that for **getEstimateX()** the further outside the range defined
by **getMinX()** and **getMaxX()**, the less the result can be trusted.
It also depends on **R** of course. Idem for **getEstimateY()**

- **float getMinX()** idem
- **float getMaxX()** idem
- **float getMinY()** idem
- **float getMaxY()** idem


### Debugging / educational

Normally not used.

- **bool setXY(uint8_t idx, float x, float y)** overwrites a pair of values.
Returns true if succeeded, idx should be < count!
- **bool setX(uint8_t idx, float x)** overwrites single X.
- **bool setY(uint8_t idx, float y)** overwrites single Y.
- **float getX(uint8_t idx)** returns single value.
- **float getY(uint8_t idx)** returns single value.
- **float getSumXiYi()** returns sum(Xi \* Yi).
- **float getSumXi2()** retuns sum(Xi \* Xi).
- **float getSumYi2()** retuns sum(Yi \* Yi).


## Future

- Template version
The constructor should get a TYPE parameter, as this
allows smaller datatypes to be analyzed taking less memory.


## Operation 

See example
