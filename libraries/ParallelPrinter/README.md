
[![Arduino CI](https://github.com/RobTillaart/ParallelPrinter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ParallelPrinter/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ParallelPrinter/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ParallelPrinter/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ParallelPrinter/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ParallelPrinter.svg)](https://github.com/RobTillaart/ParallelPrinter/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ParallelPrinter/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ParallelPrinter.svg?maxAge=3600)](https://github.com/RobTillaart/ParallelPrinter/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ParallelPrinter.svg)](https://registry.platformio.org/libraries/robtillaart/ParallelPrinter)


# ParallelPrinter

Arduino library that implements a parallel printer (driver) - implements the PRINT interface.


## Description

The ParallelPrinter library implements the protocol to connect to a parallel printer.

It implements the **Print interface** to be able to print all data types like int and float
using **write()**, **print()** and **println()**.
The printer writes every byte over 8 parallel lines including a **STROBE** (clock) pulse,
while waiting for the connected printer not to be **BUSY** or **OUT OF PAPER** (OOP).

This library is meant to be a starting point to make a "printer driver" for a 
specific parallel printer. These can often be bought in 2nd hand stores or so.

Have fun!

**Note:** This library is an extended redo of the (obsolete) ParPrinter class.

As always, feedback is welcome.


### Schema

```
      Arduino                             Printer
   *--------------+                     *--------------+
   |              |                     |              |
   |            o |<--------------------| BUSY         |
   |            o |<--------------------| OUT OF PAPER |
   |              |                     |              |
   |            o |-------------------->| STROBE       |
   |            o |-------------------->| D0           |
   |            o |-------------------->| D1           |
   |              |                     | ...          |
   |            o |-------------------->| D6           |
   |            o |-------------------->| D7           |
   |              |                     |              |
   +--------------+                     +--------------+

```


### Related

- https://en.wikipedia.org/wiki/Parallel_port#Centronics
- https://github.com/RobTillaart/ParallelPrinter

somehow related
- https://github.com/RobTillaart/ANSI  (display control)
- https://github.com/RobTillaart/lineFormatter  (columns, free format tabs)


## Interface

```cpp
#include "ParallelPrinter.h"
```

### Constructor

- **ParallelPrinter()** uses default pins (13, 2, 12, \[3,4,5,6,7,8,9,10\])
- **ParallelPrinter(uint8_t STROBE, uint8_t BUSY, uint8_t OOP, uint8_t \*arr)** 
define 3 control pins + 8 data pins (= arr\[8\]).
- **void begin(uint8_t lineLength, uint8_t pageLength)** set line and page length parameters


### Print interface

- **size_t write(uint8_t c)** send a single byte to printer, implements Print interface. 
Therefore all **print()** and **println()** functions will work.
- **size_t formfeed()** to eject current page or forced go to the next page.
- **size_t linefeed()** send a linefeed. 
The number of actual lines is set by **setLineFeed()**


### Configuration

These settings are pretty straightforward.

- **void setLineLength(uint8_t lineLength)** idem
- **uint8_t getLineLength()** returns the current line length. 
- **void setPageLength(uint8_t pageLength)** idem
- **uint8_t getPageLength()** returns the current page length.
- **uint8_t getLineNumber()** returns current line number.
- **uint8_t getPageNumber()** returns current page number.
- **uint8_t getPosition()** returns the position on a line.
- **uint8_t setTabSize(uint8_t tabsize)** tabs are replaced by spaces. n can be 0 or any size!
- **uint8_t getTabSize()** returns tabSize set
- **void setLineFeed(uint8_t lineFeeds)** lineFeeds = 1,2,3  1 = default. 
- **uint8_t getLineFeed()** returns lineFeeds set
- **void printLineNr(bool b)** can be set to true, false.


### Expert mode

- **bool isOutOfPaper()** to check paper tray before printing starts.
- **void setStrobeDelay(uint16_t n = 2000)** allows tuning of performance. 
Make the strobe pulse shorter == faster printing (printer dependant).
Default value = 2000. Time in microseconds.
- **uint16_t getStrobeDelay()** returns value set.

**Note** mechanical printers e.g. dot matrix, really do need a way to stop receiving 
data as they do not have large buffers.  (==> BUSY line)


## Future

#### Must

- update documentation

#### Should

- test more.
- extend simulator sketch.
  - Make a front end of a parallel printer, 
  - Accepts the clocked bytes and print them e.g. over serial.
- CamelCase
  - formFeed() + lineFeed()

#### Could

- extend unit tests?
- derive e.g. an HP or an EPSON printer from this class.
  - special modes e.g. bold italic underline.
- **write(uint8_t \* buf, uint8_t length)** should be added
  - might not really add to performance..  (able to send a line at once)
- fix blocking TODO in sendByte
- StrobeDelay should be in milliseconds or uint32_t?

#### Wont

- send 8 bit data over SPI with an ser2par?

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

