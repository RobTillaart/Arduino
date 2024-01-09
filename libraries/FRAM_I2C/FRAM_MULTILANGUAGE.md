
[![Arduino CI](https://github.com/RobTillaart/FRAM_I2C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FRAM_I2C.svg)](https://github.com/RobTillaart/FRAM_I2C/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FRAM_I2C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FRAM_I2C.svg?maxAge=3600)](https://github.com/RobTillaart/FRAM_I2C/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FRAM_I2C.svg)](https://registry.platformio.org/libraries/robtillaart/FRAM_I2C)


# FRAM_MULTILANGUAGE

Library for FRAM_MULTILANGUAGE (FRAM_ML) to be used with the FRAM_I2C library.


## Description

The **FRAM_MULTILANGUAGE (FRAM_ML)** is an experimental library that uses an FRAM object to 
persistently store text tables. Typical use is to implement multiple translations.
However it can be used to store strings in only a single language too.
The storage of text in FRAM reduces the RAM usage of an Arduino quite a lot.

The FRAM_ML library supports up to 5 languages. This is hard coded in the first version (0.5.1).
An FRAM module of 32KB can easily store many hundreds or even thousands (shorter) strings.
This allows to store e.g. 600 long strings in one language or 300 in two languages
or 120 in five languages. 

The FRAM_ML library can be configured to use only part of an FRAM and multiple FRAM_ML 
objects can use the same FRAM.

The current implementation is very straightforward, which is not memory efficient.
The advantage is it performs pretty well as every string can be found with little math.

As this library is experimental, implementation and API might change in the future.


#### Version

The FRAM_MULTILANGUAGE library follows FRAM_I2C version number.


## Interface

```cpp
#include "FRAM_MULTILANGUAGE.h"
```

#### Constructor

- **FRAM_ML()** Constructor.
- **uint32_t begin(FRAM \*fram, uint32_t memAddr, uint8_t languages, uint8_t strings, uint8_t maxLength)** 
initializes the FRAM and writes the parameters to FRAM for persistency. 
  - fram = pointer to FRAM object.
  - memAddr = start memory address in FRAM.
  - languages = number of language tables ( max 5 hardcoded).
  - strings = number of strings in lookup table.
  - maxLength = length of largest string. (first design is not memory efficient).
  - returns uint32_t == first free (next) FRAM location.
- **uint32_t  begin(FRAM \*fram, uint32_t memAddr)**
initializes the FRAM and reads the parameters (see above) from the FRAM.
  - fram = pointer to FRAM object.
  - memAddr = start memory address.
  - returns uint32_t == first free (next) FRAM location.
- **int getMaxLanguage()** idem.
- **int getMaxStrings()** idem.
- **int getMaxLength()** idem.


### Read write language abbreviation.

The FRAM_ML allows to store the country codes of the languages used in FRAM.
This is not mandatory.
See https://www.nationsonline.org/oneworld/country_code_list.htm

- **int setLanguageName(uint8_t index, const char \* str)**
  - index = 0..n, typical smaller than MaxLanguage.
  - str = country code == max 3 chars e.g. "IRL", "EN", "FR", "P".
  - returns error status.
- **int getLanguageName(uint8_t index, char \* str)** to fetch names.
  - returns error status.


### read write text strings

- **int setLanguage(uint8_t index)** set the current language to use.
This makes access easier as one often stays within one language.
If only one language is used this function is not used. 
  - returns error status.
- **int getLanguage()** returns the current set language.
- **int setText(uint8_t index, const char \* text)** writes text to FRAM 
under the index of the current language.
  - returns error status.
- **int getText(uint8_t index, char \* text)** reads text to FRAM 
under the index of the current language.
  - returns error status.


### Error codes

|  value  |  description                 |  Notes  |
|:-------:|:-----------------------------|:--------|
|     0   |  FRAM_ML_OK                  |
|   -10   |  FRAM_ML_INDEX_OUT_OF_RANGE  |
|   -20   |  FRAM_ML_TEXT_TOO_LONG       |


### Memory layout

Address is relative to base address.

|  ADDRESS  |   DESCRIPTION   |  Notes  |
|:---------:|:---------------:|:-------:|
|    00     |  version = 1    |
|    10     |  languages      |
|    11     |  strings        |
|    12     |  maxLength      |
|    20     |  country codes  |
|    40     |  tables         |


## Future


### Must

- test
- documentation


### Should

- add **setName(const char \* str)** + **getName(char \* str)**
  - length 8, position 2..9
  - to label the text tables.


### Could

- performance sketch.
- memory check in **begin(fram, addr, languages, strings, length)**
- version check in begin().
  - add **getVersion()**
- add CRC32 over tables to test integrity?
  - per table or total?


### Wont (unless)

- checking if translation exist / FRAM filled properly.
  - user responsibility
- set read-only flag in **begin(fram, addr)**?
  - user responsibility.

