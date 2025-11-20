
[![Arduino CI](https://github.com/RobTillaart/SparseMatrix/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SparseMatrix/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SparseMatrix/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SparseMatrix/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SparseMatrix/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SparseMatrix.svg)](https://github.com/RobTillaart/SparseMatrix/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SparseMatrix/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SparseMatrix.svg?maxAge=3600)](https://github.com/RobTillaart/SparseMatrix/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SparseMatrix.svg)](https://registry.platformio.org/libraries/robtillaart/SparseMatrix)


# SparseMatrix

Arduino library for sparse matrices.


## Description

**Experimental**

SparseMatrix is an experimental library to implement
two dimensional sparse matrices of floats on an Arduino.
A sparse matrix is a matrix with mostly zeros and a low percentage non-zero values.
The purpose of this library is efficient storage in memory.

The maximum matrix that can be represented is 255 x 255 in size 
with a theoretical maximum of 65535 non-zero elements.
In practice the library limits this to 1000 non-zero elements.
Note: The 2K memory of an UNO R3 would be filled with about 300 elements.

Note: the library does not do matrix / vector math operations.

Note: the library does not hold the dimensions of the sparse matrix
and cannot check these.


### Related

- https://github.com/RobTillaart/SparseArray
- https://github.com/RobTillaart/distanceTable
- https://github.com/RobTillaart/SET


### Implementation

The implementation is based on 3 arrays holding ``` x, y, value```
where value is float, and x and y are uint8_t.
That are 6 bytes per element.
The number of non-zero elements that the sparse matrix object can hold are
given as parameter to the constructor.
If the space cannot be allocated the size is set to zero.

In the future other data types should be possible.


### Performance

The elements are not kept sorted or indexed so optimizations might be
possible but are not investigated. 
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
- **float sum()** sum of all elements ( not zero ) in the matrix.
The sum itself can be zero!
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

### Bounding Box

- **bool boundingBox(uint8_t &minX, uint8_t &maxX, uint8_t &minY, uint8_t &maxY)**
Sets the bounding box in which all values != 0 are located.
This can be useful for printing or processing the non zero elements.
Returns false if there are no non-zero elements.
- **bool boundingX(uint8_t &minX, uint8_t &maxX)** idem, X only.
- **bool boundingY(uint8_t &minY, uint8_t &maxY)** idem, Y only.


### Traverse

(experimental 0.2.0, limited tested).

To walk through the non-zero elements array in internal storage order!
Functions returns false if there is no element.
Note the storage order changes if elements are set to zero as this 
removes the element from internal (non zero) storage.

- **bool first(uint8_t &x, uint8_t &y, float &value)**
- **bool next(uint8_t &x, uint8_t &y, float &value)**
- **bool prev(uint8_t &x, uint8_t &y, float &value)**
- **bool last(uint8_t &x, uint8_t &y, float &value)**

See also sparse_matrix_traverse.ino example how to use the functions.

These functions can be used to copy the sparse matrix to a persistent 
storage (with minimal storage requirements).


### Low level API

(experimental 0.2.0, limited tested).

For fast access to the internal array one can use the following functions.
These functions can be used to implement math operations on the non-zero values
with better performance than the get(x,y) and set(x,y) functions.

Note that these functions assume that the internal storage is not altered 
by an add() or set() command.

Note one cannot create new elements with these functions. use **set(x,y,value)**.

- **int32_t findPosition(uint8_t x, uint8_t y)** find it an (x,y) position) is 
in the internal (non zero) storage.
Returns -1 if **NOT** in the internal storage.
- **float getValue(uint16_t position)** Get the value from the given position. 
User is responsible that position is valid, use findPosition(x,y) if needed.
Returns NAN if position is out of range.
- **bool setValue(uint16_t position, float value)** Writes a value to position.
User is responsible that position is valid, use findPosition(x,y) if needed.
Warning, if the new value is zero, the element will **NOT** be removed from the internal storage.
Returns false if position is out of range.
- **uint16_t compact()** compact the internal storage by removing elements that are zero. Note this can make previous positions invalid!.
Returns the "updated count" of the internal storage.


Typical use case, multiply all non-zero elements with a factor

```
for (int position = 0; position < sm.count(); position++)
{
  value = sm.getValue(position);
  value = value * 1.21;
  sm.setValue(position, value);
}
```


## Future

#### Must

- update documentation

#### Should

- test more (boards etc.)
- support other data types
  - Template class?
  - 1, 2, 3 (RGB), 4 byte integer or 8 byte doubles
  - struct, complex number, etc.
  - effect on math ?
- add LOW level API example


#### Could

- performance (low level API - reduces search time)
  - make findPosition(x,y) public
  - getValue(position);
  - setValue(position, value);
- add constructor with X and Y sizes to allow boundary checking?
  - **SparseMatrix(uint16_t size, uint8_t Xsize, uint8_t Ysize)**
  - would be a breaking change.
  - derived class?
- investigate performance optimizations
  - sort, linked list, tree, hashing?
  - all take extra overhead => KISS 
- class tree - Sparse1D <- Sparse2D <- Sparse3D ...
  - ultimately all can be mapped unto a 1D sparse array.

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
- dump should be in the class?
  - or as static function...
  - stream as parameter **dump(Stream str, ...)**
  - user has to determine lay out.

#### Functions 

=> can be implemented by user (get -> operator -> set)

- extend the add() math series.
  - sub(uint8_t x, uint8_t y, float value);  //  add(x, y, -value)
  - mul(uint8_t x, uint8_t y, float value);
  - div(uint8_t x, uint8_t y, float value);  //  == 0 test
  - sqrt(uint8_t x, uint8_t y, float value);
  - pow(uint8_t x, uint8_t y, float value);
  - exp(uint8_t x, uint8_t y, float value);
  - log(uint8_t x, uint8_t y, float value);
  - ln(uint8_t x, uint8_t y, float value);
- do we need 'vector' operations?
  - add(value) which adds to all elements (add() would explode the sparseness).
  - mul(value) could work,
  - reciprokeAll()  X => 1/X for all elements.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

