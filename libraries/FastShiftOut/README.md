# FastShiftOut

Arduino library for (AVR) optimized shiftOut - e.g. 74HC595

A library for FastShiftOut also exist.

## Description

FastShiftOut is a class that has optimized code for AVR to shift out data faster 
than the normal shiftOut() function.
It speeds up the shift using low level ports and masks. These are predetermined
in the constructor of the FastShiftOut object.

If not an **ARDUINO_ARCH_AVR** or **ARDUINO_ARCH_MEGAAVR** the class falls back 
to the default shiftOut() implementation. 

## Performance

The performance of **write()** is substantially faster than the default Arduino 
**shiftIn()**, but not as fast as HW SPI. 
Exact how big the performance gain is can be seen with the example sketch.
It does a comparison and shows how the class is to be used.

## Interface

The interface exists of the following functions:

- **size_t write(const uint8_t data);**
- **size_t writeLSBFIRST(const uint8_t data);**  most optimized
- **size_t writeMSBFIRST(const uint8_t data);**  most optimized

Furthermore an FastShiftOut object implements the Print interface
so one can also call
- **FSO.print(any type);** or 
- **FSO.println(any type);**

to send e.g. a float with 4 digits over the line.

## Notes

- The optimizations are AVR only for now, other platforms may follow.
- The 74HC595 needs 0.1uF caps and the data and clock lines may need  
pull up resistors, especially if wires are exceeding 10 cm (4").

## Operation

See examples

