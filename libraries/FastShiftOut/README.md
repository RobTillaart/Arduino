
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

FastShiftOut is a class that has optimized code (**AVR** only) to shift out data faster 
than the default provided **shiftOut()** function.
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


### 0.4.0 breaking changes

The 0.4.0 version has a flag to unroll the inner loop in **writeLSBFIRST()**
and **writeMSBFIRST()**. The AVR optimized code blocks the interrupts per byte.

Note: this optimization is new and thus experimental.
Feedback, including improvements, is welcome.


### Performance

The performance of **write()** is substantially faster for **AVR** than the default 
Arduino **shiftOut()**, but not as fast as HW SPI (need test?). 
Exact how large the performance gain is can be seen with the example **FastShiftOut_test.ino**.
It does a measurement of different functions and shows how the class is to be used.
See also table below.


#### Measurements

Numbers may vary depending on bit-order flag.

Indicative time in microseconds, Arduino UNO, IDE 1.8.19, measured over 1000 calls.  
(delta between 2 calls and 1 call to eliminate overhead)

|  function                |  0.2.4  |   0.3.1  |   0.3.3  |   0.4.0  |  0.4.0L  |   0.4.1  |  0.4.1L  |
|:-------------------------|--------:|---------:|---------:|---------:|---------:|---------:|---------:|
|  write()                 |  21.66  |   22.48  |   22.27  |   14.10  |   11.51  |   12.83  |    9.12  |
|  writeLSBFIRST()         |  22.94  |   23.37  |   22.25  |   14.09  |   11.50  |   12.82  |    9.12  |
|  writeMSBFIRST()         |  20.30  |   21.86  |   22.26  |   14.08  |   11.50  |   12.82  |    9.12  |
|  reference shiftOut()    |  89.74  |   89.74  |   89.59  |   89.60  |   89.60  |   89.59  |   89.60  |
|  write16()               |   na    |    na    |   45.39  |   29.06  |   23.89  |   26.34  |   19.11  |
|  write24()               |   na    |    na    |   67.66  |   43.12  |   35.40  |   39.36  |   28.23  |
|  write32()               |   na    |    na    |   89.91  |   57.22  |   46.90  |   52.18  |   37.34  |
|  println("Hello world")  |   na    |  328.92  |  328.92  |  222.68  |  189.20  |  206.32  |  158.12  |
|  println(1357)           |   na    |  313.56  |  311.60  |  262.60  |  247.12  |  255.04  |  232.80  |
|  println(3.14159265, 4)  |   na    |  717.36  |  716.04  |  650.68  |  629.96  |  640.52  |  610.92  |

- Note: 0.3.3 has improved the measurement, not the code sec.
- Note: 0.3.3 numbers fixed when implementing 0.4.0. (error in test sketch).
- Note: 0.4.0 measured with loop unroll flag disabled.
- Note: 0.4.0L measured with loop unrolled flag enabled.
- Note: 0.4.1 / 0.4.1L idem.
- Note: Loop unrolled is (8046 - 7818 = 128) bytes larger in size.


### Related

- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow
- https://github.com/RobTillaart/SWSPI (experimental)


## Interface

```cpp
#include "FastShiftOut.h"
```

### Constructor

bitOrder = { LSBFIRST, MSBFIRST };

- **FastShiftOut(uint8_t dataOut, uint8_t clockPin, uint8_t bitOrder = LSBFIRST)** Constructor.


### Functions

- **size_t write(uint8_t data)** send a byte, also the workhorse of the **Print** interface.
- **size_t write16(uint16_t data)** send 2 bytes. Wrapper around 8 bit calls.
- **size_t write24(uint32_t data)** send 3 bytes. Wrapper around 8 bit calls.
- **size_t write32(uint32_t data)** send 4 bytes. Wrapper around 8 bit calls.
- **size_t write(uint8_t \*array, size_t size)** send array of size bytes.
- **uint8_t lastWritten()** returns last byte written.
- **size_t writeLSBFIRST(uint8_t data)** lowest level function, optimized for LSB.
- **size_t writeMSBFIRST(uint8_t data)** lowest level function, optimized for MSB.


### BitOrder

- **bool setBitOrder(uint8_t bitOrder)** set LSBFIRST or MSBFIRST. 
Returns false for other values ==> no change.
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST as set in constructor 
or latest set from **setBitOrder()**.


### Print interface

As the FastShiftOut library implements the Print interface, one can also call

- **size_t FSO.print(any type)** or 
- **size_t FSO.println(any type)** 

to send e.g. a float with 4 digits over the line, or some text string. 

Note: **FSO.print()** and **FSO.println()** return the number of characters printed, 
including an optional \\r and \\n.


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

The library will not support such functionality.


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

- investigate ESP32 optimization readLSBFIRST readMSBFIRST
- performance ESP32
- example schema
- add invert flag?
  - if ((value & m) == 0) ==> if ((value & m) == invertFlag...
  - derived class?

#### Wont

- investigate separate **BYTE**-order, 
  - only MSBFirst and LSBFirst
  - **void setByteOrder()** + **uint8_t getByteOrder()**


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

