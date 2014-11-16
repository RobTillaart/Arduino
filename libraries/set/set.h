//
//    FILE: set.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
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

#define SET_LIB_VERSION "0.1.01"

class set
{
public:
    set();
    set(set&);

    void clr();
    void invert();
    uint8_t count();

    void add(uint8_t);
    void sub(uint8_t);
    void invert(uint8_t);
    bool has(uint8_t);

    void operator = (set &t);       // assign
    void operator += (set &t);
    void operator -= (set &t);
    void operator &= (set &t);

    bool operator == (set&);
    bool operator != (set&);
    bool operator <= (set&);

    int first();
    int next();
    int prev();
    int last();

    // TODO
    // set(uint8_t*, uint8_t);      // constructor from uint8_t array
    // uint8_t size();
    // iterator - begin, next

    // uint8_t max();
    // uint8_t min();
    // inline bool empty() { return count() == 0; };
    // inline bool full() { return count() == 256; };

private:
    uint8_t _mem[32];  // can hold 0..255
    // uint8_t _cnt;
    // uint8_t _size;
    int _current;

};
#endif
//
// END OF FILE
//