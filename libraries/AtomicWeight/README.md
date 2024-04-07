
[![Arduino CI](https://github.com/RobTillaart/AtomicWeight/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AtomicWeight/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AtomicWeight.svg)](https://github.com/RobTillaart/AtomicWeight/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AtomicWeight/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AtomicWeight.svg?maxAge=3600)](https://github.com/RobTillaart/AtomicWeight/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AtomicWeight.svg)](https://registry.platformio.org/libraries/robtillaart/AtomicWeight)


# AtomicWeight

Arduino library for atomic weights, and related functions.


## Description

This library is mainly written to be used for educational purposes.
Of course are other applications possible.
Learning the **periodic table of elements**, the abbreviations and weights.
It provides the number of electrons, neutrons and protons per element.

Furthermore the library has a **weight()** function, which returns the weight
of either an element or of a formula (e.g. a molecule) in **Daltons**.
One **Dalton** = 1/12th of the weight of a Carbon atom.
The SI abbreviation for **Dalton** == **Da**.
One might think of it as (roughly) the number of nucleons (= protons + neutrons).

The **weight()** function can also be used to get the weight of a particular element
within a formula, e.g. the total weight of all Oxygen atoms in a **H2SO4** molecule.
This latter function allows the library to calculate the **massPercentage()** too.

The library has a **count()** function, to count the atoms in a given formula.
Derived is the **atomPercentage()** function which returns the percentage of atoms 
that is of a certain element. Oxygen in **H2S04** is 4 in 7 which is about 57.14%.

The library supports conversion from moles to grams and back.
This allows one to easily get the amount of grams of some formula one has to weigh 
to get a needed amount of moles.
With these functions, in combination with a load cell, one could create a "molar-scale".
Another application for the conversion functions is create lookup-tables, see example.


Note: the library is experimental. More testing is needed. Feedback welcome.


#### Internal

The PTOE class uses a table with "scaled" weights to save RAM.
- it stores weights as **uint16_t**, instead of floats (saves 236 bytes).
- the table (and thus the class) does not handle isotopes of elements.
- the scaling factor is named **ATOMIC_WEIGHT_FACTOR**

**Version 0.2.x**
- ATOMIC_WEIGHT_FACTOR = 1.0 / 201.3868   (found by searching - see example).
- relative error per element is less than 0.09%  (~40% better than previous 0.15%).
- **Breaking:** numbers are **not** compatible with 0.1.x version


**Version 0.1.x (for reference)**
- ATOMIC_WEIGHT_FACTOR = 1.0 / 222.909 == weight heaviest element(118) / 65535.
- relative error per element is less than 0.15%.


#### Related

List of formulae to play with.
- https://en.wikipedia.org/wiki/Glossary_of_chemical_formulae
- https://en.wikipedia.org/wiki/Avogadro_constant

Libraries useful to build the "molar-scale"
- https://github.com/RobTillaart/HX711  (load cell)
- https://github.com/RobTillaart/weight  (conversion)
- https://github.com/RobTillaart/printHelpers  (scientific notation of numbers)


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
The error is less than 0.09%, as the internal table uses "compression" to save RAM.
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

- **uint8_t splitElements(const char \* formula)** split a formula in an internal list of elements.
Returns the number of different elements found.
Maximum number of elements is hardcoded to 20, which is often enough.
- **uint8_t element(uint8_t el)** access the internal list of elements by index el.
Note: el should be between 0 and the maximum number returned by **splitElements()**.
See example.

```cpp
char formula[24] = "YBa2Cu3O7";
nr = splitElements(formula);
for (int i = 0; i < nr; i++)
{
  Serial.print(PTOE.massPercentage(formula, element(i)), 3);
  Serial.print("%\t");
  Serial.print(element(i));
  Seriel.println();
}
```

#### AtomPercentage

- **uint32_t count(const char \* formula, const char \* abbreviation = NULL)**
  - If (abbreviation != NULL) returns the total atoms of one element in a formula.
  - if (abbreviation == NULL) returns the total atoms of the whole formula.
  - Returns 0 if it cannot parse the formula given.
- **float atomPercentage(const char \* formula, const char \* abbreviation)**
Returns atom percentage of the selected element in a formula.


```cpp
ap = PTOE.atomPercentage("H2SO4", "O");
```


#### Conversion grams moles

- **float moles2grams(const char \* formula, float moles = 1.0)**
Returns the amount of grams needed for a given amount of moles.
The default moles == 1, returns the basic conversion factor.
- **float grams2moles(const char \* formula, float grams = 1.0)**
Returns the amount of moles for a given amount of grams.
The default moles == 1, returns the basic conversion factor.

These functions can be used, e.g. if one wants to solve 2.3 moles of KOH
into 10 litres of water to get a defined pH, now much grams I need to weigh?

```cpp
grams = PTOE.moles2grams("KOH", 2.3);
```


#### Weight

The unit of weight is **Daltons** (Da) or the atomic mass unit (amu), think of it as the number of nucleons.
A **Dalton** is defined as 1/12th of the weight of an Carbon atom.

The **weight(uint8_t element)** call returns the weight of a single atom (by index).
The **weight(formula)** call is meant to calculate the weight of a molecule defined by the formula.
A molecule is defined as one or more atoms.
The functions returns a float, so to get the integer weight, one should use **round()**.

If the formula can not be parsed, e.g. it contains non existing elements, 
the **weight()** function will return a weight of 0.

The **weight(formula, abbreviation)** function is meant to calculate the total weight 
of one element (by abbreviation) in a molecule. 
E.g one can weigh the H atoms in H2O (2 of 18).

```cpp
aw = PTOE.weight("H2O", "H");
```


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
- "H2SO4" = compound molecule, no groups (sulphuric acid).
- "C6(COOH)2" = repeating group, (artificial example).
- "(H2O)987" = 987 water molecules.
- "YBa2Cu3O7" = compound molecule, == some superconductor-ish material.
- "Ba((OH)4(COOH)2)3" - recursive repeating groups (artificial example).

Numbers of an element or a group should be between 1 and 2^32-1 (uint32_t).
However in practice values are relative small (< 20).
- zero (0) is mapped upon 1.
- very large numbers cause overflow when printing the output of some functions.
Use - https://github.com/RobTillaart/printHelpers if needed.


#### MassPercentage

The **massPercentage(formula, abbreviation)** function can determine the percentage of the weight 
a selected element has in a formula, e.g. the weight of the Oxygen in **H2SO4**.
This is calculated by dividing the weight of the element by the total weight.

```cpp
mp = PTOE.massPercentage("H2SO4", "O");
```

If you want to do that for all elements it might be more efficient to calculate the weight 
of the whole formula once.


#### Avogadro, Dalton, electronVolt.

The library provides the following (SI) constants:
- **const float AVOGADRO = 6.02214076e+23** number of particles in one mole.
- **const float DALTON = 1.66053907e-24** weight of one nucleon in grams.
  - relation: DALTON \* AVOGADRO == 1.0
- **const float ELEKTRON_VOLT_JOULE = 1.602176565e-19** eV in Joule
- **const float ELEKTRON_VOLT_GRAM = 1.7826619e-39** eV in grams  (E=Mc2)
- **const float DALTON_JOULE = 1.036427015e5** == DALTON / ELEKTRON_VOLT_JOULE.
- **const float DALTON_EV = 931.4940954e12** == DALTON / ELEKTRON_VOLT_GRAM.
Can be used to convert the atomic mass to electron volt.

These constants are not directly used in the library however they fit the scope of the library.
There will be functions based upon these constants in the future.

The **AVOGADRO** constant is the proportionality factor that relates the number of constituent particles 
(usually molecules, atoms, or ions) in a sample with the amount of substance in that sample.

From - https://en.wikipedia.org/wiki/Avogadro_constant

Use https://github.com/RobTillaart/printHelpers to print numbers in the scientific notation.
This will prevent printing **OVF** overflow or **0.000**.


#### Debug

- **float weightFactor()** returns the weightFactor, that was used to
minimize the memory used for the elements mass lookup table.


## Future

#### Must

- improve documentation
  - reorganize.
- float => double 
- EV is at the end of range float...


#### Should

- overload functions
  - **uint32_t protons(formula)** worker, formula can be single element.
  - **uint32_t neutrons(formula)** uses protons()
  - **uint32_t electrons(formula)** uses protons()
- add weight of electron as constant. for completeness.
- functions around **AVOGADRO**, **DALTON** etc.
  - **float weightEV(formula)**
  - **float dalton2EV(float Dalton)** to express mass in eV.
  - **float dalton2Joule(float Dalton)**


#### Could

- extend unit tests
- extend formula parser with error codes.
  - which ones?
- look for optimizations
  - 3x almost same parser
  - PROGMEM ?
- performance **find()**
  - alphabetical array? tree? 
  - ==> more memory...
- support \[] square brackets too.
  - (NH4)2\[Pt(SCN)6]


- add a derived class PERIODIC_TABLE?
- state table
  - liquid, gas, solid, unknown  (2 bits per element) = ~30 bytes
  - room temperature + sea level pressure
  - separate file like elements_name.h


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
  - only if more RAM is used. => not
- parameters element should be less than \_size
  - user responsibility
- more information?
  - will not handle isotopes (too much memory needed)
  - database needed
- Electron bands 
  - K L M etc?
  - valence
- temperatures,
  - melting point
  - evaporate point
  - 2 bytes per temp 4 x 118 = 476 bytes
  - compression 3 bytes for 2 temps 2x 12 bits = 0..4095 K = 354 bytes


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


