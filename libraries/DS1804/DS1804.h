#pragma once
//
//    FILE: DS1804.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 24-11-11
// PURPOSE: Arduino library for DS1804 Nonvolatile Trimmer Potentiometer.
//     URL: https://github.com/RobTillaart/DS1804


#include "Arduino.h"

#define DS1804_LIB_VERSION               (F("0.1.1"))


class DS1804
{
public:
  DS1804(uint8_t csPin, uint8_t incPin, uint8_t udPin)
  {
    _csPin = csPin;
    _incPin = incPin;
    _udPin = udPin;
  };


  void begin(bool b = false)
  {
    pinMode(_csPin, OUTPUT);
    pinMode(_incPin, OUTPUT);
    digitalWrite(_incPin, LOW);
    pinMode(_udPin, OUTPUT);
    digitalWrite(_udPin, HIGH);

    select(b);
  };


  inline void select(bool b)
  {
    //  inactive = LOW
    digitalWrite(_csPin, b ? LOW : HIGH);
  };


  inline bool selected()
  {
    return (digitalRead(_csPin) != LOW);
  };


  void moveUp(uint8_t n = 1)
  {
    if (n > 100) n = 100;
    digitalWrite(_udPin, HIGH);
    while (n-- > 0)
    {
      //  one step per high-to-low transition
      //  min pulselength 100 nsec => uncomment delays if needed.
      digitalWrite(_incPin, HIGH);
      //  delayMicroseconds(1);
      digitalWrite(_incPin, LOW);
      //  delayMicroseconds(1);
    }
  };


  void moveDown(uint8_t n = 1)
  {
    if (n > 100) n = 100;
    digitalWrite(_udPin, LOW);
    while (n-- > 0)
    {
      //  one step per high-to-low transition
      //  min pulselength 100 nsec => uncomment delays if needed.
      digitalWrite(_incPin, HIGH);
      //  delayMicroseconds(1);
      digitalWrite(_incPin, LOW);
      //  delayMicroseconds(1);
    }
  };


  //  device may be blocking for 10 ms
  void saveEEPROM()
  {
    digitalWrite(_incPin, HIGH);
    digitalWrite(_csPin, LOW);
    digitalWrite(_csPin, HIGH);
    digitalWrite(_incPin, LOW);
  };


protected:
  uint8_t _csPin;
  uint8_t _incPin;
  uint8_t _udPin;

};


//  -- END OF FILE --

