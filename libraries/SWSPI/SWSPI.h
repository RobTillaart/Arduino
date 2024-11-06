#pragma once
//
//    FILE: SWSPI.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2024-10-29
// PURPOSE: Arduino library for SoftWare SPI.


#include "Arduino.h"
#include "SPI.h"


#define SWSPI_LIB_VERSION     (F("0.1.2"))


class SWSPI
{
public:

  SWSPI(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
  {
    _dataIn  = dataIn;
    _dataOut = dataOut;
    _clock   = clock;

    pinMode(_dataIn,  INPUT_PULLUP);
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock, LOW);
  };

  void begin()
  {
    _bitOrder = MSBFIRST;
    _dataMode = SPI_MODE0;
    _clockPolarity = 0;
    _clockPhase    = 0;
  };

  void end()
  {
  };

  //  LSBFIRST or MSBFIRST
  void setBitOrder(uint8_t bitOrder)
  {
    _bitOrder = bitOrder;
  };

  // SPI_MODE0 .. SPI_MODE3
  void setDataMode(uint8_t dataMode)
  {
    //  if (dataMode > 3) return;
    _dataMode = dataMode;
    _clockPhase    = _dataMode & 0x01;
    _clockPolarity = ((_dataMode & 0x02) > 0);
  };

  // void setClockDivider(uint8_t clockDiv)
  // {
    // uint8_t
    // //  not applicable
  // };


//////////////////////////////////////////////////////////////
//
//  TRANSFER FUNCTIONS
//
  //  void beginTransaction(SPISettings settings)
  void beginTransaction(uint8_t bitOrder, uint8_t dataMode)
  {
    _bitOrder = bitOrder;
    _dataMode = dataMode;

    //  MODE 0 = default
    _clockPolarity = ((_dataMode & 0x02) > 0);

    //  initialize clock.
    digitalWrite(_clock, _clockPolarity);
    //  noInterrupts();
  };

  void endTransaction()
  {
    //  interrupts();
  };


  //  blocking for ...
  //  optimization, look at FastShiftInOut, fix #9

  uint8_t transfer(uint8_t data)
  {
    if (_bitOrder == MSBFIRST)
    {
      data = _bitReverse(data);
    }
    uint8_t value = _transfer(data);
    return value;
  };

  uint16_t transfer16(uint16_t data)
  {
    if (_bitOrder == MSBFIRST)
    {
      data = _bitReverse(data);
    }
    uint16_t value = 0;
    value += _transfer(data & 0xFF);
    value <<= 8;
    data >>= 8;
    value += _transfer(data & 0xFF);
    return value;
  };


  uint32_t transfer24(uint32_t data)
  {
    if (_bitOrder == MSBFIRST)
    {
      data = _bitReverse(data) >> 8;
    }
    uint32_t value = 0;
    value += _transfer(data & 0xFF);
    value <<= 8;
    data >>= 8;
    value += _transfer(data & 0xFF);
    value <<= 8;
    data >>= 8;
    value += _transfer(data & 0xFF);
    return value;
  };


  uint32_t transfer32(uint32_t data)
  {
    if (_bitOrder == MSBFIRST)
    {
      data = _bitReverse(data);
    }
    uint32_t value = 0;
    value += _transfer(data & 0xFF);
    value <<= 8;
    data >>= 8;
    value += _transfer(data & 0xFF);
    value <<= 8;
    data >>= 8;
    value += _transfer(data & 0xFF);
    value <<= 8;
    data >>= 8;
    value += _transfer(data & 0xFF);
    return value;
  };

  void transfer(const void *buf, size_t count)
  {
    for (size_t i = 0; i < count; i++)
    {
      transfer(((uint8_t*)buf)[i]);
    }
  };


protected:


  uint8_t _transfer(uint8_t data)
  {
    uint8_t rv = 0;
    uint8_t _data = data;

    if (_dataMode == 0)
    {
      //  SPI_MODE0
      //  sampled on rising edge
      //  shift out on falling edge
      for (uint8_t mask = 0x01; mask; mask <<= 1)
      {
        digitalWrite(_dataOut, (_data & mask) > 0);
        //  Serial.print((_data & mask) > 0);
        digitalWrite(_clock, HIGH);
        digitalWrite(_clock, LOW);
        rv <<= 1;
        rv += digitalRead(_dataIn);
      }
    }
    else if (_dataMode == 1)
    {
      //  SPI_MODE1
      //  shift out on rising edge
      //  sampled on falling edge
      for (uint8_t mask = 0x01; mask; mask <<= 1)
      {
        digitalWrite(_clock, HIGH);
        rv <<= 1;
        rv += digitalRead(_dataIn);
        digitalWrite(_dataOut, (_data & mask) > 0);
        //  Serial.print((_data & mask) > 0);
        digitalWrite(_clock, LOW);
      }
    }
    else if (_dataMode == 2)
    {
      //  SPI_MODE2
      //  sampled on falling edge
      //  shift out on rising edge
      for (uint8_t mask = 0x01; mask; mask <<= 1)
      {
        digitalWrite(_dataOut, (_data & mask) > 0);
        //  Serial.print((_data & mask) > 0);
        digitalWrite(_clock, LOW);
        digitalWrite(_clock, HIGH);
        rv <<= 1;
        rv += digitalRead(_dataIn);
      }
    }
    else if (_dataMode == 3)
    {
      //  SPI_MODE3
      //  sampled on rising edge
      //  shift out on falling edge
      for (uint8_t mask = 0x01; mask; mask <<= 1)
      {
        digitalWrite(_clock, LOW);
        rv <<= 1;
        rv += digitalRead(_dataIn);
        digitalWrite(_dataOut, (_data & mask) > 0);
        //  Serial.print((_data & mask) > 0);
        digitalWrite(_clock, HIGH);
      }
    }
    //  Serial.print("  ");
    return rv;
  };


  // from https://github.com/RobTillaart/bitHelpers
  inline uint8_t _bitReverse(uint8_t value)
  {
    uint8_t x = value;
    x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
    x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
    x = (x >> 4) | (x << 4);
    return x;
  }


  uint16_t _bitReverse(uint16_t value)
  {
    uint16_t x = value;
    x = (((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1));
    x = (((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2));
    x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));
    x = (x >> 8) | (x << 8);
    return x;
  }


  uint32_t _bitReverse(uint32_t value)
  {
    uint32_t x = value;
    x = (((x & 0xAAAAAAAA) >> 1)  | ((x & 0x55555555) << 1));
    x = (((x & 0xCCCCCCCC) >> 2)  | ((x & 0x33333333) << 2));
    x = (((x & 0xF0F0F0F0) >> 4)  | ((x & 0x0F0F0F0F) << 4));
    x = (((x & 0xFF00FF00) >> 8)  | ((x & 0x00FF00FF) << 8));
    x = (x >> 16) | (x << 16);
    return x;
  }


  //  SPI pins
  uint8_t _dataIn;
  uint8_t _dataOut;
  uint8_t _clock;

  //  SPI parameters
  uint8_t _bitOrder = MSBFIRST;
  uint8_t _dataMode = SPI_MODE0;
  uint8_t _clockPolarity = 0;
  uint8_t _clockPhase    = 0;
};


///////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
//  readonly and write only class?
//


//  -- END OF FILE --

