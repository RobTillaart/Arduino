#pragma once
//
//    FILE: set.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2014-09-11
// PURPOSE: SET library for Arduino
//     URL: https://github.com/RobTillaart/SET


#include "Arduino.h"


#define SET_LIB_VERSION         (F("0.2.2"))


class Set
{
public:
    explicit Set(const bool clear = true);     // create empty Set
    Set(const Set &t);                // create copy Set


    void     clear();                 // clear the Set
    void     clr() { clear(); };      // will become obsolete
    void     invert();                // flip all elements in the Set
    uint16_t count() const;           // return the #elements
    bool     isEmpty();
    bool     isFull();


    void add(const uint8_t);          // add element to the Set
    void sub(const uint8_t);          // remove element from Set
    void invert(const uint8_t);       // flip element in Set
    bool has(const uint8_t);          // element is in Set


    Set operator + (const Set &);     // union
    Set operator - (const Set &);     // diff
    Set operator * (const Set &);     // intersection

    void operator += (const Set &);   // union
    void operator -= (const Set &);   // diff
    void operator *= (const Set &);   // intersection


    bool operator == (const Set &) const;   // equal
    bool operator != (const Set &) const;   // not equal
    bool operator <= (const Set &) const;   // is subSet,
    // a superSet b is not implemented as one could 
    // say b subSet a (b <= a)
    // a <= b  


    // iterating through the Set
    // returns value or -1 if not exist
    int first();                // find first element
    int next();                 // find next element
    int prev();                 // find previous element
    int last();                 // find last element


private:
    uint8_t _mem[32];           // can hold 0..255
    uint8_t masks[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    int _current = -1;
	
    int findNext(const uint8_t, const uint8_t); // helper for first, next
    int findPrev(const uint8_t, const uint8_t); // helper for last, prev
};

// -- END OF FILE --
