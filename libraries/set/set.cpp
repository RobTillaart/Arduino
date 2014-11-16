//
//    FILE: set.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: SET library for Arduino
//     URL:
//
// HISTORY:
// 0.1.00 by Rob Tillaart 09/11/2014
//
// Released to the public domain
//

#include "set.h"

/////////////////////////////////////////////////////
//
// PUBLIC
//

////////////////////////////
set::set()
{
    clr();
}

set::set(set &t)
{
    for (int i=0; i<32; i++)
    {
        _mem[i] = t._mem[i];
    }
}


////////////////////////////

void set::add(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    _mem[idx] |= mask;
}

void set::sub(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    _mem[idx] &= ~mask;
}

bool set::has(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    return (_mem[idx] & mask) > 0;
}

void set::invert(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    _mem[idx] ^= mask;
}


////////////////////////////////////

// TODO OPTIMIZE COUNT
uint8_t set::count()
{
    uint8_t cnt = 0;
    for (int i=0; i<256; i++)
    {
        if ( has(i) ) cnt++;
    }
    return cnt;
}

uint8_t set::size()
{
    return 256; // TODO _size;
}

void set::clr()
{
    for (int i=0; i<32; i++)
    {
        _mem[i] = 0;
    }
}

void set::invert()
{
    for (int i=0; i<32; i++)
    {
        _mem[i] ^= 0xFF;
    }
}


///////////////////////////////////////////////////
void set::operator = (set &t)
{
    for (int i=0; i<32; i++)
    {
        _mem[i] = t._mem[i];
    }
}

void set::operator -= (set &t)
{
    for (int i=0; i<32; i++)
    {
        _mem[i] &= ~t._mem[i];
    }
}

void set::operator &= (set &t)
{
    for (int i=0; i<32; i++)
    {
        _mem[i] &= t._mem[i];
    }
}

void set::operator |= (set &t)
{
    for (int i=0; i<32; i++)
    {
        _mem[i] |= t._mem[i];
    }
}

void set::operator ^= (set &t)
{
    for (int i=0; i<32; i++)
    {
        _mem[i] ^= t._mem[i];
    }
}

bool set::operator == (set &t)
{
    for (int i=0; i<32; i++)
    {
        if (_mem[i] != t._mem[i]) return false;
    }
    return true;
}

bool set::operator < (set &t)
{
    for (int i=0; i<32; i++)
    {
        if (_mem[i] ^= t._mem[i]) return false;
    }
    return true;
}
//
// END OF FILE
//