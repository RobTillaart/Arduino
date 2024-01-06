
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
data in a way not possible in the standard print library of the Arduino.

- **print64()** print **uint64_t** and **int64_t** 
- **sci()** generates in scientific format - exponent has step 1.
- **eng()** generates in engineering format - exponent has step 3.
- **scieng()** generates in exponential format - exponent has step 1 to 9.
- **toBytes()** generates KB MB GB etc.
- **hex()** generates hexadecimal output with leading zeros up to **uint64_t**.
- **bin()** generates binary output with leading zeros up to **uint64_t**.
- **toRoman()** generates a ROMAN representation of a (positive) number.
- **printInch(float inch, uint16_t step)** experimental.
- **printFeet(float feet)** experimental.
- **csi()** generates a comma separated integer for readability.

For the details, see sections below.

If a (generic) print format is missing, please open an issue.


#### Thread safety

Note the functions of this library all share an internal buffer, so the library is 
definitely **not** thread safe. 
Therefore one should copy / print the data (returned pointer) as fast as possible.

Thread-safe versions of these print functions might be made in the future.


## Interface

```cpp
#include "printHelpers.h"
```

The following functions are implemented:


#### print64()

- **char \* print64(int64_t value, uint8_t base = 10)**  converts a 64 bit integer 
number to a char array. 
The plus sign is not printed, neither are leading zero's.
Base 10 (DEC) and 16 (HEX) are supported and other bases up to 36 can be used.
Default base == 10 == decimal.
Note that negative numbers will always get a minus sign for any base.
Cast the number to uint64_t to suppress the sign.

- **char \* print64(uint64_t value, uint8_t base = 10)** converts a unsigned 64 bit 
int number to a char array. 
No sign is printed, neither are leading zero's. 
Base 10 (DEC) and 16 (HEX) are supported and bases up to 36 can be used.
Default base == 10 == decimal.


#### sci() eng() 

- **char \* sci(double value, uint8_t decimals)** converts a float or double to a 
char array. 
E.g. **print(sci(f, 4))** ==> results in **"6.7407E+21"**.
The existing Arduino print library only supports printing of floats and
doubles up to about 4E9 while the range of floats goes up to ~1E38. 
The smallest float values will often be printed as 0.00 while floats 
support down to about 1E-38 (subnormal even to 1E-45).
Existing (AVR) library functions **dtostrf()** has no scientific notation 
and **dtostre()** is limited to 7 decimals. These latter two are faster.
Values printed with **sci()** do look often pretty in column output.

- **size_t sci(Stream &str, double value, uint8_t decimals)** as above.
Prints directly to a stream, returning bytes printed.

- **char \* eng(double value, uint8_t decimals)** converts a float or double to a 
char array. 
E.g. print(eng(f, 4)) ==> results in "6.7407E+21".
Note the exponent created by **eng()** is always a multiple of 3.
Values printed with **eng()** do not always look pretty in column output.
This is due to the exponent power of 3. However its output translates easy to
thousands, millions, billions, and millis, micros, nano etc which are powers of 3.

- **char \* scieng(double value, uint8_t decimals, uint8_t exponentMultiple)** converts a 
float or double to a char array. 
**sci()** and **eng()** use the same underlying function called **scieng()** 
as the initial code for converting was almost identical.
Although not intended to be used directly, feel free to use it.
The last parameter **exponentMultiple** defines where the exponent is a multiple of.
For the **sci()** function this is 1, for the **eng()** function this is 3.
The **scieng()** function works for multiples from 1..9 for the exponent.
The usability of other values than 1 and 3 are not known.
Personally I like the multiple of 2 as I get 2 orders of magnitude in the
mantissa. This is e.g. useful for temperature Celsius or percentages.


#### toBytes()

- **char \* toBytes(double value, uint8_t decimals = 2)** converts a big number 
representing an amount of bytes to a shorter string usable for displaying.
The string uses official extensions.
The number of decimals is max 3:
    Example  3.292.528 ==> "3.140 MB" 

Value ranges supported are in steps of powers of 1024. 
These will all be shown in UPPERCASE so KB, MB etc.

|  Unit       |  abbrev.  |  size    |  Unit        |  abbrev.  |  size    |
|:-----------:|:---------:|:--------:|:------------:|:---------:|:--------:|
|  bytes      |     B     |  1024^0  |              |           |          |
|  kilobytes  |    KB     |  1024^1  |  zettabytes  |    ZB     |  1024^7  |
|  megabytes  |    MB     |  1024^2  |  yottabytes  |    YB     |  1024^8  |
|  gigabytes  |    GB     |  1024^3  |  xonaytes    |    XB     |  1024^9  |
|  terabytes  |    TB     |  1024^4  |  wekabytes   |    WB     |  1024^10 |
|  petabytes  |    PB     |  1024^5  |  vundabytes  |    VB     |  1024^11 |
|  exabytes   |    EB     |  1024^6  |  udabytes    |    UB     |  1024^12 |


Treda Byte is shortened as "TDB" and uses 2 chars to indicate the magnitude. 
That would take extra memory or slightly more complex code.  
As it is very seldom used, "official" support stops with UDA. 
Should be big enough for some time.

Note: max uint64_t 2^64 is in the order of exa or zetta bytes.

