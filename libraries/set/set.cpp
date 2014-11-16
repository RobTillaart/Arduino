//
//    FILE: set.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: SET library for Arduino
//     URL:
//
// HISTORY:
// 0.1.03 changed &= to *= to follow Pascal conventions
// 0.1.02 documentation
// 0.1.01 extending/refactor etc (09/11/2014)
// 0.1.00 initial version by Rob Tillaart (09/11/2014)
//
// Released to the public domain
//

#include "set.h"

/////////////////////////////////////////////////////
//
// CONSTRUCTORS
//
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

/////////////////////////////////////////////////////
//
// METHODS
//
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

void set::invert(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    _mem[idx] ^= mask;
}

bool set::has(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    return (_mem[idx] & mask) > 0;
}

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

void set::clr()
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] = 0;
    }
}

void set::invert()
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] ^= 0xFF;
    }
}

int set::first()
{
    for (int i = 0; i < 256; i++)
    {
        if (has(i))
        {
            _current = i;
            return _current;
        }
    }
    _current = -1;
    return _current;
}

int set::next()
{
    if (_current != -1)
    {
        _current++;
        for (int i = _current; i < 256; i++)
        {
            if (has(i))
            {
                _current = i;
                return _current;
            }
        }
    }
    _current = -1;
    return _current;
}

int set::prev()
{
    if (_current != -1)
    {
        _current--;
        for (int i = _current; i > -1; --i)
        {
            if (has(i))
            {
                _current = i;
                return _current;
            }
        }
    }
    _current = -1;
    return _current;
}

int set::last()
{
    _current = -1;
    for (int i = 255; i >=0; --i)
    {
        if (has(i))
        {
            _current = i;
            break;
        }
    }
    return _current;
}


/////////////////////////////////////////////////////
//
// OPERATORS
//
void set::operator = (set &t)  // assign
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] = t._mem[i];
    }
}

void set::operator += (set &t)  // union
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] |= t._mem[i];
    }
}

void set::operator -= (set &t)  // diff
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] &= ~t._mem[i];
    }
}

void set::operator *= (set &t)  // intersection
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] &= t._mem[i];
    }
}

bool set::operator == (set &t)  // equal
{
    for (uint8_t i=0; i<32; i++)
    {
        if (_mem[i] != t._mem[i]) return false;
    }
    return true;
}

bool set::operator != (set &t)  // not equal
{
    for (uint8_t i=0; i<32; i++)
    {
        if (_mem[i] != t._mem[i]) return true;
    }
    return false;
}

bool set::operator <= (set &t)  // subset
{
    for (int i=0; i<256; i++)
    {
        if ( has(i) && !t.has(i) ) return false;
    }
    return true;
}
//
// END OF FILE
//