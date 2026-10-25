
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

The idea is as follows, if you have a slightly complex logic, you create a truth table
in the logic object and evaluate the N boolean expressions against it.

In the initial release N is 2, 3, 4 or 5, this makes the truth table 4, 8, 16 or 32 entries.
A straightforward implementation would create an array of all possible combinations and
a result boolean for those combinations. This would use at least 32 bytes if the booleans
are combined in a byte per entry.

The logic object converts up to 5 booleans to an integer, which is used as the bit 
index in an uint32_t (representing the truth table). 
This uint32_t can hold all 32 possible outcomes as a bit pattern.
So the logic object uses only 4 bytes for up to 5 booleans == 32 entries.

The internal truth table is represented as a number, an example explains the working.

Suppose we have three boolean expressions a, b and c. Furthermore we have a truth function
**eval(a,b,c)** which must return true if exact two out of three parameters are true.

|  NR  |  c  |  b  |  a  | eval(a,b,c) | neval(a,b,c) | notes |
|:----:|:---:|:---:|:---:|:-----------:|:------------:|:------|
|   0  |  0  |  0  |  0  |       0     |     0xFFFF   |  0xFFFF indicates false, no NR returned.
|   1  |  0  |  0  |  1  |       0     |     0xFFFF   |
|   2  |  0  |  1  |  0  |       0     |     0xFFFF   |
|   3  |  0  |  1  |  1  |       1     |        3     |
|   4  |  1  |  0  |  0  |       0     |     0xFFFF   |
|   5  |  1  |  0  |  1  |       1     |        5     |
|   6  |  1  |  1  |  0  |       1     |        6     |
|   7  |  1  |  1  |  1  |       0     |     0xFFFF   |

The value of the truth-table becomes the bits of the **eval(a,b,c)** function column, from bottom to top.
In the above case this value  == 0b01101000 == 0x68, so one calls **LOGIC.setTable(0b01101000)**
or the HEX equivalent **LOGIC.setTable(0x68)** to set the truth table.
Or **LOGIC.setTable( (1 << 3) | (1 << 5) | (1 << 6) )**

- Calls to **eval(a,b,c)** will return **true** in case 3, 5 and 6, **false** otherwise.
- Calls to **neval(a,b,c)** will return 3,5,6 in case 3, 5 and 6, and 0xFFFF otherwise.

The **neval()** function can be used to differentiate between the cases that would return true.
In code one could use the return value e.g. a switch case.

Note: A call to **eval()** can be read as **eval(1 + 0 + 4 + 8 + 0)**,
every bit is the next power of 2 or zero.


Since 0.2.0 one can also call **LOGIC.add(idx)** and/or **LOGIC.remove(idx)**
This can be more convenient to configure the logic object, and allows runtime 
changes to the truth table.

```
LOGIC.add(3);
LOGIC.add(5);
LOGIC.add(6);

or

LOGIC.setTable(0);  //  start with all false
LOGIC.add(index(true, true, false));
LOGIC.add(index(true, false, true));
LOGIC.add(index(false, true, true));

or

LOGIC.setTable(0xFF);  //  start with all true
LOGIC.remove(index(true, true, false));
LOGIC.remove(index(true, false, true));
LOGIC.remove(index(false, true, true));
```

Runtime changes 



Feedback as always is welcome.


### Breaking change 0.2.0

In version 2.0, the internal storage is reversed to make some new functions possible.
Most important one can mix **eval()** calls with different number of parameters,
implicitly making the other parameters **false**.

Furthermore, version 0.2.0 allows to **add(index)** and **remove(index)** which
can be used with the index function e.g. **add(index(true, false, true))**.
This allows to create truth table by example, or change the truth table
runtime by adding and removing selected cases.


### Related

- https://github.com/RobTillaart/bitHelpers
- https://github.com/RobTillaart/logic
- https://github.com/RobTillaart/Troolean


### Tested

Tested examples on Arduino UNO R3


### Performance

Run **logic_performance.ino** for actual numbers for your board.

