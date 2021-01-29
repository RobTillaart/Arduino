
[![Arduino CI](https://github.com/RobTillaart/Distancetable/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Distancetable/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Distancetable.svg?maxAge=3600)](https://github.com/RobTillaart/Distancetable/releases)


# Distancetable

Arduino library to store a symmetrical distance table in less memory.


## Description

The DistanceTable library is a class that stores a symmetrical distance table 
which is typically N x N entries in less memory space. 
It uses (N x (N-1))/2 ("in a triangle") as an eucledian distance table is 
symmetrical around its main diagonal. 
Furthermore as the main diagonal are all zero it does not need to be stored either.

An ATMEL328 (Arduino) can store a 30 x 30 matrix = 900 floats in 1740 bytes, 
where it typically would take 900 x 4 = 3600 bytes. 

Within the 2K RAM of an Arduino one could store normally a 21 x 21 matrix (1764 bytes).


## Interface

- **DistanceTable(uint8_t size)** Constructor, allocates memory and clears them.
- **~DistanceTable();** Destructor, frees memory
- **void clear()** sets all entries to 0.0.
- **void setAll(value)** sets all entries to value;
- **void set(uint8_t x, uint8_t y, float value )** sets a value for (x,y) and automatically for (y, x)
- **float get(uint8_t x, uint8_t y)** gets a value from (x,y). If x == y it will return 0.
- **float minimum(uint8_t &x, uint8_t &y)** Returns minimum and first occurence in x and y. It does skip x == y pairs as these are 0.
- **float maximum(uint8_t &x, uint8_t &y)** Returns maximum and first occurence in x and y. It does skip x == y pairs as these are 0.
- **uint16_t count(value, epsilon)** counts the number of occurences of value. As we are comparing floats the epsilon can set a margin for 'almost equal'.



### Debug

- **void dump(Print \* stream = &Serial)** dumps distance table , default to serial.
- **uint8_t dimension()** dimension of the table == parameter in constructor.
- **uint16_t elements()** amount of elements allocated.
- **uint16_t memoryUsed()** amount of memory used.


## Future

- **count()** could get an epsilon to count also nearly hits (default 0.0);
- **clear()** could set all to NAN? is that better as it iindicates unknown?  
  setAll() let the user decide.


Note: table can be used for other symmetrical 2D tables. And therefor include 
negative values.


## Operational

See examples.
