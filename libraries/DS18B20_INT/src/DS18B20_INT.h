#pragma once
//
//    FILE: DS18B20_INT.h
//  AUTHOR: Rob.Tillaart
// VERSION: 0.4.1
//    DATE: 2017-07-25
// PURPOSE: Minimalistic library for DS18B20 temperature sensor
//          uses only integer math (no float to minimize footprint)
//     URL: https://github.com/RobTillaart/DS18B20_INT
//          https://github.com/RobTillaart/DS18B20_RT

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


#include "Arduino.h"
#include "OneWire.h"


#define DS18B20_INT_LIB_VERSION       (F("0.4.1"))

//  adjust if you need values outside guaranteed range
//  (See DTCL #290)
constexpr int DS18B20_MINIMUM = -55;
constexpr int DS18B20_MAXIMUM = +125;

//  Error Codes (not all used, library specific)
constexpr int DEVICE_DISCONNECTED = -127;
constexpr int DEVICE_CRC_ERROR    = -128;
constexpr int DEVICE_POR_ERROR    = -129;
constexpr int DEVICE_GND_ERROR    = -130;  //  parasitic power Vdd must GND


typedef uint8_t DeviceAddress[8];
typedef uint8_t ScratchPad[9];


class DS18B20_INT
{
public:
  explicit  DS18B20_INT(OneWire * ow);
  bool      begin(uint8_t retries = 3);
  bool      isConnected(uint8_t retries = 3);
  bool      getAddress(uint8_t * buf);

  void      requestTemperatures(void);
  int16_t   getTempC(bool checkConnect = true);
  bool      isConversionComplete(void);

  //  for getTempCentiC()
  bool      setResolution(uint8_t resolution = 9);
  uint8_t   getResolution();  //  returns cached value

  int16_t   getTempCentiC(void);


private:
  DeviceAddress _deviceAddress;
  OneWire*      _oneWire;
  bool          _addressFound;

  uint8_t       _resolution;
  void          readScratchPad(uint8_t *scratchPad, uint8_t fields);
  void          _setResolution();
};


//  -- END OF FILE --

