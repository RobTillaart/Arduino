# FastShiftIn

Arduino library for (AVR) optimized shiftIn - e.g. for 74HC165

A library for FastShiftOut also exist.

## Description

FastShiftIn is a class that has optimized code (AVR only) to shift in data faster 
than the normal shiftIn() function.
It speeds up the shift using low level ports and masks. These are predetermined
in the constructor of the FastShiftIn object.

If not an **ARDUINO_ARCH_AVR** or **ARDUINO_ARCH_MEGAAVR** the class falls back 
to the default shiftIn() implementation.

## Performance

The performance of **read()** is substantially faster than the default Arduino 
**shiftIn()**, but not as fast as HW SPI. 
Exact how big the performance gain is can be seen with the example sketch.
It does a comparison and shows how the class is to be used.

## Interface

The interface exists of the following functions:

- **int read(void);**
- **int readLSBFIRST(void);**  most optimized
- **int readMSBFIRST(void);**  most optimized

## Notes

- The optimizations are AVR only for now, other platforms may follow.
- The 74HC165 needs 0.1uF caps and the data and clock lines may need  
pull up resistors, especially if wires are exceeding 10 cm (4").

## Operation

See examples

