#pragma once
//
//    FILE: MSP300.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for I2C MSP300 pressure transducer.
//     URL: https://github.com/RobTillaart/MSP300


#include "Arduino.h"
#include "Wire.h"


#define MSP300_LIB_VERSION          (F("0.1.1"))


//  ERROR CODES
#define MSP300_OK         0
#define MSP300_ERROR      100


/////////////////////////////////////////////////
//
//  MSP300
//

class MSP300
{
public:
  explicit MSP300(const uint8_t deviceAddress = 0x20, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool    begin(int sda, int scl, int maxValue);
#endif
  bool    begin(int maxValue);
  bool    isConnected();

  //      set the address to select other sensor if needed.
  bool    setAddress(const uint8_t deviceAddress);
  uint8_t getAddress();

  //  READ
  uint32_t readPT();
  float    getPressure();
  float    getTemperature();

  //  CALIBRATION
  void     setPressureCounts(uint16_t Pmin = 1000, uint16_t Pmax = 15000);

  //  ERROR HANDLING
  int      lastError();


private:
  uint8_t   _address;
  int       _error;
  int       _maxValue;
  uint32_t  _raw;
  //  default span reversed.
  float     _pressureFactor = 1.0/14000.0;

  TwoWire*  _wire;
  void      _request();
  void      _read(uint8_t bytes);
};


//  -- END OF FILE --

