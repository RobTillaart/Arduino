//
//    FILE: CHT8305.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for CHT8305 temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CH8305
//
//  HISTORY
//  2022-10-06  0.1.0  initial version
//


#include "CHT8305.h"


/////////////////////////////////////////////////////
//
// PUBLIC
//
CHT8305::CHT8305(TwoWire *wire)
{
  _wire            = wire;
  _address         = 0x40;   //  default AD0 to GND.
}


#if defined (ESP8266) || defined(ESP32)
int CHT8305::begin(int sda, int scl, const uint8_t address)
{
  if ((address < 0x50) || (address > 0x57)) return CHT8305_ERROR_ADDR;

  _wire = &Wire;
  _address = address;
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  } else {
    _wire->begin();
  }

  if (! isConnected()) return CHT8305_ERROR_CONNECT;
  return CHT8305_OK;
}
#endif


int CHT8305::begin(const uint8_t address)
{
  if ((address < 0x40) || (address > 0x43)) return CHT8305_ERROR_ADDR;

  _address = address;
  _wire->begin();

  if (! isConnected()) return CHT8305_ERROR_CONNECT;
  return CHT8305_OK;
}


bool CHT8305::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


////////////////////////////////////////////////
//
//  READ THE SENSOR
//
int CHT8305::read()
{
  //  do not read too fast
  if (millis() - _lastRead < 1000)
  {
    return CHT8305_ERROR_LASTREAD;
  }
  _lastRead = millis();

  uint8_t data[4] = {0, 0, 0, 0 };
  _readRegister(0, &data[0], 4);
  uint16_t tmp = data[0] << 8 | data[1];
  _temperature = tmp * (165.0 / 65535.0) - 40.0;
   tmp = data[2] << 8 | data[3];
  _humidity    = tmp / 655.35;  //  == / 65535 * 100%

  if (_tempOffset != 0.0) _temperature += _tempOffset;
  if (_humOffset  != 0.0) _humidity    += _humOffset;

  return CHT8305_OK;
}


////////////////////////////////////////////////
//
//  CONFIG REGISTER
//
void CHT8305::setConfigRegister(uint16_t bitmask)
{
  uint8_t data[2];
  data[0] = bitmask >> 8;
  data[1] = bitmask & 0xFF;
  _writeRegister(2, &data[0], 2);
}


uint16_t CHT8305::getConfigRegister()
{
  uint8_t data[2] = { 0, 0};
  _readRegister(2, &data[0], 2);
  uint16_t tmp = data[0] << 8 | data[1];
  return tmp;
}


void CHT8305::softReset()
{
  uint16_t tmp = getConfigRegister();
  tmp |= 0x8000;
  setConfigRegister(tmp);
}


////////////////////////////////////////////////
//
//  VOLTAGE
//
//  TODO verify conversion unit
//  TODO check datasheet.
float CHT8305::getVoltage()
{
  uint8_t data[2] = { 0, 0};
  _readRegister(2, &data[0], 2);
  uint16_t tmp = data[0] << 8 | data[1];
  return tmp * (5.0 / 65535.0);  //  this is best guess
}


////////////////////////////////////////////////
//
//  META DATA
//
uint16_t CHT8305::getManufacturer()
{
  uint8_t data[2] = { 0, 0};
  _readRegister(0xFE, &data[0], 2);
  uint16_t tmp = data[0] << 8 | data[1];
  return tmp;
}


uint16_t CHT8305::getVersionID()
{
  uint8_t data[2] = { 0, 0};
  _readRegister(0xFF, &data[0], 2);
  uint16_t tmp = data[0] << 8 | data[1];
  return tmp;
}


////////////////////////////////////////////////
//
//  PRIVATE
//
int CHT8305::_readRegister(uint8_t reg, uint8_t * buf, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int n = _wire->endTransmission();
  if (n != 0) return CHT8305_ERROR_I2C;

  if (reg == 0x00) delay(14);  //  2x 6.5 ms @ 14 bit.

  n = _wire->requestFrom(_address, size);
  if (n == size)
  {
    for (uint8_t i = 0; i < size; i++)
    {
      buf[i] = _wire->read();
    }
  }
  return CHT8305_OK;
}


int CHT8305::_writeRegister(uint8_t reg, uint8_t * buf, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(buf[i]);
  }
  int n = _wire->endTransmission();
  if (n != 0) return CHT8305_ERROR_I2C;
  return CHT8305_OK;
}


// -- END OF FILE --

