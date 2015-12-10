//
//    FILE: avrheap.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: library for avrheap Arduino
//     URL: http://forum.arduino.cc/index.php?topic=355660
//
// REFERENCES
// http://forum.arduino.cc/index.php?topic=27536.15
//
// Released to the public domain
//
// 0.1.02 - added followHeap()
// 0.1.01 - refactor, added startAddress()
// 0.1.00 - initial version

#include "Avrheap.h"

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
extern uint16_t __heap_start;


Avrheap::Avrheap()
{
};

bool Avrheap::isFragmented()
{
    return this->freeListCount() > 0;
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

void Avrheap::freeListDump()
{
    for (struct __freelist* p = __flp; p; p = p->next)
    {
        Serial.print((uint16_t)p);
        Serial.print("\t");
        Serial.println((uint16_t)p->size);
    }
    Serial.println();
}

uint16_t Avrheap::startAddress()
{
    return (uint16_t) &__heap_start;
}

// PRINTTO?
void Avrheap::dump(uint16_t count)
{
    /*
    Serial.println((int)__brkval);
    Serial.println((int)RAMEND);
    Serial.println((int)SP);
    Serial.println((int)__data_start);
    Serial.println((int)__data_end);
    Serial.println((int)__bss_start);
    Serial.println((int)__bss_end);
    Serial.println((int)__malloc_heap_start);
    Serial.println((int)__malloc_heap_end);
    Serial.println((int)__malloc_margin);
    */

    for (int i = 0; i < count;)
    {
        Serial.print('\t');
        Serial.print((uint8_t) * ((&__heap_start) + i) );
        if (++i % 16 == 0) Serial.println();
    }
    Serial.println();
}

// EXPERIMENTAL
void Avrheap::followHeap()
{
    byte* p = (byte*) &__heap_start;
    struct __freelist* fp = __flp;

    Serial.println("addr\tsize");
    while ((int)p < (int)__brkval)
    {
        Serial.print((uint16_t)p); // p+2 ?
        Serial.print("\t\t");
        Serial.print(*p, DEC);
        // if (inFreeList(p) Serial.print("\t (free)");
        if ( (fp != NULL) && ((uint16_t)p == (uint16_t)fp))
        {
            Serial.print("\t (free)");
            fp = fp->next;
        }
        Serial.println();
        p += (byte) *p + 2;
    }
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

// --- END OF FILE ---