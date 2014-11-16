//
//    FILE: set.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.04
// PURPOSE: SET library for Arduino
//     URL:
//
// HISTORY:
// see set.cpp file
//

#ifndef set_h
#define set_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define SET_LIB_VERSION "0.1.04"

class set
{
public:
    set();                      // create empty set
    set(set &t);                // create copy set

    void clr();                 // clear the set
    void invert();              // flip all elements in the set
    uint8_t count();            // return the #elements
    inline bool isEmpty() { return count() == 0; };

    void add(uint8_t);          // add element to the set
    void sub(uint8_t);          // remove element from set
    void invert(uint8_t);       // flip element in set
    bool has(uint8_t);          // element is in set

    set operator + (set &t);    // union
    set operator - (set &t);    // diff
    set operator * (set &t);    // intersection

    void operator += (set &t);  // union
    void operator -= (set &t);  // diff
    void operator *= (set &t);  // intersection

    bool operator == (set&);    // equal
    bool operator != (set&);    // not equal
    bool operator <= (set&);    // is subset

    // iterating through the set
    // returns value or -1 if not exist
    int first();                // find first element
    int next();                 // find next element
    int prev();                 // find previous element
    int last();                 // find last element

private:
    uint8_t _mem[32];           // can hold 0..255
    int _current;
};
#endif
//
// END OF FILE
//