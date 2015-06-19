//
//    FILE: DistanceTable.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: library for a memory efficient DistanceTable for Arduino
//     URL:
//
// Released to the public domain
//

// 0.1.00 - initial version
// 0.1.01 - refactor

#include "DistanceTable.h"

DistanceTable::DistanceTable(uint8_t size)
{
    _size = size;
    uint16_t s = size * (size-1)/2;
    _distanceTable = (double*) malloc(s * sizeof(double));
    if (_distanceTable == NULL) _size = 0;
}

DistanceTable::~DistanceTable()
{
    if (_distanceTable != NULL) free(_distanceTable);
}

void DistanceTable::clear()
{
    uint16_t s = _size * (_size-1)/2;
    for (uint16_t index = 0; index < s; index++)
    {
        _distanceTable[index] = 0;
    }
};

void DistanceTable::set(uint8_t x, uint8_t y, double value )
{
    if ( x >= _size || y >= _size) return;
    if ( x == y ) return;
    // need swap?
    if ( x < y ) 
    {
        uint8_t t = x; x = y; y = t;
    }
    uint16_t index = x;
    index = index * (index-1)/2 + y;
    _distanceTable[index] = value;
};

double DistanceTable::get(uint8_t x, uint8_t y)
{
    if ( x >= _size || y >= _size) return -1;
    if ( x == y ) return 0;
    // need swap?
    if ( x < y ) 
    {
        uint8_t t = x; x = y; y = t;
    }
    uint16_t index = x;
    index = index * (index-1)/2 + y;
    return _distanceTable[index];
};


void DistanceTable::dump()
{
    uint16_t index = 0;
    for (uint16_t i = 0; i < _size-1; i++)
    {
        for (uint16_t j = 0; j <= i; j++)
        {
            Serial.print(_distanceTable[index++]);
            Serial.print("\t");
        }
        Serial.println();
    }     
    Serial.println();
};


// --- END OF FILE ---