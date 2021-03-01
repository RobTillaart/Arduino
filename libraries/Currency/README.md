
[![Arduino CI](https://github.com/RobTillaart/currency/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/currency/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/currency.svg?maxAge=3600)](https://github.com/RobTillaart/currency/releases)



# Currency

Arduino library to help formatting integers for printing as currency

## Warning: experimental


## Description

The currency library contains a number of functions that help to print 
integers as currency.

The currency functions assume you do the currency math in integer units.
For dollars and euro's this would be cents. For numbers with more decimals 
it is a smaller unit. 

Using integers makes addition, subtraction and multiplication exact. 

Choosing int32_t as 'base' also means that there is a limit in terms 
of minimum and maximum values. When large amounts are needed one can 
use the currency64() or one of its derived formatters as this is based
upon int64_t numbers.

There is a relation with the printhelpers class - https://github.com/RobTillaart/printHelpers
When this library has matured it might be merged with it.


## Interface

The following functions are implemented:


### Core function

- **char \* currency(int32_t value, uint8_t decimals, char decimalseparator, char thousandseparator, char symbol);** 
- **char \* currency64(int64_t value, uint8_t decimals, char decimalseparator, char thousandseparator, char symbol);**


### int32 Wrapper functions

- **char \* bitcoin(int32_t value)**
- **char \* dollar(int32_t value)**
- **char \* euro(int32_t value)**
- **char \* roebel(int32_t value)**
- **char \* yen(int32_t value)**
- **char \* yuan(int32_t value)**


### int64 Wrapper functions

- **char \* bitcoin64(int64_t value)**
- **char \* dollar64(int64_t value)**
- **char \* euro64(int64_t value)**
- **char \* roebel64(int64_t value)**
- **char \* yen64(int64_t value)**
- **char \* yuan64(int64_t value)**


### float Wrapper functions

Even more experimental - not tested

- **char \* bitcoinf(double value)**
- **char \* dollarf(double value)**
- **char \* eurof(double value)**
- **char \* roebelf(double value)**
- **char \* yenf(double value)**
- **char \* yuanf(double value)**


## Future

- More wrapper functions?
- test double parameters.


## Operation

See examples

