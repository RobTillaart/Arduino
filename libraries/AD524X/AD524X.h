#pragma once
//
//    FILE: AD524X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.1
// PURPOSE: I2C digital PotentioMeter AD5241 AD5242
//    DATE: 2013-10-12
//     URL: https://github.com/RobTillaart/AD524X


#include "Arduino.h"
#include "Wire.h"


#define AD524X_LIB_VERSION    (F("0.5.1"))


#define AD524X_OK             0
#define AD524X_ERROR          100


#define AD524X_MIDPOINT       127


class AD524X
{
public:
  AD524X(const uint8_t address, TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();
  uint8_t getAddress();

  //  RESET
  uint8_t reset();    //  reset both channels to AD524X_MIDPOINT and O1/O2 to LOW
  uint8_t zeroAll();  //  set both channels to 0 and O1/O2 to LOW

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
  uint8_t shutDown();          //  datasheet P15


protected:
  uint8_t _pmCount = 0;

  uint8_t send(const uint8_t cmd, const uint8_t value);

  uint8_t _address;
  uint8_t _lastValue[2];
  uint8_t _O1;
  uint8_t _O2;

  TwoWire * _wire;
};


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES  AD5241 AD5242
//
class AD5241 : public AD524X
{
public:
  AD5241(const uint8_t address, TwoWire *wire = &Wire);

  uint8_t write(const uint8_t value);
  uint8_t write(const uint8_t value, const uint8_t O1, const uint8_t O2);

  uint8_t write(const uint8_t rdac, const uint8_t value);
  uint8_t write(const uint8_t rdac, const uint8_t value, const uint8_t O1, const uint8_t O2);
};


class AD5242 : public AD524X
{
public:
  AD5242(const uint8_t address, TwoWire *wire = &Wire);
};


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES  AD5280 AD5282
//
class AD5280 : public AD524X
{
public:
  AD5280(const uint8_t address, TwoWire *wire = &Wire);

  uint8_t write(const uint8_t value);
  uint8_t write(const uint8_t value, const uint8_t O1, const uint8_t O2);

  uint8_t write(const uint8_t rdac, const uint8_t value);
  uint8_t write(const uint8_t rdac, const uint8_t value, const uint8_t O1, const uint8_t O2);
};


class AD5282 : public AD524X
{
public:
  AD5282(const uint8_t address, TwoWire *wire = &Wire);
};


//  -- END OF FILE --

