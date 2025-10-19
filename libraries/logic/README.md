
[![Arduino CI](https://github.com/RobTillaart/logic/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/logic/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/logic/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/logic/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/logic/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/logic.svg)](https://github.com/RobTillaart/logic/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/logic/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/logic.svg?maxAge=3600)](https://github.com/RobTillaart/logic/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/logic.svg)](https://registry.platformio.org/libraries/robtillaart/logic)


# logic

Arduino library for evaluation of larger logic conditions.


## Description

**Experimental**

This library is to evaluate larger or more complex logic conditions in a simple way.

The idea is as follows, if you have a slightly complex logic, you set a truth table 
in the logic object and evaluate the N boolean expressions against it. 

In the initial release N is 2, 3, 4 or 5, this makes the truth table 32 bits long so
an uint32_t can hold all 32 possible outcomes.

A truth table is represented as a number, an example explains the working.

Suppose we have three boolean expressions a, b and c. Furthermore we have a truth function
**eval(a,b,c)** which should return true if exact two out of three parameters are true.

|  NR  |  a  |  b  |  c  | eval(a,b,c) | neval(a,b,c) | notes |
|:----:|:---:|:---:|:---:|:-----------:|:------------:|:------|
|   0  |  0  |  0  |  0  |       0     |     0xFFFF   |  0xFFFF indicates false, no NR returned.
|   1  |  0  |  0  |  1  |       0     |     0xFFFF   |
|   2  |  0  |  1  |  0  |       0     |     0xFFFF   |
|   3  |  0  |  1  |  1  |       1     |        3     |
|   4  |  1  |  0  |  0  |       0     |     0xFFFF   |
|   5  |  1  |  0  |  1  |       1     |        5     |
|   6  |  1  |  1  |  0  |       1     |        6     |
|   7  |  1  |  1  |  1  |       0     |     0xFFFF   |

The value of the truth-table becomes the bits of the **eval(a,b,c)** function column, from top to bottom.
In the above case this value  == 0b00010110 == 0x16, so one calls **LOGIC.setTable(0b00010110)**
or the HEX equivalent **LOGIC.setTable(0x16)** to set the truth table.

- Calls to **eval(a,b,c)** will return **true** in case 3, 5 and 6, **false** otherwise.
- Calls to **neval(a,b,c)** will return 3,5,6 in case 3, 5 and 6, and 0xFFFF otherwise.

The **neval()** function can be used to differentiate between the cases that would return true.
In code one could use this for e.g. a switch case. 


### Related

- https://github.com/RobTillaart/logic
- https://github.com/RobTillaart/Troolean


### Tested

Tested examples on Arduino UNO R3


### Performance

See - logic_performance.ino

eval(n) => n parameters.
The timing does not include the evaluation of a, b etc. themselves.

|  function  |  AVR (us)  |  Notes  |
|:----------:|:----------:|:--------|
|  setTable  |       4    |  
|  eval(2)   |       8    |  
|  eval(3)   |       8    |
|  eval(4)   |      12    |
|  eval(5)   |      24    |
|  neval(2)  |       8    | 
|  neval(3)  |      12    |
|  neval(4)  |      12    |
|  neval(5)  |      20    |


## Interface

```cpp
#include "logic.h"
```

### Constructor

- **logic()** Constructor, sets default truth table to all false.
- **void setTable(uint32_t table)** set the table to use. 
Note this table can be changed runtime to another value.
- **uint32_t getTable()** return the set table.


### Eval

The eval(...) functions do a lookup in the configured truth table and 
if the combination equals 1, it returns true.

Note: the parameters must always be evaluated in the same order.

- **bool eval(bool a, bool b)**
- **bool eval(bool a, bool b, bool c)**
- **bool eval(bool a, bool b, bool c, bool d)**
- **bool eval(bool a, bool b, bool c, bool d, bool e)**


### Neval

neval = numeric eval.

The neval(...) functions do a lookup in truth table and if the combination equals 1, 
it returns its numeric value, and **0xFFFF** otherwise. 
This makes it useful if you need to handle different cases with the same N booleans expressions.

Note: the parameters must always be evaluated in the same order.

- **uint16_t neval(bool a, bool b)** Can return {0,1,2,3, 0xFFFF}
- **uint16_t neval(bool a, bool b, bool c)** Can return {0,1,2,3...7, 0xFFFF}
- **uint16_t neval(bool a, bool b, bool c, bool d)** Can return { 0,1,2,3, ... 15, 0xFFFF}
- **uint16_t neval(bool a, bool b, bool c, bool d, bool e)** Can return { 0,1,2,3, ... 31, 0xFFFF} 


### Index

Helper function made public.

- **uint16_t index(bool a, bool b)** Can return {0,1,2,3}
- **uint16_t index(bool a, bool b, bool c)** Can return {0,1,2,3...7}
- **uint16_t index(bool a, bool b, bool c, bool d)** Can return { 0,1,2,3, ... 15}
- **uint16_t index(bool a, bool b, bool c, bool d, bool e)** Can return { 0,1,2,3, ... 31} 


## Future

#### Must

- improve documentation

#### Should

- investigate how to support more than five bool expressions.
  - split in 2 LOGIC parts to handle 10? does that work? (would allow short circuit eval).
  - array of booleans + array of bits for the answers?
  - how many bool expressions max? 8? 10? 16?
  - 4 bytes support 5 expressions. 8 bytes will support 6... 32 bytes support 8. grows exponential.
  - or another strategy, sparse true list, uses uint16_t per true, scales linear.


#### Could

- optimize possible?
  - code size => one function with defaults = slower.
- runtime modify truth-table per "bit". e.g. setTT(int index, bool value)
- keep last value?
- true-count() = how many of the parameters are TRUE.
  - e.g. to test if at least N conditions are met
- add unit tests.

#### Wont

- **bool eval(bool a)** too simple? :)
- print interface? (overkill)
- define constants
  - AND == 0x0001  OR et al depends on # parameters
  
## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


