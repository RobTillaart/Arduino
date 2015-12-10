//
//    FILE: avrheap.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: library for avrheap Arduino
//     URL: http://forum.arduino.cc/index.php?topic=355660
//
// Released to the public domain
//
// 0.1.01 - refactor, added startAddress
// 0.1.00 - initial version

#include "Avrheap.h"

struct __freelist {
    size_t size;
    struct __freelist *next;
};

extern struct __freelist *__flp;
extern int __heap_start, *__brkval;
extern char *__malloc_heap_start;
extern char *__malloc_heap_end;

Avrheap::Avrheap()
{
};

size_t Avrheap::printTo(Print& p) const
{
    size_t n = 0;
    for (int i = 0; i < count; )
    {
        n += p.print('\t');
        n += p.print((uint8_t) * ((&__heap_start) + i) );
        if (++i % 16 == 0) n += p.println();
    }
    n += p.println();
    return n;
};

bool Avrheap::isFragmented()
{
    return this->freeListCount() > 1;
};

uint16_t Avrheap::freeListCount()
{
    uint16_t count = 0;
    for (struct __freelist*  p = __flp; p; p = p->next)
    {
        count++;
    }
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
    return &__heap_start;
}

// PRINTTO
void Avrheap::dump(uint16_t count)
{
    for (int i = 0; i < count; )
    {
        Serial.print('\t');
        Serial.print((uint8_t) * ((&__heap_start) + i) );
        if (++i % 16 == 0) Serial.println();
    }
    Serial.println();
}



// void followHeap()
// {
// Serial.println("followHeap");
// int *p = (int*)&__heap_start;
// int x = 0;
// for (int i = 0; i < 10; i++)
// {
// Serial.print(i);
// Serial.print('\t');
// Serial.print(*p, DEC);
// Serial.println();
// p += (int) * p;
// }
// }

// --- END OF FILE ---