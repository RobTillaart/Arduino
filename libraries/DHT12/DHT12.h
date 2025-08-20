#pragma once
//
//    FILE: DHT12.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.1
// PURPOSE: Arduino library for I2C DHT12 temperature and humidity sensor.
//     URL: https://github.com/RobTillaart/DHT12


#include "Arduino.h"
#include "Wire.h"

#define DHT12_LIB_VERSION                    (F("0.5.1"))

#define DHT12_OK                             0
#define DHT12_ERROR_CHECKSUM                -10
#define DHT12_ERROR_CONNECT                 -11
#define DHT12_MISSING_BYTES                 -12


class DHT12
{
public:
  DHT12(TwoWire *wire = &Wire);        //  to be tested explicitly

  bool     begin();

  bool     isConnected();

  int8_t   read();
  float    getHumidity();
  float    getTemperature();

  //  allows 1st order calibration
  void     setHumOffset(float offset = 0);
  void     setTempOffset(float offset = 0);
  float    getHumOffset();
  float    getTempOffset();

  uint32_t lastRead();


private:
  float    _humidity;
  float    _temperature;
  float    _humOffset;
  float    _tempOffset;
  uint8_t  _bits[5];
  uint32_t _lastRead;

  int      _readSensor();
  TwoWire* _wire;
};


//  -- END OF FILE --

