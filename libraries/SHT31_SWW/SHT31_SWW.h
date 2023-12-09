#pragma once
//
//    FILE: SHT31_SWW.h
//  AUTHOR: Rob Tillaart, Gunter Haug
// VERSION: 0.2.0
//    DATE: 2019-02-08 (base SHT31 lib)
// PURPOSE: Arduino library for the SHT31 temperature and humidity sensor
//          to be used with the SoftwareWire library instead of (hardware) Wire.
//          derives from SHT31 0.3.8
//     URL: https://www.adafruit.com/product/2857
//          https://github.com/RobTillaart/SHT31_SWW
//          https://github.com/RobTillaart/SHT31


#include "Arduino.h"
#include "SoftwareWire.h"
#include "SHT31.h"


#define SHT31_SWW_LIB_VERSION             (F("0.2.0"))


class SHT31_SWW : public SHT31
{
public:
  SHT31_SWW(uint8_t address,  SoftwareWire *wire);

  bool begin();

  //  check sensor is reachable over I2C
  bool isConnected();

private:
  bool writeCmd(uint16_t cmd);
  bool readBytes(uint8_t n, uint8_t *val);
  SoftwareWire* _softwareWire;
};


//  -- END OF FILE --

