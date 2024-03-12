#pragma once
//
//    FILE: AD5246.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino Library for AD5246, I2C 128 step rheostat.
//    DATE: 2023-08-02
//     URL: https://github.com/RobTillaart/AD5246


// experimental - to be tested - use at own risk

#include "Arduino.h"
#include "Wire.h"


#define AD5246_LIB_VERSION   (F("0.2.1"))


#define AD5246_OK             0
#define AD5246_ERROR          100

#define AD5246_MIDPOINT       64


class AD5246
{
public:
  explicit AD5246(TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();

  uint8_t reset();

  uint8_t read();        //  read from cache (fast!)
  uint8_t readDevice();  //  read from device
  uint8_t write(const uint8_t value);


private:
  uint8_t send(const uint8_t value);

  const uint8_t _address = 0x2E;
  uint8_t _lastValue;

  TwoWire*  _wire;
};


//  -- END OF FILE --

