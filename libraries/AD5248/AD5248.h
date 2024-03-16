#pragma once
//
//    FILE: AD5248.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Library for I2C digital potentiometer AD5243 + rheostat AD5248
//    DATE: 2023-12-12
//     URL: https://github.com/RobTillaart/AD5248


#include "Arduino.h"
#include "Wire.h"


#define AD5248_LIB_VERSION    (F("0.1.1"))


#define AD5248_OK             0
#define AD5248_ERROR          100


#define AD5248_MIDPOINT       127


class AD5248
{
public:
  AD5248(uint8_t address, TwoWire * wire = &Wire);

  bool    begin();
  bool    isConnected();
  uint8_t getAddress();

  //  RESET
  uint8_t reset();    //  reset both channels to AD524X_MIDPOINT
  uint8_t zeroAll();  //  set both channels to 0

  //  READ WRITE
  uint8_t read(const uint8_t channel);
  uint8_t write(const uint8_t channel, const uint8_t value);

  uint8_t midScaleReset(const uint8_t channel);
  uint8_t pmCount();


  //  DEBUGGING
  uint8_t readBackRegister();  //  returns the last value written in register.

  //  experimental - to be tested - use at own risk
  uint8_t shutDown();          //  datasheet P15


protected:
  uint8_t   _pmCount = 2;

  uint8_t   send(const uint8_t cmd, const uint8_t value);

  uint8_t   _lastValue[2];
  uint8_t   _address;
  TwoWire * _wire;
};


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASS  AD5243 potentiometer
//
class AD5243 : public AD5248
{
public:
  AD5243(TwoWire *wire = &Wire);
};


//  -- END OF FILE --

