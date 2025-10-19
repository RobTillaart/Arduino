#pragma once
//
//    FILE: logic.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for evaluation of larger logic conditions.
//    DATE: 2025-04-24
//     URL: https://github.com/RobTillaart/logic
//


#include "Arduino.h"

#define LOGIC_LIB_VERSION       (F("0.1.0"))


class logic
{
public:
  logic() 
  {
    _table = 0;
    _idx = 0;
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
  
  bool eval(bool a, bool b)
  {
    return (_table & (0x08 >> index(a, b)));
  }

  bool eval(bool a, bool b, bool c)
  {
    return (_table & (0x80 >> index(a, b, c)));
  }
  
  bool eval(bool a, bool b, bool c, bool d)
  {
    return (_table & (0x8000 >> index(a, b, c, d)));
  }

  bool eval(bool a, bool b, bool c, bool d, bool e)
  {
    return (_table & (0x80000000 >> index(a, b, c, d, e)));
  }


  ////////////////////////////////////////////////////
  
  uint16_t neval(bool a, bool b)
  {
    return eval(a, b) ? _idx : 0xFFFF;
  }
  
  uint16_t neval(bool a, bool b, bool c)
  {
    return eval(a, b, c) ? _idx : 0xFFFF;
  }
  
  uint16_t neval(bool a, bool b, bool c, bool d)
  {
    return eval(a, b, c, d) ? _idx : 0xFFFF;
  }
  
  uint16_t neval(bool a, bool b, bool c, bool d, bool e)
  {
    return eval(a, b, c, d, e) ? _idx : 0xFFFF;
  }


  ////////////////////////////////////////////////////

  uint16_t index(bool a, bool b)
  {
    uint16_t _idx = 0;
    if (a) _idx += 2;
    if (b) _idx += 1;
    return _idx;
  }

  uint16_t index(bool a, bool b, bool c)
  {
    uint16_t _idx = 0;
    if (a) _idx += 4;
    if (b) _idx += 2;
    if (c) _idx += 1;
    return _idx;
  }

  uint16_t index(bool a, bool b, bool c, bool d)
  {
    uint16_t _idx = 0;
    if (a) _idx += 8;
    if (b) _idx += 4;
    if (c) _idx += 2;
    if (d) _idx += 1;
    return _idx;
  }

  uint16_t index(bool a, bool b, bool c, bool d, bool e)
  {
    uint16_t _idx = 0;
    if (a) _idx += 16;
    if (b) _idx += 8;
    if (c) _idx += 4;
    if (d) _idx += 2;
    if (e) _idx += 1;
    return _idx;
  }

private:
  uint32_t _table;
  uint16_t _idx;
};


//  -- END OF FILE --

