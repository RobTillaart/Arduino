#pragma once
//
//    FILE: logic.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library for evaluation of larger logic conditions.
//    DATE: 2025-04-24
//     URL: https://github.com/RobTillaart/logic
//


#include "Arduino.h"

#define LOGIC_LIB_VERSION       (F("0.2.0"))


class logic
{
public:
  logic()
  {
    _table = 0;
  }

  void setTable(uint32_t table)
  {
    _table = table;
  }

  uint32_t getTable()
  {
    return _table;
  }


  ////////////////////////////////////////////////////

  void add(uint8_t idx)
  {
    _table |= (1UL << idx);
  }

  void remove(uint8_t idx)
  {
    _table &= ~(1UL << idx);
  }


  ////////////////////////////////////////////////////

  bool eval(bool a, bool b)
  {
    return (_table & (1UL << index(a, b)));
  }

  bool eval(bool a, bool b, bool c)
  {
    return (_table & (1UL << index(a, b, c)));
  }

  bool eval(bool a, bool b, bool c, bool d)
  {
    return (_table & (1UL << index(a, b, c, d)));
  }

  bool eval(bool a, bool b, bool c, bool d, bool e)
  {
    return (_table & (1UL << index(a, b, c, d, e)));
  }


  ////////////////////////////////////////////////////

  uint16_t neval(bool a, bool b)
  {
    uint16_t idx = index(a, b);
    return _table & (1UL << idx) ? idx : 0xFFFF;
  }

  uint16_t neval(bool a, bool b, bool c)
  {
    uint16_t idx = index(a, b, c);
    return _table & (1UL << idx) ? idx : 0xFFFF;
  }

  uint16_t neval(bool a, bool b, bool c, bool d)
  {
    uint16_t idx = index(a, b, c, d);
    return _table & (1UL << idx) ? idx : 0xFFFF;
  }

  uint16_t neval(bool a, bool b, bool c, bool d, bool e)
  {
    uint16_t idx = index(a, b, c, d, e);
    return _table & (1UL << idx) ? idx : 0xFFFF;
  }


  ////////////////////////////////////////////////////

  uint8_t countTrue(bool a, bool b)
  {
    uint8_t cnt = 0;
    if (b) cnt++;
    if (a) cnt++;
    return cnt;
  }

  uint8_t countTrue(bool a, bool b, bool c)
  {
    uint8_t cnt = 0;
    if (c) cnt++;
    if (b) cnt++;
    if (a) cnt++;
    return cnt;
  }

  uint8_t countTrue(bool a, bool b, bool c, bool d)
  {
    uint8_t cnt = 0;
    if (d) cnt++;
    if (c) cnt++;
    if (b) cnt++;
    if (a) cnt++;
    return cnt;
  }

  uint8_t countTrue(bool a, bool b, bool c, bool d, bool e)
  {
    uint8_t cnt = 0;
    if (e) cnt++;
    if (d) cnt++;
    if (c) cnt++;
    if (b) cnt++;
    if (a) cnt++;
    return cnt;
  }


  ////////////////////////////////////////////////////

  uint16_t index(bool a, bool b)
  {
    uint16_t _idx = 0;
    if (b) _idx += 2;
    if (a) _idx += 1;
    return _idx;
  }

  uint16_t index(bool a, bool b, bool c)
  {
    uint16_t _idx = 0;
    if (c) _idx += 4;
    if (b) _idx += 2;
    if (a) _idx += 1;
    return _idx;
  }

  uint16_t index(bool a, bool b, bool c, bool d)
  {
    uint16_t _idx = 0;
    if (d) _idx += 8;
    if (c) _idx += 4;
    if (b) _idx += 2;
    if (a) _idx += 1;
    return _idx;
  }

  uint16_t index(bool a, bool b, bool c, bool d, bool e)
  {
    uint16_t _idx = 0;
    if (e) _idx += 16;
    if (d) _idx += 8;
    if (c) _idx += 4;
    if (b) _idx += 2;
    if (a) _idx += 1;
    return _idx;
  }

private:
  uint32_t _table;
};


//  -- END OF FILE --

