//
//    FILE: avrheap.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.7
//    DATE: 2015-10-25
// PURPOSE: Experimental Arduino library to investigate the AVR heap Arduino UNO
//     URL: https://github.com/RobTillaart/avrheap
//
//  REFERENCES
//  http://forum.arduino.cc/index.php?topic=27536.15
//  http://forum.arduino.cc/index.php?topic=355660


#include "avrheap.h"


struct __freelist
{
  size_t size;
  struct __freelist *next;
};


extern struct   __freelist *__flp;
extern uint16_t __heap_start;
extern uint16_t *__brkval;
extern char     *__malloc_heap_start;
extern char     *__malloc_heap_end;
extern size_t   __malloc_margin;
extern uint16_t __data_start;
extern uint16_t __data_end;
extern uint16_t __bss_start;
extern uint16_t __bss_end;


size_t hNibble(Print& p, byte val)
{
  return p.write(val + (val < 10 ? '0' : 'A' - 10));
}


size_t hByte(Print& p, byte val)
{
  size_t len = hNibble(p, val >> 4);
  return len + hNibble(p, val & 0x0F);
}


size_t hWord(Print& p, uint16_t val)
{
  size_t len = hByte(p, (byte)(val >> 8));
  return len + hByte(p, (byte)(val & 0xFF) );
}


size_t dumpR(Print& p, byte* adr, int len)
{
  size_t glen = 0;
  byte idx;
  if (!len)
  {
    len = 16;
  }
  for (; len > 0; len -= 16, adr += 16)
  {
    glen += hWord(p, (uint16_t)adr);
    glen += p.print(F(": "));
    for (idx = 0; idx < 16; idx++)
    {
      if (idx < len )
      {
        glen += hByte(p, adr[idx]);
        glen += p.write(' ');
      } else {
        glen += p.print(F("   "));
      }
    }
    glen += p.write('\'');
    for (idx = 0; (idx < 16) && (idx < len); idx++)
    {
      glen += p.write(adr[idx] < 0x20 ? '.' : adr[idx]);
    }
    glen += p.write('\'');
    glen += p.println();
  }
  return glen;
}


size_t dumpAlloced(byte *ptr, bool withDump)
{
  return dumpAlloced(Serial, ptr, withDump);
}


size_t dumpAlloced(Print& p, byte *ptr, bool withDump)
{
  size_t len = hWord(p, (uint16_t)ptr);
  if (!ptr)
  {
    len += p.println(F(": NULL"));
  } else {
    size_t size = *(size_t*)(ptr - sizeof(size_t));
    if (size < __malloc_margin)
    {
      len += p.print(F(": size "));
      len += p.println(size);
    } else {
      len += p.print(F(": invalid size "));
      len += p.println(size);
      size = 16;
    }
    if (withDump)
    {
      len += dumpR(p, ptr, size);
      len += p.println();
    }
  }
  return len;
}


//////////////////////////////////////////////////////
//
//  AVRHEAP
//
Avrheap::Avrheap()
{
};


bool Avrheap::isFragmented()
{
  return freeListCount() > 0;
};


uint16_t Avrheap::freeListCount()
{
  uint16_t count = 0;
  for (struct __freelist*  p = __flp; p; p = p->next) count++;
  return count;
}


uint16_t Avrheap::freeListSize()
{
  uint16_t total = 0;
  for (struct __freelist*  p = __flp; p; p = p->next)
  {
    total += 2;     // malloc size
    total += (uint16_t) p->size;
  }
  return total;
}


void Avrheap::freeListWalk(bool withDump)
{
  int elements = freeListCount();
  Serial.print(F("\nFreeList: "));
  Serial.print(isFragmented() ? F("fragmented") : F("clean"));
  Serial.print(F(", count "));
  Serial.print(elements);
  Serial.print(F(", largest "));
  Serial.print(freeListLargest());
  Serial.print(F(", total size "));
  Serial.println(freeListSize());
  Serial.println();
  if (elements)
  {
    for (struct __freelist* p = __flp; p; p = p->next)
    {
      hWord(Serial, (uint16_t)p);
      Serial.print(F(": size "));
      Serial.print((uint16_t)p->size);
      Serial.print(F(" next "));
      hWord(Serial, (uint16_t)p->next);
      Serial.println();
      if (withDump)
      {
        dumpR(Serial, ((byte*)p) + 2, p->size);
        Serial.println();
      }
    }
  }
}


uint16_t Avrheap::startAddress()
{
  return (uint16_t) &__heap_start;
}


void Avrheap::dumpHeap(uint16_t count)
{
  hWord(Serial, (uint16_t)RAMEND);
  Serial.println(F(" RAMEND"));
  hWord(Serial, (uint16_t)SP);
  Serial.println(F(" SP"));
  hWord(Serial, (uint16_t)__brkval);
  Serial.println(F(" __brkval"));
  hWord(Serial, (uint16_t)__malloc_heap_end);
  Serial.println(F(" __malloc_heap_end"));
  hWord(Serial, (uint16_t)__malloc_heap_start);
  Serial.println(F(" __malloc_heap_start"));
  hWord(Serial, (uint16_t)&__heap_start);
  Serial.println(F(" __heap_start"));
  hWord(Serial, (uint16_t)&__bss_end);
  Serial.println(F(" __bss_end"));
  hWord(Serial, (uint16_t)&__bss_start);
  Serial.println(F(" __bss_start"));
  hWord(Serial, (uint16_t)&__data_end);
  Serial.println(F(" __data_end"));
  hWord(Serial, (uint16_t)&__data_start);
  Serial.println(F(" __data_start"));
  hWord(Serial, (uint16_t)__malloc_margin);
  Serial.println(F(" __malloc_margin"));
  Serial.println();
  Serial.println(F("start of heap"));
  Serial.println();
  dumpR(Serial, (byte*)startAddress(), count);
}


size_t Avrheap::heapWalk(bool withDump) {
  return heapWalk(Serial, withDump);
}


//  EXPERIMENTAL
size_t Avrheap::heapWalk(Print& pr, bool withDump) const
{
  byte* p = (byte*) &__heap_start;
  struct __freelist* fp = __flp;

  size_t len = pr.println(F("Heap\n"));
  while ((int)p < (int)__brkval)
  {
    len += hWord(pr, (uint16_t)p);  //  p+2 ?
    len += pr.write(' ');
    len += pr.print(*p, DEC);
    if ( (fp != NULL) && ((uint16_t)p == (uint16_t)fp))
    {
      len += pr.print(F(" (free)"));
      fp = fp->next;
    }
    len += pr.println();
    if (withDump) {
      len += dumpR(pr, p, *p + 2);
      len += pr.println();
    }
    p += (byte) * p + 2;
  }
  return len;
}


bool Avrheap::inFreeList(uint16_t addr)
{
  for (struct __freelist* p = __flp; p; p = p->next)
  {
    if (addr == (uint16_t)p) return true;
  }
  return false;
}


uint16_t Avrheap::freeListLargest()
{
  uint16_t largest = 0;
  for (struct __freelist*  p = __flp; p; p = p->next)
  {
    largest = max(largest, (uint16_t) p->size);
  }
  return largest;
}


size_t Avrheap::printTo(Print& p) const
{
  size_t len = heapWalk(p, true);
  return len;
}


//  --- END OF FILE ---
