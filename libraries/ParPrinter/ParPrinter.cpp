//
//    FILE: parprinter.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: parallel printer class that implements the Print interface
//    DATE: 2013-09-30
//     URL:
//
// Released to the public domain
//

#include "ParPrinter.h"

ParPrinter::ParPrinter()
{
    // define pins
    for (uint8_t i = 0; i < 8; i++)
    {
        pin[i] = 2+i;
    }
}

void ParPrinter::begin()
{
    pinMode(BUSY, INPUT);
    pinMode(STROBE, OUTPUT);
    for (uint8_t i = 0; i < 8; i++)
    {
        pinMode(pin[i], OUTPUT);
    }
}

// write() must implement the virtual write of the Print class
size_t ParPrinter::write(uint8_t data)
{
    while(digitalRead(BUSY) == HIGH);

    for (uint8_t i = 0; i < 8; i++)
    {
        digitalWrite(pin[i], bitRead(data, i) );    // direct port access will be faster
    }
    digitalWrite(STROBE, LOW);
    delay(2);                       // main time consuming part, so max 500chars/second = 10 lines.
    digitalWrite(STROBE, HIGH);
    while (digitalRead(BUSY) == HIGH);

    return 1;
}

/*
derive CLass HP: ParPrinter
{
}
*/

// -- END OF FILE --