To have some support for the really big sizes the code uses lowercase for the next 8 levels:
treda sorta rinta quexa pepta ocha nena minga luma (1024\^13 ~~ 1024\^21)
To enable this patch the function in the **printHelpers.cpp** file.


#### hex() bin()

The default print() function of Arduino does not have leading zero's 
for **HEX** and **BIN**. 
This often causes a "broken" layout especially if one wants to print 
the output in columns or so.

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

Note: hex() does not print hex indicator like "0x" or "H" in front.

Note: bin() does not print bin indicator like "b" at the end.


#### toRoman()

https://en.wikipedia.org/wiki/Roman_numerals

A less used but well known print format are the Roman digits. 
The library function **toRoman()** will convert any number from 0..100 million into a Roman number.
The numbers 1..5000 ("official" range) are the well known UPPER case characters.

- **char \* toRoman(uint32_t value)** returns Roman string.

|  char  |  unit  |  notes      |
|:------:|:-------|:------------|
|   M    |  1000  |  M = Mille  |
|   D    |  500   |
|   C    |  100   |  C = Cent   |
|   L    |  50    |
|   X    |  10    |
|   V    |  5     |
|   I    |  1     |
|   N    |  0     |  extension  |


Note: The maximum length returned is 16 characters in the "official" supported range.
4888 == MMMMDCCCLXXXVIII.

Notes:
- value == 0 => N is not part of the "official" numbers but we need it.
- values < 0 are not supported (note parameter is unsigned)
- values between 5K-10K are extended with extra M chars.
- values 10K-100M are represented with lower case characters.
  This is not a standard, but it sort of works well.
- values > 100M return OVF == overflow. 
- There is no special 'subtract code' for 9000 to have a clear distinction between
  "official" and extended numbers.
- The number 4 is often written as IIII on clocks with Roman digits,
  although IV would be (more?) correct and therefore IV is used.
  The reason for IIII is that it is opposite of VIII giving a visual balance.


#### Distance feet inch

Experimental 0.4.1

- **char \* printInch(float inch, uint16_t step = 16)** prints a float inch distance default in sixteenth ```a b/16```.
The parameter step must be a power of 2 == 2, 4, 8, 16, 32, 64, 128.

- **char \* printFeet(float feet)** prints a float feet distance as
``` a'b"``` e.g. 4.5 feet prints as ```4'6"```


#### Comma Separated Integer

Experimental 0.4.3

When you are working with large numbers, more than lets say 6 digits.
With these numbers it is often difficult to see if it is 2 million something or 20 million something. 
A proven way to solve this is to print those large numbers in groups of 3 digits separated by comma's.
This improves the readability a lot and yes the price is more room needed on a display.
The comma is chosen as it is default thousands separator in Excel.

In the first version the separator is hardcoded a ",", in future it might be configurable.
This new printHelper function can work with both signed and unsigned up to 64 bit numbers.
Like all printHelper functions it uses a shared print buffer to keep memory usage low.

Example 192837465 becomes 192,837,465.

signed
- **char \* csi(int64_t n)** 
- **char \* csi(int32_t n)** 
- **char \* csi(int16_t n)** 
- **char \* csi(int8_t n)**

unsigned
- **char \* csi(uint64_t n)** 
- **char \* csi(uint32_t n)** 
- **char \* csi(uint16_t n)** 
- **char \* csi(uint8_t n)**


## Shared print buffer

The implementation of the function all use a shared buffer to hold the 
generated string. 
This is done to reduce the memory overhead of embedding static buffers. 
**Note this is not thread safe!**
In a coming release the functions will be able to pass a buffer to them 
to become more thread safe.

The size of this shared buffer is default 66 to be able to print a 64 bit 
integer in base 2. 
To save memory one can change this buffer size in the code or compile time 
by changing **PRINTBUFFERSIZE** in printHelpers.h.
Be aware that  **sci()** and **eng()** use the same buffer. 
These functions need about 10 bytes plus one bytes for every decimal used.
So for floats one need 15-20 bytes max, for doubles one need up to 30 bytes max.
In practice a size of 22 will work for most applications.

| PRINTBUFFERSIZE | BASE SUPPORTED | nr. decimals | Notes     |
|:---------------:|:--------------:|:------------:|:----------|
|     66          |    02 - 36     |    0 - 50    | (default) |
|     34          |    04 - 36     |    0 - 20    |
|     24          |    08 - 36     |    0 - 14    |
|     22          |    10 - 36     |    0 - 12    |
|     18          |    16 - 36     |    0 - 07    |

When functions are added, the recommended minimum size might increase.


## Future

#### Must

- check TODO's in the code

#### Should

- documentation
- improve readability of the code
  - em ==> exponentFactor?

#### Could

- investigate separators in **hex()**
  - space per 8, 4 or 2
- investigate thread safe version
  - pass char buffer as parameter (breaking)
  - could be the log10 pow version?
- optimize **char \* hex(uint8_t / uint16_t ...)**
- make this library a .h file only?
- PRINTHELPERS_LIB_VERSION
- is there need for Scientific or Engineering integers
  - 23.457e3 only positive powers
  - could be without float math
  - 4 versions (un)signed 32/64 ?

#### Wont

- add **oct()** along BIN, HEX
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


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

