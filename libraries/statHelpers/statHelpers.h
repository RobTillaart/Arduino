#pragma once
//
//    FILE: statHelpers.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library with a number of statistic helper functions.
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/statHelpers


#include "Arduino.h"


#define STATHELPERS_LIB_VERSION       (F("0.1.2"))


// TODO
// Look for optimizations
// Look for ways to extend the scope


///////////////////////////////////////////////////////////////////////////
//
// PERMUTATIONS
//

uint32_t permutations(uint8_t n, uint8_t k)
{
  uint32_t rv = 1;
  for (uint8_t i = n; i > (n - k); i--) rv *= i;
  return rv;
}


uint64_t permutations64(uint8_t n, uint8_t k)
{
  uint64_t rv = 1;
  for (uint8_t i = n; i > (n - k); i--) rv *= i;
  return rv;
}

// can be optimized similar to dfactorial
double dpermutations(uint8_t n, uint8_t k)
{
  double rv = 1;
  for (uint8_t i = n; i > (n - k); i--) rv *= i;
  return rv;
}


/*
http://wordaligned.org/articles/next-permutation snippet

As an example consider finding the next permutation of:

8342666411
The longest monotonically decreasing tail is 666411, and the corresponding head is 8342.

8342 666411
666411 is, by definition, reverse-ordered, and cannot be increased by permuting its elements. To find the next permutation, we must increase the head; a matter of finding the smallest tail element larger than the head’s final 2.

8342 666411
Walking back from the end of tail, the first element greater than 2 is 4.

8342  666411
Swap the 2 and the 4

8344 666211
Since head has increased, we now have a greater permutation. To reduce to the next permutation, we reverse tail, putting it into increasing order.

8344 112666
Join the head and tail back together. The permutation one greater than 8342666411 is 8344112666.
*/


// http://www.nayuki.io/page/next-lexicographical-permutation-algorithm

// b = nextPermutation<char>(array, 100);
template <typename T>
bool nextPermutation(T * array,  uint16_t size)
{
  // Find longest non-increasing suffix
  int i = size - 1;
  while (i > 0 && array[i - 1] >= array[i]) i--;
  // Now i is the head index of the suffix

  // Are we at the last permutation already?
  if (i <= 0) return false;

  // Let array[i - 1] be the pivot
  // Find rightmost element that exceeds the pivot
  int j = size - 1;
  while (array[j] <= array[i - 1])
    j--;
  // Now the value array[j] will become the new pivot
  // Assertion: j >= i

  // Swap the pivot with j
  T temp = array[i - 1];
  array[i - 1] = array[j];
  array[j] = temp;

  // Reverse the suffix
  j = size - 1;
  while (i < j)
  {
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    i++;
    j--;
  }
  return true;
}


///////////////////////////////////////////////////////////////////////////
//
// FACTORIAL
//

// exact ==> 12!
uint32_t factorial(uint8_t n)
{
  uint32_t f = 1;
  while(n > 1) f *= (n--);
  return f;
}


// exact ==> 20!
uint64_t factorial64(uint8_t n)
{
  // to be tested
  // if ( n <= 12) return factorial(12);
  // uint64_t f = factorial(12);
  // for (uint8_t t = 13; t <= n; t++) f *= t;
  uint64_t f = 1;
  while(n > 1) f *= (n--);
  return f;
}


// float  => 34!
// double => 170!
double dfactorialReference(uint8_t n)
{
  double f = 1;
  while (n > 1) f *= (n--);
  return f;
}


// FASTER VERSION 
// does part of the math with integers.
// tested on UNO and ESP32, roughly 3x faster
// numbers differ slightly in the order of IEEE754 precision  => acceptable.
// 10e-7  for 4 bit float 
// 10e-16 for 8 bit double
double dfactorial(uint8_t n)
{
  double f = 1;
  while (n > 4)
  {
    uint32_t val = n * (n-1);
    val *= (n-2) * (n-3);
    f *= val;
    n -= 4;
  }
  while (n > 1) f *= (n--); // can be squeezed too.
  return f;
}


// stirling is an approximation function for factorial(n).
// it is slower but constant in time.
// float  => 26!
// double => 143!
double stirling(uint8_t n)
{
  double v = exp(-n) * pow(n, n) * sqrt(TWO_PI * n);
  return v;
}


///////////////////////////////////////////////////////////////////////////
//
// COMBINATIONS
//

// works for n = 0..30 for all k
uint32_t combinations(uint16_t n, uint16_t k)
{
  if ((k == 0) || (k == n)) return 1;
  if (k < (n-k)) k = n - k;   // symmetry
  uint32_t rv = n;
  uint8_t p = 2;
  for (uint8_t i = n-1; i > k; i--)
  {
    // if ((0xFFFFFFFF / i) < rv) return 0;
    rv = (rv * i) / p;
    p++;
  }
  return rv;
}


// works for n = 0..61 for all k
uint64_t combinations64(uint16_t n, uint16_t k)
{
  if ((k == 0) || (k == n)) return 1;
  if (k < (n-k)) k = n - k;   // symmetry
  uint64_t rv = n;
  uint8_t p = 2;
  for (uint8_t i = n-1; i > k; i--)
  {
    rv = (rv * i) / p;
    p++;
  }
  return rv;
}


// experimental - not exact but allows large values
// float  (4 bits) works till n = 125    for all k
// double (8 bits) works till n = 1020   for all k
double dcombinations(uint16_t n, uint16_t k)
{
  if ((k == 0) || (k == n)) return 1;
  if (k < (n-k)) k = n - k; // symmetry
  double rv = n;
  uint16_t p = 2;
  for (uint16_t i = n-1; i > k; i--)
  {
    rv = (rv * i) / p;
    p++;
  }
  return rv;
}


// recursive (mind your stack)
// works for n = 0..30 for all k
uint32_t rcombinations(uint16_t n, uint16_t k)
{
  if (k > (n-k)) k = n - k; // symmetry
  if (k == 0) return 1;
  return (n * rcombinations(n - 1, k - 1)) / k;
}


// recursive
// works for n = 0..61 for all k
uint64_t rcombinations64(uint16_t n, uint16_t k)
{
  if (k > (n-k)) k = n - k; // symmetry
  if (k == 0) return 1;
  return (n * rcombinations64(n - 1, k - 1)) / k;
}


// very slow recursive way by means of Pascals triangle.
// works for n = 0..30 for all k  (but takes a lot of time)
uint32_t combPascal(uint16_t n, uint16_t k)
{
  if (k > (n-k)) k = n - k; // symmetry
  if (k > n ) return 0;
  if (k == 0) return 1;
  if (n < 2) return 1;
  uint32_t rv = combPascal(n-1, k-1);
  rv += combPascal(n-1, k);
  return rv;
}

// -- END OF FILE --
