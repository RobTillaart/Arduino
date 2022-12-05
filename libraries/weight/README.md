
[![Arduino CI](https://github.com/RobTillaart/weight/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/weight/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/weight/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/weight/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/weight/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/weight/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/weight.svg?maxAge=3600)](https://github.com/RobTillaart/weight/releases)


# Weight

Library of weight conversion functions.


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


## Operation

See examples

----

# weightConverter class

Since version 0.2.0 a weight convertor class is added to convert to and from
other (less known) weight scales.
The idea is to set a value in one scale and retrieve it in the other.
As the converter holds the last value set, multiple conversions of the same 
weight are easy.

New conversions are possible by providing a setXYZ and getXYZ() function.
These two should convert to and from grams respectively.
Additions are welcome, please open an issue.

Internal representation is the gram as it the standard.

## Interface


#### Constructor

- **weightConverter()**

#### setters

- **void setKilogram(float value = 0)** 
- **void setGram(float value = 0)** 
- **void setLBS(float value = 0)**
- **void setStone(float value = 0)**
- **void setOunce(float value = 0)**
- **void setLongTonUK(float value = 0)**
- **void setShortTonUS(float value = 0)**
- **void setQuarterUK(float value = 0)**
- **void setQuarterUS(float value = 0)**
- **void setSlug(float value = 0)**
- **void setTroyPound(float value = 0)**
- **void setTroyOunce(float value = 0)**
- **void setRobie(float value = 0)**
- **void setDram(float value = 0)**
- **void setDrachme(float value = 0)**
- **void setPoint(float value = 0)**
- **void setGrain(float value = 0)**
- **void setCarat(float value = 0)**


#### getters

- **float getKilogram()**
- **float getGram()**
- **float getLBS()**
- **float getStone()**
- **float getOunce()**
- **float getLongTonUK()**
- **float getShortTonUS()**
- **float getQuarterUK()**
- **float getQuarterUS()**
- **float getSlug()**
- **float getTroyPound()**
- **float getTroyOunce()**
- **float getRobie()**
- **float getDram()**
- **float getDrachme()**
- **float getPoint()**
- **float getGrain()**
- **float getCarat()**


## Future

#### must
- improve documentation
  - where are units used

#### should


#### could
- create data types of stone lbs kilo etc.?


#### won't (unless)
- large masses - sun planets ?   (see relativity library)
- gravity constants of planets REL or ABS eg REL_GRAVITY_EARTH 1.0
- mass of all elements
  - an array of floats
  - a compressed format with access function (1 byte/ element)
  - constants e.g. MASS_OXYGEN
  - separate periodicTable.h file ?
- molarity functions
- mass of common substances.
- teaspoon
  - that is a volume unit.
  - volume conversion too?


