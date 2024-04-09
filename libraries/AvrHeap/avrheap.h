#pragma once
//
//    FILE: avrheap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.7
//    DATE: 2015-10-25
// PURPOSE: Experimental Arduino library to investigate the AVR heap Arduino UNO


#if !defined(ARDUINO_ARCH_AVR)
  #error “Avrheap library only AVR boards, tested only with UNO.”
#endif


#include "Arduino.h"
#include "Printable.h"


#define AVRHEAP_LIB_VERSION                   (F("0.2.7"))


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


//  -- END OF FILE --
