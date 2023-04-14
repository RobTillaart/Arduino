# Change Log AtomicWeight

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


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
