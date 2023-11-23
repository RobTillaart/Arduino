
[![Arduino CI](https://github.com/RobTillaart/XMLWriter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/XMLWriter/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/XMLWriter/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/XMLWriter/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/XMLWriter/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/XMLWriter.svg)](https://github.com/RobTillaart/XMLWriter/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/XMLWriter/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/XMLWriter.svg?maxAge=3600)](https://github.com/RobTillaart/XMLWriter/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/XMLWriter.svg)](https://registry.platformio.org/libraries/robtillaart/XMLWriter)


# XMLWriter

Arduino Library to create simple XML (messages, files, print, ...).


## Description

The XMLWriter class supports generating XML files and send these over a stream
like Ethernet SD.File or Serial.

When instantiating an XMLWriter one can define the internal buffer size.
A bigger buffer will make the output faster, especially for Ethernet and SD.File.
The buffer size should be at least 2 bytes and max 250.
How much faster depends on the properties of the stream and the platform used.
E.g. the baud rate and internal buffer of Serial, packet behaviour of Ethernet,
or paging of SD cards.
If performance is low one should do test runs with different sizes for the buffer 
and choose one that is appropriate.

Indicative sizes based upon the examples.
Run your tests to find your application optimum.

|  STREAM    |    SIZE    |
|:-----------|:-----------|
|  Ethernet  |   20-30    |
|  Serial    |     5      |
|  SD File   |   10-16    |

**IMPORTANT:** When using buffering you should always call **XML.flush()** 
at the end of the XML generation. This will flush the last bytes in the internal buffer into the output stream.


## Interface

```cpp
#include "XMLWriter.h"
```

### Constructor

- **XMLWriter(Print\* stream = &Serial, uint8_t bufferSize = 10)** Constructor defines the stream and the buffer size
to optimize performance vs memory usage.
Note the default bufferSize of 10 can be optimized. 
See table in description above.


### Functions for manual layout control

- **void setIndentSize(uint8_t size = 2)** preferred a multiple of 2; no limit.
- **uint8_t getIndentSize()** returns set indent.
- **void incrIndent()** increments indent by 2 spaces.
- **void decrIndent()** decrements indent by 2 spaces.
- **void indent()** manually indent output.
- **void raw(char\* str)** inject any string.


### General settings

- **void setConfig(uint8_t config)** used to show/strip comment, indent, newLine. 
use **setConfig(0);** to minimize the output.
- **void newLine(uint8_t n)** add a number of newlines to the output, default = 1.


### Functions

- **void header()** injects standard XML header string, must be first line.
- **void reset()** resets internal state, to be called before new XML is written.
- **void comment(char\* text, bool multiLine = false)** \<!-- text --\>  
if multiline == true it does not indent to allow bigger text blocks
multiline is default false.
- **void flush()** call flush() at the end of writing to empty the internal buffer. **!!**


### Functions to create simple tags with named fields

- **void tagOpen(char\* tag, bool newLine)** \<tag\>
- **void tagOpen(char\* tag, char\* name, bool newLine)** \<tag name="name"\>
- **void tagClose()** \</tag\>


### Functions to make up tags with multiple fields

- **void tagStart(char\* tag)**  \<tag 
- **void tagField(char\* field, char\* string)**  field="string"
- **void tagField(char\* field, T value, uint8_t base = DEC)** standard math types,  field="value"
- **void tagEnd(bool newline = true, bool addSlash = true);**  /\>


### Functions to make a node

- **void writeNode(char\* tag, bool value);** \<tag\>value\</tag\>
- **void writeNode(char\* tag, T value, uint8_t base = DEC);** standard math types.


### Helper 

- **void escape(char\* str)** expands the XML chars: \"\'\<\>\&
Note one need to set the **XMLWRITER_ESCAPE_SUPPORT** flag.


### Metrics and debug

To optimize buffer size in combination with timing.

- **uint8_t bufferIndex()** returns the size of the internal buffer.
- **uint32_t bytesWritten()** idem, since reset().
- **void version()** injects the **XMLWRITER_VERSION** as comment in output stream.
- **void debug()** injects comment with internal info.


## Print interface

XMLWriter 0.2.4 implements the Print interface, so at any moment one can use 
**print()** or **println()** to inject specific information. 

Note that **tagField()** and **writeNode()** do not support 64 bit integer
types and large values of double. 
My **printHelpers library** helps to convert these to strings which can be printed.
See example.

The Print interface can also be used to print objects that 
implement the **Printable** interface. See example.

With the support of the Print interface, **raw()** is becoming obsolete as it only
can inject strings.


## Configuration flags

|  Flag               |  Value  |  Description        |
|:--------------------|:--------|:--------------------|
|  XMLWRITER_NONE     |  0x00   |  minimize output, smaller & faster |
|  XMLWRITER_COMMENT  |  0x01   |  allow comments     |
|  XMLWRITER_INDENT   |  0x02   |  allow indentation  |
|  XMLWRITER_NEWLINE  |  0x04   |  allow newlines     |


- **setConfig(XMLWRITER_NONE);** to minimize the output in bytes.
- **setConfig(XMLWRITER_NEWLINE);** to break an XML stream in lines.
- **setConfig(XMLWRITER_NEWLINE | XMLWRITER_INDENT);** to see XML structure.
- **setConfig(XMLWRITER_NEWLINE | XMLWRITER_INDENT | XMLWRITER_COMMENT);** to see XML structure + comments.


## Operation

See examples


## Future

#### Must

- update documentation

#### Should

#### Could

- move code to .cpp

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
