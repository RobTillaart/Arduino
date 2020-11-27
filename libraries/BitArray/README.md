# BitArray
Arduino library for compact array of objects with a size expressed in bits. typically 1..10

## Description
The BitArray class allows the user to instantiate an array of elements, each of the same size in bits.
For example one could create an array of 100 throws with a dice. Normally this would take 100 bytes,
but BitArray can store one throw in 3 bits, so 100 throws in approx 40 bytes.
Another example is to store multiple 10 bit analogRead() values efficiently

The class is optimized for storage and takes care of efficiently packing the elements 
into multiple bytes, and byte borders. Depending where an element is located writing and reading
can take more time. You need to check if your application needs more performance than
this library can deliver. 

The BitArray library is one from a set of three:
* BitArray  for elements of user defined size in bits (values 0 .. 2^n-1)
* BoolArray for elements of 1 bit (values 0 .. 1)
* nybbleArray for elements of 4 bits (values 0 .. 15)


## Operations
In the function **begin(#elementsize, #elements)** the element size and number of elements 
needs to be defined. The maximum number of elements is 65535 if memory allows, 
the maximum element size is 32.

The basic functions of the class are
* **set(index, value)**
* **get(index)**
* **toggle(index)**
* **clear()**

Check out the examples.

## Notes
The BitArray class dynamicly allocates memory, so called BA_SEGMENTS, 
each of 200 bytes.
As the memory size of different processors differ the maximum amount of SEGMENTS 
depends on architecture.

The library is tested on AVR architecture only.

