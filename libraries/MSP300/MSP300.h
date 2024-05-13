#pragma once
//
//    FILE: MSP300.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library for I2C MSP300 pressure transducer.
//     URL: https://github.com/RobTillaart/MSP300


#include "Arduino.h"
#include "Wire.h"


#define MSP300_LIB_VERSION          (F("0.3.0"))


//  ERROR AND STATUS CODES
#define MSP300_OK               0
#define MSP300_RESERVED         1
#define MSP300_STALE_DATA       2
#define MSP300_READ_ERROR       3
#define MSP300_REQUEST_ERROR    100


/////////////////////////////////////////////////
//
//  MSP300
//

class MSP300
{
public:
  explicit MSP300(const uint8_t deviceAddress = 0x28, TwoWire *wire = &Wire);

  bool    begin(int maxValue);
  bool    isConnected();

  //      set the address to select other sensor if needed.
  bool    setAddress(const uint8_t deviceAddress);
  uint8_t getAddress();

  //  READ
  uint32_t readP();      //  returns _raw, reads S + P
  uint32_t readPT();     //  returns _raw, reads S + P + T
  uint8_t  getStatus();  //  0 == OK, other = error.
  float    getPressure();
  float    getTemperature();

  //  CALIBRATION
  //  use with care!
  //  read datasheet page 5
  //  Pmin = count at zero pressure
  //  Pmax = count at max pressure (which depends on sensor);
  //  1000 and 15000 are the default counts from datasheet.
  void     setPressureCounts(int Pmin = 1000, int Pmax = 15000);
  int      getPmin();
  int      getPmax();

  //  ERROR HANDLING
  int      lastError();


private:
  uint8_t   _address;
  int       _error;
  int       _maxValue;

  float     _pressure;
  float     _temperature;
  uint8_t   _status;

  float     _pressureFactor;
  int       _Pmin;
  int       _Pmax;

  TwoWire*  _wire;
  void      _request();
  uint32_t  _read(uint8_t bytes);
};


//  -- END OF FILE --

