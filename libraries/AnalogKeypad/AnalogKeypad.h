//
//    FILE: AnalogKeypad.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2019-01-31
// PURPOSE: Class for analog keypad
//     URL: https://github.com/RobTillaart/Arduino.git
//
// Released to the public domain
//

#ifndef AnalogKeypad_h
#define AnalogKeypad_h

#include "Arduino.h"

#define ANALOGKEYPAD_LIB_VERSION "0.1.2"

#define NOKEY     0x00
#define PRESSED   0x80
#define RELEASED  0x40
#define REPEATED  0x20
#define CHANGED   0x10

class AnalogKeypad
{
public:
  explicit AnalogKeypad(const uint8_t pin);

  // returns 0 if no key pressed
  // otherwise returns key pressed first => ignoring fluctuations
  // 2nd or more presses simultaneous are ignored
  uint8_t pressed();

  // returns 0 if no key pressed
  // otherwise returns key pressed (may fluctuate)
  uint8_t read();

  
  // event alike approach
  // switch(int e = event())
  uint8_t event();
  uint8_t key() { return _lastKey; } ;

private:
  uint8_t rawRead();
  uint8_t _pin;
  uint8_t _lastKey;
};

#endif
// -- END OF FILE --