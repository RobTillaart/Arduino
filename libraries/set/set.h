//
//    FILE: set.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
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

#define SET_LIB_VERSION "0.1.00"

class set
{
public:
    set();  // TODO size
    set(set&);

    void add(uint8_t);
    void sub(uint8_t);
    bool has(uint8_t);

    void invert(uint8_t);

    void clr();
    void invert();
    uint8_t count();
    uint8_t size();

    // uint8_t max();
    // uint8_t min();

    // inline bool empty() { return count() == 0; };
    // inline bool full() { return count() == 256; };

    void operator = (set &t);       // assign
    void operator -= (set &t);
    void operator &= (set &t);
    void operator |= (set &t);

    bool operator == (set&);
    bool operator != (set&);
    bool operator < (set&);



    // iterator

private:
    uint8_t _mem[32];  // TODO SIZE PARAM enough to hold 0..255
    // uint8_t _cnt;
};
#endif
//
// END OF FILE
//