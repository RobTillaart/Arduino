
[![Arduino CI](https://github.com/RobTillaart/XXXXXXXX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/XXXXXXXX/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/XXXXXXXX/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/XXXXXXXX/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/XXXXXXXX/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/XXXXXXXX.svg)](https://github.com/RobTillaart/XXXXXXXX/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/XXXXXXXX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/XXXXXXXX.svg?maxAge=3600)](https://github.com/RobTillaart/XXXXXXXX/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/XXXXXXXX.svg)](https://registry.platformio.org/libraries/robtillaart/XXXXXXXX)


# SparseMatrix

Arduino library for sparse matrices.


## Description

SparseMatrix is an **experimental** library to implement
two dimensional sparse matrices (of floats) on an Arduino.
A sparse matrix is a matrix with mostly zeros and a low percentage non-zero values.
The purpose of this library is efficient storage in memory. 

The maximum matrix that can be represented is 255 x 255 
with a theoretical maximum of 65535 non-zero elements.
In practice the library limits this to 1000 non-zero elements.
Note: 255 elements would still fit in an UNO's 2K memory.

Note: the library does not do matrix math operations.

Note: the library does not hold the dimensions of the matrix
and cannot check these.

#### Related

- https://github.com/RobTillaart/SparseArray
- https://github.com/RobTillaart/distanceTable
 

#### Implementation

The implementation is based on 3 arrays holding ``` x, y, value``` 
where value is float, and x and y are uint8_t. 
That are 6 bytes per element. 
The number of elements that the sparse matrix object can hold are 
given as parameter to the constructor. 
If the space cannot be allocated the size is set to zero.

In the future other data types should be possible.


#### Performance

The elements are not kept sorted or indexed so optimizations might be 
possible but are not investigated yet.
There is however a test sketch to monitor the performance of
the most important functions.

Accessing elements internally is done with a linear search, 
which becomes (much) slower if the number of elements is increasing. 
This means that although in theory there can be 65535 elements, 
in practice a few 100 can already become annoyingly slow.
To keep performance a bit the library has a limit build in.
Check the .h file for **SPARSEMATRIX_MAX_SIZE 1000**


## Interface

```cpp
#include "SparseMatrix.h"
```

### Constructor + meta

- **SparseMatrix(uint16_t size)** constructor. 
Parameter is the maximum number of elements in the sparse matrix.
Note this number is limited to **SPARSEMATRIX_MAX_SIZE 1000**.
If the space requested cannot be allocated size will be set to 0.
- **uint16_t size()** maximum number of elements.
If this is zero, a problem occurred with allocation happened.
- **uint16_t count()** current number of elements in the matrix.
Should be between 0 and size.
- **float sum()** sum of all elements ( > 0 ) in the matrix.
- **void clear()** resets the matrix to all zero's again.


### Access

- **bool set(uint8_t x, uint8_t y, float value)** gives an element in the matrix a value.
If the value is set to zero, it is removed from the internal store.
Returns false if the internal store is full, true otherwise.
- **float get(uint8_t x, uint8_t y)** returns the value in the matrix. 
- **bool add(uint8_t x, uint8_t y, float value)** adds value to an element in the matrix.
If needed a new internal element is created. 
If the sum is zero, the element is removed from the internal store.
Returns false if the internal store is full, true otherwise.
- **void  boundingBox(uint8_t &minX, uint8_t &maxX, uint8_t &minY, uint8_t &maxY)** 
Returns the bounding box in which all values != 0 are located.
This can be useful for printing or processing the non zero elements.


## Future

#### Must

- update documentation

#### Should

- do tests

#### Could

- template version to store other data types 
  - 1, 2, 3 (RGB), 4 byte integer or 8 byte doubles
  - struct, complex number
  - etc
- investigate performance optimizations
  - sort
  - linked list, tree, hashing?
- SparseArray?
  - derived class that only uses X and Value
    - only need an extra get/set/add
  - separate class memory efficient  (base class?)
  - class tree - Sparse1D <- Sparse2D <- Sparse3D ...
- dump should be in the class?
  - or as static function...
  - stream as parameter **dump(Stream str, ...)**


#### Functions

- extend the add() math series.
  - sub(uint8_t x, uint8_t y, float value);
  - mul(uint8_t x, uint8_t y, float value);
  - div(uint8_t x, uint8_t y, float value);
  - sqrt(uint8_t x, uint8_t y, float value);
  - pow(uint8_t x, uint8_t y, float value);
  - exp(uint8_t x, uint8_t y, float value);
  - log(uint8_t x, uint8_t y, float value);
  - ln(uint8_t x, uint8_t y, float value);
  - on request.
- do we need 'vector' operations
  - add(value) which adds to all elements.
- walk through the elements.
  - in storage order.
  - bool first(uint8_t &x, uint8_t &y, float &value);
  - bool next(uint8_t &x, uint8_t &y, float &value);
  - bool prev(uint8_t &x, uint8_t &y, float &value);
  - bool last(uint8_t &x, uint8_t &y, float &value);
  - returns false if there is no element any more
  - if count = 0 or current == -1 or end of list.
  - mutating values can disrupt the iteration..

#### Won't

- should **set()** and **add()** return the number of free places?
  - more informative than just a bool.
  - One looses the info that the operation was successful
- set a zero threshold ?
  - if (abs(x) < TH) element is considered zero => remove
  - not portable to template version  (sum() is not either!)
  - user can do this.
- math
  - determinant?
  - M x M
  - diagonal?
- add examples
  - N queens game.
  - battleship game
  - minesweeper game


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

