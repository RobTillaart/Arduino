
[![Arduino CI](https://github.com/RobTillaart/LineFormatter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LineFormatter/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LineFormatter/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LineFormatter/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LineFormatter/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LineFormatter/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LineFormatter.svg?maxAge=3600)](https://github.com/RobTillaart/LineFormatter/releases)


# LineFormatter

Arduino library to enhance the layout of tabular data on serial output,


# Description

LineFormatter is a wrapper class for Serial (and other streams) to enhance 
layout of tabular data.

The class intercepts the **TAB (\t)** characters printed and replaces them with spaces to
the next defined tab-position. These positions can be created with **addTab(pos)** 
for absolute positions and **addRelTab(n)** for relative positions.

Absolute tab positions must be added in **increasing** order as the class does not
check or sort the input. Adding the same tab position is not possible since 0.2.0.
Also position 0 will be ignored as tabStop.

The maximum number of tabs is defined by **MAX_TAB_STOPS** == 12 default. 
This value can be overruled by -D compile flag or edited in the LineFormatter.h file.

All tab positions can be cleared in one call by **clearTabs()**.
Since 0.2.0 the library also supports **removeTab(pos)** to remove a single tab.

The function **autoNewLine(n)** prints a newline after every n lines automatically. 
This makes it easier to count the lines in a table, e.g after every 10 lines.
Setting **n** to 0 disables this function.

The function **gotoPos(pos)** prints spaces until the cursor is on position **pos**.
If the current position is beyond **pos**, it does nothing (check the returned position!).
Besides for tabular data, this function can be used to make simple text based 
graphs, e.g. a sine wave.

The function **repeat(n, s, nl)** which repeats a character or a string n times.
This is followed by **nl** newlines which is zero by default.
**repeat()** is useful to make separator lines or to print several newlines at once.
A simple histogram is easy to make.

The function **setMaxLength(n)** to cut off (brute force, no intelligence) lines 
after n characters by injecting an extra newline. This prevents scrolling hundreds
of positions to the right. 
Setting the value to 0 results in no maximum line length.

Note: the maximum line length is 255 as all internal positions are 8 bit.
A 16 bit lineFormatter is planned for future (on request).


## Interface

```cpp
#include "LineFormatter.h"
```

#### Constructor

- **LineFormatter(Print\* stream = &Serial)** constructor.
Connects to a stream, default Serial.
- **reset()** reset internal variables to restart from default again.


#### Printing

- **size_t write(uint8_t c)** implements printing per character.
- **uint8_t gotoPos(uint8_t pos)** if position is smaller than pos, move to the right.
Returns the updated position.
- **void repeat(uint8_t n, char c, uint8_t newLine = 0)** repeat a char n times.
Typical used to create separation lines, or multiple line feeds.
The repeated string is optionally followed by a number of newlines.
- **void repeat(uint8_t n, const char\* str, uint8_t newLine = 0)** repeat a "string" n times.
The repeated string is optionally followed by a number of newlines.
Typical used to create separation lines.


#### Tab configuration

- **bool addTab(uint8_t n)** Add a tab at an absolute position. 
Returns true on success.
Note: no tab can be set on position 0 (return false)
Note: existing tabs will be ignored (return false)
- **bool addRelTab(uint8_t n)** Add a tab at a relative position. 
Returns true on success.
- **void clearTabs()** remove all the tabs.
- **bool removeTab(uint8_t pos)** remove a tab at given position.
Returns true if a tab exists at the position **pos**.
Returns false if no tab existed.
- **void tab(uint8_t n = 1)** print zero or more tabs, similar as e.g. "\t\t\t".

Note: 
Removing a tab is non-reversible (for now), so one cannot insert a removed tab stop again.
Also replacing a tab can only be done by clear all the tabs and reinsert the new ones.


#### Line configuration

- **void setMaxLength(uint8_t maxPos)** set the maximum line length - bold cut off.
Will be disabled when set to 0.
Note: maximum line length == 255.
- **uint8_t getMaxLength()** return max line length set.
- **void setAutoNewLine(uint8_t n = 1)** n = 0 switches autoNewLine off.
- **uint8_t getAutoNewLine()** returns number of newlines set before.


#### Miscellaneous

For debugging and other purposes there are the following functions:

- **uint8_t getPos()** returns current position.
- **void resetLineCount()** sets internal lineCounter to zero.
- **uint32_t getLineCount()** returns current line number (since last reset).
- **uint8_t getTabCount()** get the number of tab positions.
- **uint8_t getTabStop(uint8_t n)** returns the position of the n-th tab.
- **void printRuler(uint8_t length)** prints a dotted line with 5 and 10 markers, 
and # for tab positions.
Line is length long.


## Future

#### Must

- redo documentation misc/debug part

#### Should

- add sorting to **addTab()**  0.3.0?
  - insert sort - bit like in removeTab()
  - would allow dynamic inserting.
- add examples
- investigate correct working of maxPosition handling.
- investigate position 1 as tabStop?
  - 0 is ignored but 1 is ambiguous


#### Could

- 0.3.0 ?
  - addTab ==> addAbsoluteTab()
  - addRelTab ==> addRelativeTab()
  - error handling in addTab()?
- lineFormatter16
  - or just make it 16 bit version to allow tables more than 255 chars wide
  - uses more memory!
  - separate class as 8 bit is everywhere
- right alignment for numbers
- point alignment for floats
- investigate macros again.
- filter for unprintable characters,
  - isAscii() test
  - define replace char, default point?
  

#### Wont

- check if print interface is completely covered.
  - due to tab parsing it is, so no speed up.


