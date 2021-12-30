#pragma once
//
//    FILE: CRC64.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC64
//     URL: https://github.com/RobTillaart/CRC


#include "Arduino.h"

#define CRC64_DEFAULT_POLYNOME      0x814141AB  // TODO


class CRC64
{
public:
  CRC64();

  // set parameters to default
  void     reset();       // set all to constructor defaults
  void     restart();     // reset crc with same parameters.

  // set parameters
  void     setPolynome(uint64_t polynome) { _polynome = polynome; };
  void     setStartXOR(uint64_t start)    { _startMask = start; };
  void     setEndXOR(uint64_t end)        { _endMask = end; };
  void     setReverseIn(bool reverseIn)   { _reverseIn = reverseIn; };
  void     setReverseOut(bool reverseOut) { _reverseOut = reverseOut; };

  void     add(uint8_t value);
  void     add(const uint8_t * array, uint8_t length);

  uint64_t getCRC();  // returns CRC
  uint64_t count()    { return _count; };

private:
  uint64_t _reverse(uint64_t value);
  uint8_t  _reverse8(uint8_t value);
  void     _update(uint8_t value);

  uint64_t _polynome;
  uint64_t _startMask;
  uint64_t _endMask;
  uint64_t _crc;
  bool     _reverseIn;
  bool     _reverseOut;
  bool     _started;
  uint64_t _count;
};


// -- END OF FILE --

