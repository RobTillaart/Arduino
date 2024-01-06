//
//    FILE: statHelpers.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library with a number of statistic helper functions.
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"


///////////////////////////////////////////////////////////////////////////
//
//  PERMUTATIONS
//
uint32_t permutations(uint8_t n, uint8_t k)
{
  uint32_t rv = 1;
  for (uint8_t i = n; i > (n - k); i--)
  {
    rv *= i;
  }
  return rv;
}


uint64_t permutations64(uint8_t n, uint8_t k)
{
  uint64_t rv = 1;
  for (uint8_t i = n; i > (n - k); i--)
  {
    rv *= i;
  }
  return rv;
}


//  can be optimized similar to dfactorial
double dpermutations(uint8_t n, uint8_t k)
{
  double rv = 1;
  for (uint8_t i = n; i > (n - k); i--)
  {
    rv *= i;
  }
  return rv;
}


/*
http://wordaligned.org/articles/next-permutation snippet

As an example consider finding the next permutation of:

8342666411
The longest monotonically decreasing tail is 666411, and the corresponding head is 8342.

8342 666411
666411 is, by definition, reverse-ordered, and cannot be increased by permuting its elements.
To find the next permutation, we must increase the head; a matter of finding the smallest tail
 element larger than the head’s final 2.

8342 666411
Walking back from the end of tail, the first element greater than 2 is 4.

8342  666411
Swap the 2 and the 4

8344 666211
Since head has increased, we now have a greater permutation. To reduce to the next permutation,
we reverse tail, putting it into increasing order.

8344 112666
Join the head and tail back together. The permutation one greater than 8342666411 is 8344112666.
*/


// http://www.nayuki.io/page/next-lexicographical-permutation-algorithm

// b = nextPermutation<char>(array, 100);
/*
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
*/


///////////////////////////////////////////////////////////////////////////
//
//  FACTORIAL
//

//  exact ==> 12!
uint32_t factorial(uint8_t n)
{
  uint32_t f = 1;
  while(n > 1) f *= (n--);
  return f;
}


//  exact ==> 20!
uint64_t factorial64(uint8_t n)
{
  //  to be tested
  //  if ( n <= 12) return factorial(12);
  //  uint64_t f = factorial(12);
  //  for (uint8_t t = 13; t <= n; t++) f *= t;
  uint64_t f = 1;
  while(n > 1) f *= (n--);
  return f;
}


//  float  (4 byte) => 34!
//  double (8 byte) => 170!
double dfactorialReference(uint8_t n)
{
  double f = 1;
  while (n > 1) f *= (n--);
  return f;
}


//  FASTER VERSION
//  does part of the math with integers.
//  tested on UNO and ESP32, roughly 3x faster
//  numbers differ slightly in the order of IEEE754 precision  => acceptable.
//  10e-7  for 4 bit float
//  10e-16 for 8 bit double
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
  while (n > 1) f *= (n--);   //  can be squeezed too.
  return f;
}


//  stirling is an approximation function for factorial(n).
//  it is slower but constant in time.
//  float  => 26!
//  double => 143!
double stirling(uint8_t n)
{
  double v = exp(-n) * pow(n, n) * sqrt(TWO_PI * n);
  return v;
}


///////////////////////////////////////////////////////////////////////////
//
//  SEMI_FACTORIAL
//

//  exact ==> 20!!
uint32_t semiFactorial(uint8_t n)
{
  uint32_t f = 1;
  while(n > 1)
  {
    f *= n;
    n -= 2;
  }
  return f;
}


//  exact ==> 33!!
uint64_t semiFactorial64(uint8_t n)
{
  uint64_t f = 1;
  while(n > 1)
  {
    f *= n;
    n -= 2;
  }
  return f;
}


//  float  (4 byte) => 56!!
//  double (8 byte) => 300!!
double dSemiFactorial(uint16_t n)
{
  double f = 1;
  while (n > 6)  // TODO: test performance gain by integer math. (depends on platform ?)
  {
    uint32_t val = n * (n-2) * (n-4);
    f *= val;
    n -= 6;
  }
  while (n > 1)
  {
    f *= n;
    n -= 2;
  }
  return f;
}



///////////////////////////////////////////////////////////////////////////
//
//  SKIP_FACTORIAL
//

