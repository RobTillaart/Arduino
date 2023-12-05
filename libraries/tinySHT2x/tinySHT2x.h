#pragma once
//
//    FILE: tinySHT2x.h
//  AUTHOR: Rob Tillaart, Viktor Balint
// VERSION: 0.2.0
//    DATE: 2021-09-27
// PURPOSE: Arduino library for the SHT2x temperature and humidity sensor optimized for AVR tiny
//     URL: https://github.com/RobTillaart/tinySHT2x



#include "Arduino.h"
#include "Wire.h"

#define TINY_SHT2x_LIB_VERSION            (F("0.2.0"))

#define TINY_SHT2x_NO_VALUE               -999


class tinySHT2x
{
public:
  tinySHT2x(TwoWire *wire = &Wire);

  bool  begin();
  bool  isConnected();
  bool  reset();

  //  ASYNC INTERFACE
  void  requestTemperature();
  void  requestHumidity();
  float readTemperature();
  float readHumidity();
  
  //  SYNC INTERFACE
  float getTemperature(uint8_t del = 70);
  float getHumidity(uint8_t del = 30);


private:
  bool  writeCmd(uint8_t cmd);
  bool  readBytes(uint8_t n, uint8_t * val, uint8_t maxDuration);
  TwoWire* _wire;
};


//  -- END OF FILE --

