//
//    FILE: Set.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.07
// PURPOSE: SET library for Arduino
//     URL:
//
// HISTORY:
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
Set::Set(bool clear)
{
    if (clear)
    {
        clr();
    }
}

Set::Set(const Set &t)
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] = t._mem[i];
    }
}

/////////////////////////////////////////////////////
//
// METHODS
//
void Set::add(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    _mem[idx] |= mask;
}

void Set::sub(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    _mem[idx] &= ~mask;
}

void Set::invert(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    _mem[idx] ^= mask;
}

bool Set::has(uint8_t v)
{
    uint8_t mask = 1 << (v & 7);
    uint8_t idx = v / 8;
    return (_mem[idx] & mask) > 0;
}

uint8_t Set::count()
{
    uint8_t cnt = 0;
    for (uint8_t i=0; i<32; i++)
    {
        // kerningham bit count trick
        uint8_t b = _mem[i];
        if (b!=0)
        {
        for (; b; cnt++)
        {
            b &= b-1;
        }
        }
    }
    return cnt;
}

void Set::clr()
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] = 0;
    }
}

void Set::invert()
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] ^= 0xFF;
    }
}

int Set::first()
{
    return findNext(0,0);
}

int Set::next()
{
    if (_current & 0x8000) return -1;
    _current++;
    uint8_t p = (uint8_t)_current / 8;
    uint8_t q = (uint8_t)_current & 7;
    return findNext(p, q);
}

int Set::findNext(uint8_t p, uint8_t q)
{
    for (uint8_t i=p; i<32; i++)
    {
        uint8_t b = _mem[i];
        if (b != 0)
        {
            uint8_t mask = 1<<q;
            for (uint8_t j=q; j<8; j++)
            {
                if (b & mask)
                {
                    _current = i*8 + j;
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

int Set::findPrev(uint8_t p, uint8_t q)
{
    uint8_t m = 1 << q;
    for (uint8_t i=p; i!=255; --i)
    {
        uint8_t b = _mem[i];
        if (b != 0)
        {
            uint8_t mask = m;
            for (uint8_t j=q; j!=255; --j)
            {
                if (b & mask)
                {
                    _current = i*8 + j;
                    return _current;
                }
                mask >>= 1;
            }
        }
        m = 1<<7;
        q = 7;
    }
    _current = -1;
    return _current;
}


/////////////////////////////////////////////////////
//
// OPERATORS
//

Set Set::operator + (Set &t)  // union
{
    Set s(false);
    for (uint8_t  i=0; i<32; i++)
    {
        s._mem[i] = this->_mem[i] | t._mem[i];
    }
    return s;
}

Set Set::operator - (Set &t)  // diff
{
    Set s(false);
    for (uint8_t i=0; i<32; i++)
    {
        s._mem[i] = this->_mem[i] & ~t._mem[i];
    }
    return s;
}

Set Set::operator * (Set &t)  // intersection
{
    Set s(false);
    for (uint8_t i=0; i<32; i++)
    {
        s._mem[i] = this->_mem[i] & t._mem[i];
    }
    return s;
}

void Set::operator += (Set &t)  // union
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] |= t._mem[i];
    }
}

void Set::operator -= (Set &t)  // diff
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] &= ~t._mem[i];
    }
}

void Set::operator *= (Set &t)  // intersection
{
    for (uint8_t i=0; i<32; i++)
    {
        _mem[i] &= t._mem[i];
    }
}

bool Set::operator == (Set &t)  // equal
{
    for (uint8_t i=0; i<32; i++)
    {
        if (_mem[i] != t._mem[i]) return false;
    }
    return true;
}

bool Set::operator != (Set &t)  // not equal
{
    for (uint8_t i=0; i<32; i++)
    {
        if (_mem[i] != t._mem[i]) return true;
    }
    return false;
}

bool Set::operator <= (Set &t)  // subSet
{
    for (uint8_t i=0; i<32; i++)
    {
        if ((_mem[i] & ~t._mem[i]) > 0) return false;
    }
    return true;
}
//
// END OF FILE
//