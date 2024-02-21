#pragma once
//
//    FILE: MTP40F.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-25
// VERSION: 0.2.0
// PURPOSE: Arduino library for MTP40F CO2 sensor
//     URL: https://github.com/RobTillaart/MTP40F


#include "Arduino.h"


#define MTP40F_LIB_VERSION                    (F("0.2.0"))


#define MTP40F_DEFAULT_ADDRESS                0x64

#define MTP40F_OK                             0x00
#define MTP40F_INVALID_AIR_PRESSURE           0x01
#define MTP40F_INVALID_GAS_LEVEL              0x02
#define MTP40F_INVALID_CRC                    0x10
#define MTP40F_INVALID_ADDRESS                0xFF
#define MTP40F_REQUEST_FAILED                 0xFFFF


class MTP40F
{
public:
  MTP40F(Stream * stream);

  bool     begin();

  int      getAirPressureReference();
  bool     setAirPressureReference(int apr = 1013);

  uint32_t getGasConcentration();  //  returns PPM

  void     suppressError(bool se) { _suppressError = se; };
  bool     getSuppressError()     { return _suppressError; };

  //  CALIBRATION FUNCTIONS
  //  READ DATASHEET !!
  bool     setSinglePointCorrection(uint32_t spc);
  bool     getSinglePointCorrectionReady();

  bool     openSelfCalibration();
  bool     closeSelfCalibration();
  uint8_t  getSelfCalibrationStatus();
  bool     setSelfCalibrationHours(uint16_t hours = 168);
  uint16_t getSelfCalibrationHours();


  //  set timeout of serial communication.
  void     setTimeout(uint32_t timeout = 100) { _timeout = timeout; };
  uint32_t getTimeout() { return _timeout; };

  uint32_t lastRead() { return _lastRead; };

  //       2 = MTP40C - other library
  //       3 = MTP40D - other library
  //       5 = MTP40F
  uint8_t  getType()  { return _type; };
  int      lastError();


//////////////////////////////////////////////////////
//
//  PROTECTED
//
protected:
  Stream * _ser;
  uint8_t  _buffer[16];

  uint32_t _timeout       = 100;
  uint32_t _lastRead      = 0;

  int      _airPressureReference = 0;
  uint32_t _gasLevel      = 0;
  uint8_t  _type          = 5;

  bool     _suppressError = false;
  int      _lastError     = MTP40F_OK;

  bool     request(uint8_t *data, uint8_t commandLength, uint8_t responseLength);
  uint16_t CRC(uint8_t *data, uint16_t length);
};


//  -- END OF FILE --

