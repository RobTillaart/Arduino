
[![Arduino CI](https://github.com/RobTillaart/LineFormatter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
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
number of tabs is defined by **MAX_TAB_STOPS** == 10 default. This value canbe
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

### Debugging

For debugging purposes there are the following functions:
- **getPos()** - returns current position
- **resetLineCount()** - sets internal lineCounter to zero
- **getLineCount()** - returns current line number (since last reset)
- **getTabCount()** - get the number of tab positions added.
- **printRuler()** - prints a dotted line with 5 and 10 markers, and # for tab positions.

# Operational

See examples
