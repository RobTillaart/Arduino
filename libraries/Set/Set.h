#pragma once
//
//    FILE: set.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.7
//    DATE: 2014-09-11
// PURPOSE: SET library for Arduino
//     URL: https://github.com/RobTillaart/SET


#include "Arduino.h"


#define SET_LIB_VERSION               (F("0.2.7"))


class Set
{
public:
    explicit Set(const bool clear = true);     //  create empty Set
    Set(const Set &t);                 //  create copy Set

    void     clear();                  //  clear the Set
    void     clr() { clear(); };       //  will become obsolete 0.3.0
    void     invert();                 //  flip all elements in the Set
    void     addAll();                 //  add all elements
    uint16_t count() const;            //  return the #elements
    bool     isEmpty();
    bool     isFull();


    void add(const uint8_t value);     //  add element to the Set
    void sub(const uint8_t value);     //  remove element from Set
    void invert(const uint8_t value);  //  flip element in Set
    bool has(const uint8_t value);     //  element is in Set


    Set operator + (const Set &);      //  union
    Set operator - (const Set &);      //  diff
    Set operator * (const Set &);      //  intersection

    void operator += (const Set &);    //  union
    void operator -= (const Set &);    //  diff
    void operator *= (const Set &);    //  intersection


    bool operator == (const Set &) const;   //  equal
    bool operator != (const Set &) const;   //  not equal
    bool operator <= (const Set &) const;   //  is subSet,
    //  a superSet b is not implemented as one could
    //  say b subSet a (b <= a)
    //  a <= b


    //  iterating through the Set
    //  returns value or -1 if not exist
    int setCurrent(const uint8_t current);  //  set element as current
    int first();                            //  find first element
    int next();                             //  find next element
    int prev();                             //  find previous element
    int last();                             //  find last element
    int getNth(const uint8_t n);            //  find Nth element in a set (from start)


private:
    uint8_t _mem[32];           // can hold 0..255
    uint8_t _masks[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    int _current = -1;

    int findNext(const uint8_t p, const uint8_t q); //  helper for first, next
    int findPrev(const uint8_t p, const uint8_t q); //  helper for last, prev
};


//  -- END OF FILE --

