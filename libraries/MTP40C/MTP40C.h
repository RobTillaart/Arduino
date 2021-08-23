#pragma once
//
//    FILE: MTP40C.h
//  AUTHOR: Rob Tillaart
//    DATE: 2021-08-20
// VERSION: 0.1.1
// PURPOSE: Arduino library for MTP40C CO2 sensor
//     URL: https://github.com/RobTillaart/MTP40C
//
// HISTORY:
// see MTP40C.cpp file
//
// Based upon datasheet June 2020, version 2.0
//


#include "Arduino.h"


#define MTP40C_LIB_VERSION            (F("0.1.1"))
#define MTP40C_DEFAULT_ADDRESS        0x64
#define MTP40C_INVALID_AIR_PRESSURE   0x00
#define MTP40C_INVALID_GAS_LEVEL      0x00
#define MTP40C_INVALID_ADDRESS        0xFF



class MTP40C
{
public:
  MTP40C(Stream * str);

  bool     begin(uint8_t address = 0x64);
  bool     isConnected();

  uint8_t  getAddress();
  bool     setAddress(uint8_t address);

  float    getAirPressure();
  bool     setAirPressureReference(float apr);

  uint16_t getGasConcentration();  // returns PPM 

  //  CALIBRATION FUNCTIONS
  //  READ DATASHEET !!
  bool     setSinglePointCorrection(float spc);
  bool     getSinglePointCorrectionReady();

  bool     openSelfCalibration();
  bool     closeSelfCalibration();
  uint8_t  getSelfCalibrationStatus();
  bool     setSelfCalibrationHours(uint16_t hrs);
  uint16_t getSelfCalibrationHours();

  void     setGenericAddress()  { _useAddress = false; };
  void     setSpecificAddress() { _useAddress = true; };
  bool     useSpecificAddress() { return _useAddress; };

  // set timeout of serial communication.
  void     setTimeout(uint32_t to = 100) { _timeout = to; };
  uint32_t getTimeout() { return _timeout; };

  uint32_t lastRead() { return _lastRead; };

/////////////////////////


private:
  Stream * _ser;
  char     _buffer[256];       // datasheet states 256 - why ???
  uint8_t  _address     = 64;

  bool     _useAddress  = false;
  uint32_t _timeout     = 100;
  uint32_t _lastRead    = 0;

  float    _airPressure = 0;
  uint16_t _gasLevel    = 0;

  bool     request(uint8_t *data, uint8_t cmdlen, uint8_t anslen);
  uint16_t CRC(uint8_t *data, uint16_t len);

};



// -- END OF FILE -- 
