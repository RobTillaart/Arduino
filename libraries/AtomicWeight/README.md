
[![Arduino CI](https://github.com/RobTillaart/AtomicWeight/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AtomicWeight/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AtomicWeight.svg?maxAge=3600)](https://github.com/RobTillaart/AtomicWeight/releases)


# AtomicWeight

Arduino library for atomic weights.


## Description

This library is mainly to be used as a base for educational purposes.
Learning the **periodic table of elements**, the abbreviations and weight.
It also provides the number of electrons, neutrons and protons per element.

Furthermore the library has a **weight()** function, which returns the weight
of either an element or of a formula (e.g. a molecule). 
The weight function can also be used to get the weight of a particular element
from a formula, e.g. the weight of the Oxygen atoms in the **H2SO4** molecule.

This latter function allows the library to calculate the **massPercentage()** too.

The library also has a **count()** function, to count the atoms in a formula.
Derived is the **atomPercentage()** function to give the percentage of atoms 
that is a certain element.

Note: library is experimental. More testing is needed.


#### Internal

The PTOE class uses a table that has compressed weight to save RAM.
- it stores weights as **uint16_t**, 0..65535 instead of floats.
- weight factor = 222.909  = 65535.0 / weight heaviest element(118)
- error < 0.3%
- the table (and thus the class) does not handle isotopes.


#### Related

Useful list of formulae.

- https://en.wikipedia.org/wiki/Glossary_of_chemical_formulae


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
- **float weight(char \* formula, char \* abbreviation == NULL)** see below.
  - If (el != NULL) returns the total weight of one element in a formula.
  - if (el == NULL) returns the weight of the whole formula.
  - Returns 0 if it cannot parse the formula given.
- **float massPercentage(char \* formula, char \* abbreviation)**
Returns mass percentage of a selected element in a formula.


- **uint8_t find(char \* abbreviation)** returns the element number.
This function is relative expensive as it searches linear through the internal array of elements.
- **char \* name(uint8_t element)** returns the abbreviation of element.


#### SplitElements 

(0.1.4 experimental)
- **uint8_t splitElements(const char \* formula)** split a formula in an internal list of elements.
Returns the number of different elements found.
Max nr of elements is hardcoded to 20.
- **uint8_t element(uint8_t el)** access the internal list of elements by index el.
Note: el should be between 0 and the max nr returned by **splitElements()**.
See example.


#### AtomPercentage

(0.1.4 experimental)
- **uint32_t count(const char \* formula, const char \* el = NULL)**
  - If (el != NULL) returns the total atoms of one element in a formula.
  - if (el == NULL) returns the total atoms of the whole formula.
  - Returns 0 if it cannot parse the formula given.
- **float atomPercentage(const char \* formula, const char \* el)**
Returns atom percentage of the selected element in a formula.


#### Weight

The **weight(uint8_t element)** call returns the weight of a single atom (by index).
The **weight(formula)** call is meant to calculate the weight of a molecule.
A molecule is defined as one or more atoms.

The latter function does not care about the order of the atoms. 
So "C6H6" is equal to "H6C6" or even "CCCCCCHHHHHH" or "C3H3C3H3" etc.
Elements are defined as one or two characters long.
The first char must be upper case, the (optional) second must be lower case.
If no number is provided the count of 1 is assumed.

The functions returns a float, so to get the integer weight, one should use **round()**.

If the formula can not be parsed it will return a weight of 0.

The **weight(formula, element)** function is meant to calculate the total weight of one element
in a molecule. E.g one can weigh the H atoms in H2O (2 of 18).


#### Formulas

The weight formula parsing supports round brackets () to indicate groups in the formula.

Valid formula's might look like:
- "B" = single element
- "Na" = single element
- "C6" = single element, multiple times
- "H2SO4" compound molecule, no groups
- "C6(COOH)2" compound molecule, with a repeating group
- "YBa2Cu3O7" some superconductor-ish material
- "Ba((OH)4(COOH)2)c" recursive repeating groups (artificial example).


#### MassPercentage

The **massPercentage(formula, element)** function can determine the percentage of the weight 
a selected element has in a formula, e.g. the weight of the Oxygen in **H2SO4**.
This is calculated by dividing the weight of the element by the total weight.

If you want to do that for all elements it might be more efficient to calculate the weight 
of the whole formula once.


#### Debug

- **float weightFactor()** returns the weightFactor, that was used to
minimize the memory used for the elements mass lookup table.


## Future

#### Must

- improve documentation
  - reorganize.


#### Should

- add examples
- extend formula parser with error codes.
  - which ones?
- support \[] square brackets too.
  - (NH4)2\[Pt(SCN)6]
- look for optimizations
  - 3x almost same parser 

#### Could

- extend unit tests
- state table
  - liquid, gas, solid, unknown  (2 bits per element) = ~30 bytes
  - room temperature + sea level pressure
- (short) table of English names
  - which ones ?
- case (in)sensitive **find()**
  - always or configurable
  - more expensive search
  - alphabetical array?
  

#### Wont (unless)

- support hydrates ?
  - **Ba(BrO3)2·2H2O**  new separator + starts with number.
  - other liquids than water?
  - https://en.wikipedia.org/wiki/Glossary_of_chemical_formulae
- is there a faster data structure?
  - search by nr is O(1)
  - search by name is O(n)
  - only if more RAM is used.
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

