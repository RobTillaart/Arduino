
[![Arduino CI](https://github.com/RobTillaart/ParallelPrinter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ParallelPrinter/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ParallelPrinter.svg?maxAge=3600)](https://github.com/RobTillaart/ParallelPrinter/releases)

# ParallelPrinter

Arduino library that implements a parallel printer (driver) - implements the PRINT interface


## Description

This library defines a parallel printer object.

It implements the **Print interface** to be able to print all datatypes using **write()**, **print()** and **println()**
The printer writes every byte over 8 parallel lines including a **STROBE** (clock) pulse,
while waiting for the connected printer not to be **BUSY** or **OUT OF PAPER**.

This library is meant to be a starting point to make a "printer driver" for a 
specific parallel printer. These can often be bought in 2nd hand stores or so.

Have fun!

**Note:** This lib is a extended redo of the ParPrinter class.


## Interface

### Constructor

- **ParallelPrinter()** uses default pins (13, 2, 12, \[3,4,5,6,7,8,9,10\])
- **ParallelPrinter(strobe, busy, oop, arr)** define 3 control pins + 8 datapins (= arr)
- **begin(linelength, pagelength)** set line and page length parameters


### Print interface
- **write(c)** send a single byte to printer, implements Print interface. 
Therefor all **print()** and **println()** functions will work.
- **formfeed()** to eject current page or forced go to the next page.
- **linefeed()** send a linefeed. The number of actual lines is set by **setLineFeed()**


### Config

These settings are pretty straightforward.

- **setLineLength(lineLength)** idem
- **getLineLength()** returns the current line length. 
- **setPageLength(pageLength)** idem
- **getPageLength()** returns the current page length.
- **getLineNumber()** returns current line number.
- **getPageNumber()** returns current page number.
- **getPosition()** returns the position on a line.
- **setTabSize(tabsize)** tabs are replaced by spaces. n can be 0 or any size!
- **getTabSize()** returns tabSize set
- **setLineFeed(lineFeeds)** lineFeeds = 1,2,3  1 = default
- **getLineFeed()** returns lineFeeds set
- **printLineNr(bool)** can be set to true, false


### Expert mode

- **isOutOfPaper()** to check paper tray before printing starts.
- **setStrobeDelay(n = 2000)** make the strobe pulse shorter == faster printing
allows tuning of performance. Default value = 2000. Time in microseconds.
- **getStrobeDelay()** returns value set.

**Note** mechanical printers e.g. dot matrix, really do need a way to stop receiving 
data as they do not have large buffers.


## See also

https://en.wikipedia.org/wiki/Parallel_port#Centronics


## Future

- Make a front end of a parallel printer, that accepts the clocked bytes and print them 
- derive e.g. an HP or an EPSON printer from this class.

## Operation

See examples
