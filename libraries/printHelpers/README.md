
[![Arduino CI](https://github.com/RobTillaart/printHelpers/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/printHelpers/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/printHelpers.svg?maxAge=3600)](https://github.com/RobTillaart/printHelpers/releases)



# printHelpers

Arduino library to help formatting data for printing


## Description

The printHelpers library contains a number of functions that help to print 
data in a way not possible in the standard print library of the Arduino.

The following functions are implemented:

- **print64(int64_t, base)**  converts a 64 bit integer number to a char array. 
The plus sign is not printed, neither are leading zero's.
Base 10 (DEC) and 16 (HEX) are supported and other bases up to 36 can be used.
Note that negative numbers will always get a minus sign for any base.
Cast the number to uint64_t to suppress the sign.

- **print64(uint64_t, base)** converts a unsigned 64 bit int number to a char array. 
No sign is printed, neither are leading zero's. 
Base 10 (DEC) and 16 (HEX) are supported and bases up to 36 can be used.

----

- **sci(double, decimals)** converts a float or double to a char array. 
E.g. print(sci(f, 4)) ==> results in "6.7407E+21".
The existing Arduino print library only supports printing of floats and
doubles up toabout 4E9 while the range of floats goes up to ~1E38. 
The smallest float values will often be printed as 0.00 while floats 
support down to about 1E-38 (subnormal even to 1E-45). 
Exisiting library functions **dtostrf()** has no scientific notation 
and **dtostre()** (AVR) is limited to 7 decimals.

- **eng(double, decimals)** converts a float or double to a char array. 
E.g. print(eng(f, 4)) ==> results in "6.7407E+21".
Note the exponent created by **eng()** is always a multiple of 3.

- **scieng(double, decimals, expmultiple)** converts a float or double to a char array. 
**sci()** and **eng()** use the same underlying function called **scieng()** 
as the initial code for converting was almost identical.
Although not intended to be used directly, one can use it. 
The last parameter expmultiple defines where the exponent is a multiple of.
For the **sci()** function this is 1, for the **eng()** function this is 3.
The **scieng()** function works for multiples from 1..9 for the exponent.
The usability of other values than 1 and 3 are not known.
Personally I like the multiple of 2 as I get 2 orders of magnitude in the
mantissa.

----

- **toBytes(val, decimals = 2)** makes from a big number 
representing an amount of bytes a shorter string usable for displaying.
The number of decimals is max 3
    Example  3.292.528 ==> "3.140MB" 
Value ranges supported are in steps of powers of 1024. 
These will all be shown in UPPERCASE so KB, MB etc.  
List of prefixes:
- kilo mega giga tera (1024\^4)
- peta exa zetta yotta (1024\^8)
- xona weka vunda uda (1024\^12)  
treda Byte == TDB uses 2 chars to indicate the magnitude so that would 
take extra memory of more complex code.  
As it is seldom used, "official" support stops with UDA. 
Should be big enough for some time.
To have some support the code uses lowercase for the next 8 levels:  
treda sorta rinta quexa pepta ocha nena minga luma (1024\^21 ~~ 10\^63)

----

More formatting functions might be added in the future.


## Shared buffer

The implementation of the function all use a shared buffer to hold the generated string. 
This is done to reduce the memory overhead of embedding static buffers. **Note this is not thread safe!**
In a coming release the functions will be able to pass a buffer to them to become more thread safe.

The size of this shared buffer is default 66 to be able to print a 64 bit integer in base 2. 
To save memory one can change this buffersize in the code or compile time by changing **PRINTBUFFERSIZE**.
Be aware that  **sci()** and **eng()** use the same buffer. 
These need about 10 bytes plus one bytes for every decimal used.
So for floats one need 15-20 bytes max, for doubles one need up to 30 bytes max.
In practice a size of 22 will work for most applications.

| PRINTBUFFERSIZE | BASE SUPPORTED | nr. decimals |
|:----:|:----:|:----:|
| 66 | 02 - 36 | 0 - 50 |(default)
| 34 | 04 - 36 | 0 - 20 |
| 24 | 08 - 36 | 0 - 14 |
| 22 | 10 - 36 | 0 - 12 |
| 18 | 16 - 36 | 0 - 07 |

When functions are added, the recommended minimum size might increase.


## Future

- Investigate the precision of **sci()** and **eng()**.
- Investigate performance of **sci()** and **eng()**.
- Add option to pass char buffer as parameter (improve threadsafe)
- Add more print helpers. 


## Operation

See examples

