#pragma once
//
//    FILE: SGP30.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2021-06-24
// PURPOSE: Arduino library for SGP30 environment sensor.
//     URL: https://github.com/RobTillaart/SGP30
//          https://www.adafruit.com/product/3709


#include "Arduino.h"
#include "Wire.h"

#define SGP30_LIB_VERSION               (F("0.3.1"))

#define SGP30_OK                        0x00
#define SGP30_ERROR_CRC                 0xFF
#define SGP30_ERROR_I2C                 0xFE


class SGP30
{
public:
  explicit SGP30(TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  //  WARNING resets all I2C devices that support this call !!
  void     GenericReset();


  //  META
  bool     getID();
  uint16_t getFeatureSet();
  bool     measureTest();   //  need a better name


  //  MEASUREMENTS
  //  lastMeasurement works only with measure();
  //                 not with async calls.
  uint32_t lastMeasurement() { return _lastTime; };
  //  all == false ==> only TVOC and eCO2
  //  blocks 15 - 40 milliseconds  (depends on parameter all).
  bool     measure(bool all = false);

  //  async interface
  void     request();
  bool     read();
  void     requestRaw();
  bool     readRaw();

  //  get the data                                 //   UNITS
  uint16_t getTVOC()        { return _tvoc; };     //   PPB
  uint16_t getCO2()         { return _co2; };      //   PPM
  uint16_t getH2_raw()      { return _h2; };       //   UNKNOWN
  uint16_t getEthanol_raw() { return _ethanol; };  //   UNKNOWN
  float    getH2();         //  experimental       //   PPM
  float    getEthanol();    //  experimental       //   PPM


  //  CALIBRATION - read datasheet
  //  T  in °C
  //  RH == 0..100
  float    setRelHumidity(float T, float RH);      //  P10
  //  Absolute humidity in grams / m3
  //  set Abs Hum to 0 to disables it...
  void     setAbsHumidity(float absoluteHumidity);

  void     setBaseline(uint16_t CO2, uint16_t TVOC);
  bool     getBaseline(uint16_t *CO2, uint16_t *TVOC);

  //  See Inceptive Baseline for TVOC measurements in data sheet
  void     setTVOCBaseline(uint16_t TVOC);
  bool     getTVOCBaseline(uint16_t *TVOC);


  //  EXPERIMENTAL
  //  13119 = average raw measured outside 22°C  (example)
  void      setSrefH2(uint16_t s = 13119)      { _srefH2 = s; };
  uint16_t  getSrefH2()                        { return _srefH2; };
  //  18472 = average raw measured outside 22°C  (example)
  void      setSrefEthanol(uint16_t s = 18472) { _srefEth = s; };
  uint16_t  getSrefEthanol()                   { return _srefEth; };


  //  MISCELLANEOUS
  int      lastError();

  //  need an access function to prevent writing _id[]
  //  for now it is OK.  TODO private?
  uint8_t  _id[6];


private:
  uint8_t  _address;
  int      _error;
  uint32_t _lastTime;
  uint32_t _lastRequest;

  //  TODO improve?
  int      _command(uint16_t cmd);
  int      _command(uint16_t cmd, uint16_t v1);
  int      _command(uint16_t cmd, uint16_t v1, uint16_t v2);

  uint8_t  _CRC8(uint16_t val);
  void     _init();

  uint16_t _tvoc;
  uint16_t _co2;
  uint16_t _h2;
  uint16_t _ethanol;

  //  experimental
  //  average raw values measured outside 22°C
  uint16_t _srefH2  = 13119;
  uint16_t _srefEth = 18472;

  TwoWire*  _wire;
};


//  -- END OF FILE --

