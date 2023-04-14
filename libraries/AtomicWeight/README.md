
[![Arduino CI](https://github.com/RobTillaart/AtomicWeight/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AtomicWeight/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AtomicWeight.svg?maxAge=3600)](https://github.com/RobTillaart/AtomicWeight/releases)


# AtomicWeight

Arduino library for atomic weights, and related functions.


## Description

This library is mainly written to be used for educational purposes.
Learning the **periodic table of elements**, the abbreviations and weights.
It also provides the number of electrons, neutrons and protons per element.

Furthermore the library has a **weight()** function, which returns the weight
of either an element or of a formula (e.g. a molecule). 
The weight function can also be used to get the weight of a particular element
within a formula, e.g. the total weight of all Oxygen atoms in a **H2SO4** molecule.
This latter function allows the library to calculate the **massPercentage()** too.

The library has a **count()** function, to count the atoms in a given formula.
Derived is the **atomPercentage()** function which returns the percentage of atoms 
that is of a certain element. Oxygen in H2S04 is 4 in 7 which is about 57%.

Since 0.1.5 the library supports conversion from moles to grams and back.
This allows one to easily get the amount of grams of some formula one has to weigh 
to get a needed amount of moles.
With these functions, in combination with a load cell, one could create a "molar-scale".
Another application for the conversion functions is create lookup-tables, see example.

Note: the library is experimental. More testing is needed. Feedback welcome.


#### Internal

The PTOE class uses a table that has "compressed" weight to save RAM.
- it stores weights as **uint16_t**, 0..65535 instead of floats.
- weight factor = 222.909  = 65535.0 / weight heaviest element(118)
- relative error per element is less than 0.15%
- the table (and thus the class) does not handle isotopes of elements.


#### Related

List of formulae to play with.
- https://en.wikipedia.org/wiki/Glossary_of_chemical_formulae

Libraries useful to build the "molar-scale"
- https://github.com/RobTillaart/HX711
- https://github.com/RobTillaart/weight


## Interface

```cpp
#include "AtomicWeight.h"
```

The parameter **element** in the following functions is 0..118.  
(element 0 being 'n' == a single neutron).

- **PTOE(uint8_t size = 118)** Constructor (Periodic Table Of Elements).
Default it holds all 118 elements. 
The parameter size is used in the **find()** and guards some parameters.
- **uint8_t electrons(uint8_t element)** returns the number of electrons of the element.
- **uint8_t neutrons(uint8_t element)** returns the number of neutrons of the element.
- **uint8_t protons(uint8_t element)** returns the number of protons of the element.
- **float weight(uint8_t element)** returns the weight of the element.
The error is less than 0.15%, as the internal table uses "compression" to save RAM.
- **float weight(char \* formula, char \* abbreviation == NULL)** see below.
  - if (abbreviation == NULL) returns the weight of the whole formula.
  - If (abbreviation != NULL) returns the total weight of one element in a formula.
  - Returns 0 if it cannot parse the given formula.
- **float massPercentage(char \* formula, char \* abbreviation)**
Returns mass percentage of a given element in a formula.
- **uint8_t find(char \* abbreviation)** returns the element number.
This function is relative expensive as it searches linear through the internal array of elements.
Note: the find function is case sensitive.
- **char \* name(uint8_t element)** returns the abbreviation of element.
If the element is out of range **NULL** will be returned.


#### SplitElements 

(0.1.4 experimental)
- **uint8_t splitElements(const char \* formula)** split a formula in an internal list of elements.
Returns the number of different elements found.
Maximum number of elements is hardcoded to 20, which is often enough.
- **uint8_t element(uint8_t el)** access the internal list of elements by index el.
Note: el should be between 0 and the maximum number returned by **splitElements()**.
See example.


#### AtomPercentage

(0.1.4 experimental)
- **uint32_t count(const char \* formula, const char \* abbreviation = NULL)**
  - If (abbreviation != NULL) returns the total atoms of one element in a formula.
  - if (abbreviation == NULL) returns the total atoms of the whole formula.
  - Returns 0 if it cannot parse the formula given.
- **float atomPercentage(const char \* formula, const char \* abbreviation)**
Returns atom percentage of the selected element in a formula.


#### Conversion grams moles

- **float moles2grams(const char \* formula, float moles = 1.0)**
Returns the amount of grams needed for a given amount of moles.
The default moles == 1, returns the basic conversion factor.
- **float grams2moles(const char \* formula, float grams = 1.0)**
Returns the amount of moles for a given amount of grams.
The default moles == 1, returns the basic conversion factor.

These functions can be used, e.g. if one wants to solve 2 moles of KOH
into 10 litres of water to get a defined pH, now much grams I need to weigh?


#### Weight

The **weight(uint8_t element)** call returns the weight of a single atom (by index).
The **weight(formula)** call is meant to calculate the weight of a molecule defined by the formula.
A molecule is defined as one or more atoms.
The functions returns a float, so to get the integer weight, one should use **round()**.

If the formula can not be parsed, e.g. it contains non existing elements, 
the **weight()** function will return a weight of 0.

The **weight(formula, abbreviation)** function is meant to calculate the total weight 
of one element (by abbreviation) in a molecule. 
E.g one can weigh the H atoms in H2O (2 of 18).


#### Formulas

All element abbreviations are one or two characters long.
The first char must be upper case, the (optional) second must be lower case.
(except for element 0, n == neutronium, which is added as placeholder).
Elements can be followed by a number indicating an amount, no number implies 1.

Formulas do not care about the order of the atoms. 
So "C6H6" is equal to "H6C6" or even "CCCCCCHHHHHH" or "C3H3C3H3" etc.

The formula parsing supports round brackets () to indicate groups in the formula.
The library does **not** support square brackets to indicate a group.

The library does **not** support \*6H20 to indicate hydration.

Valid formula's might look like:
- "B" = single element, Hydrogen, 1 atom.
- "Na" = single element, Sodium, 1 atom..
- "C6" = single element, multiple times, Benzene.
- "H2SO4" compound molecule, no groups (sulphuric acid).
- "C6(COOH)2" repeating group, (artificial example).
- "YBa2Cu3O7" compound molecule, == some superconductor-ish material.
- "Ba((OH)4(COOH)2)c" recursive repeating groups (artificial example).


#### MassPercentage

The **massPercentage(formula, abbreviation)** function can determine the percentage of the weight 
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
- A better weight factor would be 201.3868  (see example)
  - relative error is less than 0.09%  (which is 40% better than 0.15%)
  - for 0.2.0 release.


#### Should

- add examples
- extend formula parser with error codes.
  - which ones?
- look for optimizations
  - 3x almost same parser
  - PROGMEM ?


#### Could

- extend unit tests
- state table
  - liquid, gas, solid, unknown  (2 bits per element) = ~30 bytes
  - room temperature + sea level pressure
- (short) table of English names
  - which ones ?
  - separate include file?
  - rename **name()** to **abbrev()** ?
  - add **longName()**?
- performance **find()**
  - alphabetical array? tree? 
  - ==> more memory
- support \[] square brackets too.
  - (NH4)2\[Pt(SCN)6]
- optimize weigh-factor
  - Arduino sketch


#### Wont (unless)

- case insensitive **find()**
  element 0 is defined as n conflict with N
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
  - will not handle isotopes (too much memory needed)
  - database needed
- Electron bands 
  - K L M etc?
  - valence
- temperatures,
  - melt
  - evaporate
  - 2 bytes per temp 4 x 118 = 476 bytes
  - compression 3 bytes for 2 temps 2x 12 bits = 0..4095 K = 354 bytes

