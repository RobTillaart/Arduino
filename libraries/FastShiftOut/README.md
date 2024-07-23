
[![Arduino CI](https://github.com/RobTillaart/FastShiftOut/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FastShiftOut/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FastShiftOut/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FastShiftOut/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FastShiftOut/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FastShiftOut.svg)](https://github.com/RobTillaart/FastShiftOut/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FastShiftOut/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FastShiftOut.svg?maxAge=3600)](https://github.com/RobTillaart/FastShiftOut/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FastShiftOut.svg)](https://registry.platformio.org/libraries/robtillaart/FastShiftOut)


# FastShiftOut

Arduino library for **AVR** optimized shiftOut - e.g. 74HC595.


## Description

FastShiftOut is a class that has optimized code (AVR only) to shift out data faster 
than the normal **shiftOut()** function.
It speeds up the shift using low level ports and masks. These are predetermined
in the constructor of the FastShiftOut object.

If not an **ARDUINO_ARCH_AVR** or **ARDUINO_ARCH_MEGAAVR** the class falls back 
to the default shiftOut() implementation. 

The library allows to set (and get) the bitOrder and apply this to multiple write()
calls. It also provide access to **writeLSBFIRST()** and **writeMSBFIRST()** which 
are the low level workers and most optimized code (so far).

The library provides wrapper functions to write multi-byte variables. 
These are write16(), write24(), write32() and write(array, size).
The latter is used to shift out any size object.


### Performance

The performance of **write()** is substantially faster for **AVR** than the default 
Arduino **shiftOut()**, but not as fast as HW SPI. 
Exact how large the performance gain is can be seen with the example sketch.
It does a comparison and shows how the class is to be used.

Time in microseconds, Arduino UNO

|  function                |  0.2.4  |   0.3.1  |   0.3.3  |
|:-------------------------|--------:|---------:|---------:|
|  write()                 |  21.66  |   22.48  |   22.37  |
|  writeLSBFIRST()         |  22.94  |   23.37  |   23.26  |
|  writeMSBFIRST()         |  20.30  |   21.86  |   21.75  |
|  reference shiftOut()    |  89.74  |   89.74  |   89.60  |
|  println("Hello world")  |         |  328.92  |  328.92  |
|  println(1357)           |         |  313.56  |  311.68  |
|  println(3.14159265, 4)  |         |  717.36  |  716.04  |


Note: 0.3.3 has improved the measurement, not the code sec.


### Related

- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow


## Interface

```cpp
#include "FastShiftOut.h"
```

### Constructor

- **FastShiftOut(uint8_t dataOut, uint8_t clockPin, uint8_t bitOrder = LSBFIRST)** Constructor.

### Functions

- **size_t write(uint8_t data)** send a byte, also the workhorse of the **Print** interface.
- **size_t write16(uint16_t data)** send 2 bytes.
- **size_t write24(uint32_t data)** send 3 bytes.
- **size_t write32(uint32_t data)** send 4 bytes.
- **size_t write(uint8_t \*array, size_t size)** send size bytes.
- **uint8_t lastWritten()** returns last byte written.

### Meta

- **bool setBitOrder(uint8_t bitOrder)** set LSBFIRST or MSBFIRST. Returns false for other values.
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST.
- **size_t writeLSBFIRST(uint8_t data)**  most optimized.
- **size_t writeMSBFIRST(uint8_t data)**  most optimized.


As a FastShiftOut object implements the Print interface, one can also call

- **FSO.print(any type)** or 
- **FSO.println(any type)** 

to send e.g. a float with 4 digits over the line, or some text string. 

Note: **FSO.print()** returns the number of characters printed, including an optional \\r or \\n.


### Byte order

The functions **write16()**, **write24()** and **write32()** of this library assume
that the BIT-order is also the BYTE-order.
This is not always the case as an n-byte element can have n! == factorial(n)
distinct byte orders.

So **write16()** can have two, **write24()** can have six and **write32()** can even have 
(in theory) 24 distinct byte orders. Although LSB and MSB are the most common,
other byte orders exist, and sometimes one explicitly wants to reorder the bytes.

If the BIT-order is not the BYTE-order, the user has two options
- call **write()** multiple times and merge the bytes in the order needed.
- call **write32()** (a.o) and reorder the bytes in a separate function.


## Notes

- The optimizations are AVR only for now, other platforms may follow.
- The 74HC595 needs 0.1uF caps and the data and clock lines may need  
pull up resistors, especially if wires are exceeding 10 cm (4").


## Future


#### Must

- keep in sync with FastShiftIn()

#### Should

- extend unit tests

#### Could

- investigate separate **BYTE**-order, 
  - only MSBFirst and LSBFirst
  - **void setByteOrder()** + **uint8_t getByteOrder()**
- investigate ESP32 optimization readLSBFIRST readMSBFIRST
- performance ESP32
- example schema

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

