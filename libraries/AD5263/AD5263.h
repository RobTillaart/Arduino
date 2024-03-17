#pragma once
//
//    FILE: AD5263.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library for I2C digital potentiometer AD5263 and compatibles.
//    DATE: 2023-10-09
//     URL: https://github.com/RobTillaart/AD5263
//          based upon AD524X interface.


#include "Arduino.h"
#include "Wire.h"


#define AD5263_LIB_VERSION    (F("0.1.3"))


#define AD5263_OK             0
#define AD5263_ERROR          100


#define AD5263_MIDPOINT       128  //  by datasheet.


class AD5263
{
public:
  AD5263(const uint8_t address, TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();
  uint8_t getAddress();

  //  RESET
  uint8_t reset();    //  reset all channels to AD5263_MIDPOINT and O1/O2 to LOW
  uint8_t zeroAll();  //  set all channels to 0 and O1/O2 to LOW
  uint8_t setAll(const uint8_t value);  //  set all channels to value and O1/O2 to LOW


  //  READ WRITE
  uint8_t read(const uint8_t rdac);
  uint8_t write(const uint8_t rdac, const uint8_t value);
  uint8_t write(const uint8_t rdac, const uint8_t value, const uint8_t O1, const uint8_t O2);


  //  IO LINES
  uint8_t setO1(const uint8_t value = HIGH);  //  HIGH (default) / LOW
  uint8_t setO2(const uint8_t value = HIGH);  //  HIGH (default) / LOW
  uint8_t getO1();
  uint8_t getO2();

  uint8_t midScaleReset(const uint8_t rdac);
  uint8_t pmCount();


  //  DEBUGGING
  uint8_t readBackRegister();  //  returns the last value written in register.

  //  experimental - to be tested - use at own risk
  uint8_t shutDown();


protected:
  uint8_t _pmCount = 4;

  uint8_t send(const uint8_t cmd, const uint8_t value);

  uint8_t _address;
  uint8_t _lastValue[4];
  uint8_t _O1;
  uint8_t _O2;

  TwoWire*  _wire;
};


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
//  None known so far.


//  -- END OF FILE --

