//
//    FILE: I2C_SCANNER.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2022-08-29
// PURPOSE: Arduino class to implement an I2C scanner.


#include "I2C_SCANNER.h"


I2C_SCANNER::I2C_SCANNER(TwoWire *wire)
{
  _wire = wire;
}


//
//  CONFIGURATION
//
bool I2C_SCANNER::begin()
{
  _init();
  return true;
}


//
//  I2C PORT
//
uint8_t I2C_SCANNER::getWirePortCount()
{
  return _wirePortCount;
}


//  0 == Wire, 1 = Wire1 etc.
bool I2C_SCANNER::setWire(uint8_t n)
{
  if (n == 0) { _wire = &Wire; return true; };
#if defined WIRE_IMPLEMENT_WIRE1 || WIRE_INTERFACES_COUNT > 1
  if (n == 1) { _wire = &Wire1; return true; };
#endif
#if defined WIRE_IMPLEMENT_WIRE2 || WIRE_INTERFACES_COUNT > 2
  if (n == 2) { _wire = &Wire2; return true; };
#endif
#if defined WIRE_IMPLEMENT_WIRE3 || WIRE_INTERFACES_COUNT > 3
  if (n == 3) { _wire = &Wire3; return true; };
#endif
#if defined WIRE_IMPLEMENT_WIRE4 || WIRE_INTERFACES_COUNT > 4
  if (n == 4) { _wire = &Wire4; return true; };
#endif
#if defined WIRE_IMPLEMENT_WIRE5 || WIRE_INTERFACES_COUNT > 5
  if (n == 5) { _wire = &Wire5; return true; };
#endif
  return false;
}


bool I2C_SCANNER::setWire(TwoWire *wire)
{
  _wire = wire;
  return true;
}


TwoWire* I2C_SCANNER::getWire()
{
  return _wire;
}


//
//  RESET
//
int I2C_SCANNER::softwareReset(uint8_t method)
{
  //  only support 0 and 1
  if (method > 1) return -999;
  if (method == 1)
  {
    //  from https://github.com/RobTillaart/PCA9634/issues/10#issuecomment-1206326417
   const uint8_t SW_RESET = 0x03;
   _wire->beginTransmission(SW_RESET);
   _wire->write(0xA5);
   _wire->write(0x5A);
   return _wire->endTransmission(true);
  }

  //  default
  //  based upon NXP specification - UM10204.pdf - page 16
  _wire->beginTransmission(0x00);
  _wire->write(0x06);
  return _wire->endTransmission(true);
}


//
//  TIMING
//
bool I2C_SCANNER::setClock(uint32_t clockFrequency)
{
  _wire->setClock(clockFrequency);
  return true;
}


#if defined(ESP32)
uint32_t I2C_SCANNER::getClock()
{
  return _wire->getClock();
}
#endif


//
//  SCANNING
//
uint16_t I2C_SCANNER::ping(uint8_t address, uint16_t count)
{
  if (count == 0) count = 1;
  uint16_t success = 0;
  while (count > 0)
  {
    count--;
    if (diag(address) == 0) success++;
  }
  return success;
}


int I2C_SCANNER::diag(uint8_t address)
{
  _wire->beginTransmission(address);
  int x = _wire->endTransmission();
  return x;
}


int32_t I2C_SCANNER::pingTime(uint8_t address)
{
  uint32_t start = micros();
  int x = diag(address);
  int32_t duration = (int32_t)(micros() - start);
  if (x == 0) return duration;
  return -duration;
}


uint8_t I2C_SCANNER::count(uint8_t start, uint8_t end)
{
  uint8_t cnt = 0;
  for (uint8_t addr = start; addr <= end; addr++)
  {
    if (diag(addr) == 0) cnt++;
  }
  return cnt;
}


bool I2C_SCANNER::setWireTimeout(uint32_t timeOut)
{
  if (_timeout != timeOut)
  {
    _timeout = timeOut;
    //  not all platforms support this.
    //  _wire->setWireTimeout(timeOut);
    return true;
  }
  return false;
}


uint32_t I2C_SCANNER::getWireTimeout()
{
  return _timeout;
}


////////////////////////////////////////////////////
//
//  PRIVATE
//
int I2C_SCANNER::_init()
{
  Wire.begin();

  _wirePortCount = 1;
#if defined WIRE_IMPLEMENT_WIRE1 || WIRE_INTERFACES_COUNT > 1
  Wire1.begin();
  _wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE2 || WIRE_INTERFACES_COUNT > 2
  Wire2.begin();
  _wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE3 || WIRE_INTERFACES_COUNT > 3
  Wire3.begin();
  _wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE4 || WIRE_INTERFACES_COUNT > 4
  Wire4.begin();
  _wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE5 || WIRE_INTERFACES_COUNT > 5
  Wire5.begin();
  _wirePortCount++;
#endif
  return _wirePortCount;
}


//  -- END OF FILE --

