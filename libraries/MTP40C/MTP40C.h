#pragma once
//
//    FILE: MTP40C.h
//  AUTHOR: Rob Tillaart
//    DATE: 2021-08-20
// VERSION: 0.3.1
// PURPOSE: Arduino library for MTP40C + MTP40D CO2 sensor
//     URL: https://github.com/RobTillaart/MTP40C
//
// Based upon datasheet June 2020, version 2.0


#include "Arduino.h"


#define MTP40_LIB_VERSION                     (F("0.3.1"))


#define MTP40_DEFAULT_ADDRESS                 0x64

#define MTP40_OK                              0x00
#define MTP40_INVALID_AIR_PRESSURE            0x01
#define MTP40_INVALID_GAS_LEVEL               0x02
#define MTP40_INVALID_ADDRESS                 0xFF
#define MTP40_REQUEST_FAILED                  0xFFFF


class MTP40
{
public:
  MTP40(Stream * stream);

  bool     begin(uint8_t address = MTP40_DEFAULT_ADDRESS);
  bool     isConnected();

  uint8_t  getAddress();
  bool     setAddress(uint8_t address = MTP40_DEFAULT_ADDRESS);

  float    getAirPressureReference();
  bool     setAirPressureReference(float apr);

  uint16_t getGasConcentration();  // returns PPM

  void     suppressError(bool se) { _suppressError = se; };
  bool     getSuppressError()     { return _suppressError; };

  //  CALIBRATION FUNCTIONS
  //  READ DATASHEET !!
  bool     setSinglePointCorrection(float spc);
  bool     getSinglePointCorrectionReady();

  bool     openSelfCalibration();
  bool     closeSelfCalibration();
  uint16_t getSelfCalibrationStatus();
  bool     setSelfCalibrationHours(uint16_t hours);
  uint16_t getSelfCalibrationHours();

  void     setGenericAddress()  { _useAddress = false; };
  void     setSpecificAddress() { _useAddress = true; };
  bool     useSpecificAddress() { return _useAddress; };

  //  set timeout of serial communication.
  void     setTimeout(uint32_t timeOut = 100) { _timeout = timeOut; };
  uint32_t getTimeout() { return _timeout; };

  uint32_t lastRead() { return _lastRead; };

  //       2   = MTP40C
  //       3   = MTP40D
  //       255 = MTP40 base class
  uint8_t  getType()  { return _type; };
  int      lastError();


//////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
protected:
  Stream * _ser;
  uint8_t  _buffer[24];   //  should be big enough.
  uint8_t  _address       = MTP40_DEFAULT_ADDRESS;

  bool     _useAddress    = false;
  uint32_t _timeout       = 100;
  uint32_t _lastRead      = 0;

  float    _airPressureReference = 0;
  uint16_t _gasLevel      = 0;
  uint8_t  _type          = 0xFF;

  bool     _suppressError = false;
  int      _lastError     = MTP40_OK;

  bool     request(uint8_t *data, uint8_t cmdlen, uint8_t anslen);

  uint16_t CRC(uint8_t *data, uint16_t len);

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t  reverse8(uint8_t in);
  uint16_t reverse16(uint16_t in);

#endif
};

/////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class MTP40C : public MTP40
{
public:
  MTP40C(Stream * str);
};


class MTP40D : public MTP40
{
public:
  MTP40D(Stream * str);

  //  TODO
  //  I2C interface
  // PWM interface
};


//  -- END OF FILE --

