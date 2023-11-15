#pragma once
//
//    FILE: PIR.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2022-08-13
// PURPOSE: PIR library
//     URL: https://github.com/RobTillaart/PIR


#include "Arduino.h"


#define PIR_LIB_VERSION        (F("0.1.3"))

//
#define PIR_OK                0x00
#define PIR_ERR_NO_SENSOR     0xFF
#define PIR_ERR_ARRAY_FULL    0xFE
#define PIR_ERR_INDEX         0xFD


class PIR
{
public:
  PIR();

  //  adds a pin to the set
  //  returns the index or PIR_ARRAY_FULL
  uint8_t add(uint8_t pin);

  //  returns number of PIR sensors added.
  uint8_t count();

  //  MULTI PIN INTERFACE
  //  read all PIR sensors in the set
  //  returns a mask of HIGH / LOW values.
  //  not used slots will return 0.
  uint8_t read();

  //  returns last values read (bit mask) with read().
  uint8_t lastValue();

  //  returns bit mask of changed pins since last read().
  //  updates lastValue().
  uint8_t changed();


  //  SINGLE PIN INTERFACE
  //  read a specific PIR, faster than read() above.
  //  returns 0 or 1.  (in fact just a digitalRead(pin).
  //  does not affect lastValue()
  uint8_t read(uint8_t index);


protected:
  uint8_t  _pins[8]   = {0,0,0,0, 0,0,0,0};
  uint8_t  _count     = 0;
  uint8_t  _lastValue = 0;
};



// PIR16 or dynamic memory in base class
//
// class PIR16 : public PIR    //  MEGA
// {
//   static array of pins[16].
// }
//
// class PIR
// {
//    PIR(uint8_t size = 4);
//  ...
// }


// -- END OF FILE --

