
[![Arduino CI](https://github.com/RobTillaart/weight/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/weight/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/weight.svg?maxAge=3600)](https://github.com/RobTillaart/weight/releases)


# Weight

Library of weight conversion functions

## Description

Weight.h is a library containing weight conversion functions.

Open for additions, including obscure weight metrics or 
weight related math functions and constants.


## Interface

Overview of conversions:

```
          stone - lbs - ounce
            |      |      |
           kilo   kilo - gram


           kilo - (stone, lbs, ounce)
```

Functions are straightforward.

- **float lbs2kilo(float lbs)**
- **float kilo2lbs(float kilos)**
- **float ounce2gram(float ounce)**
- **float gram2ounce(float gram)**
- **float gram2kilo(float gram)**
- **float kilo2gram( float kilo)**
- **float lbs2ounce(float lbs)**
- **float ounce2lbs(float ounce)**
- **float stone2lbs(float stone)**
- **float lbs2stone(float lbs)**
- **float stone2kilo(float stone)**
- **float kilo2stone(float kilo)**
- **float US2metric(float stone, float lbs, float ounce)**
- **float metric2US(float kilo, float &stone, float &lbs, float &ounce)**


## ideas for future (TBD)
- mass of all elements - 
  - an array of floats 
  - a compressed format with access function (1 byte/ element)
  - constants e.g. MASS_OXYGEN
- molarity functions
- mass of common substances.
- large masses - sun planets ?
- gravity constants of planets REL or ABS eg REL_GRAVITY_EARTH 1.0
- teaspoon
  - although that is a volume unit.
  - volume conversion too?
- create datatypes of stone lbs kilo etc.?


## Operation

See examples
