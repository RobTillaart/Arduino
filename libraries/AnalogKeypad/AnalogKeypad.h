#pragma once
//
//    FILE: AnalogKeypad.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.5
//    DATE: 2019-01-31
// PURPOSE: Class for (Robotdyn) 4x4 and 4x3 analogue keypad
//     URL: https://github.com/RobTillaart/AnalogKeypad


#include "Arduino.h"


#define ANALOGKEYPAD_LIB_VERSION      (F("0.2.5"))

#define NOKEY         0x00
#define PRESSED       0x80
#define RELEASED      0x40
#define REPEATED      0x20
#define CHANGED       0x10


class AnalogKeypad
{
public:
  //  bits is resolution of the internal ADC.
  explicit AnalogKeypad(const uint8_t analogPin, const uint8_t bitsADC = 10);

  //  returns 0 if no key pressed
  //  otherwise returns key pressed first => ignoring fluctuations
  //  2nd or more presses simultaneous are ignored
  uint8_t pressed();

  //  returns 0 if no key pressed
  //  otherwise returns key pressed (may fluctuate)
  uint8_t read();

  //  event alike approach
  //  switch(int e = event()) see examples
  uint8_t event();
  uint8_t key();


private:
  uint8_t _rawRead();
  uint8_t _analogPin;
  uint8_t _analogShift;
  uint8_t _lastKey;
};


//  -- END OF FILE --