eval(n) => n parameters.
The timing in us does not include the evaluation of a, b etc. themselves.

|  function  |  AVR 0.1.0 |  Notes  |
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


### Create truth table

- **void setTable(uint32_t table)** set the truth table to use.
Note the truth table can be changed runtime to any another value.
To set all entries to true one can use **setTable(-1)**.
- **uint32_t getTable()** return the internal truth table.
Can be used to temporary store a previous table before a number of 
runtime changes is applied.
- **void add(uint8_t idx)** add a single option to the truth table.
- **void remove(uint8_t idx)** removes a single option from the truth table.

**add()** and **remove()** can be used in combination with the helper
function **index()** to fill and change the truth table **run time**.

```
LGC.setTable(0xF5C3);
+
LGC.add(index(true, true, false, true));
+ somewhat later remove that entry.
LGC.remove(index(true, true, false, true));
```

One can set all values to false and add the true entries.
```
LGC.setTable(0);  //  default
+
LGC.remove(index(true, true, false, true));
```

One can set all values to true and remove the false entries.
```
LGC.setTable(-1);
+
LGC.remove(index(true, true, false, true));
```


### Eval

The **eval(...)** functions do a lookup in the configured truth table and
if the combination equals 1, it returns true.

Note: the parameters **must** always be evaluated in the same order.

- **bool eval(bool a, bool b)**
- **bool eval(bool a, bool b, bool c)**
- **bool eval(bool a, bool b, bool c, bool d)**
- **bool eval(bool a, bool b, bool c, bool d, bool e)**


### Neval

neval = numeric eval.

The **neval(...)** functions do a lookup in the truth table and if the combination equals 1,
it returns its numeric value, or **0xFFFF** otherwise.
This makes it useful if you need to handle different true cases with the same N booleans expressions.

Note: the parameters **must** always be evaluated in the same order.

- **uint16_t neval(bool a, bool b)** Can return {0,1,2,3, 0xFFFF}
- **uint16_t neval(bool a, bool b, bool c)** Can return {0,1,2,3 ... 7, 0xFFFF}
- **uint16_t neval(bool a, bool b, bool c, bool d)** Can return { 0,1,2,3, ... 15, 0xFFFF}
- **uint16_t neval(bool a, bool b, bool c, bool d, bool e)** Can return { 0,1,2,3, ... 31, 0xFFFF}


### CountTrue

Count the parameters True, no separate countFalse() counter.
Convenience function.

- **uint8_t countTrue(bool a, bool b)**
- **uint8_t countTrue(bool a, bool b, bool c)**
- **uint8_t countTrue(bool a, bool b, bool c, bool d)**
- **uint8_t countTrue(bool a, bool b, bool c, bool d, bool e)**


### Index

Helper function.

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
    works only if eval_1(...) == true is needed for all eval_2(...)
  - array of booleans + array of bits for the answers?
  - how many bool expressions max? 8? 10? 16? memory grows exponential!
    - 4 bytes support 5 expressions (== current implementation)
    - 8 bytes will support 6 expressions (2x uint32_t).
    - 16 bytes will support 7 expressions.
    - 32 bytes support 8 expressions.
    - is more than 8 realistic?
  - or another strategy, sparse true list, scales linear.
    - use uint8_t per true = 8 expressions
    - use uint16_t per true = 16 expressions (65536 virtual entries)

#### Could

- optimize possible?
- investigate how to handle "don't care's" ?
- rename neval() to int8_t numEval() {0...N, -1}
- dumpTable(size?) dumps all entries e.g. as 0 0 0 => 1
  - char_ptr dumpEntry(idx) ?
- extend unit tests.
- is an a,b,c == integer version possible?
  
#### Wont

- code size => one function with defaults = slower.
- create a logic6/logic7/logic8 class? (on request)
- **bool eval(bool a)** too simple? :)
- print interface? (overkill)
- define constants
  - AND == 0x0001  OR et al depends on # parameters
- add a table in the constructor? (one call less).
- make **setTable(0)** default. nope, keep it explicit.

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


