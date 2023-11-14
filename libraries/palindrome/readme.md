
[![Arduino CI](https://github.com/RobTillaart/palindrome/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/palindrome/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/palindrome/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/palindrome/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/palindrome/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/palindrome.svg)](https://github.com/RobTillaart/palindrome/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/palindrome/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/palindrome.svg?maxAge=3600)](https://github.com/RobTillaart/palindrome/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/palindrome.svg)](https://registry.platformio.org/libraries/robtillaart/palindrome)


# Palindrome

Library for palindrome search


## Description

The palindrome library can test if a string is a palindrome and is able to find 
the longest palindrome within a character string.

This library is written mainly for some educational purpose, however other
applications are possible. Please share your ideas.


#### tests

The library is tested with an Arduino UNO, random string of 1600 characters.

(TODO performance compare)


## Interface

```cpp
#include "palindrome.h"
```

- **palindrome()** constructor.
- **int findPalindrome(const char \* str, int & position, int & length)** find the longest palindrome in a string. (first occurrence).
- **int findEvenPalindrome(const char \* str, int & position, int & length)** find the longest palindrome in a string with even length. (first occurrence).
- **int findOddPalindrome(const char \* str, int & position, int & length)** find the longest palindrome in a string with odd length. (first occurrence).
- **bool isPalindrome(const char \* str)** checks if a string is a palindrome.
- **int palindromeCount(const char \* str)** returns the count of matching pairs in a string. 
This is at most the ```length / 2 + 1```.
- **float palindromePercentage(const char \* str)** returns the count as percentage 0.0 .. 100.0 %


## Operation

The examples show the basic working of the functions.


## Questions

- is an empty string a palindrome?


## Future

#### Must

- update documentation

#### Should

#### Could

- function names?
  - palindromeCount -- symmetryCount?
  - palindromePercentage -- symmetryPercentage?
- improve algorithms
  - merge odd / even find algorithms?
- investigate Print interface?
- investigate palindrome for numbers - radix 2..16 (36?)
- investigate case (in)sensitive flag?
- investigate ignore spaces flag?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

