#pragma once
//
//    FILE: SLF3S.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-11-02
// VERSION: 0.1.0
// PURPOSE: Arduino library for the Sensirion I2C Low Flow sensor SLF3S
//     URL: https://github.com/RobTillaart/SLF3S
//
//  WORK IN PROGRESS, use with care.


#include "Arduino.h"
#include "Wire.h"


#define SLF3S_LIB_VERSION         (F("0.1.0"))


//  ERROR CODES
//  values <> 0 are errors.
const uint8_t SLF3S_OK         = 0x00;
const uint8_t SLF3S_CRC_ERROR  = 0x01;
const uint8_t SLF3S_NOT_READY  = 0x10;
const uint8_t SLF3S_NO_REQUEST = 0x11;


class SLF3S
{
public:
  SLF3S(uint8_t address = 0x08, TwoWire *wire = &Wire);

  bool     begin(uint16_t type = 600);
  bool     isConnected();
  uint8_t  getAddress();

  //  REQUEST
  int      requestH2O();
  int      requestIPA();
  bool     isReady();
  int      stopMeasurement();


  //  READ
  int      readFlow();
  int      readFlowTemp();
  int      readFlowTempSignal();
  float    getFlow();
  float    getTemperature();
  uint16_t getSignalFlags();


  //  ID and SERIAL
  uint32_t readProductID();
  uint64_t readSerialNR();


  //  ERROR HANDLING
  int      genericReset();
  int      getLastError();

  //  DEBUG
  //  uncomment if needed.
  //  uint16_t getRawFlow() { return _rawFlow; };
  //  uint16_t getRawTemp() { return _rawTemp; };
  //  void setFlowScale(float fs) { _flowScale = fs; };
  //  float getFlowScale() { return _flowScale; };
  //  float getTempScale() { return _tempScale; };


protected:
  uint8_t  _address = 0x08;  //  fixed
  TwoWire* _wire;

  int      _command(uint16_t cmd);
  int      _read(uint8_t * arr, uint8_t size);
  uint8_t  _crc8(uint8_t * arr, uint8_t size);

  uint16_t _rawFlow = 0;
  uint16_t _rawTemp = 0;
  uint16_t _rawSignal = 0;

  float    _flowScale = 1.0f / 10.0f;
  float    _tempScale = 1.0f / 200.0f;

  uint32_t _lastRequest = 0;
  uint32_t _lastRead = 0;
  int      _error;
};


//  -- END OF FILE --

