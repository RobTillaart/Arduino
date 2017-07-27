//
//    FILE: DistanceTable.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: library for a memory efficient DistanceTable for Arduino
//     URL:
//
// Released to the public domain
//
// 0.1.3  2017-07-27 Fix issue #33
// 0.1.2  - fix overflow;  add some error detection;  revert float to float to memory
// 0.1.01 - refactor
// 0.1.00 - initial version

#include "DistanceTable.h"

DistanceTable::DistanceTable(uint8_t size)
{
    // MUST: size > 1
    // ATMEL 328 has 2000 bytes mem, 
    // so roughly 30X30 = 900 floats(4Bytes) => 1740 bytes is max feasible
    _size = size;
    _store = _size;
    _store *= (_size-1)/2;
    _distanceTable = (float *) malloc(_store * sizeof(float));
    if (_distanceTable == NULL) _size = 0;
    clear();
}

DistanceTable::~DistanceTable()
{
    if (_distanceTable != NULL) free(_distanceTable);
}

void DistanceTable::clear()
{
    for (uint16_t index = 0; index <_store; index++) _distanceTable[index] = 0;
};

void DistanceTable::set(uint8_t x, uint8_t y, float value )
{
    if ( x == y ) return;
    // comment next line to skip rangecheck (squeeze performance)
    if ( x >= _size || y >= _size) return;

    // uint16_t index = getIndex(uint8_t x, uint8_t y);
    if ( x < y ) 
    {
        uint8_t t = x; x = y; y = t;
    }
    // prevent overflow by moving to 16 bit
    uint16_t index = x;
    index = (index * (index-1))/2 + y;
    _distanceTable[index] = value;
};

float DistanceTable::get (uint8_t x, uint8_t y)
{
    if ( x == y ) return 0.0;
    // comment next line to skip rangecheck (squeeze performance)
    if ( x >= _size || y >= _size) return -1;

    // uint16_t index = getIndex(uint8_t x, uint8_t y);
    if ( x < y ) 
    {
        uint8_t t = x; x = y; y = t;
    }
    uint16_t index = x;
    index = (index * (index-1))/2 + y;
    return _distanceTable[index];
};

// TODO remove identical code
// int DistanceTable::getIndex(uint8_t x, uint8_t y)
// {
    // if ( x < y ) 
    // {
        // uint8_t t = x; x = y; y = t;
    // }
    // uint16_t index = x;
    // index = (index * (index-1))/2 + y;
    // return index;
// }

// triangular dump 
void DistanceTable::dump()
{
    uint16_t index = 0;
    for (uint8_t i = 0; i < _size-1; i++)
    {
        for (uint8_t j = 0; j <= i; j++)
        {
            Serial.print(_distanceTable[index++]);
            Serial.print("\t");
        }
        Serial.println();
    }     
    Serial.println();
};


// --- END OF FILE ---