#pragma once
//
//    FILE: DS18B20_INT.h
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.3
//    DATE: 2017-07-25
// PUPROSE: Minimalistic library for DS18B20 temperature sensor
//          uses only integer math (no float to minimize footprint)
//     URL: https://github.com/RobTillaart/DS18B20_INT

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

#include "Arduino.h"
#include "OneWire.h"

// Error Code
#define DEVICE_DISCONNECTED     -127

typedef uint8_t DeviceAddress[8];


class DS18B20_INT
{
public:
  explicit DS18B20_INT(OneWire *);
  bool     begin(void);
  void     requestTemperatures(void);
  bool     isConversionComplete(void);
  int16_t  getTempC(void);

private:
  uint8_t  _deviceAddress[8];
  OneWire* _wire;
  bool     _addresFound;
};

//  -- END OF FILE --
