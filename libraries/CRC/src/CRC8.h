#pragma once
//
//    FILE: CRC8.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC8
//     URL: https://github.com/RobTillaart/CRC


#include "CrcParameters.h"
#include "CrcDefines.h"


class CRC8
{
public:
  CRC8(uint8_t polynome = CRC8_POLYNOME,
       uint8_t initial  = CRC8_INITIAL,
       uint8_t xorOut   = CRC8_XOR_OUT,
       bool reverseIn   = CRC8_REV_IN,
       bool reverseOut  = CRC8_REV_OUT);

  void reset(uint8_t polynome = CRC8_POLYNOME,
             uint8_t initial  = CRC8_INITIAL,
             uint8_t xorOut   = CRC8_XOR_OUT,
             bool reverseIn   = CRC8_REV_IN,
             bool reverseOut  = CRC8_REV_OUT);

  void restart();
  uint8_t calc() const;
  crc_size_t count() const;
  void add(uint8_t value);
  void add(const uint8_t *array, crc_size_t length);
  void add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod);

  void setPolynome(uint8_t polynome) { _polynome = polynome; }
  void setInitial(uint8_t initial) { _initial = initial; }
  void setXorOut(uint8_t xorOut) { _xorOut = xorOut; }
  void setReverseIn(bool reverseIn) { _reverseIn = reverseIn; }
  void setReverseOut(bool reverseOut) { _reverseOut = reverseOut; }

  uint8_t getPolynome() const { return _polynome; }
  uint8_t getInitial() const { return _initial; }
  uint8_t getXorOut() const { return _xorOut; }
  bool getReverseIn() const { return _reverseIn; }
  bool getReverseOut() const { return _reverseOut; }

  [[deprecated("Use calc() instead")]]
  uint8_t getCRC() const;
  [[deprecated("Use setInitial() instead")]]
  void setStartXOR(uint8_t initial) { _initial = initial; }
  [[deprecated("Use setXorOut() instead")]]
  void setEndXOR(uint8_t xorOut) { _xorOut = xorOut; }
  [[deprecated("Use getInitial() instead")]]
  uint8_t getStartXOR() const { return _initial; }
  [[deprecated("Use getXorOut() instead")]]
  uint8_t getEndXOR() const { return _xorOut; }
  [[deprecated("Use add() with yieldPeriod instead")]]
  void enableYield() const {}
  [[deprecated("Use add() without yieldPeriod instead")]]
  void disableYield() const {}

private:
  void _add(uint8_t value);

  uint8_t _polynome;
  uint8_t _initial;
  uint8_t _xorOut;
  bool _reverseIn;
  bool _reverseOut;
  uint8_t _crc;
  crc_size_t _count;
};


//  -- END OF FILE --

