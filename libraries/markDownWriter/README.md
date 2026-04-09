
[![Arduino CI](https://github.com/RobTillaart/markDownWriter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/markDownWriter/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/markDownWriter/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/markDownWriter/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/markDownWriter/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/markDownWriter.svg)](https://github.com/RobTillaart/markDownWriter/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/markDownWriter/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/markDownWriter.svg?maxAge=3600)](https://github.com/RobTillaart/markDownWriter/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/markDownWriter.svg)](https://registry.platformio.org/libraries/robtillaart/markDownWriter)


# markDownWriter

Arduino library for creating simple mark down content.


## Description

**Experimental, Work In Progress**

This library is written to be able to generate simple mark down reports.

The library supports only a part of the mark down functionality, including headers on several levels, bold and italic styles, the creation of tables 
and external links. 

The markDownWriter prints to a stream, default **Serial**, bit other streams
like **file**, **SD**, **socket** are possible (not tested yet).
The writes are buffered similar as in my XMLWriter library.
Performance measurements with XML showed a serious performance gain.
Only point of attention is flushing the stream at the end.

The library is work in progress and not all functionality works perfect,
but is good enough to get started for now.

Core reason to write this library was to speed up creation of tables
with measurements.

If needed, additional functionality or improvements will be made on request.

As always feedback is welcome.


### Print interface

The markDownWriter implements the print interface allowing to print 
all data types, including floats with decimals, signed and unsigned integers.

```
MDW.header(3, "kitchen");

MDW.print("TempC: ");
MDW.println(temperature, 1);
```

### Related

- https://www.markdownguide.org/basic-syntax/ reference
- https://github.com/RobTillaart/markDownWriter simple mark down content.
- https://github.com/RobTillaart/XMLWriter an XML format writer.
- https://github.com/RobTillaart/lineFormatter tabular output on Serial.


### Tested

Tested on Arduino UNO R3 with demo sketches.


## Interface

```cpp
#include "markDownWriter.h"
```

### Constructor

- **markDownWriter(Print \* stream = &Serial, uint8_t bufferSize = 10)** constructor with 
default stream. Other streams e.g. SD, socket etc. are possible.
By setting the bufferSize to 0 or 1 there will be no buffering.
Max bufferSize == 250
- **~markDownWriter()** destructor.
- **bool reset()** reset internals.


### Headers

- **void header(uint8_t level, const char \* text)** header at level n.
Note that level 1 is largest font, and MarkDown supports up to level 6.
- **void title(const char \* str)** wrapper for header level 1.
- **void chapter(const char \* str)** wrapper for header level 2.
- **void section(const char \* str)** wrapper for header level 3.
- **void subSection(const char \* str)** wrapper for header level 4.


### Style

These functions work, but not perfect.
The ...off() functions add a space after the markup.
These functions do not mix well so use carefully.

- **void boldOn()** idem.
- **void boldOff()** idem.
- **void italicOn()** idem.
- **void italicOFF()** idem.
- **void boldItalicOn()** idem.
- **void boldItalicOff()** idem.
- **void line()** draw a line in the report. (splitter).


### Tables I

Initial the tables are simple, with headers of max 11 characters.
The align array consist of L=Left, C=Centre, R=Right alignment.
The align array should at least have size elements and is case insensitive.
Invalid chars for align are centred (default).

- **void tableHeader(uint8_t size, char headers[][12], char \* align = "CCCCCCCCCC")** If no align array is given the default is centred.
Note: default align length = 10, so more columns need an array.
- **void tableValues(float values[], uint8_t decimals = 2)** values must be at least contain **size** elements as defined in **tableHeader()**.
Decimals is set for this row. Not nice but works for now.


### Tables II

Functions to create a row per cell / column. 
Allows every column its own type.
User must do the admin to print enough cells / columns, however mark down
seems to be not too strict here.

- **void tableRowStart()**
- **template <typename T> void tableRowValue(T var)** for all types.
- **void tableRowValue(float value, uint8_t decimals)** for float 
with decimals (default = 2).
- **void tableRowEnd()** 


### Links

- **void URL(const char \* text, const char \* link)** URL "hidden" under a text.
- **void image(const char \* text, const char \* link)** Image, with text underneath.
- **void link(const char \* link)** simple link.


## Future

#### Must

- improve documentation

#### Should

#### Could

- add examples (see XML writer)
  - other streams like SD card and HTTP sockets
- escaping characters in text fields e.g. \* ?
- void blockQuote(text) - nesting ?
- void code(text)
- void codeBlockOn() / codeBlockOff()
- simple style calls for single words.
  - void bold(text) and void italic(text).
  - void bold(float, dec = 0) and void italic(float, dec = 0).
- lists API
  - pointListBegin(indent)       (unordered list)
  - pointListItem(text)
  - pointListEnd(footer)
  - numberListBegin(indent)      (ordered lists) - nesting ?
  - numberListItem(text)
  - numberListEnd(footer)


#### Wont

- performance example (not needed)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


