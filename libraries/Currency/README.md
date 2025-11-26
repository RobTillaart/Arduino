
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

Choosing int32_t as 'base' also means that there is a limit in terms
of minimum and maximum values. When large amounts are needed one can
use the currency64() or one of its derived formatters as this is based
upon int64_t numbers.

The 0.2.0 version added wrapper functions in the form of a TLA (Three Letter Acronym).
The TLA's are international used acronyms for currency e.g. CNY(value) or GBP(value).

There is a relation with the printHelpers class - https://github.com/RobTillaart/printHelpers
When this currency library has matured it might be merged with printHelpers.

As always feedback (or ideas for extensions) are welcome.


### Breaking change 0.2.0 float/double

The library 0.1.x had experimental wrappers for float/double values.
Testing showed the limits of **float** => seven significant digits explicitly.
As that caused the converted string to be incorrect (thus useless) this part
of the API is deprecated.


### Symbols

Not all symbol codes work on all platforms, so you need to test for your platform.

|  name              |  sign  |  code        |  Notes  |
|:-------------------|:------:|:-------------|:--------|
|  Euro              |   €    |  Alt + 0128  |
|  Pound             |   £    |  Alt + 0163  |
|  Dollar            |   $    |  Alt + 36    |
|  Yen               |   ¥    |  Alt + 0165  |
|  Cent              |   ¢    |  Alt + 0162  |
|  Generic Currency  |   ¤    |  Alt + 0164  |
|  Peseta            |   ₧    |  Alt + 158   |
|  Frank / Florin    |   ƒ    |  Alt + 159   |

More see e.g. https://www.webnots.com/alt-code-shortcuts-for-currency-symbols/


### Related

- https://github.com/RobTillaart/printHelpers
- https://www.easymarkets.com/eu/learn-centre/discover-trading/currency-acronyms-and-abbreviations/


## Interface

```cpp
#include "currency.h"
```

The following functions are implemented:

### Core functions

- **char \* currency(int32_t value, uint8_t decimals, char decimalSeparator, char thousandSeparator, char symbol)**
- **char \* currency64(int64_t value, uint8_t decimals, char decimalSeparator, char thousandSeparator, char symbol)**


### int32_t Wrapper functions

- **char \* bitcoin(int32_t value)**
- **char \* dollar(int32_t value)**
- **char \* euro(int32_t value)**
- **char \* pound(int32_t value)**
- **char \* roubles(int32_t value)**
- **char \* yen(int32_t value)**
- **char \* yuan(int32_t value)**


### int64_t Wrapper functions

- **char \* bitcoin64(int64_t value)**
- **char \* dollar64(int64_t value)**
- **char \* euro64(int64_t value)**
- **char \* pound64(int64_t value)**
- **char \* roubles64(int64_t value)**
- **char \* yen64(int64_t value)**
- **char \* yuan64(int64_t value)**


### int32_t TLA Wrapper functions

- **char \* BTC(int32_t value)**
- **char \* USD(int32_t value)**
- **char \* EUR(int32_t value)**
- **char \* GBP(int32_t value)**
- **char \* RUB(int32_t value)**
- **char \* JPY(int32_t value)**
- **char \* CNY(int32_t value)**


### int64_t TLA Wrapper functions

- **char \* BTC64(int32_t value)**
- **char \* USD64(int32_t value)**
- **char \* EUR64(int32_t value)**
- **char \* GBP64(int32_t value)**
- **char \* RUB64(int32_t value)**
- **char \* JPY64(int32_t value)**
- **char \* CNY64(int32_t value)**


### Deprecated float/double Wrapper functions

Deprecated, has serious limitations, therefore commented in the library.

All assumes 2 decimals except bitcoin which has 6.
The accuracy of a float is just 7 digits.
On some platforms (e.g. UNO R3) float == double so one gets errors.

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

Performance is hard to optimize. 
Most time is spend in splitting individual digits (div / mod 10).
The **divmod10()** function from my fast_math library might be an option.


## Future

#### Must

- update documentation.

#### Should

- investigate a better double/float API
- investigate impact **divmod10()** for int32 and int64.

#### Could

- add more TLA wrapper functions
- consider .h library only as codebase is rather small?

#### Won't

- currency conversion
  - ratios change daily (or faster)
  - intern in pecunia

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

