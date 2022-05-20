#pragma once
//
//    FILE: CRC64.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC64
//     URL: https://github.com/RobTillaart/CRC


#include "Arduino.h"

#include "CRC_polynomes.h"


class CRC64
{
public:
  CRC64();
  CRC64(uint64_t polynome, uint64_t XORstart, uint64_t XORend, bool reverseIn, bool reverseOut);

  // set parameters to default
  void     reset();       // set all to constructor defaults
  void     restart();     // reset crc with same parameters.

  // set parameters
  void     setPolynome(uint64_t polynome) { _polynome = polynome; };
  void     setStartXOR(uint64_t start)    { _startMask = start; };
  void     setEndXOR(uint64_t end)        { _endMask = end; };
  void     setReverseIn(bool reverseIn)   { _reverseIn = reverseIn; };
  void     setReverseOut(bool reverseOut) { _reverseOut = reverseOut; };

  // get parameters
  uint64_t getPolynome()   { return _polynome; };
  uint64_t getStartXOR()   { return _startMask; };
  uint64_t getEndXOR()     { return _endMask; };
  bool     getReverseIn()  { return _reverseIn; };
  bool     getReverseOut() { return _reverseOut; };

  void     add(uint8_t value);
  void     add(const uint8_t * array, uint16_t length);

  uint64_t getCRC();       // returns CRC
  uint64_t count()         { return _count; };

  // POWER USER ONLY
  void     enableYield()   { _canYield = true; };
  void     disableYield()  { _canYield = false; };

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
  bool     _canYield;
  uint64_t _count;
};


// -- END OF FILE --
