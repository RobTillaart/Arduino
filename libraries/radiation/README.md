
[![Arduino CI](https://github.com/RobTillaart/radiation/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/radiation/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/radiation/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/radiation/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/radiation/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/radiation.svg)](https://github.com/RobTillaart/radiation/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/radiation/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/radiation.svg?maxAge=3600)](https://github.com/RobTillaart/radiation/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/radiation.svg)](https://registry.platformio.org/libraries/robtillaart/radiation)


# radiation

Arduino library for conversion of radiation units.


## Description

**Experimental**

This library is to convert radiation (absorption) units between Gray and Rad,
and to convert (dose equivalent) units between Sievert and Rem.

The library was primary written for educational purpose and released as it
might be useful.
It fits in the lists of other conversion libraries.

See Wikipedia links for details about radiation.

Feedback as always is welcome.


### Special character

ALT-230 = µ


### Related

- https://www.ncbi.nlm.nih.gov/books/NBK230653/
- https://github.com/RobTillaart/pressure
- https://github.com/RobTillaart/radiation
- https://github.com/RobTillaart/temperature
- https://github.com/RobTillaart/printHelpers - to print scientific format


## Interface

```cpp
#include "radiation.h"
```

### Constructor

- **radiation()**

### Absorbed dose

Setters

- **void setGray(float value)** SI unit Gy
- **void setMilliGray(float value)**
- **void setMicroGray(float value)**
- **void getGray()**
- **void getMilliGray()**
- **void getMicroGray()**

Getters

- **float getRad()**
- **float getMilliRad()**
- **float getMicroRad()**
- **float getRad()**
- **float getMilliRad()**
- **float getMicroRad()**


### Dose Equivalent

Setters

- **void setSievert(float value)** SI unit Sv.
- **void setMilliSievert(float value)**
- **void setMicroSievert(float value)**
- **void setRem(float value)**
- **void setMilliRem(float value)**
- **void setMicroRem(float value)**

Getters

- **float getSievert()**
- **float getMilliSievert()**
- **float getMicroSievert()**
- **float getRem()**
- **float getMilliRem()**
- **float getMicroRem()**


### Disintegrations

Just simple conversions as the factor is BIG (3.7e10).

- **float BecquerelToCurie(float Bq)**
- **float CurieToBecquerel(float Ci)**


## Radiation related units

|  Name        | (SI)unit |  Description   |
|:-------------|:--------:|:---------------|
|  Becquerel   |    Bq    | The SI unit of activity. 1 Bq equals 1 disintegration per second.
|  Curie       |    Ci    | 1 Ci equals 1 Ci = 3.7e10 Bq = 3.7e10 disintegrations per second.
|  Gray        |    Gy    | The SI unit of absorbed dose. 1 Gy equals an absorbed dose of 1 J/kg (100 rad).
|  Rad         |   rad    | The special unit of absorbed dose. 1 rad equals an absorbed dose of 100 ergs per gram or 0.01 J per kg (0.01 Gy).
|  Rem         |   rem    | Roentgen equivalent man. The special unit of any of the quantities expressed as dose equivalent. The dose equivalent equals the product of the absorbed dose in rads and the quality factor (1 rem = 0.01 Sv).
|  Rutherford  |    Rd    | is a non-SI unit of radioactive decay.
|  Sievert     |    Sv    | The SI unit of any of the quantities expressed as dose equivalent. The dose equivalent in sieverts is equal to the product of the absorbed dose in Grays and the quality factor (1 Sv = 100 Rem).
|              |          | 

Backgrounders

- https://en.wikipedia.org/wiki/Gray_(unit)
- https://en.wikipedia.org/wiki/Rad_(radiation_unit)
- https://en.wikipedia.org/wiki/Sievert
- https://en.wikipedia.org/wiki/Roentgen_equivalent_man
- https://en.wikipedia.org/wiki/Becquerel
- https://en.wikipedia.org/wiki/Curie_(unit)
- https://en.wikipedia.org/wiki/Rutherford_(unit)


## Future

#### Must

- improve documentation


#### Should

- investigate (obscure) units to convert.

#### Could

- investigate constants
  - lethal dose, safe dose per day
  - background level
  - space level, normal vs solar storm?
  - Chernobyl, Fukushima historical numbers.
- investigate related formulas etc.
  - weight of a person max dose.
- unit tests


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


