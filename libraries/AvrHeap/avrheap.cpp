//
//    FILE: avrheap.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: library for avrheap Arduino
//     URL: http://forum.arduino.cc/index.php?topic=355660
//
// REFERENCES
// http://forum.arduino.cc/index.php?topic=27536.15
//
// Released to the public domain
// 0.1.03 - refactoring
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

// WHAT USES
void Avrheap::dump()
{
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
}

void Avrheap::followHeap()
{
    size_t n = 0;
    byte* heapNodePtr = (byte*) &__heap_start;
    n += Serial.println("addr\tsize\tcontent");
    while ((int)heapNodePtr < (int)__brkval)  // brkval is first free place.
    {
        // address of heap-node (- 2)
        n += Serial.print((uint16_t)heapNodePtr); // p+2 ?
        n += Serial.print("\t");
        // size of heap node
        n += Serial.print(*heapNodePtr, DEC);
        if (inFreeList((uint16_t)heapNodePtr)) n += Serial.print(":f\t");
        else n += Serial.print(":\t");
        // dump content of heap-node
        for (int i = 0; i < *heapNodePtr; i++)
        {
            uint8_t v = (uint8_t) *( heapNodePtr + 2 + i);
            if (v < 16) n += Serial.print('0');
            n += Serial.print(v, HEX);
            n += Serial.print(" ");
        }
        n += Serial.println();
        // goto next heap-node
        heapNodePtr += (byte) *heapNodePtr + 2;
    }
    // return n;
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