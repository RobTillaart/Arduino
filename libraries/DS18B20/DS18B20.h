//
//    FILE: DS18B20.h
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.0
//    DATE: 2017-07-25
//
// PUPROSE: library for DS18B20 temperature sensor with minimal footprint
//

#ifndef DS18B20_H
#define DS18B20_H

#define DS18B20_LIB_VERSION "0.1.0"

#include <OneWire.h>

// Error Code
#define DEVICE_DISCONNECTED -127

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

private:
  void          readScratchPad(uint8_t *, uint8_t);
  DeviceAddress deviceAddress;
  OneWire*      _wire;
};

#endif

//  END OF FILE