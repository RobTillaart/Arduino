//
//    FILE: set.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.7
//    DATE: 2014-09-11
// PURPOSE: SET library for Arduino
//     URL: https://github.com/RobTillaart/SET


#include "set.h"


/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
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
    for (uint8_t i = 0; i < 32; i++)
    {
        _mem[i] = t._mem[i];
    }
    _current = -1;
}


/////////////////////////////////////////////////////
//
//  METHODS
//
void Set::add(const uint8_t value)
{
    uint8_t idx = value / 8;
    _mem[idx] |= _masks[value & 7];
}


void Set::sub(const uint8_t value)
{
    uint8_t idx = value / 8;
    _mem[idx] &= ~_masks[value & 7];
}


void Set::invert(const uint8_t value)
{
    uint8_t idx = value / 8;
    _mem[idx] ^= _masks[value & 7];
}


void Set::addAll()
{
    memset(_mem, 0xFF, 32);
}


bool Set::has(const uint8_t value)
{
    uint8_t idx = value / 8;
    return (_mem[idx] & _masks[value & 7]) > 0;
}


uint16_t Set::count() const
{
    uint16_t cnt = 0;

    uint8_t i = 32;
    do
    {
        //  Kerningham bit count trick
        uint8_t b = _mem[--i];
        for (; b; cnt++)
        {
            b &= b-1;
        }
    }
    while (i != 0);
    return cnt;
}


void Set::clear()
{
    memset(_mem, 0, 32);
}


void Set::invert()
{
    uint8_t i = 32;
    do
    {
        _mem[--i] ^= 0xFF;
    }
    while (i != 0);
}


bool Set::isEmpty()
{
    uint8_t i = 32;
    do
    {
      if (_mem[--i] > 0) return false;
    }
    while (i != 0);
    return true;
}


bool Set::isFull()
{
    //  check two elements per loop
    //  is faster for full sets but slower for empty set.
    //  footprint is ~25 bytes larger
    //  overall performance gain
    uint8_t i = 32;
    do
    {
        if ((_mem[--i]) != 255) return false;
    }
    while (i != 0);
    return true;
}


int Set::setCurrent(const uint8_t current)
{
    _current = -1;
    if (has(current))
    {
      _current = current;
    }
    return _current;
}


int Set::first()
{
    if (has(0))
    {
      _current = 0;
      return _current;
    }
    return findNext(0, 0);
}


int Set::next()
{
    if (_current & 0x8000) return -1; // if current == -1
    _current++;
    uint8_t p = (uint8_t)_current / 8;
    uint8_t q = (uint8_t)_current & 7;
    return findNext(p, q);
}

// pointer math version ~12% faster but not for previous
// needs investigation.
// int Set::findNext(const uint8_t p, const uint8_t q)
// {
  // uint8_t * pp = &_mem[p];
  // uint8_t mask = 1 << q;
  // uint8_t j = q;
  // do
  // {
    // if (*pp != 0)
    // {
            // while (j < 8)
            // {
                // if (*pp & mask)
                // {
                    // _current = (pp - _mem) * 8 + j;
                    // return _current;
                // }
                // mask <<= 1;
        // j++;
            // }
    // }
    // j = 0;
    // mask = 1;
    // pp++;
  // }
  // while (pp != &_mem[31]);
    // _current = -1;
    // return _current;
// }


int Set::findNext(const uint8_t p, uint8_t q)
{
    for (uint8_t i = p; i < 32; i++)
    {
        uint8_t b = _mem[i];
        if (b != 0)
        {
            uint8_t mask = 1 << q;  //  _masks[q]
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
    if (has(255))
    {
      _current = 255;
      return _current;
    }
    return findPrev(31, 7);
}


int Set::getNth(const uint8_t n)
{
    if (n == 0) return -1;
    if (n == 1) return first();
    _current = first();
    int i = 1;
    while ((_current > -1) && (i < n))
    {
      _current = next();
      i++;
    }
    return _current;
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
        m = 128;  // 1 << 7;
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


Set Set::operator - (const Set &t)  //  diff
{
    Set s(false);
    for (uint8_t i = 0; i < 32; i++)
    {
        s._mem[i] = this->_mem[i] & ~t._mem[i];
    }
    return s;
}


Set Set::operator * (const Set &t)  //  intersection
{
    Set s(false);
    for (uint8_t i = 0; i < 32; i++)
    {
        s._mem[i] = this->_mem[i] & t._mem[i];
    }
    return s;
}


void Set::operator += (const Set &t)  //  union
{
    for (uint8_t i = 0; i < 32; i++)
    {
        _mem[i] |= t._mem[i];
    }
}


void Set::operator -= (const Set &t)  //  diff
{
    for (uint8_t i = 0; i < 32; i++)
    {
        _mem[i] &= ~t._mem[i];
    }
}


void Set::operator *= (const Set &t)  //  intersection
{
    for (uint8_t i = 0; i < 32; i++)
    {
        _mem[i] &= t._mem[i];
    }
}


bool Set::operator == (const Set &t) const  //  equal
{
    for (uint8_t i = 0; i < 32; i++)
    {
        if (_mem[i] != t._mem[i]) return false;
    }
    return true;
}


bool Set::operator != (const Set &t) const  //  not equal
{
    for (uint8_t i = 0; i < 32; i++)
    {
        if (_mem[i] != t._mem[i]) return true;
    }
    return false;
}


bool Set::operator <= (const Set &t) const  //  subSet
{
    for (uint8_t i = 0; i < 32; i++)
    {
        if ((_mem[i] & ~t._mem[i]) > 0) return false;
    }
    return true;
}


//  -- END OF FILE --

