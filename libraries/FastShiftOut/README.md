
[![Arduino CI](https://github.com/RobTillaart/FastShiftOut/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FastShiftOut/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FastShiftOut/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FastShiftOut/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FastShiftOut/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FastShiftOut.svg)](https://github.com/RobTillaart/FastShiftOut/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FastShiftOut/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FastShiftOut.svg?maxAge=3600)](https://github.com/RobTillaart/FastShiftOut/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FastShiftOut.svg)](https://registry.platformio.org/libraries/robtillaart/FastShiftOut)


# FastShiftOut

Arduino library for **AVR** optimized shiftOut - e.g. 74HC595.

Related libraries
- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow


## Description

FastShiftOut is a class that has optimized code for AVR to shift out data faster 
than the normal **shiftOut()** function.
It speeds up the shift using low level ports and masks. These are predetermined
in the constructor of the FastShiftOut object.

If not an **ARDUINO_ARCH_AVR** or **ARDUINO_ARCH_MEGAAVR** the class falls back 
to the default shiftOut() implementation. 


## Performance

The performance of **write()** is substantially faster than the default Arduino 
**shiftOut()**, but not as fast as HW SPI. 
Exact how big the performance gain is can be seen with the example sketch.
It does a comparison and shows how the class is to be used.

Time in microseconds, Arduino UNO

|  function                |  0.2.4  |   0.3.1  |
|:-------------------------|--------:|---------:|
|  write()                 |  21.66  |   22.48  |
|  writeLSBFIRST()         |  22.94  |   23.37  |
|  writeMSBFIRST()         |  20.30  |   21.86  |
|  reference shiftOut()    |  89.74  |   89.74  |
|  println("Hello world")  |         |  328.92  |
|  println(1357)           |         |  313.56  |
|  println(3.14159265, 4)  |         |  717.36  |


## Interface

```cpp
#include "FastShiftOut.h"
```

#### Functions

- **FastShiftOut(uint8_t dataOut, uint8_t clockPin, uint8_t bitOrder = LSBFIRST)** Constructor.
- **size_t write(const uint8_t data)** send a byte, also the workhorse of the **Print** interface.
- **uint8_t lastWritten()** returns last byte written.
- **bool setBitOrder(uint8_t bitOrder)** set LSBFIRST or MSBFIRST. Returns false for other values.
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST.
- **size_t writeLSBFIRST(const uint8_t data);**  most optimized.
- **size_t writeMSBFIRST(const uint8_t data);**  most optimized.


As a FastShiftOut object implements the Print interface, one can also call

- **FSO.print(any type);** or 
- **FSO.println(any type);** 

to send e.g. a float with 4 digits over the line, or some text string. 

Note: **FSO.print()** returns the number of characters printed, including an optional \\r or \\n.


## Notes

- The optimizations are AVR only for now, other platforms may follow.
- The 74HC595 needs 0.1uF caps and the data and clock lines may need  
pull up resistors, especially if wires are exceeding 10 cm (4").


## Future


#### Must

#### Should

- extend unit tests

#### Could

- performance ESP32
- check optimized ESP32
- add **size_t write(const uint8_t \*buffer, size_t size)**
- example schema

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

