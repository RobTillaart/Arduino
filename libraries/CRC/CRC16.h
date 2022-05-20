#pragma once
//
//    FILE: CRC16.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC16
//     URL: https://github.com/RobTillaart/CRC


#include "Arduino.h"

#include "CRC_polynomes.h"


class CRC16
{
public:
  CRC16();
  CRC16(uint16_t polynome, uint16_t XORstart, uint16_t XORend, bool reverseIn, bool reverseOut);

  // set parameters to default
  void     reset();       // set all to constructor defaults
  void     restart();     // reset crc with same parameters.

  // set parameters
  void     setPolynome(uint16_t polynome) { _polynome = polynome; };
  void     setStartXOR(uint16_t start)    { _startMask = start; };
  void     setEndXOR(uint16_t end)        { _endMask = end; };
  void     setReverseIn(bool reverseIn)   { _reverseIn = reverseIn; };
  void     setReverseOut(bool reverseOut) { _reverseOut = reverseOut; };

  // get parameters
  uint16_t getPolynome()   { return _polynome; };
  uint16_t getStartXOR()   { return _startMask; };
  uint16_t getEndXOR()     { return _endMask; };
  bool     getReverseIn()  { return _reverseIn; };
  bool     getReverseOut() { return _reverseOut; };

  void     add(uint8_t value);
  void     add(const uint8_t * array, uint16_t length);

  uint16_t getCRC();       // returns CRC
  uint32_t count()         { return _count; };

  // POWER USER ONLY
  void     enableYield()   { _canYield = true; };
  void     disableYield()  { _canYield = false; };

private:
  uint16_t _reverse(uint16_t value);
  uint8_t  _reverse8(uint8_t value);
  void     _update(uint8_t value);

  uint16_t _polynome;
  uint16_t _startMask;
  uint16_t _endMask;
  uint16_t _crc;
  bool     _reverseIn;
  bool     _reverseOut;
  bool     _started;
  bool     _canYield;
  uint32_t _count;
};


// -- END OF FILE --

