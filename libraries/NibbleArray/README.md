# nibbleArray

Arduino library for a compact array of nibbles (4 bit units)

## Description

A nibble is a 4 bit element, which can hold a value 0..15 (0..F in HEX).

The nibbleArray is an array that stores 2 nibbles in a byte therefor it is 
twice as small as a normal array.

The current implementation can hold 510 elements. This is due a limitation of
the UNO which can alloc max 255 bytes in one **malloc()** call.

This **NIBBLEARRAY_MAXSIZE** can be defined compiletime "-D NIBBLEARRAY_MAXSIZE" 
or one can adjust it in the library if other platforms can allocate more memory.

## Interface

The interface of the nibbleArray is straightforward:

* **get(index)** idem
* **set(index, value)** idem
* **clear()**       set all elements to 0;
* **SetAll(value)** set all elements to value

## Operation


