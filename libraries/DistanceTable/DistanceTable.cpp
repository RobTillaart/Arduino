//
//    FILE: DistanceTable.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: library for a memory efficient DistanceTable for Arduino
//     URL:
//
// Released to the public domain
//

// 0.1.2 - prevent overflow; refactor memory usage;
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
    _distanceTable = (double *) malloc(_store * sizeof(double));
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

void DistanceTable::set(uint8_t x, uint8_t y, double value )
{
    if ( x == y ) return;
    if ( x >= _size || y >= _size) return;
    if ( x < y )
    {
        uint8_t t = x; x = y; y = t;
    }
    // prevent overflow by moving to 16 bit
    uint16_t index = x;
    index = index * (index-1)/2 + y;
    _distanceTable[index] = value;
};

double DistanceTable::get (uint8_t x, uint8_t y)
{
    if ( x == y ) return 0;
    if ( x >= _size || y >= _size) return -1;
    if ( x < y )
    {
        uint8_t t = x; x = y; y = t;
    }
    uint16_t index = x;
    index = index * (index-1)/2 + y;
    return _distanceTable[index];
};

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