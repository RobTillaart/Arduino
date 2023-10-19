
[![Arduino CI](https://github.com/RobTillaart/currency/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/currency/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/currency/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/currency/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/currency/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/currency.svg)](https://github.com/RobTillaart/currency/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/currency/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/currency.svg?maxAge=3600)](https://github.com/RobTillaart/currency/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/currency.svg)](https://registry.platformio.org/libraries/robtillaart/currency)


# Currency

Arduino library to help formatting integers for printing as currency.


## Description

**Experimental**

The currency library contains a number of functions that help to print 
integers as currency.

The currency functions assume you do the currency math in integer units.
For dollars and euro's this would be cents. For numbers with more decimals 
it is a smaller unit. 

Using integers makes addition, subtraction and multiplication of currency exact.

The library has experimental wrappers for float/double values. 
Not tested extensively yet.

Choosing int32_t as 'base' also means that there is a limit in terms 
of minimum and maximum values. When large amounts are needed one can 
use the currency64() or one of its derived formatters as this is based
upon int64_t numbers.

There is a relation with the printHelpers class - https://github.com/RobTillaart/printHelpers
When this currency library has matured it might be merged with printHelpers.


#### Related

- https://github.com/RobTillaart/printHelpers

## Interface

```cpp
#include "currency.h"
```

The following functions are implemented:

### Core function

- **char \* currency(int32_t value, uint8_t decimals, char decimalSeparator, char thousandSeparator, char symbol);** 
- **char \* currency64(int64_t value, uint8_t decimals, char decimalSeparator, char thousandSeparator, char symbol);**


### int32 Wrapper functions

- **char \* bitcoin(int32_t value)**
- **char \* dollar(int32_t value)**
- **char \* euro(int32_t value)**
- **char \* pound(int32_t value)**
- **char \* roubles(int32_t value)**
- **char \* yen(int32_t value)**
- **char \* yuan(int32_t value)**


### int64 Wrapper functions

- **char \* bitcoin64(int64_t value)**
- **char \* dollar64(int64_t value)**
- **char \* euro64(int64_t value)**
- **char \* pound64(int64_t value)**
- **char \* roubles64(int64_t value)**
- **char \* yen64(int64_t value)**
- **char \* yuan64(int64_t value)**


### float Wrapper functions

Experimental - not tested

All assumes 2 decimals except bitcoin which has 6.

- **char \* bitcoinf(double value)**
- **char \* dollarf(double value)**
- **char \* eurof(double value)**
- **char \* poundf(double value)**
- **char \* roublesf(double value)**
- **char \* yenf(double value)**
- **char \* yuanf(double value)**


## Operation

See examples.


## Performance

Performance is hard to optimize. Most time is spend in splitting 
individual digits (div / mod 10).


## Future

#### Must

- update documentation.

#### Should

#### Could

- More wrapper functions?
- test double parameters.
  - should decimals be a parameter too?
- add BTC, USD, EUR, GBP, RUB, JPY, CNY, etc. (3+1 chars)
- https://www.easymarkets.com/eu/learn-centre/discover-trading/currency-acronyms-and-abbreviations/

#### Won't

- currency conversion?
  - intern all in ???


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

