
[![Arduino CI](https://github.com/RobTillaart/statHelpers/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/statHelpers/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/statHelpers.svg?maxAge=3600)](https://github.com/RobTillaart/statHelpers/releases)

# statHelpers

Arduino library with a number of statistic helper functions.

## Description

This library contains functions that have the goal to help with 
some basic statistical calculations.


## Functions

### Permutation

returns how many different ways one can choose a set of k elements 
from a set of n. The order does matter. 
The limits mentioned is the n for which all k still work.

- **uint32_t permutations(n, k)** exact up to 12
- **uint64_t permutations64(n, k)** exact up to 20
- **double dpermutations(n, k)** not exact up to 34 (4 byte) or 170 (8 byte)

If you need a larger n but k is near 0 the functions will still work, but 
to which k differs per value for n. (no formula found, and an overflow
detection takes overhead).


- **nextPermutation<Type>(array, size)** given an array of type T it finds the next permutation
of that array in a lexicographical way.  ABCD --> ABDC. 
Based upon // http://www.nayuki.io/page/next-lexicographical-permutation-algorithm although 
other same code examples exist.


### Factorial

- **uint32_t factorial(n)** exact up to 12!
- **uint64_t factorial64(n)** exact up to 20!  (Print 64 bit ints with my printHelpers)
- **double dfactorial(n)** not exact up to 34! (4 byte) or 170! (8 byte)
- **double stirling(n)** approximation function for factorial (right magnitude)

**dfactorial()** is quite accurate over the whole range.
**stirling()** is up to 3x faster for large n (> 100), 
but accuracy is less than the **dfactorial()**, see example.


### Combination

returns how many different ways one can choose a set of k elements 
from a set of n. The order does not matter. 
The number of combinations grows fast so n is limited per function.
The limits mentioned is the n for which all k still work.

- **uint32_t combinations(n, k)**   n = 0 .. 30 (iterative version)
- **uint64_t combinations64(n, k)**  n = 0 .. 61 (iterative version)
- **uint32_t rcombinations(n, k)**    n = 0 .. 30 (recursive version, slightly slower)
- **uint64_t rcombinations64(n, k)**  n = 0 .. 61 (recursive version, slightly slower)
- **double dcombinations(n, k)**  n = 0 .. 125 (4bit)  n = 0 .. 1020 (8 bit) 

If you need a larger n but k is near 0 or near n the functions will still work, 
but for which k differs per value for n. (no formula found, and an overflow
detection takes overhead). 


- **combPascal(n, k)** n = 0 .. 30 but due to double recursion per iteration it takes
time and a lot of it for larger values. Added for recreational purposes, limited tested.


## Notes

- **perm1** is a sketch in the examples that shows a recursive permutation 
algorithm. It generates all permutations of a given char string. 
It allows you to process every instance.
It is added to this library as it fits in the context.


## Future

- code & example for get Nth Permutation
- investigate valid range detection for a given (n, k) for combinations and permutations.


## Operation

See examples
