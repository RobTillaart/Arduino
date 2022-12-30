
[![Arduino CI](https://github.com/RobTillaart/AtomicWeight/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AtomicWeight/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AtomicWeight.svg?maxAge=3600)](https://github.com/RobTillaart/AtomicWeight/releases)


# AtomicWeight

Arduino library for atomic weights.


## Description

This library is mainly as a base for educational purposes.
Learning the periodic table of elements, the abbreviations and weight.
It also provides the number of electrons, neutrons and protons per element. 

#### internal

Table uses compressed weight to save RAM
- store weight as **uint16_t**, 0..65535 
- weight factor = 222.909  = (65535.0 / heaviest element=118)
- error < 0.5%


## Interface

```cpp
#include "AtomicWeight.h"
```

- **PTOE()** Constructor (Periodic Table Of Elements)
- **uint8_t electrons(uint8_t element)** returns the number of electrons of the element.
- **uint8_t neutrons(uint8_t element)** returns the number of neutrons of the element.
- **uint8_t protons(uint8_t element)** returns the number of protons of the element.
- **float weight(uint8_t element)** returns the weight of the element. (error < 0.5%, table uses "weight compression")
- **uint8_t find(char \* abbreviation)** returns the element number.
- **char \* name(uint8_t element)** returns the abbreviation of element.


#### debug

- **float weightFactor()** returns weightFactor.


## Operation

See examples


## Future

#### must

- improve documentation
- add examples

#### should

- state table
  - liquid, gas, solid, unknown  (2 bits per element) = ~30 bytes
- (short) table of English names
  - which ones ?
- move code to .cpp file
- parameters element should be less than _size

#### could

- extend unit tests
- function weight("H2O") => 18
  - easier to parse with separator:  weight("C6 H6 O6 ")

#### wont (unless)

- more information?
- Electron bands K L M etc?
  - database needed
- temperatures,
  - melt
  - evaporate
  - 2 bytes per temp 4 x 118 = 476 bytes
  - compression 3 bytes for 2 temps 2x 12 bits = 0..4095 K = 354 bytes

  

