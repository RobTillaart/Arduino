
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

The class intercepts the TAB characters printed and replaces them with spaces to
the next defined tab-position. These positions can be created with **addTab(n)** 
for absolute positions and **andRelTab(n)** for relative positions. 

Absolute tab positions must be added in increasing order as the class does not
check the input. Also adding same value twice is not checked for. The maximum
number of tabs is defined by **MAX_TAB_STOPS** == 12 default. This value can be
overruled by -D compile flag or edited in the LineFormatter.h file.

Tab positions can be cleared by **clearTabs()**. This removes all tabs in one call.

The function **autoNewLine(n)** prints a newline after every n lines. This makes 
it easier to count the lines in a table. Setting **n** to 0 disables this function.

The function **gotoPos(n)** prints spaces until the cursor is on position **n**. 
Besides for tabular data, this function can be used to make simple text based 
graphs, e.g. a histogram (see examples).

The function **repeat(n, s, nl)** which repeats a certain character or a string n times.
This is followed by **nl** newlines which is zero by default.
**repeat()** is useful to make separator lines or to print several newlines at once.

The function **setMaxLength(n)** to cut off (brute force, no intelligence) lines 
after n characters by injecting an extra newline. This prevents scrolling hundreds
of positions to the right e.g. when copying a file from disk to Serial. 
Setting the value to 0 results in no maximum line length.
Note: the maximum value is 255.


## Interface

- **LineFormatter(Print\* stream = &Serial)** constructor
- **reset()** reset internal variables to start over again.


#### Printing

- **size_t write(uint8_t c)** implements print.
- **uint8_t gotoPos(uint8_t pos)** if position is smaller than pos, move to the right.
- **void repeat(uint8_t n, char c, uint8_t newLine = 0)** repeat a char n times.
- **void repeat(uint8_t n, const char\* str, uint8_t newLine = 0)** repeat a "string" n times.


#### Tab configuration

- **bool addTab(uint8_t n)** Add a tab at an absolute position. Returns true on success.
- **bool addRelTab(uint8_t n)** Add a tab at a relative position. Returns true on success.
- **void clearTabs()** remove all the tabs.
- **void tab(uint8_t n = 1)** print zero or more tabs, similar as e.g. "\t\t\t"


#### Line configuration

- **void setMaxLength(uint8_t maxPos)** set the maximum line length - bold cut off.
- **uint8_t getMaxLength()** return max line length set.
- **void setAutoNewLine(uint8_t n)** n = 0 switches autoNewLine off.
- **uint8_t getAutoNewLine()** returns number of newlines.


### Debugging

For debugging purposes there are the following functions:

- **uint8_t getPos()** returns current position.
- **void resetLineCount()** sets internal lineCounter to zero.
- **uint16_t getLineCount()** returns current line number (since last reset).
- **uint8_t getTabCount()** get the number of tab positions added.
- **uint8_t getTabStop(uint8_t n)** returns the n-th tab position.
- **void printRuler()** prints a dotted line with 5 and 10 markers, and # for tab positions.


# Operational

See examples


## Future

#### must
- improve documentation

#### should
- add examples
- add **rmTab(position)**

#### could
- set defaults for functions

#### Wont
- check if print interface is completely covered.
  - due to tab parsing it is, so no speed up.


