#ifndef AVRHEAP_H
#define AVRHEAP_H
//
//    FILE: Avrheap.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.04
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

#define AVRHEAP_LIB_VERSION "0.1.04"

class Avrheap : public Printable
{
public:
    Avrheap();

    bool     isFragmented();
    uint16_t freeListCount();
    uint16_t freeListSize();
    void     freeListWalk(bool withDump = true);
    uint16_t freeListLargest();

    uint16_t startAddress();

    void     dumpHeap(uint16_t count);
    size_t   heapWalk(Print& p, bool withDump = true) const;
    size_t   heapWalk(bool withDump = true);
    virtual size_t printTo(Print& p) const;

private:
    bool     inFreeList(uint16_t addr);
};

size_t hNibble(Print& p, byte val);
size_t hByte(Print& p, byte val);
size_t hWord(Print& p, uint16_t val);
size_t dumpR(Print& p, byte* adr, int len);
size_t dumpAlloced(Print& p, byte *ptr, bool withDump = true);
size_t dumpAlloced(byte *ptr, bool withDump = true);

#endif