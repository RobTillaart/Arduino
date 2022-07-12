
[![Arduino CI](https://github.com/RobTillaart/SparseMatrix/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SparseMatrix/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SparseMatrix/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SparseMatrix/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SparseMatrix/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SparseMatrix/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SparseMatrix.svg?maxAge=3600)](https://github.com/RobTillaart/SparseMatrix/releases)


# SparseMatrix

Arduino library for sparse matrices.


## Description

SparseMatrix is an **experimental** library to implement sparse matrices on an Arduino.

The maximum matrix that can be represented is 255 x 255 
with a maximum of 255 non-zero elements.
This would just fit in an UNO's 2K memory.

The library does not hold the dimensions of the matrix (at least in 0.1.0)

The purpose of the library is efficient storage in memory. 
It does not do math operations except sum().

Relates to https://github.com/RobTillaart/distanceTable


#### Implementation

The implementation is based on 3 arrays holding ``` x, y, value``` where value is float.
In the future other datatypes should be possible.

The elements are not kept sorted or indexed so optimizations are possible
but not investigated yet.


## Interface

- **SparseMatrix(uint8_t size)** constructor. 
Parameter is the maximum number of elements in the sparse matrix.
- **uint8_t size()** maximum number of elements.
- **uint8_t count()** current number of elements in the matrix.
- **float sum()** sum of all elements ( > 0 ) in the matrix.
- **bool set(uint8_t x, uint8_t y, float value)** gives an element in the matrix a value.
If the value is set to zero, it is removed from the internal store.
Returns false if the internal store is full, true otherwise.
- **float get(uint8_t x, uint8_t y)** returns the value in the matrix. 


## Future

- documentation
- test
- template version to store other data types 
  - 1, 2, 3 (RGB), 4 byte integer or 8 byte doubles
  - struct, complex number
  - etc
- add examples
  - 2D histogram e.g. temperature vs humidity
  - N queens game.
- investigate optimizations.
- should **set()** return the number of free places?
  - no hard code and more informative than just a bool.
- add link in distanceTable repo
- uint16_t size for larger platforms.
  - max matrix still 255 x 255 but more elements <> 0.


#### new functions

- **float add(uint8_t x, uint8_t y, float value)** adds value to the x,y position.
  - add or remove an internal element if needed,
  - functional **set(x,y, get(x,y) + value)**
- **void clear()** sets all elements to zero again. 
  - \_count = 0; should be sufficient.
- walking through the elements?
  - first -> next;  last -> prev.
  

#### won't

- math
  - determinant?
  - M x M
  - diagonal?
- add examples
  - battleship game
  - minesweeper game
  - nice exercise 

