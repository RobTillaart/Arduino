#pragma once
//
//    FILE: tinySHT2x.h
//  AUTHOR: Rob Tillaart, Viktor Balint
// VERSION: 0.1.3
//    DATE: 2021-09-27
// PURPOSE: Arduino library for the SHT2x temperature and humidity sensor optimized for AVR tiny
//     URL: https://github.com/RobTillaart/tinySHT2x
//


#include "Arduino.h"
#include "Wire.h"

#define TINY_SHT2x_LIB_VERSION            (F("0.1.3"))

#define TINY_SHT2x_NO_VALUE               -999


class tinySHT2x
{
public:
  tinySHT2x();

  void  begin(TwoWire *wire = &Wire);
  bool  reset();
  float getTemperature();
  float getHumidity();

private:
  bool  writeCmd(uint8_t cmd);
  bool  readBytes(uint8_t n, uint8_t *val, uint8_t maxDuration);
  TwoWire* _wire;
};


//  -- END OF FILE --

