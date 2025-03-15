
[![Arduino CI](https://github.com/RobTillaart/DistanceTable/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DistanceTable/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DistanceTable/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DistanceTable/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DistanceTable/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DistanceTable.svg)](https://github.com/RobTillaart/DistanceTable/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DistanceTable/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DistanceTable.svg?maxAge=3600)](https://github.com/RobTillaart/DistanceTable/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DistanceTable.svg)](https://registry.platformio.org/libraries/robtillaart/DistanceTable)


# DistanceTable

Arduino library to store a symmetrical distance table in less memory.


## Description

The DistanceTable library is a class that stores a **symmetrical** distance table
which is typically N x N elements in less memory space. 
The class uses (N x (N-1))/2 ("in a triangle") as an Euclidean distance table is 
**symmetrical** around its main diagonal. 
This means distance(x, y) == distance(y, x)
Furthermore as the main diagonal are all zero's it does not need to be stored either.

An ATMEL328 (Arduino UNO) with 2KB of RAM can store a 30 x 30 matrix (= 900 floats) in 1740 bytes, 
where it would normally take 900 x 4 = 3600 bytes. 
Within the 2K RAM of an Arduino one could only store a 21 x 21 matrix (1764 bytes).
The class therefore saves around 50% of RAM. 
The price is performance as it takes more time to access the elements.

The distance table can set an invert flag which causes **get(x, y) == -get(y, x)**,
so values are symmetrical in "absolute size" but inverted in sign. 
This can be used e.g. when storing height differences, A is 100 higher than B,
and B is -100 higher than A.


### Difference table

The distance table can also be used to store any difference between x, y pairs.
E.g difference in weight, voltage, temperature or air pressure or any unit 
as long as the values are symmetrical (optionally inverted).


### Related

- https://github.com/RobTillaart/SparseArray
- https://github.com/RobTillaart/SparseMatrix
- https://github.com/RobTillaart/printHelpers  to print large float values.
- https://www.codeproject.com/Tips/5368686/From-Linear-to-Upper-Triangular-Matrix-Indices


## Interface

```cpp
#include "DistanceTable.h"
```

### Constructor set get

- **DistanceTable(uint8_t size, float value = 0.0)** Constructor, allocates memory and 
sets the initial value to all the elements. 
If memory cannot be allocated, the size will be set to 0. 
This can be checked with **uint8_t dimension()**.
A size of N allows indices x,y from 0..N-1.
- **~DistanceTable()** Destructor, frees allocated memory.
- **void clear()** sets all elements to 0.0.
- **void setAll(float value)** sets all elements to value.
- **bool set(uint8_t x, uint8_t y, float value )** sets a value for (x, y) and automatically for (y, x).
Checks dimensions of x and y and if ```x == y``` the value should be zero.
Returns true on success.
- **float get(uint8_t x, uint8_t y)** gets a value from (x, y). If ```x == y``` it will return 0.


### Statistics

- **float minimum(uint8_t &x, uint8_t &y)** Returns the minimum and first occurrence in x and y. 
It skips all x == y pairs as these are 0.
- **float maximum(uint8_t &x, uint8_t &y)** Returns the maximum and first occurrence in x and y. 
It skips all x == y pairs as these are 0.
- **float sum()** Returns the sum of the stored distances times 2 (== all distances)
It ignores the invert flag, as invert would make the sum 0 (zero).
- **float average()** Returns the average distance (== sum() / elements() ).
It ignores the invert flag, as invert would make the average 0.
It skips all x == y pairs as these are 0.

Note: If you want the average of the whole table (including zeros) you need to use the formula
```avg = dt.sum() / (dt.dimension() * dt.dimension());```


### Column functions

If skipSelf is set to true in the functions, the function skips (x,x) which is by definition zero.

- **float sumOfColumn(uint8_t x)** returns the sum of a column (or row as symmetrical).
- **float averageOfColumn(uint8_t x, bool skipSelf = false)** returns the average of a column.
- **float minimumOfColumn(uint8_t x, bool skipSelf = false)** returns minimum of a column.
Use skipSelf to ignore (x,x) as this is 0.
- **float maximumOfColumn(uint8_t x, bool skipSelf = false)** returns maximum of a column.


### GeoMetric Median

**EXPERIMENTAL**

from Wikipedia: Geometric median

_In geometry, the Geometric Median (GM) of a discrete point set in a Euclidean space 
is the point minimizing the sum of distances to the sample points._

The function **minimumColumn()** is an approximation of GM as it assumes the GM must be
in the set of points.
The other functions were added to make the set of column based functions complete.

- **float geometricMedian(uint8_t &x);** find the (first) median point, 
returns the sum of all distances in column(x).
- **float minColumn(uint8_t &x)** find the (first) median point, 
returns the sum of all distances in column(x).
Same as **geometricMedian()**.
- **float maxColumn(uint8_t &x)** find the (first) point that maximizes 
the sum of distances to the other points.
returns the sum of all distances in column(x).


### Count

- **uint16_t count(float value, float epsilon = 0)** counts the number of occurrences of value. 
As we are comparing floats the epsilon can set a margin for 'almost equal'. Default this is 0.
- **uint16_t countAbove(float value)** counts the number of occurrences larger than value.
- **uint16_t countBelow(float value)** counts the number of occurrences smaller than value.

Note 1: these 3 numbers do not always add up exactly as **count()** uses an epsilon where the
other two do not.  
Note 2: the functions do not count the ```x == y``` diagonal.
So if you want to count the values == 0.0 you should add **dimension()** as the diagonal == zeros.  
Note 3: to count all negative numbers, use **countBelow(0.0)**,  
Note 4: to count all non-negative numbers, use **count(0.0) + countAbove(0.0)**, Think greater or equal.  

Behaviour might change in the future.


### Invert (experimental)

- **void setInvert(bool invert = false)** Set the invert flag. 
- **bool getInvert()** returns the current value of the invert flag.

Normally the table is value symmetrical around the y == x diagonal.
With the invert flag, all values are inverted ==> **get(x, y) == -get(y, x)**.
This allows other uses for the table for only a few bytes of RAM.
The table becomes a **magnitude symmetrical distance table**.

The performance of the distance table is affected by the invert flag as most
functions need to test it. 
In practice this means slower, especially when the flag is set to true.

Some application thoughts:
- difference in height between points on a route or map.
- energy levels e.g. transitions of electrons, other physics phenomena.
- transactions between players of a game, + for one is - for the other.
- hold a 2D colour space

Note: this functionality is not tested extensively.


### Debug

- **void dump(Print \* stream = &Serial)** dumps complete distance table, default to Serial. 
Note in previous releases it dumped only a "triangle".
- **uint8_t dimension()** dimension of the table == parameter in constructor.
- **uint16_t elements()** amount of elements allocated.
- **uint16_t memoryUsed()** amount of memory used. 
Typical ```elements() x sizeof(float)```.


## Operational

See examples.


## Future

#### Must

- improve documentation


#### Should

- improve unit tests
- rethink class hierarchy (see ideas below).
  - base class
  - derived "non zero diagonal"
- investigate **normalize()** which reduces all values to range [-1..1],
  by dividing by the maximum absolute value.
- investigate **float absMax(&x, &y)** and **float absMin(&x, &y)** 
  to find maximum absolute value. e.g. "absMax(100, -101) == 101."

#### Could

- add examples
  - Note: table can be used for other symmetrical 2D tables. 
  - And therefore include negative values
- investigate behaviour of **count()** functions a bit more.
  - include diagonal?
- could the "non-inverted" distance table be a derived or base class?
  - more performant
- diagonal not zero derived class, 
  - uses N more bytes but allows also extra functionality while staying symmetrical.
- what if dimension(x) = 2x dimension(y) - non square tables.
  - is there a spectrum of sparsity of a matrix?
- int64_t int32_t int16_t int8_t + unsigned variants? (8 variations? invert flag)
  - Template class?  (release 0.4.0 ?)


#### won't 

- **clear()** could set all to NAN? is that better as it indicates unknown?  
  - setAll() let the user decide.
- Hamilton paths? 
- math
  - add / subtract an offset? 
  - multiply a factor (e.g. go from km to miles)?
  - perform a function on all values e.g. log.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


