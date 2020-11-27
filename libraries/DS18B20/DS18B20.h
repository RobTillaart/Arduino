#pragma once
//
//    FILE: DS18B20.h
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.6
//    DATE: 2017-07-25
// PUPROSE: library for DS18B20 temperature sensor with minimal footprint
//

//
//  BOTTOM VIEW
//
//          PIN  MEANING
//   /---+
//  /  o |  1    GND
//  |  o |  2    DATA
//  \  o |  3    VCC
//   \---+
//

#define DS18B20_LIB_VERSION     "0.1.6"

#include <OneWire.h>

// Error Code
#define DEVICE_DISCONNECTED     -127
#define DEVICE_CRC_ERROR        -128

// config codes
#define DS18B20_CLEAR           0x00
#define DS18B20_CRC             0x01


typedef uint8_t DeviceAddress[8];
typedef uint8_t ScratchPad[9];


class DS18B20
{
public:
  explicit  DS18B20(OneWire *);
  bool      begin(void);
  void      setResolution(uint8_t);
  void      requestTemperatures(void);
  float     getTempC(void);
  bool      isConversionComplete(void);
  bool      getAddress(uint8_t*);

  void      setConfig(uint8_t config) { _config = config; };
  uint8_t   getConfig()               { return _config; };

private:
  void          readScratchPad(uint8_t *, uint8_t);
  DeviceAddress _deviceAddress;
  OneWire*      _wire;
  bool          _addresFound;
  uint8_t       _config;
};

//  -- END OF FILE --
