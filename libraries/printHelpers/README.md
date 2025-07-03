
[![Arduino CI](https://github.com/RobTillaart/printHelpers/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/printHelpers/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/printHelpers/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/printHelpers/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/printHelpers/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/printHelpers.svg)](https://github.com/RobTillaart/printHelpers/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/printHelpers/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/printHelpers.svg?maxAge=3600)](https://github.com/RobTillaart/printHelpers/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/printHelpers.svg)](https://registry.platformio.org/libraries/robtillaart/printHelpers)


# printHelpers

Arduino library to help formatting data for printing.


## Description

The printHelpers library contains a number of functions that help to print
data in a way not supported in the standard print library of the Arduino.

- **char \* print64()** returns a string for **uint64_t** and **int64_t**.
- **char \* sci()** returns a string in scientific format - exponent has step 1.
- **char \* eng()** returns a string in engineering format - exponent has step 3.
- **char \* scieng()** returns a string in exponential format - exponent has step 1 to 9.
- **char \* toBytes()** returns a string in KB MB GB etc.
- **char \* hex()** returns hexadecimal output with **leading zeros** up to **uint64_t**.
- **char \* bin()** returns binary output with **leading zeros** up to **uint64_t**.
- **char \* toRoman()** returns a ROMAN representation of a number.
- **char \* printInch(float inch, uint16_t step)** returns a string e.g. 5 7/8".
- **char \* printFeet(float feet)** returns a string e.g. 7"4'
- **char \* csi()** returns a comma separated integer for readability e.g. 3,254,152.
- **char \* fraction()** returns a fraction representation of a double/float e.g. 355/113.

For the details, see sections below.

As always, feedback is welcome.
If a (generic) print format is missing, please open an issue.


### PRINTBUFFERSIZE

The functions of this library share the same internal char array / buffer
to hold the generated data.
The reason for a shared buffer is that the output still exists after the function call. 
Giving every function a static buffer would increase footprint (RAM).
**NOTE: This is not thread safe!**
See section about thread safety below.

The library defines **PRINTBUFFERSIZE** = 66 for this in the printHelpers.h file.
With this size one is able to print a 64 bit integer in base 2.

One can reduce the footprint by using a smaller **PRINTBUFFERSIZE** e.g. 22,
however it would limit especially the base used in **print64()**.
Making the buffer even smaller limits e.g. the number of decimals shown
which might be completely valid as it depends on your requirements.

Note that **sci()** and **eng()** (imho most important functions) use the same buffer.
These functions need about 10 bytes plus one bytes for every decimal used.
So for floats one need 15-20 bytes max, for doubles one need up to 30 bytes max.
In practice a size of 22 will work for most applications.


#### Table PRINTBUFFERSIZE vs base print64()

| PRINTBUFFERSIZE | BASE SUPPORTED | nr. decimals | Notes     |
|:---------------:|:--------------:|:------------:|:----------|
|     66          |    02 - 36     |    0 - 50    | (default) |
|     34          |    04 - 36     |    0 - 20    |
|     24          |    08 - 36     |    0 - 14    |
|     22          |    10 - 36     |    0 - 12    |
|     18          |    16 - 36     |    0 - 07    |

When functions are added, the recommended minimum size might increase.


### 0.5.0 Thread safe

As stated above, the functions share the same internal char array / buffer.
So **printHelpers.h** is definitely **not** thread safe.
Therefore one should copy / print the data (returned pointer) as fast as possible,
or at least before another function from this library is called.

Since 0.5.0 a thread-safe version of this library is under development.
To use the threadsafe version one need to include **printHelpersMT.h**.
The implementation is quite different but the core code is identical.
More details see sections below and in the code.

The thread safe version is minimally tested, feedback is welcome.


### Related

- https://github.com/RobTillaart/Fraction
- https://github.com/RobTillaart/lineFormatter for tabular formatting.
- https://github.com/RobTillaart/PrintCharArray captures data in a char array buffer.
- https://github.com/RobTillaart/PrintSize counts length of a number of print commands. (right alignment)
- https://github.com/RobTillaart/PrintString captures data in a String.


## Interface printHelpers.h

```cpp
#include "printHelpers.h"
```

The following functions are implemented:


### print64()

- **char \* print64(int64_t value, uint8_t base = 10)** converts a 64 bit integer
number to a char array.
The plus sign is not printed, neither are leading zero's.
Base 10 (DEC) and 16 (HEX) are supported and other bases to 36 can be used.
Default base == 10 == decimal.
Note that negative numbers will always get a minus sign for any base.
Cast the number to uint64_t to suppress the sign.

- **char \* print64(uint64_t value, uint8_t base = 10)** converts a unsigned 64 bit
integer number to a char array.
No sign is printed, neither are leading zero's.
Base 10 (DEC) and 16 (HEX) are supported and bases up to 36 can be used.
Default base == 10 == decimal.


### sci() eng()

The existing Arduino print library only supports printing of floats and
doubles up to about 4E9 while the range of floats goes up to ~1E38.
The smallest float values will often be printed as 0.00 while floats
support down to about 1E-38 (subnormal even to 1E-45).
The existing (AVR) library function **dtostrf()** has no scientific notation
and **dtostre()** is limited to 7 decimals. These latter two are faster.

- **char \* sci(double value, uint8_t decimals)** converts a float or double to a
char array.
E.g. **print(sci(f, 4))** ==> results in **"6.7407E+21"**.
Values printed with **sci()** do look often pretty in column output.

- **size_t sci(Stream &str, double value, uint8_t decimals)** as above.
Prints directly to a stream, returning bytes printed.

- **char \* eng(double value, uint8_t decimals)** converts a float or double to a
char array.
E.g. print(eng(f, 4)) ==> results in "6.7407E+21".
Note the exponent created by **eng()** is always a multiple of 3.
Values printed with **eng()** do not always look pretty in column output.
This is due to the exponent power of 3. However its output translates easy to
thousands, millions, billions, and millis, micros, nano etc. which are powers of 3.

- **char \* scieng(double value, uint8_t decimals, uint8_t exponentMultiple)** converts a
float or double to a char array.
**sci()** and **eng()** use the same underlying function called **scieng()**
as the initial code for converting is almost identical.
Although not intended to be used directly, feel free to use it.
The last parameter **exponentMultiple** defines where the exponent is a multiple of.
For the **sci()** function this is 1, for the **eng()** function this is 3.
The **scieng()** function works for multiples from 1..9 for the exponent.
The usability of other values than 1 and 3 are not known.
Personally I like the multiple of 2 as I get 2 orders of magnitude in the
mantissa. This is e.g. useful for temperature Celsius or percentages.

Note: if the parameter **exponentMultiple** is set to zero, 
the function **scieng()** will print e.g. x.xxxxxE+00, with the exponent set to zero.
Although this is technically a bug it could be a feature for someone.
So I decided to leave this behaviour in the code.


### toBytes()

- **char \* toBytes(double value, uint8_t decimals = 2)** converts a big number
representing an amount of bytes to a shorter string usable for displaying.
The string uses official extensions.

The number of decimals is max 3, example: 3.292.528 ==> "3.140 MB"

Value ranges supported are in steps of powers of 1024.
These abbreviations will all be shown in UPPERCASE so KB, MB etc.

|  Unit       |  abbrev.  |  size    |  Unit        |  abbrev.  |  size    |
|:-----------:|:---------:|:--------:|:------------:|:---------:|:--------:|
|  bytes      |     B     |  1024^0  |              |           |          |
|  kilobytes  |    KB     |  1024^1  |  zettabytes  |    ZB     |  1024^7  |
|  megabytes  |    MB     |  1024^2  |  yottabytes  |    YB     |  1024^8  |
|  gigabytes  |    GB     |  1024^3  |  xonaytes    |    XB     |  1024^9  |
|  terabytes  |    TB     |  1024^4  |  wekabytes   |    WB     |  1024^10 |
|  petabytes  |    PB     |  1024^5  |  vundabytes  |    VB     |  1024^11 |
|  exabytes   |    EB     |  1024^6  |  udabytes    |    UB     |  1024^12 |

Most applications will only use the first 5 entries, so there is some room
to optimize the code-size of this function.


#### Bigger

Treda Byte is officially shortened as "TDB" and uses 2 chars to indicate the magnitude.
That would take extra memory or slightly more complex code.
As it is very seldom used, "official" support stops with UDA.
Should be big enough for some time.

Note: max uint64_t == 2^64 is in the order of exa or zetta bytes. 
And a 4 byte float can represent up to ~100 udabytes range (1024^12 == 10^36)

To have some support for the really big sizes the code uses lowercase for the next 8 levels:
To enable this patch the function in the **printHelpers.cpp** file.

|  Unit       |  abbrev.  |  size     |  Unit       |  abbrev.  |  size     |
|:-----------:|:---------:|:---------:|:-----------:|:---------:|:---------:|
|  tredabytes |    tB     |  1024^13  |  ochabytes  |    oB     |  1024^18  |
|  sortabytes |    sB     |  1024^14  |  nenabytes  |    nB     |  1024^19  |
|  rintabytes |    rB     |  1024^15  |  mingabytes |    mB     |  1024^20  |
|  quexabytes |    qB     |  1024^16  |  lumabytes  |    lB     |  1024^21  |
|  peptabytes |    pB     |  1024^17  |             |           |           |

Note that from the ZETTA prefix all higher prefixes are starting with the
previous letter of the alphabet ZYXWVUtsrqponml


### hex() bin()

The default print() function of Arduino does not have leading zero's
for **HEX** and **BIN**.
This often causes a "broken" layout especially if one wants to print
the output in columns.

To solve this the following functions are added that will generate a
constant length char array.

- **char \* hex(uint64_t value, uint8_t digits = 16)**
- **char \* hex(uint32_t value, uint8_t digits = 8)**
- **char \* hex(uint16_t value, uint8_t digits = 4)**
- **char \* hex(uint8_t value, uint8_t digits = 2)**
- **char \* bin(uint64_t value, uint8_t digits = 64)**
- **char \* bin(uint32_t value, uint8_t digits = 32)**
- **char \* bin(uint16_t value, uint8_t digits = 16)**
- **char \* bin(uint8_t value, uint8_t digits = 8)**

Note: Data types not supported, must be cast to an supported type.

Note: There is overlap between **hex(value)** and **print64(value, HEX)**.
The latter does not produce the leading zero's or fixed length output.

Note: **hex()** does not print hex indicator like "0x" or "H".

Note: **bin()** does not print bin indicator like "0b" or "B".


### toRoman()

https://en.wikipedia.org/wiki/Roman_numerals

A less used but well known print format are the Roman digits.
The library function **toRoman()** will convert any number from 0..100 million into a Roman number.
The numbers 1..5000 ("official" range) are the well known UPPER case characters.

- **char \* toRoman(int32_t value)** returns Roman string.

|  char  |  unit  |  notes      | |  char  |  unit    |
|:------:|-------:|:------------|-|:------:|---------:|
|   M    |  1000  |  M = Mille  | |   m    |  10^7    |
|   D    |  500   |             | |   d    |  5.10^6  |
|   C    |  100   |  C = Cent   | |   c    |  10^6    |
|   L    |  50    |             | |   l    |  5.10^5  |
|   X    |  10    |             | |   x    |  10^5    |
|   V    |  5     |             | |   v    |  5.10^4  |
|   I    |  1     |             | |   i    |  10^4    |
|   N    |  0     |  extension  | |        |          |


Note: The maximum length returned is 16 characters in the "official" supported range.

example:
- 4888 == MMMMDCCCLXXXVIII.
- 12345678 == mccxxxivMMMMMDCLXXVIII (unofficial).

Deviations from the standard:
- value == 0 => N is not part of the "official" numbers but useful.
- values between 5K-10K are extended with extra M chars.
- values 10K-100M are represented with lower case characters.
  This is not a standard, but it sort of works well.
- values > 100M return OVF == overflow.
- There is no special 'subtract code' for 9000 to have a clear distinction between
  "official" and extended numbers.
- The number 4 is often written as IIII on clocks with Roman digits,
  although IV would be (more?) correct and therefore IV is generated.
  The reason for IIII in a clock face is that it is opposite of VIII giving a visual balance.
- Since 0.4.6 negative numbers will have a - sign in front.

There is no **roman2intger()** function (yet).


### Distance feet inch

Note that both inch and feet should be positive or zero.
A negative value will return an error ("E-NEG").

- **char \* printInch(float inch, uint16_t step = 16)** prints a float inch distance 
default in sixteenth ```a b/16```.
The parameter step must be a power of 2 == 2, 4, 8, 16, 32, 64 .. 32768.

- **char \* printFeet(float feet)** prints a float feet distance as
``` a'b"``` e.g. 4.5 feet prints as ```4'6"```.


### Comma Separated Integer

Experimental 0.4.3

When you are working with large numbers, more than lets say 6 digits, readability becomes an issue.
With these numbers it is often difficult to see if it is 2 million something or 20 million something.
A proven way to solve this is to print those large numbers in (fixed) groups of 3 digits separated by comma's.
This improves the readability a lot, and yes, the price is more room needed on a display.

The comma is chosen as default thousands separator, however since 0.5.0 
one can set the separator to any character e.g. to underscore or a point.

This function can work with both signed and unsigned up to 64 bit numbers.
Like all printHelper functions it uses the shared print buffer.

Example **csi(192837465)** becomes "192,837,465".

signed:
- **char \* csi(int64_t value, char separator = ',')**
- **char \* csi(int32_t value, char separator = ',')**
- **char \* csi(int16_t value, char separator = ',')**
- **char \* csi(int8_t value, char separator = ',')**

unsigned:
- **char \* csi(uint64_t value, char separator = ',')**
- **char \* csi(uint32_t value, char separator = ',')**
- **char \* csi(uint16_t value, char separator = ',')**
- **char \* csi(uint8_t value, char separator = ',')**


### Fraction

Experimental 0.4.5, based upon Fraction class - https://github.com/RobTillaart/Fraction

The precision is hard set to absolute 1e-6.
The fraction will have a numerator and denumerator in the range 1..99999.
Note that as floats only have 7 significant digits the precision varies
especially for numbers above 1 (as decimal part eats up significant digits).

The algorithm is primary meant for values between 0 and 1 however any float 
will be processed. The algorithm does not always come up with the best 
possible fraction (balance performance quality).

Time is not constant, e.g. **fraction(PI)** takes about 620 us on an Arduino UNO 16 MHz.

- **char \* fraction(double value)** approach the value with a fraction like n / d.
- **char \* fraction(double value, uint16_t denominator)** choose the denominator.
Note it will be reduced if possible e.g. 6/8 => 3/4

If you have a faster or more accurate algorithm or both please let me know
and open an issue.

----

## Interface printHelpersMT.h

**EXPERIMENTAL 0.5.0**

This MT ( == MultiThreading) version of the library implements classes for the printHelper functions.
These are short living classes that do not share a buffer, so they should be thread safe.

Warning: the internal char buffer does not exist any more when the objects go out of scope.
So one must copy its contents before it goes out of scope.

The description is identical to functions above, however there might be unknown behaviour 
details that differ. So use with care.

This version needs more testing / verification e.g. in RTOS.

```cpp
#include "printHelpersMT.h"
```

### print64()

- **print64(int64_t value, uint8_t base = 10)**
- **print64(uint64_t value, uint8_t base = 10)**

### sci() eng()

- **scieng(double value, uint8_t decimals, uint8_t em = 1)**
- **sci(double value, uint8_t decimals)**
- **eng(double value, uint8_t decimals)**

### toBytes()

- **toBytes(double value, uint8_t decimals = 2)**

### hex() bin()

- **hex(uint64_t value, uint8_t digits = 16)**
- **hex(uint32_t value, uint8_t digits = 8)**
- **hex(uint16_t value, uint8_t digits = 4)**
- **hex(uint8_t value, uint8_t digits = 2)**
- **bin(uint64_t value, uint8_t digits = 64)**
- **bin(uint32_t value, uint8_t digits = 32)**
- **bin(uint16_t value, uint8_t digits = 16)**
- **bin(uint8_t value, uint8_t digits = 8)**

### toRoman()

- **toRoman(int32_t value)**

### Distance feet inch

- **printInch(float inch, uint16_t step = 16)**
- **printFeet(float feet)**

### Comma Separated Integer

- **csi(int64_t value, char separator = ',')**
- **csi(int32_t value, char separator = ',')**
- **csi(int16_t value, char separator = ',')**
- **csi(int8_t value, char separator = ',')**
- **csi(uint64_t value, char separator = ',')**
- **csi(uint32_t value, char separator = ',')**
- **csi(uint16_t value, char separator = ',')**
- **csi(uint8_t value, char separator = ',')**

### Fraction

- **fraction(double value)**
- **fraction(double value, uint32_t denominator)**

----

## Future

#### Must

- check TODO's in the code / documentation
- improve documentation

#### Should

- test and verify printHelpersMT
- implement printHelpersMT.h unit tests
  - rewrite of current needed
- improve readability of the code
  - em ==> exponentFactor?

#### Could

- investigate **bin(float)** to dump floats?
  - "sign, mantissa, exponent bits"
  - like this "s0 m0111010 e100010" (right length)
- investigate separators in **hex()**
  - space per 8, 4 or 2
- optimize **char \* hex(uint8_t / uint16_t ...)**
- base64 representation
  - base64(float)
  - base64(double)
  - base64(any type) 
  - type debase64(type, string);
  - needs investigation
- rename sci() to **scientific()** for readability?
- rename eng() to **engineering()** for readability?
- implement **roman2intger()**?

#### Wont

- is there need for Scientific or Engineering integers?
  - this just works! (OK some loss of precision.
- add **oct()** along BIN, HEX
  - rarely used.
- add **float()** as Arduino limits floats to "MAXLONG" by code.
  - use dtostrf() - is that portable?
  - use sci() or eng()
- add **base(value, digits, base)** for any base > 1.
  - only upon request.
- investigate separators in **bin()**
  - point or space, per 8 or 4 or 2
  - ==> printBuffer too small for bin(64) ==> need 75-100 bytes.
- Investigate performance and accuracy
  - **sci()** and **eng()**.
  - investigate sci() version based upon use of log()
  - done => see examples.
- investigate group size in csi() ?
  - not or very very rarely needed

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

