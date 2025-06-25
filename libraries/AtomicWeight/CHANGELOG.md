# Change Log AtomicWeight

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.2] - 2025-06-22
- update minerals.h (add formulas chapter 14)
- split minerals example in 3 parts
- update atomic_weight_split.ino (add element nr)
- update readme.md
- add example atomic_weight_count_protons.ino
- minor update examples

## [0.3.1] - 2025-01-02
- fix #4, update minerals.h
- update example
- update keywords.txt

## [0.3.0] - 2024-08-27
- support float indices e.g. "(Mg0.4Fe1.6)2.0SiO4" == Olivine
- update **atomic_weight_formula.ino**
- add **minerals.h** (short list)
- add **atomic_weight_minerals.ino** 
- update / clean up constants
- add **weightEV()**
- add **weightEV()**
- add **dalton2EV()**
- update readme.md

----

## [0.2.2] - 2024-04-07
- update GitHub actions
- refactor internal names for readability
- minor edits

## [0.2.1] - 2023-10-17
- update readme.md

## [0.2.0] - 2023-04-15
- use new weight factor 201.3868 to reduce maximum relative error
- create **elements_uint16.h** file.
- move **ATOMIC_WEIGHT_FACTOR** to **elements_uint16.h** file.
- create **elements_name.h** file with full element names. Uses ~1670 bytes of RAM.
  so will **NOT** work on all boards.
- add related constants
  - **AVOGADRO** = 6.02214076e+23; number of particles in one mole.
  - **DALTON** = 1.66053907e-24; weight of one nucleon in grams.
  - **ELEKTRON_VOLT_JOULE** = 1.602176565e-19; eV in Joule
  - **ELEKTRON_VOLT_GRAM**  = 1.7826619e-39; eV in grams
  - **DALTON_EV** = 931.4940954e12 = DALTON / ELEKTRON_VOLT_GRAM
  - **DALTON_JOULE** = 1.036427015e5 = DALTON / ELEKTRON_VOLT_JOULE
- update unit tests.
- update readme.md
- update keywords.txt.

----

## [0.1.5] - 2023-04-13
- add **moles2grams(formula, moles)**
- add **grams2moles(formula, grams)**
- add example.
- add guarding with **size** parameter in **weight()**
- improved usage **abbrev**(name) versus **el**(index).
- improved readme.md.
- add define for **ATOMIC_WEIGHT_MAX_SPLIT_LIST**
- update keywords.txt.
- minor edits.

## [0.1.4] - 2023-04-12
- add **splitElements()** split a formula in an internal list of elements.
- add **element()** access to split elements. See example.
- add **count()** to count atoms in a formula.
- add **atomPercentage()** to calculate percentage of atoms of an element.
- add examples.
- update readme.md
- update keywords.txt
- minor edits.

## [0.1.3] - 2023-01-01
- refactor interface
- add **weight(formula, element)**
- add **massPercentage(formula, element)**
- fix version number in .cpp
- update readme.md.
- update keywords.txt

## [0.1.2] - 2023-01-01
- add weight(formula) group () support
- rewrote example
- update readme.md.
- add unit tests

## [0.1.1] - 2022-12-30
- fix offset in some functions
- move code to .cpp file
- add **float weight(char \* formula)**
- refactor and clean up a bit.
- update readme.md.

## [0.1.0] - 2022-12-30
- initial release
- renamed class from AtomicWeight to PTOE.
- add **find(abbrev)**
- add examples.
- update readme.md.

----

## [0.0.1] - 2022-03-09
- first light (not released)
