#pragma once
//
//    FILE: DistanceTable.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: Arduino library to store a symmetrical distance table in less memory
//     URL: https://github.com/RobTillaart/DistanceTable
//

#include "Arduino.h"

#define DISTANCETABLE_LIB_VERSION "0.1.5"

class DistanceTable
{
public:
    explicit DistanceTable(uint8_t);
    ~DistanceTable();

    void clear();
    void set(uint8_t x, uint8_t y, float value );
    float get(uint8_t x, uint8_t y);
    void dump();
    uint16_t size() { return _store; };

protected:
    int getIndex(uint8_t, uint8_t);

    uint8_t _size;
    uint16_t _store;
    float * _distanceTable;
};

// --- END OF FILE ---
