
[![Arduino CI](https://github.com/RobTillaart/AtomicWeight/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AtomicWeight/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AtomicWeight.svg?maxAge=3600)](https://github.com/RobTillaart/AtomicWeight/releases)


# AtomicWeight

Arduino library for atomic weights.


## Description

This library is mainly as a base for educational purposes.
Learning the **periodic table of elements**, the abbreviations and weight.
It also provides the number of electrons, neutrons and protons per element.

Furthermore the library has a **weight()** function, that returns the weight
of either an element or by formula. See examples.

Note: library is still experimental. More testing is needed.


#### internal

The PTOE class uses a table that has compressed weight to save RAM
- it stores weights as **uint16_t**, 0..65535 instead of floats.
- weight factor = 222.909  = (65535.0 / heaviest element = 118)
- error < 0.3%
- the table (and thus the class) does not handle isotopes.


## Interface

```cpp
#include "AtomicWeight.h"
```

The parameter **element** in the following functions is 0..118.  
(element 0 being a single neutron).

- **PTOE()** Constructor (Periodic Table Of Elements)
- **uint8_t electrons(uint8_t element)** returns the number of electrons of the element.
- **uint8_t neutrons(uint8_t element)** returns the number of neutrons of the element.
- **uint8_t protons(uint8_t element)** returns the number of protons of the element.
- **float weight(uint8_t element)** returns the weight of the element.
The error < 0.3%, table uses "weight compression".
- **float weight(char \* formula)** returns the weight of a molecule e.g. "H2O".
Returns 0 if it cannot parse the formula given.
Cannot parse complex formulas with brackets () in it. 
- **uint8_t find(char \* abbreviation)** returns the element number.
- **char \* name(uint8_t element)** returns the abbreviation of element.


#### weight

The **weight(int n)** function returns the weight of a single atom.
The **weight(formula)** function is meant to calculate the weight of a molecule.

The latter function does not care about the order of the atoms. 
So "C6H6" is equal to "H6C6" or even "CCCCCCHHHHHH" or "C3H3C3H3" etc.
Elements are defined as 1 or two characters long.
The first must be uppercase, the second must be lowercase.
If no number is provided the count of 1 is assumed.

The functions returns a float, so to get the integer weight, one should use **round()**.

If the formula is not parseable it will return a weight of 0.

(Since 0.1.2)
The weight formula parsing experimentally supports brackets () to indicate groups in the formula.

Valid formula's might look as:
- "B" = single element
- "Na" = single element
- "C6" = single element, multiple times
- "H2SO4" compound molecule, no groups
- "C6(COOH)2" compound molecule, with repeating groups
- "YBa2Cu3O7" some superconductor-ish material


#### debug

- **float weightFactor()** returns weightFactor.


## Operation

See examples


## Future

#### must

- improve documentation

#### should

- add examples
- extend formula parser with error codes.

#### could

- extend unit tests
- state table
  - liquid, gas, solid, unknown  (2 bits per element) = ~30 bytes
- (short) table of English names
  - which ones ?
- function **float massPercentage("H2O", "H")**  ~10%
- function **float atomicPercentage("H2O", "H")**  ~33%
- performance functions
  - especially **find()** ?
- case (in)sensitive **find()**
- is there a faster data structure.

#### wont (unless)

- parameters element should be less than \_size
  - user responsibility
- more information?
  - database needed
- Electron bands K L M etc?
- temperatures,
  - melt
  - evaporate
  - 2 bytes per temp 4 x 118 = 476 bytes
  - compression 3 bytes for 2 temps 2x 12 bits = 0..4095 K = 354 bytes

  

