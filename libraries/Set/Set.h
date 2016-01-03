//
//    FILE: Set.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.08
// PURPOSE: SET library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=279044.0
//
// HISTORY:
// see Set.cpp file
//

#ifndef Set_h
#define Set_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define SET_LIB_VERSION "0.1.08"

class Set
{
public:
    Set(bool clear = true);     // create empty Set
    Set(const Set &t);          // create copy Set

    void clr();                 // clear the Set
    void invert();              // flip all elements in the Set
    uint8_t count();            // return the #elements
    // bool isEmpty();

    void add(uint8_t);          // add element to the Set
    void sub(uint8_t);          // remove element from Set
    void invert(uint8_t);       // flip element in Set
    bool has(uint8_t);          // element is in Set

    Set operator + (Set &);     // union
    Set operator - (Set &);     // diff
    Set operator * (Set &);     // intersection

    void operator += (Set &);   // union
    void operator -= (Set &);   // diff
    void operator *= (Set &);   // intersection

    bool operator == (Set &);   // equal
    bool operator != (Set &);   // not equal
    bool operator <= (Set &);   // is subSet,
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
    int _current;
    int findNext(uint8_t, uint8_t); // helper for first, next
    int findPrev(uint8_t, uint8_t); // helper for last, prev
};
#endif
//
// END OF FILE
//