uint32_t skipFactorial(uint32_t n, uint32_t skip)
{
  if (skip == 0) return 0;
  uint32_t f = 1;
  while(n > skip)
  {
    f *= n;
    n -= skip;
  }
  return f;
}


uint64_t skipFactorial64(uint32_t n, uint32_t skip)
{
  if (skip == 0) return 0;
  uint64_t f = 1;
  while(n > skip)
  {
    f *= n;
    n -= skip;
  }
  return f;
}


//  float  (4 byte)
//  double (8 byte)
double dSkipFactorial(uint32_t n, uint32_t skip)
{
  if (skip == 0) return 0;
  double f = 1;
  while(n > skip)   //  optimize like sSemiFactorial?
  {
    f *= n;
    n -= skip;
  }
  return f;
}


///////////////////////////////////////////////////////////////////////////
//
//  COMBINATIONS
//

//  works for n = 0..30 for all k
uint32_t combinations(uint16_t n, uint16_t k)
{
  if ((k == 0) || (k == n)) return 1;
  if (k < (n-k)) k = n - k;   // symmetry
  uint32_t rv = n;
  uint8_t p = 2;
  for (uint8_t i = n-1; i > k; i--)
  {
    //  if ((0xFFFFFFFF / i) < rv) return 0;   // overflow detect...
    rv = (rv * i) / p;
    p++;
  }
  return rv;
}


//  works for n = 0..61 for all k
uint64_t combinations64(uint16_t n, uint16_t k)
{
  if ((k == 0) || (k == n)) return 1;
  if (k < (n-k)) k = n - k;     //  symmetry
  uint64_t rv = n;
  uint8_t p = 2;
  for (uint8_t i = n-1; i > k; i--)
  {
    //  overflow detect here ?
    rv = (rv * i) / p;
    p++;
  }
  return rv;
}


//  experimental - not exact but allows large values
//  float  (4 bits) works till n = 125    for all k
//  double (8 bits) works till n = 1020   for all k
double dcombinations(uint16_t n, uint16_t k)
{
  if ((k == 0) || (k == n)) return 1;
  if (k < (n-k)) k = n - k;  //  symmetry
  double rv = n;
  uint16_t p = 2;
  for (uint16_t i = n-1; i > k; i--)
  {
    rv *= i;
    rv /= p;
    p++;
  }
  return rv;
}


//  recursive (mind your stack and time)
//  works for n = 0..30 for all k
//  educational purpose
uint32_t rcombinations(uint16_t n, uint16_t k)
{
  if (k > (n-k)) k = n - k; // symmetry
  if (k == 0) return 1;
  return (n * rcombinations(n - 1, k - 1)) / k;
}


//  recursive
//  works for n = 0..61 for all k
//  educational purpose
uint64_t rcombinations64(uint16_t n, uint16_t k)
{
  if (k > (n-k)) k = n - k; // symmetry
  if (k == 0) return 1;
  return (n * rcombinations64(n - 1, k - 1)) / k;
}


//  very slow double recursive way by means of Pascals triangle.
//  works for n = 0..30 for all k  (but takes a lot of time)
//  educational purpose
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


/////////////////////////////////////////////////
//
//  EXPERIMENTAL
//
//  BIG SECTION
//
//  keep track of exponent myself in 32 bit unsigned integer
//  - can be extended to a 64 bit integer
//    however it already takes hours to calculate with 32 bits

/*

UNO
n           n!                  millis() from earlier version
-----------------------------------------
1           1.00000e0           0
10          3.62880e6           1
100         9.33262e157         7
1000        4.02386e2567        105
2000        3.31627e5735        231
4000        1.82880e12673       504
8000        5.18416e27752       1086
10000       2.84625e35659       1389
16000       5.11880e60319       2330
32000       1.06550e130270      4978
100000      2.82428e456573      17201
1000000     8.26379e5565708     206421 (3.5 minutes)
10000000                        an hour? too long...

ESP32  240MHz
n           n!                  millis() from earlier version
-----------------------------------------
1           1.00000e0           0
10          3.62880e6           0
100         9.33262e157         0
1000        4.02387e2567        8
10000       2.84626e35659       110
100000      2.82423e456573      1390
1000000     8.26393e5565708     16781
10000000    1.20242e65657059    196573 (3++ minutes)
100000000   1.61720e756570556   2253211
1000000000  9.90463e4270738226  25410726 (7++ hrs to detect overflow! :(


1           0
10          0.6
100         1.57
1000        2.567
10000       3.5659
100000      4.56573
1000000     5.565708
10000000    6.5657059
100000000   7.56570556

// largest found - exponent is approaching max_uint32_t - 4294967296
518678058!  4.1873547e4294967283  // break condition was hit...
next one should fit too
518678059!  2.1718890e4294967292

*/


