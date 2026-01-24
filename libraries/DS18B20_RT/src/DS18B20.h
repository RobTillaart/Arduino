#pragma once
//
//    FILE: DS18B20.h
//  AUTHOR: Rob.Tillaart
// VERSION: 0.2.6
//    DATE: 2017-07-25
// PURPOSE: library for DS18B20 temperature sensor with minimal footprint
//     URL: https://github.com/RobTillaart/DS18B20_RT

//
//          BOTTOM VIEW
//
//                  PIN     MEANING
//           /---+
//          /  o |  1       GND
//          |  o |  2       DATA
//          \  o |  3       VCC
//           \---+
//


#include "OneWire.h"


#define DS18B20_LIB_VERSION     (F("0.2.6"))

//  Error Codes
const int DEVICE_DISCONNECTED = -127;
const int DEVICE_CRC_ERROR    = -128;
const int DEVICE_POR_ERROR    = -129;
const int DEVICE_GND_ERROR    = -130;  //  parasitic power Vdd must GND

//  configuration masks
const uint8_t DS18B20_CLEAR   = 0x00;  //  fast mode only temp register
const uint8_t DS18B20_CRC     = 0x01;  //  slow mode, all registers


typedef uint8_t DeviceAddress[8];
typedef uint8_t ScratchPad[9];


class DS18B20
{
public:
  explicit  DS18B20(OneWire * ow, uint8_t resolution = 9);
  bool      begin(uint8_t retries = 3);
  bool      isConnected(uint8_t retries = 3);
  bool      getAddress(uint8_t * buf);

  void      requestTemperatures(void);
  bool      isConversionComplete(void);
  //        backwards compatible
  float     getTempC(bool checkConnect = true);
  //        conversion wrapper Fahrenheit
  //        (keep in .h for footprint)
  float     getTempF() { return 32.0 + getTempC() * 1.8; };

  void      setOffset(float offset = 0);
  float     getOffset();

  bool      setResolution(uint8_t resolution = 9);
  uint8_t   getResolution();  //  returns cached value

  void      setConfig(uint8_t config);
  uint8_t   getConfig();


private:
  void          readScratchPad(uint8_t * scratchPad, uint8_t fields);
  void          _setResolution();

  DeviceAddress _deviceAddress;
  OneWire*      _oneWire;
  bool          _addressFound;

  uint8_t       _resolution;
  uint8_t       _config;
  float         _offset;
};


//  -- END OF FILE --

