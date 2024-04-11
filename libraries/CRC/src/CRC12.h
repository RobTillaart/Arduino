#pragma once
//
//    FILE: CRC12.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC12
//     URL: https://github.com/RobTillaart/CRC
//          https://github.com/RobTillaart/CRC/issues/13


#include "CrcParameters.h"
#include "CrcDefines.h"


class CRC12
{
public:
  CRC12(uint16_t polynome = CRC12_POLYNOME,
        uint16_t initial  = CRC12_INITIAL,
        uint16_t xorOut   = CRC12_XOR_OUT,
        bool reverseIn    = CRC12_REV_IN,
        bool reverseOut   = CRC12_REV_OUT);

  void reset(uint16_t polynome = CRC12_POLYNOME,
             uint16_t initial  = CRC12_INITIAL,
             uint16_t xorOut   = CRC12_XOR_OUT,
             bool reverseIn    = CRC12_REV_IN,
             bool reverseOut   = CRC12_REV_OUT);

  void restart();
  uint16_t calc() const;
  crc_size_t count() const;
  void add(uint8_t value);
  void add(const uint8_t *array, crc_size_t length);
  void add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod);

  void setPolynome(uint16_t polynome) { _polynome = polynome; }
  void setInitial(uint16_t initial) { _initial = initial; }
  void setXorOut(uint16_t xorOut) { _xorOut = xorOut; }
  void setReverseIn(bool reverseIn) { _reverseIn = reverseIn; }
  void setReverseOut(bool reverseOut) { _reverseOut = reverseOut; }

  uint16_t getPolynome() const { return _polynome; }
  uint16_t getInitial() const { return _initial; }
  uint16_t getXorOut() const { return _xorOut; }
  bool getReverseIn() const { return _reverseIn; }
  bool getReverseOut() const { return _reverseOut; }

  [[deprecated("Use calc() instead")]]
  uint16_t getCRC() const;
  [[deprecated("Use setInitial() instead")]]
  void setStartXOR(uint16_t initial) { _initial = initial; }
  [[deprecated("Use setXorOut() instead")]]
  void setEndXOR(uint16_t xorOut) { _xorOut = xorOut; }
  [[deprecated("Use getInitial() instead")]]
  uint16_t getStartXOR() const { return _initial; }
  [[deprecated("Use getXorOut() instead")]]
  uint16_t getEndXOR() const { return _xorOut; }
  [[deprecated("Use add() with yieldPeriod instead")]]
  void enableYield() const {}
  [[deprecated("Use add() without yieldPeriod instead")]]
  void disableYield() const {}

private:
  void _add(uint8_t value);

  uint16_t _polynome;
  uint16_t _initial;
  uint16_t _xorOut;
  bool _reverseIn;
  bool _reverseOut;
  uint16_t _crc;
  crc_size_t _count;
};


//  -- END OF FILE --

