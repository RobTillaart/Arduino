
[![Arduino CI](https://github.com/RobTillaart/statHelpers/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/statHelpers/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/statHelpers/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/statHelpers/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/statHelpers/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/statHelpers.svg)](https://github.com/RobTillaart/statHelpers/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/statHelpers/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/statHelpers.svg?maxAge=3600)](https://github.com/RobTillaart/statHelpers/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/statHelpers.svg)](https://registry.platformio.org/libraries/robtillaart/statHelpers)


# statHelpers

Arduino library with a number of statistic helper functions.


## Description

This library contains functions that have the goal to help with 
basic statistical calculations like permutations, combinations,
and factorials.

It includes an experimental section for large numbers. 
Note that these are very computation (time) intensive so not suited for real time math :)

To print very large numbers - https://github.com/RobTillaart/PrintHelpers


#### Related

- https://github.com/RobTillaart/Correlation
- https://github.com/RobTillaart/GST - Golden standard test metrics
- https://github.com/RobTillaart/Histogram
- https://github.com/RobTillaart/RunningAngle
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian
- https://github.com/RobTillaart/statHelpers - combinations & permutations
- https://github.com/RobTillaart/Statistic


## Interface

```cpp
#include "statHelpers.h"
```

### Permutation

Returns how many different ways one can choose a set of k elements from a set of n. 
The order does matter so (1, 2) is not equal to (2, 1). 
The limits mentioned is the n for which all k still work.

- **uint32_t permutations(n, k)** exact up to n = 12
- **uint64_t permutations64(n, k)** exact up to n = 20
- **double dpermutations(n, k)** not exact up to n = 34 (4 byte) or n = 170 (8 byte)

If you need a larger n but k is near 0 the functions will still work.
To which value of k the formulas work differs per value for n. 
No formula found, and build in an overflow detection takes overhead, so that is not done.


- **nextPermutation<Type>(array, size)** given an array of type T it finds the next permutation
of that array in a lexicographical way.  ABCD --> ABDC. 
Based upon // http://www.nayuki.io/page/next-lexicographical-permutation-algorithm although 
other same code examples exist.


### Factorial

- **uint32_t factorial(n)** exact up to n = 12.
- **uint64_t factorial64(n)** exact up to n = 20.  (Print 64 bit integers with my printHelpers)
- **double dfactorial(n)** not exact up to n = 34 (4 byte) or n = 170 (8 byte).
- **double stirling(n)** approximation function for factorial (right magnitude).
Constant run-time.

**dfactorial()** is quite accurate over the whole range.
**stirling()** is up to 3x faster for large n (> 100), 
but accuracy is less than the **dfactorial()**, see example.


### SemiFactorial

SemiFactorials are like factorials but skipping every other.
SemiFactorials are written as a number with two exclamation marks.
 
SemiFactorial are defined for
- **odd** values:  n!! == n x (n-2) x (n-4) ... x 1
- **even** values: n!! == n x (n-2) x (n-4) ... x 2

Example 12!! = 12 x 10 x 8 x 6 x 4 x 2 = 46080

- **uint32_t semiFactorial(n)** exact up to 20!!
- **uint64_t semiFactorial64(n)** exact up to 33!!  (Print 64 bit integers with printHelpers library)
- **double dSemiFactorial(n)** not exact up to 56!! (4 byte) or 300!! (8 byte)


Notes:  
```
n! = n!! x (n-1)!!
``` 
This formula allows to calculate the value of n! indirectly.


### SkipFactorial (experimental)

- **uint32_t skipFactorial(uint32_t n, uint32_t skip)** 
- **uint64_t skipFactorial64(uint32_t n, uint32_t skip)** 
- **double dSkipFactorial(uint32_t n, uint32_t skip)** 

SkipFactorials are like factorials and semiFactorials but they skip **skip** numbers.
- **skipFactorial(12, 4)** = 12 x 8 x 4 = 384
- **skipFactorial(17, 5)** = 17 x 12 x 7 x 2 = 2856
- **skipFactorial(n, 1)** == **factorial(n)**
- **skipFactorial(n, 2)** == **semiFactorial(n)**

As the maximum depends on both n and step sizze there is no single maximum for n.
This is similar to combinations and permutations.

An indicative table of maxima per function call, the larger the skip, the larger the maximum n.
Note that for skip <= 10 n still is an 8 bit number.

|   function        |  n, 2   |  n, 3   |  n, 4   |  n, 5   |  n, 10  |  notes  |
|:------------------|:-------:|:-------:|:-------:|:-------:|:-------:|:--------|
|  skipFactorial    |   20    |   27    |   32    |    40   |    69   |  max expected smaller than 7 x skip when skip > 10.
|  skipFactorial64  |   33    |   45    |   55    |    66   |   115   |  max expected smaller than 12 x skip when skip > 10.
|  dSkipFactorial   |   56    |   77    |   95    |   115   |   200   |  float  (4 bytes)  max expected smaller than 20 x skip when skip > 10.
|  dSkipFactorial   |  300    |         |         |         |         |  double (8 bytes) 

Note that for the function the **max / skip** is decreasing when **skip grows**.


### Combinations

Returns how many different ways one can choose a set of k elements from a set of n. 
The order does **not** matter so (1, 2) is equal to (2, 1). 
The number of combinations grows fast so n is limited per function.
The limits mentioned is the n for which all k still work.

- **uint32_t combinations(n, k)**     n = 0 .. 30 (iterative version)
- **uint64_t combinations64(n, k)**   n = 0 .. 61 (iterative version)
- **uint32_t rcombinations(n, k)**    n = 0 .. 30 (recursive version, slightly slower)
- **uint64_t rcombinations64(n, k)**  n = 0 .. 61 (recursive version, slightly slower)
- **double dcombinations(n, k)**      n = 0 .. 125 (4bit)  n = 0 .. 1020 (8 bit) 

If you need a larger n but k is near 0 the functions will still work.
To which value of k the formulas work differs per value for n. 
No formula found, and build in an overflow detection takes overhead, so that is not done.


- **combPascal(n, k)** n = 0 .. 30 but due to double recursion per iteration it takes
time and a lot of it for larger values. Added for recreational purposes, limited tested.
Uses Pascal's triangle.


## Notes

- **perm1** is a sketch in the examples that shows a recursive permutation algorithm. 
It generates all permutations of a given char string and allows you to process every instance.
This sketch is added to this library as it fits in the context.


## Experimental 

#### 32 bit numbers

- **void bigFactorial(uint32_t n, double &mantissa, uint32_t &exponent)** 
returns a double mantissa between 0 and 10, and an integer exponent. 
- **void bigPermutation(uint32_t n, uint32_t k, double &mantissa, uint32_t &exponent)** 
returns a double mantissa between 0 and 10, and an integer exponent. 
- **void bigCombination(uint32_t n, uint32_t k, double &mantissa, uint32_t &exponent)** 
returns a double mantissa between 0 and 10, and an integer exponent. 

An experimental **bigFactorial(n)** calculation to get an idea of the big numbers. 
it can calculate factorials up to an exponent of 4294967295 max.  100.000.000! can be 
done in 38 minutes on an ESP32 at 240 MHz.  
Maximum value for n is **518678059! ==  2.1718890e4294967292** a number that took ~10 hours to calculate. 

An experimental **bigPermutation(n, k)** calculation, to handle big numbers too. 
Maximum value for n is **518678059** to have full range support. For small(er) 
values of k, n can even be much larger, but not larger than 4294967295 max.

An experimental **bigCombination(n, k)** calculation for big numbers. 
Not investigated what its maximum value is, but it should be higher than **518678059** as the number 
of combinations is always smaller than number of permutations.


#### 64 bit numbers- not investigated

To have support for huge numbers one could upgrade the code to use uint64_t as parameter and 
internally but calculating these values could take a lot of time, although **bigPermutations64(n, k)** 
and **bigCombinations64(n, k)** would work fast for small values of k. 

- **void bigFactorial64(uint64_t n, double &mantissa, uint64_t &exponent)** 
returns a double mantissa between 0 and 10, and an integer exponent.
- **void bigPermutation64(uint64_t n, uint64_t k, double &mantissa, uint64_t &exponent)** 
returns a double mantissa between 0 and 10, and an integer exponent.
- **void bigCombination64(uint64_t n, uint64_t k, double &mantissa, uint64_t &exponent)** 
returns a double mantissa between 0 and 10, and an integer exponent.

If someone has found the limits of these 64 bit versions, please let me know.


## Operation

See examples


## Future

#### Must

#### Should

- investigate valid range detection for a given (n, k) for combinations and permutations.
- Look for optimizations

#### Could

- investigate a bigFloat class to do math for permutations and combinations to substantially larger values.
- Look for ways to extend the scope
- fill table for skipFactorial for **double**


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

