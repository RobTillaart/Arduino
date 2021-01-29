
[![Arduino CI](https://github.com/RobTillaart/FastShiftOut/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FastShiftOut/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FastShiftOut.svg?maxAge=3600)](https://github.com/RobTillaart/FastShiftOut/releases)


# FastShiftOut

Arduino library for (AVR) optimized shiftOut - e.g. 74HC595

A library for FastShiftIn also exist - https://github.com/RobTillaart/FastShiftIn

## Description

FastShiftOut is a class that has optimized code for AVR to shift out data faster 
than the normal shiftOut() function.
It speeds up the shift using low level ports and masks. These are predetermined
in the constructor of the FastShiftOut object.

If not an **ARDUINO_ARCH_AVR** or **ARDUINO_ARCH_MEGAAVR** the class falls back 
to the default shiftOut() implementation. 

## Performance

The performance of **write()** is substantially faster than the default Arduino 
**shiftOut()**, but not as fast as HW SPI. 
Exact how big the performance gain is can be seen with the example sketch.
It does a comparison and shows how the class is to be used.

## Interface

The interface exists of the following functions:

- **size_t write(const uint8_t data);** send a byte, also the workhorse of the **Print** interface
- **uint8_t lastWritten()** returns last byte writtem
- **bool setBitOrder(bitOrder)** set LSBFIRST or MSBFIRST. Returns false for other values.
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST
- **size_t writeLSBFIRST(const uint8_t data);**  most optimized
- **size_t writeMSBFIRST(const uint8_t data);**  most optimized

As a FastShiftOut object implements the Print interface, one can also call
- **FSO.print(any type);** or 
- **FSO.println(any type);** 

to send e.g. a float with 4 digits over the line, or some text string. 

Note: **FSO.print()** returns the characters printed, including an optional \\r or \\n.


## Notes

- The optimizations are AVR only for now, other platforms may follow.
- The 74HC595 needs 0.1uF caps and the data and clock lines may need  
pull up resistors, especially if wires are exceeding 10 cm (4").

## Operation

See examples