void bigFactorial(uint32_t n, double &mantissa, uint32_t &exponent)
{
  exponent = 0;
  double f = 1;
  while (n > 1)
  {
    f *= n--;
    while (f > 1000000000)
    {
      f /= 1000000000;
      exponent += 9;
    }
  }
  while (f > 10)  //  fix exponent if needed.
  {
    f /= 10;
    exponent++;
  }
  mantissa = f;
}


//  Should work full range for n = 518678059, k = { 0..n }
//  and n > 518678059 => max k is definitely smaller ==> expect n+1 ==> k-15 at start
//  performance: low. depends on k.
//
//
//  for relative small k and large n (multiple orders of magnitude) one can get an estimate
//  P(n,k) ~  raw = log10(n - k/2) * k;
//            exponent = int(raw);
//            mantissa = pow(10, raw - int(raw));
void bigPermutations(uint32_t n, uint32_t k, double &mantissa, uint32_t &exponent)
{
  exponent = 0;
  double f = 1;
  for (uint32_t i = n; i > (n - k); i--)
  {
    f *= i;
    while (f > 1000000000)
    {
      f /= 1000000000;
      exponent += 9;
    }
  }
  while (f > 10)      //  fix exponent if needed.
  {
    f /= 10;
    exponent++;
  }
  mantissa = f;
}


void bigCombinations(uint32_t n, uint32_t k, double &mantissa, uint32_t &exponent)
{
  exponent = 0;
  if ((k == 0) || (k == n)) return;
  if (k < (n-k)) k = n - k;     //  symmetry

  double f = n;
  uint32_t p = 2;
  for (uint32_t i = n-1; i > k; i--)
  {
    f = (f * i) / p;
    p++;
    while (f > 1000000000)
    {
      f /= 1000000000;
      exponent += 9;
    }
  }
  while (f > 10)    //  fix exponent if needed.
  {
    f /= 10;
    exponent++;
  }
  mantissa = f;
}


////////////////////////////////////////////////////////////
//
//  EXPERIMENTAL 64 BIT (not tested)
//
void bigFactorial64(uint64_t n, double &mantissa, uint64_t &exponent)
{
  exponent = 0;
  double f = 1;
  while (n > 1)
  {
    f *= n--;
    while (f > 1000000000)  //  optimize - per 1e9 to save divisions.
    {
      f /= 1000000000;
      exponent += 9;
    }
  }
  while (f > 10)    //  fix exponent if needed.
  {
    f /= 10;
    exponent++;
  }
  mantissa = f;
}


void bigPermutations64(uint64_t n, uint64_t k, double &mantissa, uint64_t &exponent)
{
  exponent = 0;
  double f = 1;
  for (uint64_t i = n; i > (n - k); i--)
  {
    f *= i;
    while (f > 1000000000)
    {
      f /= 1000000000;
      exponent += 9;
    }
  }
  while (f > 10)    //  fix exponent if needed.
  {
    f /= 10;
    exponent++;
  }
  mantissa = f;
}


void bigCombinations64(uint64_t n, uint64_t k, double &mantissa, uint64_t &exponent)
{
  exponent = 0;
  mantissa = 0;
  if ((k == 0) || (k == n)) return;
  if (k < (n-k)) k = n - k;  //  symmetry

  double f = n;
  uint64_t p = 2;
  for (uint64_t i = n-1; i > k; i--)
  {
    f = (f * i) / p;
    p++;
    while (f > 1000000000)
    {
      f /= 1000000000;
      exponent += 9;
    }
  }
  while (f > 10)    //  fix exponent if needed.
  {
    f /= 10;
    exponent++;
  }
  mantissa = f;
}


//  -- END OF FILE --

