#pragma once
//
//    FILE: CRC32.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC32
//     URL: https://github.com/RobTillaart/CRC


#include "Arduino.h"

#define CRC32_DEFAULT_POLYNOME      0x04C11DB7


class CRC32
{
public:
  CRC32();

  // set parameters to default
  void     reset();       // set all to constructor defaults
  void     restart();     // reset crc with same parameters.

  // set parameters
  void     setPolynome(uint32_t polynome) { _polynome = polynome; };
  void     setStartXOR(uint32_t start)    { _startMask = start; };
  void     setEndXOR(uint32_t end)        { _endMask = end; };
  void     setReverseIn(bool reverseIn)   { _reverseIn = reverseIn; };
  void     setReverseOut(bool reverseOut) { _reverseOut = reverseOut; };

  void     add(uint8_t value);
  void     add(const uint8_t * array, uint8_t length);

  uint32_t getCRC();  // returns CRC
  uint32_t count()    { return _count; };

private:
  uint32_t _reverse(uint32_t value);
  uint8_t  _reverse8(uint8_t value);
  void     _update(uint8_t value);

  uint32_t _polynome;
  uint32_t _startMask;
  uint32_t _endMask;
  uint32_t _crc;
  bool     _reverseIn;
  bool     _reverseOut;
  bool     _started;
  uint32_t _count;
};


// -- END OF FILE --

