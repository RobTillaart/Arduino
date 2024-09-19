
[![Arduino CI](https://github.com/RobTillaart/FastShiftIn/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FastShiftIn/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FastShiftIn/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FastShiftIn/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FastShiftIn/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FastShiftIn.svg)](https://github.com/RobTillaart/FastShiftIn/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FastShiftIn/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FastShiftIn.svg?maxAge=3600)](https://github.com/RobTillaart/FastShiftIn/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FastShiftIn.svg)](https://registry.platformio.org/libraries/robtillaart/FastShiftIn)


# FastShiftIn

Arduino library for **AVR** optimized shiftIn - e.g. for 74HC165.


## Description

FastShiftIn is a class that has optimized code (AVR only) to shift in data faster 
than the default provided **shiftIn()** function.
It speeds up the shift using low level ports and masks. These are predetermined
in the constructor of the FastShiftIn object.

If not an **ARDUINO_ARCH_AVR** or **ARDUINO_ARCH_MEGAAVR** the class falls back 
to the default **shiftIn()** implementation.

The library allows to set (and get) the bitOrder and apply this to multiple read()
calls. It also provide access to **readLSBFIRST()** and **readMSBFIRST()** which 
are the low level workers and most optimized code (so far).

The library provides wrapper functions to read multi-byte variables. 
These are read16(), read24(), read32() and read(array, size).
The latter is used to shift in any size object.


### 0.4.0 breaking changes

The 0.4.0 version has a flag to unroll the inner loop in **readLSBFIRST()**
and **readMSBFIRST()**. The AVR optimized code blocks the interrupts per byte.

Note: this optimization is new and thus experimental.
Feedback, including improvements, is welcome.


### Performance

The performance of **read()** is substantially faster for **AVR** than the default 
Arduino **shiftIn()**, but not as fast as HW SPI. 
Exact how large the performance gain is can be seen with the example sketch.
It does a comparison and shows how the class is to be used.


#### Measurements

Numbers may vary depending on bit-order flag.

Indicative time in microseconds, Arduino UNO, IDE 1.8.19, measured over 1000 calls. 

|  function            |   0.2.3  |   0.3.2  |   0.4.0  |  0.4.0L  |
|:---------------------|---------:|---------:|---------:|---------:|
|  read()              |   19.30  |   20.49  |   12.71  |    9.51  |
|  read16()            |          |   41.04  |   25.39  |   18.98  |
|  read24()            |          |   62.91  |   39.10  |   29.48  |
|  read32()            |          |   83.95  |   51.42  |   38.60  |
|  readLSBFIRST()      |   19.04  |   19.92  |   11.96  |    8.81  |
|  readMSBFIRST()      |   19.04  |   19.92  |   11.94  |    8.75  |
|  reference shiftIn() |  107.82  |  108.20  |  108.05  |  108.05  |


- Note: 0.3.2 is a bit slower (incl. reference) than 0.2.3 but still much
faster than the reference. (Older IDE?)
- Note: 0.4.0 improved test sketch, 
- Note: 0.4.0 measured with loop unroll flag disabled.
- Note: 0.4.0L measured with loop unrolled flag enabled.


### Related libraries

- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow


## Interface

```cpp
#include "FastShiftIn.h"
```

### Constructor

bitOrder = { LSBFIRST, MSBFIRST };

- **FastShiftIn(uint8_t dataIn, uint8_t clockPin, uint8_t bitOrder = LSBFIRST)** Constructor

### Functions

- **uint16_t read(void)** reads a new value, 8 bit.
- **uint16_t read16(void)** reads a new value, 16 bit.
- **uint32_t read24(void)** reads a new value, 24 bit.
- **uint32_t read32(void)** reads a new value, 32 bit.
- **uint32_t lastRead()** returns last value read.
- **uint16_t readLSBFIRST(void)**  optimized LSB read(), 8 bit.
- **uint16_t readMSBFIRST(void)**  optimized MSB read(), 8 bit.


### BitOrder

- **bool setBitOrder(uint8_t bitOrder)** set LSBFIRST or MSBFIRST. 
Returns false for other values ==> no change.
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST as set in the constructor
or latest set from **setBitOrder()**.


### Experimental

- **void read(uint8_t \*array, uint8_t size)** read an array of values.
The order in the array follows as BYTE order MSB / LSB, that is why this function
is made experimental. This might change in the future, and fill the array
in arrival order.


### Byte order

The functions **read16()**, **read24()** and **read32()** of this library assume
that the BIT-order is also the BYTE-order.
This is not always the case as an n-byte element can have n! == factorial(n)
distinct byte orders.

So **read16()** can have two, **read24()** can have six and **read32()** can even have 
(in theory) 24 distinct byte orders. Although LSB and MSB are the most common,
other byte orders exist, and sometimes one explicitly wants to reorder the bytes.

If the BIT-order is not the BYTE-order, the user has two options
- call **read()** multiple times and merge the bytes in the order needed.
- call **read32()** (a.o) and reorder the bytes in a separate function.

The library will not support such functionality.


## Notes

- The optimizations are AVR only for now, other platforms may follow.
- The 74HC165 needs 0.1uF caps and the data and clock lines may need  
pull up resistors, especially if wires are exceeding 10 cm (4").


## Future

#### Must

- keep in sync with FastShiftOut()

#### Should

- extend unit tests

#### Could

- investigate ESP32 optimization readLSBFIRST readMSBFIRST
- performance ESP32
- example schema
- add invert flag?
- would it be interesting to make a fastShiftIn16() etc?
  - squeeze performance but more maintenance.?           

#### Wont

- investigate separate **BYTE**-order, 
  - only MSBFirst and LSBFirst
  - **void setByteOrder()** + **uint8_t getByteOrder()**
  - other option is add parameters / overload to make byte order explicit
    - **read32(1,0,3,2)** performance penalty + invalid combination.

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
