#pragma once
//
//    FILE: SHT31_SW.h
//  AUTHOR: Rob Tillaart, Gunter Haug
// VERSION: 0.2.0
//    DATE: 2019-02-08 (base SHT31 lib)
// PURPOSE: Arduino library for the SHT31 temperature and humidity sensor
//          to be used with the SoftWire library instead of (hardware) Wire.
//          derives from SHT31 0.3.8
//     URL: https://www.adafruit.com/product/2857
//          https://github.com/RobTillaart/SHT31_SW
//          https://github.com/RobTillaart/SHT31


#define SHT31_SW_LIB_VERSION             (F("0.2.0"))


#include "Arduino.h"
#include "SoftWire.h"
#include "SHT31.h"


class SHT31_SW : public SHT31
{
public:
  SHT31_SW(uint8_t address, SoftWire *wire);
  bool begin();

  //  check if sensor is reachable over I2C
  bool isConnected();

private:
  bool writeCmd(uint16_t cmd);
  bool readBytes(uint8_t n, uint8_t *val);
  SoftWire* _softWire;
};


//  -- END OF FILE --

