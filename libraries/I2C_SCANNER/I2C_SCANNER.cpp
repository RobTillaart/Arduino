//
//    FILE: I2C_SCANNER.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-08-29
// PURPOSE: I2C scanner class
//

#include "I2C_SCANNER.h"



I2C_SCANNER::I2C_SCANNER(TwoWire *wire)
{
  _wire = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool I2C_SCANNER::begin(int dataPin, int clockPin)
{
  _wire = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  return true;
}
#endif


bool I2C_SCANNER::begin()
{
  _wire->begin();
  return true;
}


bool I2C_SCANNER::ping(uint8_t address)
{
  _wire->beginTransmission(address);
  return ( _wire->endTransmission() == 0);
}


bool I2C_SCANNER::setClock(uint32_t clockFrequency)
{
  _wire->setClock(clockFrequency);
  return true;
}


// -- END OF FILE --

