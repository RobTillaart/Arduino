#ifndef AVRHEAP_H
#define AVRHEAP_H
//
//    FILE: Avrheap.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.03
// PURPOSE: heap library for Arduino (AVR)
// HISTORY: See avrheap.cpp
//
// Released to the public domain
//

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Printable.h"

#define AVRHEAP_LIB_VERSION "0.1.03"

class Avrheap
{
public:
    Avrheap();

    void     dump();
    void     followHeap();

    bool     isFragmented();
    uint16_t freeListCount();
    uint16_t freeListSize();
    void     freeListDump();
    uint16_t freeListLargest();

    uint16_t startAddress();

private:
    bool     inFreeList(uint16_t addr);

};

#endif