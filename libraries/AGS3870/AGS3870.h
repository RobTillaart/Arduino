#pragma once
//
//    FILE: AGS3870.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-14
// VERSION: 0.1.0
// PURPOSE: Arduino library for AGS3870 - Methane CH4 sensor.
//     URL: https://github.com/RobTillaart/AGS3870


#include "Arduino.h"
#include "Wire.h"


#define AGS3870_LIB_VERSION         (F("0.1.0"))

#define AGS3870_OK                  0
#define AGS3870_ERROR               -10
#define AGS3870_ERROR_CRC           -11
#define AGS3870_ERROR_READ          -12
#define AGS3870_ERROR_NOT_READY     -13


class AGS3870
{
public:
  struct RegisterData
  {
    uint8_t data[4];
    uint8_t crc;
    bool    crcValid;
  };

  struct ZeroCalibrationData
  {
    /**
     *  Warning, the exact meaning of this status is not fully documented.
     */
    uint16_t status;
    uint16_t value;
  };

  //  fixed address 26 = 0x1A
  explicit AGS3870(TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  void     reset();
  bool     isHeated() { return (millis() - _startTime) > 120000UL; };

  //  CONFIGURATION
  uint8_t  getAddress() { return _address; };
  uint8_t  getVersion();

  //  READ function, be sure to check lastError().
  uint32_t readPPM();   //  parts per million 10^6
  uint32_t lastPPM()    { return _lastPPM; };


  //  CALIBRATION
  //  to be called after at least 5 minutes in fresh air.
  //  use with care
  //  NOT TESTED
  bool     zeroCalibration() { return manualZeroCalibration(0); };
  bool     manualZeroCalibration(uint16_t value = 0);
  bool     getZeroCalibrationData(ZeroCalibrationData &data);
  //  READ RESISTANCE - datasheet 4.4
  //  Ω = ALT-234
  uint32_t readResistance();  //  Meaning unknown.


  //  STATUS
  uint32_t lastRead()   { return _lastRead; };  //  timestamp last measurement
  int      lastError();
  uint8_t  lastStatus() { return _status; };
  bool     dataReady()  { return (_status & 0x01) == 0; };

  //  Reading registers
  bool     readRegister(uint8_t address, RegisterData &reg);


private:
  uint32_t _readSensor();
  bool     _readRegister(uint8_t reg);
  bool     _writeRegister(uint8_t reg);

  uint32_t _startTime     = 0;
  uint32_t _lastRead      = 0;
  uint32_t _lastPPM       = 0;
  uint8_t  _status        = 0;
  uint8_t  _buffer[5];

  uint16_t _getDataMSB();
  uint16_t _getDataLSB();
  uint8_t  _CRC8(uint8_t * buf, uint8_t size);

  int      _error = AGS3870_OK;

  TwoWire*  _wire;
  const uint8_t _address = 0x1A;  //  26 decimal
};


//  -- END OF FILE --

