#pragma once
//
//    FILE: AD520X.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-24
// VERSION: 0.1.1
// PURPOSE: Arduino library for AD5204 and AD5206 digital potentiometers (+ older AD8400, AD8402, AD8403)
//     URL: https://github.com/RobTillaart/AD520X
//
// HISTORY:
// see AD520X.cpp file
//

#include "Arduino.h"
#include "SPI.h"

#define AD520X_LIB_VERSION   "0.1.1"

class AD520X
{
public:
  AD520X(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);  

  void     begin(uint8_t value = 128);
  void     setValue(uint8_t pm, uint8_t value);
  void     setAll(uint8_t value);
  uint8_t  getValue(uint8_t pm);

  void     reset(uint8_t value = 128);
  int      pmCount()   { return _pmCount; };

  void     powerOn()   { digitalWrite(_shutdown, LOW); };
  void     powerOff()  { digitalWrite(_shutdown, HIGH); };
  void     powerDown() { powerOff(); };      // will become obsolete 
  bool     isPowerOn() { return digitalRead(_shutdown) == LOW; };


protected:
  uint8_t _data;
  uint8_t _clock;
  uint8_t _select;
  uint8_t _reset;
  uint8_t _shutdown;
  bool    _hwSPI = 3;
  uint8_t _value[6];
  uint8_t _pmCount = 6;

  void    updateDevice(uint8_t pm);
  void    swSPI_transfer(uint8_t value);
};


/////////////////////////////////////////////////////////////////////////////

class AD5206 : public AD520X
{
public:
  AD5206(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut = 255, uint8_t clock = 255);
};

class AD5204 : public AD520X
{
public:
  AD5204(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut = 255, uint8_t clock = 255); 
};

class AD8400 : public AD520X
{
public:
  AD8400(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut = 255, uint8_t clock = 255); 
};

class AD8402 : public AD520X
{
public:
  AD8402(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut = 255, uint8_t clock = 255); 
};

class AD8403 : public AD520X
{
public:
  AD8403(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut = 255, uint8_t clock = 255); 
};

// -- END OF FILE -- 
