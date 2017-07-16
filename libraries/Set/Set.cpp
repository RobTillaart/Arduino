//
//    FILE: Set.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.11
// PURPOSE: SET library for Arduino
//     URL:
//
// HISTORY:
// 0.1.11 2017-07-16 fix count() --> 16 bit when set is full !
// 0.1.10 2017-07-16 performance refactor. isEmpty()
// 0.1.09 2015-07-12 const + constructor
// 0.1.08 memset for clr()
// 0.1.07 faster first/next/last/prev; interface
// 0.1.06 added flag to constructor to optimize +,-,*,
//        set -> Set
// 0.1.05 bug fixing + performance a.o. count()
// 0.1.04 support for + - *, some optimizations
// 0.1.03 changed &= to *= to follow Pascal conventions
// 0.1.02 documentation
// 0.1.01 extending/refactor etc (09/11/2014)
// 0.1.00 initial version by Rob Tillaart (09/11/2014)
//
// Released to the public domain
//

#include "Set.h"

/////////////////////////////////////////////////////
//
// CONSTRUCTORS
//
Set::Set(const bool clear)
{
    if (clear)
    {
        clr();
    }
    _current = -1;
}

Set::Set(const Set &t)
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] = t._mem[i];
    }
    _current = -1;
}

/////////////////////////////////////////////////////
//
// METHODS
//
void Set::add(const uint8_t v)
{
    uint8_t idx = v / 8;
    _mem[idx] |= masks[v&7];
}

void Set::sub(const uint8_t v)
{
    uint8_t idx = v / 8;
    _mem[idx] &= ~masks[v&7];
}

void Set::invert(const uint8_t v)
{
    uint8_t idx = v / 8;
    _mem[idx] ^= masks[v&7];;
}

bool Set::has(const uint8_t v)
{
    uint8_t idx = v / 8;
    return (_mem[idx] & masks[v&7]) > 0;
}

uint16_t Set::count() const
{
    uint16_t cnt = 0;
    for (uint8_t i=0; i<32; i++)
    {
        // kerningham bit count trick
        uint8_t b = _mem[i];
        for (; b; cnt++)
        {
            b &= b-1;
        }
    }
    return cnt;
}

void Set::clr()
{
    memset(_mem, 0, 32);
}

void Set::invert()
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] ^= 0xFF;
    }
}

bool Set::isEmpty()
{
    for (uint8_t i=0; i<32; i++)
    {
        if (_mem[i]) return false;
    }
    return true;
}

bool Set::isFull()
{
    for (uint8_t i=0; i<32; i++)
    {
        if (_mem[i] != 255) return false;
    }
    return true;
}

int Set::first()
{
    return findNext(0,0);
}

int Set::next()
{
    if (_current & 0x8000) return -1; // if current == -1
    _current++;
    uint8_t p = (uint8_t)_current / 8;
    uint8_t q = (uint8_t)_current & 7;
    return findNext(p, q);
}

int Set::findNext(const uint8_t p, uint8_t q)
{
    for (uint8_t i = p; i < 32; i++)
    {
        uint8_t b = _mem[i];
        if (b != 0)
        {
            uint8_t mask = 1 << q;
            for (uint8_t j = q; j < 8; j++)
            {
                if (b & mask)
                {
                    _current = i * 8 + j;
                    return _current;
                }
                mask <<= 1;
            }
        }
        q = 0;
    }
    _current = -1;
    return _current;
}

int Set::prev()
{
    if (_current & 0x8000) return -1;
    _current--;
    uint8_t p = (uint8_t)_current / 8;
    uint8_t q = (uint8_t)_current & 7;
    return findPrev(p, q);
}

int Set::last()
{
    return findPrev(31, 7);
}

int Set::findPrev(const uint8_t p, uint8_t q)
{
    uint8_t m = 1 << q;
    for (uint8_t i = p; i != 255; --i)  // uint < 0
    {
        uint8_t b = _mem[i];
        if (b != 0)
        {
            uint8_t mask = m;
            for (uint8_t j = q; j != 255; --j)
            {
                if (b & mask)
                {
                    _current = i * 8 + j;
                    return _current;
                }
                mask >>= 1;
            }
        }
        m = 1 << 7;
        q = 7;
    }
    _current = -1;
    return _current;
}


/////////////////////////////////////////////////////
//
// OPERATORS
//

Set Set::operator + (const Set &t)  // union
{
    Set s(false);
    for (uint8_t  i = 0; i < 32; i++)
    {
        s._mem[i] = this->_mem[i] | t._mem[i];
    }
    return s;
}

Set Set::operator - (const Set &t)  // diff
{
    Set s(false);
    for (uint8_t i = 0; i < 32; i++)
    {
        s._mem[i] = this->_mem[i] & ~t._mem[i];
    }
    return s;
}

Set Set::operator * (const Set &t)  // intersection
{
    Set s(false);
    for (uint8_t i = 0; i < 32; i++)
    {
        s._mem[i] = this->_mem[i] & t._mem[i];
    }
    return s;
}

void Set::operator += (const Set &t)  // union
{
    for (uint8_t i = 0; i < 32; i++)
    {
        _mem[i] |= t._mem[i];
    }
}

void Set::operator -= (const Set &t)  // diff
{
    for (uint8_t i = 0; i < 32; i++)
    {
        _mem[i] &= ~t._mem[i];
    }
}

void Set::operator *= (const Set &t)  // intersection
{
    for (uint8_t i = 0; i < 32; i++)
    {
        _mem[i] &= t._mem[i];
    }
}

bool Set::operator == (const Set &t) const // equal
{
    for (uint8_t i = 0; i < 32; i++)
    {
        if (_mem[i] != t._mem[i]) return false;
    }
    return true;
}

bool Set::operator != (const Set &t) const // not equal
{
    for (uint8_t i = 0; i < 32; i++)
    {
        if (_mem[i] != t._mem[i]) return true;
    }
    return false;
}

bool Set::operator <= (const Set &t) const // subSet
{
    for (uint8_t i = 0; i < 32; i++)
    {
        if ((_mem[i] & ~t._mem[i]) > 0) return false;
    }
    return true;
}
//
// END OF FILE
//