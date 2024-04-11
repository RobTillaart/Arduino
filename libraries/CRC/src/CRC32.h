#pragma once
//
//    FILE: CRC32.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC32
//     URL: https://github.com/RobTillaart/CRC


#include "CrcParameters.h"
#include "CrcDefines.h"


class CRC32
{
public:
  CRC32(uint32_t polynome = CRC32_POLYNOME,
        uint32_t initial  = CRC32_INITIAL,
        uint32_t xorOut   = CRC32_XOR_OUT,
        bool reverseIn    = CRC32_REV_IN,
        bool reverseOut   = CRC32_REV_OUT);

  void reset(uint32_t polynome = CRC32_POLYNOME,
             uint32_t initial  = CRC32_INITIAL,
             uint32_t xorOut   = CRC32_XOR_OUT,
             bool reverseIn    = CRC32_REV_IN,
             bool reverseOut   = CRC32_REV_OUT);

  void restart();
  uint32_t calc() const;
  crc_size_t count() const;
  void add(uint8_t value);
  void add(const uint8_t *array, crc_size_t length);
  void add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod);

  void setPolynome(uint32_t polynome) { _polynome = polynome; }
  void setInitial(uint32_t initial) { _initial = initial; }
  void setXorOut(uint32_t xorOut) { _xorOut = xorOut; }
  void setReverseIn(bool reverseIn) { _reverseIn = reverseIn; }
  void setReverseOut(bool reverseOut) { _reverseOut = reverseOut; }

  uint32_t getPolynome() const { return _polynome; }
  uint32_t getInitial() const { return _initial; }
  uint32_t getXorOut() const { return _xorOut; }
  bool getReverseIn() const { return _reverseIn; }
  bool getReverseOut() const { return _reverseOut; }

  [[deprecated("Use calc() instead")]]
  uint32_t getCRC() const;
  [[deprecated("Use setInitial() instead")]]
  void setStartXOR(uint32_t initial) { _initial = initial; }
  [[deprecated("Use setXorOut() instead")]]
  void setEndXOR(uint32_t xorOut) { _xorOut = xorOut; }
  [[deprecated("Use getInitial() instead")]]
  uint32_t getStartXOR() const { return _initial; }
  [[deprecated("Use getXorOut() instead")]]
  uint32_t getEndXOR() const { return _xorOut; }
  [[deprecated("Use add() with yieldPeriod instead")]]
  void enableYield() const {}
  [[deprecated("Use add() without yieldPeriod instead")]]
  void disableYield() const {}

private:
  void _add(uint8_t value);

  uint32_t _polynome;
  uint32_t _initial;
  uint32_t _xorOut;
  bool _reverseIn;
  bool _reverseOut;
  uint32_t _crc;
  crc_size_t _count;
};


//  -- END OF FILE --

