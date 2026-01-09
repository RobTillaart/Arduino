
[![Arduino CI](https://github.com/RobTillaart/SET/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SET/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SET/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SET/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SET/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SET.svg)](https://github.com/RobTillaart/SET/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SET/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SET.svg?maxAge=3600)](https://github.com/RobTillaart/SET/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SET.svg)](https://registry.platformio.org/libraries/robtillaart/SET)


# SET

Arduino library to implement a simple SET data structure.


## Description

The set library implements the set data structure for integers 0..255.
This limit is chosen because of the memory limitations of an Arduino UNO R3, 
however these numbers can be used as indices to a table of strings or other
data types.

Feedback as always is welcome.


## Interface

```cpp
#include "SET.h"
```

### Constructor

- **Set(bool clear = true)** creates an empty set, default it is cleared.
- **Set(&Set)** copies a set.


### Set level

- **clear()** empty the set.
- **invert()** flip all elements in the set.
- **addAll()** add all 256 elements to the set.
- **count()** returns the number of elements.
- **isEmpty()** idem
- **isFull()** idem


### Element level

- **add(uint8_t value)** add element n to the Set.
- **sub(uint8_t value)** remove element n from the Set.
- **invert(uint8_t value)** flip element n in the Set.
- **has(uint8_t value)** check if element n is in the Set.


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
- **next()** find the next element. Will not wrap around when 'end' of the set is reached.
- **prev()** find the previous element. Will not wrap around when 'begin' of the set is reached.
- **last()** find the last element.
- **getNth(n)** find the Nth element in a set if it exist.


## Usage Examples

### Add and Remove Elements
See: [`allTest.ino`](examples/allTest/allTest.ino)

```cpp
Set mySet;
mySet.add(10);
mySet.add(20);
mySet.add(30);

if (mySet.has(20)) {
  Serial.println("20 is in the set");
}

mySet.sub(20);  // remove element
Serial.println(mySet.count());
```

### Set Operations (Union, Intersection, Difference)
See: [`interSectionTest.ino`](examples/interSectionTest/interSectionTest.ino)

```cpp
Set setA, setB, result;
for (int i = 0; i < 150; i++) {
  setA.add(random(256));
  setB.add(random(256));
}

result = setA + setB;  // union
result = setA * setB;  // intersection
result = setA - setB;  // difference

setA += setB;  // in-place union
```

### Iterate Through a Set
See: [`iterationTest.ino`](examples/iterationTest/iterationTest.ino)

```cpp
Set mySet;
for (int i = 0; i < 10; i++) {
  mySet.add(random(256));
}

int n = mySet.first();
while (n != -1) {
  Serial.print(n);
  Serial.print('\t');
  n = mySet.next();
}
```

### Set Comparison and Subset Testing
See: [`subsetTest.ino`](examples/subsetTest/subsetTest.ino)

```cpp
Set setE;
for (int i = 0; i < 5; i++) setE.add(i);

Set setF(setE);
Serial.println(setE <= setF ? "subset" : "no subset");

setF.add(6);
Serial.println(setE <= setF ? "subset" : "no subset");
```

## Performance Considerations

- The SET library uses a compact 32-byte bitmap (256 bits) to store membership of values 0-255
- **Memory usage**: Fixed at 32 bytes per Set object, very efficient for Arduino platforms
- **Time complexity**: Most operations (add, remove, has) are **O(1)** constant time
- **Set operations** (union, intersection, difference) are **O(1)** since they operate on all 32 bytes
- **Iteration** is **O(n)** where n is the number of elements
- Useful as indices to map to larger data structures like arrays of strings or sensor readings

## Return Values

- Iterator functions return the **element value** (0-255) if found, or **-1** if not found
- The `_current` position persists across calls and is updated by iterator functions

## Technical Details

- The set stores values in a **bitmap** using 8 bytes per element position (0-31)
- Each byte holds 8 boolean values representing 8 consecutive integers
- Maximum 256 unique elements (0-255) due to Arduino memory constraints
- The library uses efficient bit manipulation for fast operations
- Bit counting uses **Kernighan's bit count algorithm** for optimal performance

## Operational

See the `examples/` folder for complete working examples:
- **allTest**: Comprehensive test suite with timing measurements
- **equalTest**: Demonstrates set equality and copying
- **interSectionTest**: Shows intersection, union, and difference operations
- **iterationTest**: Forward and backward iteration examples
- **randomFromSet**: Using the SET library with random operations
- **subsetTest**: Subset relationship testing
- **timingTest**: Performance benchmarking on Arduino


## Future

#### Must

- Complete documentation updates

#### Should

#### Could

#### Wont


## Support

If you appreciate this library, please consider:

- ⭐ **Star** the repository on GitHub
- 🐛 **Report issues** or contribute **pull requests**
- 💬 **Provide feedback** to help improve the library
- 💰 Support development via PayPal or GitHub sponsors

For questions or issues, visit: https://github.com/RobTillaart/SET/issues

Thank you,

