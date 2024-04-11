#pragma once
//
//    FILE: CRC64.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for CRC64
//     URL: https://github.com/RobTillaart/CRC


#include "CrcParameters.h"
#include "CrcDefines.h"


class CRC64
{
public:
  CRC64(uint64_t polynome = CRC64_POLYNOME,
        uint64_t initial  = CRC64_INITIAL,
        uint64_t xorOut   = CRC64_XOR_OUT,
        bool reverseIn    = CRC64_REV_IN,
        bool reverseOut   = CRC64_REV_OUT);

  void reset(uint64_t polynome = CRC64_POLYNOME,
             uint64_t initial  = CRC64_INITIAL,
             uint64_t xorOut   = CRC64_XOR_OUT,
             bool reverseIn    = CRC64_REV_IN,
             bool reverseOut   = CRC64_REV_OUT);

  void restart();
  uint64_t calc() const;
  crc_size_t count() const;
  void add(uint8_t value);
  void add(const uint8_t *array, crc_size_t length);
  void add(const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod);

  void setPolynome(uint64_t polynome) { _polynome = polynome; }
  void setInitial(uint64_t initial) { _initial = initial; }
  void setXorOut(uint64_t xorOut) { _xorOut = xorOut; }
  void setReverseIn(bool reverseIn) { _reverseIn = reverseIn; }
  void setReverseOut(bool reverseOut) { _reverseOut = reverseOut; }

  uint64_t getPolynome() const { return _polynome; }
  uint64_t getInitial() const { return _initial; }
  uint64_t getXorOut() const { return _xorOut; }
  bool getReverseIn() const { return _reverseIn; }
  bool getReverseOut() const { return _reverseOut; }

  [[deprecated("Use calc() instead")]]
  uint64_t getCRC() const;
  [[deprecated("Use setInitial() instead")]]
  void setStartXOR(uint64_t initial) { _initial = initial; }
  [[deprecated("Use setXorOut() instead")]]
  void setEndXOR(uint64_t xorOut) { _xorOut = xorOut; }
  [[deprecated("Use getInitial() instead")]]
  uint64_t getStartXOR() const { return _initial; }
  [[deprecated("Use getXorOut() instead")]]
  uint64_t getEndXOR() const { return _xorOut; }
  [[deprecated("Use add() with yieldPeriod instead")]]
  void enableYield() const {}
  [[deprecated("Use add() without yieldPeriod instead")]]
  void disableYield() const {}

private:
  void _add(uint8_t value);

  uint64_t _polynome;
  uint64_t _initial;
  uint64_t _xorOut;
  bool _reverseIn;
  bool _reverseOut;
  uint64_t _crc;
  crc_size_t _count;
};


//  -- END OF FILE --
