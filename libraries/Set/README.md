
[![Arduino CI](https://github.com/RobTillaart/SET/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SET/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SET.svg?maxAge=3600)](https://github.com/RobTillaart/SET/releases)

# SET

Arduino library to implement a simple SET data structure.


## Description

The set library implements the set data structure for integers 0..255.
This limit is chosen because of the memory limitations of an Arduino UNO, 
however these numbers can be used as indices to a table of strings or other
datatypes.


## Interface


### Constructor

- **Set(bool clear = true)** creates an empty set, default it is cleared.
- **Set(&Set)** copies a set.


### Set level

- **clear()** empty the set.
- **invert()** flip all elements in the set.
- **addAll(n)** add all 256 elements to the set.
- **count()** returns the number of elements.
- **isEmpty()** idem
- **isFull()** idem


### Element level

- **add(n)** add element n to the Set.
- **sub(n)** remove element n from the Set.
- **invert(n)** flip element n in the Set.
- **has(n)** check if element n is in the Set.


### Operators

- union + +=
- diff - -=
- intersection * *=


### Equality

- equal ==
- not equal !=
- is subSet <=

A superSet B is not implemented as one could say B subSet A (B <= A)


### Iterators 

all iterator-functions returns the current element or -1 if not exist.

- **setCurrent(n)** if n is in the Set, n will be the current
- **first()** find the first element
- **next()** find the next element. Will not wrap zround when 'end' of the set is reached.
- **prev()** find the previous element. Will not wrap zround when 'begin' of the set is reached.
- **last()** find the last element.


## Operational

See examples
