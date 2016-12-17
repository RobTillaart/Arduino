//
//    FILE: nibbleArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: compact storage for array of nibbles
//     URL:
//
// HISTORY:
// see nibbleArray.cpp
//

#ifndef nibbleArray_h
#define nibbleArray_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define NIBBLEARRAY_LIB_VERSION "0.1.00"

class nibbleArray
{
public:
    nibbleArray(uint16_t size);
    ~nibbleArray();

    uint8_t get(const uint16_t idx);
    uint8_t set(const uint16_t idx, uint8_t value);

private:
    uint16_t *arr;
    uint16_t _size;
};
#endif
//
// END OF FILE
//