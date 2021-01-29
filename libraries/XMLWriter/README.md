
[![Arduino CI](https://github.com/RobTillaart/XMLWriter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/XMLWriter/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/XMLWriter.svg?maxAge=3600)](https://github.com/RobTillaart/XMLWriter/releases)


# XMLWriter

Arduino Library to create simple XML (messages, files, print, ...)

## Description

The XMLWriter class supports generating XML files and send these over a stream
like Ethernet SD.File or Serial.

When instantiating an XMLWriter one can define the internal buffer size.
A bigger buffer will make the output faster, especially for Ethernet and SD.File.
The buffer size should be at least 2 bytes and max 250.
How much faster depends on the properties of the stream and the platform used.
E.g. the baudrate and internal buffer of Serial, packet behaviour of Ethernet,
or paging of SD cards.
If performance is low one should do testruns with different sizes for the buffer 
and choose one that is appropriate.

Indicative sizes based upon the examples.
Run your tests to find your application optimum.

| STREAM   |    SIZE    |
|:------------|:----------|
| Ethernet | 20-30 |
| Serial   |  5 |
| SD File  |  10-16 |

**IMPORTANT:** When using buffering you should always call **XML.flush()** 
at the end of the XML generation. This will flush the last bytes in the internal buffer into the output stream.


## Interface

### Constructor

- **XMLWriter(stream, bufsize);** Constructor defines the stream and the buffersize
to optimize performance vs memory usage.


### Functions for manual layout control

- **setIndentSize(size = 2)** preferred a multiple of 2; no limit
- **getIndentSize()** returns set indent
- **incrIndent()** increments indent by 2 spaces
- **decrIndent()** decrements indent by 2 spaces
- **indent()** manually indent output
- **raw(str)** inject any string


### General settings

- **setConfig(cfg)** used to show/strip comment, indent, newLine. 
use **setConfig(0);** to minimize the output
- **newLine(n)** add a number of newlines to the output, default = 1


### Functions

- **header()** injects standard XML header string, must be first line
- **reset()** resets internal state, to be called before new XML is written
- **comment(text, multiline)** \<!-- text --\>  
if multiline == true it does not indent to allow bigger text blocks
multiline is default false.
- **flush()** call flush() at the end of writing to empty the internal buffer. **!!**


### Functions to create simple tags with named fields

- **tagOpen(tag, newLine)** \<tag\>
- **tagOpen(tag, name, newLine)** \<tag name="name"\>
- **tagClose()** \</tag\>


### Functions to make up tags with multiple fields

- **tagStart(tag)**  \<tag 
- **tagField(field, string);**  field="string"
- **tagField(field, T value, base = DEC);** standard math types,  field="value"
- **tagEnd(newline = true, addSlash = true);**  /\>

### Functions to make a node

- **writeNode(tag, value);** \<tag\>value\</tag\>
- **writeNode(tag, T value, base = DEC);** standard math types

### Helper 

- **escape(str)** expands the xml chars: \"\'\<\>\&


### Metrics and debug

To optimize buffersize in combination with timing.

- **bufferIndex()** returns the size of the internal buffer
- **bytesWritten()** idem, since reset().
- **version()** injects the XMLWRITER_VERSION as comment in outputstream.
- **debug()** injects comment with internal info.


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

| Flag | Value | Meaning |
|:----|:----|:----|
|XMLWRITER_NONE    | 0x00 | minimize output, smaller & faster |
|XMLWRITER_COMMENT | 0x01 | allow comments |
|XMLWRITER_INDENT  | 0x02 | allow indentation |
|XMLWRITER_NEWLINE | 0x04 | allow newlines |

- **setConfig(XMLWRITER_NONE);** to minimize the output in bytes.
- **setConfig(XMLWRITER_NEWLINE);** to break an XML stream in lines.
- **setConfig(XMLWRITER_NEWLINE | XMLWRITER_INDENT);** to see XML structure.
- **setConfig(XMLWRITER_NEWLINE | XMLWRITER_INDENT | XMLWRITER_COMMENT);** to see XML structure + comments.


## Operation

See examples

