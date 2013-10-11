//
//    FILE: ParPrinter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: parallel printer class that implements the Print interface
//    DATE: 2013-09-30
//     URL:
//
// Released to the public domain
//

#ifndef ParPrinter_h
#define ParPrinter_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define PARPRINTER_VERSION "0.1.00"

#include "Print.h"

// constant pin numbers
#define STROBE          13  // same as build in LED ! makes it visible
#define BUSY            2
#define OUT_OF_PAPER    12

class ParPrinter: public Print
{
public:
    ParPrinter();  // lets assume fixed pins for now,
    void begin();
    size_t write(uint8_t);

private:
    uint8_t pin[8];
};
#endif
// -- END OF FILE --
