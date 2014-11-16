//
//    FILE: set.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
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

#define SET_LIB_VERSION "0.1.03"

class set
{
public:

    set();                      // create empty set
    set(set &t);                // create copy set
    // TODO ??
    // set(uint8_t*, uint8_t);  // constructor from uint8_t array
    // set(uint8_t size);       // constructor with restricted size

    void clr();                 // clear the set
    void invert();              // flip all elements in the set
    uint8_t count();            // return the #elements
    inline bool isEmpty() { return count() == 0; };
    // TODO
    // inline uint8_t size() { return _size; };
    // inline bool isfull() { return count() == 256; };

    void add(uint8_t);          // add element to the set
    void sub(uint8_t);          // remove element from set
    void invert(uint8_t);       // flip element in set
    bool has(uint8_t);          // element is in set

    void operator = (set &t);   // assignment
    void operator += (set &t);  // union
    void operator -= (set &t);  // diff
    void operator *= (set &t);  // intersection

    bool operator == (set&);    // equal
    bool operator != (set&);    // not equal
    bool operator <= (set&);    // is subset

    // iterating through the set
    // returns value
    // or -1 if not exist
    int first();                // find first element
    int next();                 // find next element
    int prev();                 // find previous element
    int last();                 // find last element


private:
    uint8_t _mem[32];           // can hold 0..255
    // uint8_t _cnt;
    // uint8_t _size;
    int _current;

};
#endif
//
// END OF FILE
//