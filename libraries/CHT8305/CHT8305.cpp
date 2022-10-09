//
//    FILE: CHT8305.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for CHT8305 temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CH8305
//
//  HISTORY
//  2022-10-06  0.1.0  initial version
//  2022-10-08  0.1.1  add config specific functions
//                     fix ESP32 begin() address check
//                     add config ALERT functions.
//                     add constants for registers
//                     fix getVoltage() register


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
  if ((address < 0x40) || (address > 0x43)) return CHT8305_ERROR_ADDR;

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
  _readRegister(CHT8305_REG_TEMPERATURE, &data[0], 4);

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
  _readRegister(CHT8305_REG_CONFIG, &data[0], 2);
  uint16_t tmp = data[0] << 8 | data[1];
  return tmp;
}


void CHT8305::softReset()
{
  _setConfigMask(CHT8305_CFG_SOFT_RESET);
}


void CHT8305::setI2CClockStretch(bool on)
{
  if (on) _setConfigMask(CHT8305_CFG_CLOCK_STRETCH);
  else    _clrConfigMask(CHT8305_CFG_CLOCK_STRETCH);
}


bool CHT8305::getI2CClockStretch()
{
  return (getConfigRegister() & CHT8305_CFG_CLOCK_STRETCH) > 0;
}

void CHT8305::setHeaterOn(bool on)
{
  if (on) _setConfigMask(CHT8305_CFG_HEATER);
  else    _clrConfigMask(CHT8305_CFG_HEATER);
}


bool CHT8305::getHeater()
{
  return (getConfigRegister() & CHT8305_CFG_HEATER) > 0;
}


void CHT8305::setMeasurementMode(bool both)
{
  if (both) _setConfigMask(CHT8305_CFG_MODE);
  else      _clrConfigMask(CHT8305_CFG_MODE);
}


bool CHT8305::getMeasurementMode()
{
  return (getConfigRegister() & CHT8305_CFG_MODE) > 0;
}


bool CHT8305::getVCCstatus()
{
  return (getConfigRegister() & CHT8305_CFG_VCCS) > 0;
}


void CHT8305::setTemperatureResolution(bool b)
{
  if (b) _setConfigMask(CHT8305_CFG_TEMP_RES);
  else   _clrConfigMask(CHT8305_CFG_TEMP_RES);
}


bool CHT8305::getTemperatureResolution()
{
  return (getConfigRegister() & CHT8305_CFG_TEMP_RES) > 0;
}


void CHT8305::setHumidityResolution(uint8_t res)
{
  _clrConfigMask(CHT8305_CFG_HUMI_RES);
  if (res == 2)_setConfigMask(0x0100);  //  magic
  if (res == 3)_setConfigMask(0x0200);  //  magic
  //  default == 00 if not 2 or 3
}


uint8_t CHT8305::getHumidityResolution()
{
 return (getConfigRegister() & CHT8305_CFG_HUMI_RES) >> 8;
}


void CHT8305::setVCCenable(bool enable)
{
  if (enable) _setConfigMask(CHT8305_CFG_VCC_ENABLE);
  else        _clrConfigMask(CHT8305_CFG_VCC_ENABLE);
}


bool CHT8305::getVCCenable()
{
 return (getConfigRegister() & CHT8305_CFG_VCC_ENABLE) > 0;
}


////////////////////////////////////////////////
//
//  ALERT (config register)
//
bool CHT8305::setAlertTriggerMode(uint8_t mode)
{
  _clrConfigMask(CHT8305_CFG_ALERT_MODE);
  if (mode > 3) return false;   //  check 0,1,2,3
  uint16_t mask = mode << 6;
  _setConfigMask(mask);
  return true;
}


uint8_t CHT8305::getAlertTriggerMode()
{
 return (getConfigRegister() & CHT8305_CFG_ALERT_MODE) >> 6;
}


bool CHT8305::getAlertPendingStatus()
{
 return (getConfigRegister() & CHT8305_CFG_ALERT_PENDING) > 0;
}


bool CHT8305::getAlertHumidityStatus()
{
 return (getConfigRegister() & CHT8305_CFG_ALERT_HUMI) > 0;
}


bool CHT8305::getAlertTemperatureStatus()
{
 return (getConfigRegister() & CHT8305_CFG_ALERT_TEMP) > 0;
}


bool CHT8305::setAlertLevels(float temperature, float humidity)
{
  //  range check
  if ((temperature < -40 ) || (temperature > 125)) return false;
  if ((humidity < 0 )      || (humidity > 100)) return false;

  uint16_t mask = 0;
  uint16_t tmp = humidity * (65535.0/100.0);
  mask = tmp << 9;

  tmp = (temperature + 40.0) * (65535.0 / 165.0);
  mask |= tmp;
  _writeRegister(CHT8305_REG_ALERT, (uint8_t *)&mask, 2);
  return true;
}

float CHT8305::getAlertLevelTemperature()
{
  uint16_t data = 0;
  _readRegister(CHT8305_REG_ALERT, (uint8_t *)&data, 2);
  data &= 0x01FF;
  return data * (165.0 / 65535.0) - 40.0;
}


float CHT8305::getAlertLevelHumidity()
{
  uint16_t data = 0;
  _readRegister(CHT8305_REG_ALERT, (uint8_t *)&data, 2);
  data >>= 9;
  return data * (100.0 / 65535.0);
}


////////////////////////////////////////////////
//
//  VOLTAGE
//
float CHT8305::getVoltage()
{
  uint8_t data[2] = { 0, 0};
  _readRegister(CHT8305_REG_VOLTAGE, &data[0], 2);
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
  _readRegister(CHT8305_REG_MANUFACTURER, &data[0], 2);
  uint16_t tmp = data[0] << 8 | data[1];
  return tmp;
}


uint16_t CHT8305::getVersionID()
{
  uint8_t data[2] = { 0, 0};
  _readRegister(CHT8305_REG_VERSION, &data[0], 2);
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

  if (reg == CHT8305_REG_TEMPERATURE)  //  wait for conversion...
  {
    delay(14);  //  2x 6.5 ms @ 14 bit.
  }

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


void CHT8305::_setConfigMask(uint16_t mask)
{
  uint16_t tmp = getConfigRegister();
  tmp |= mask;
  setConfigRegister(tmp);
}


void CHT8305::_clrConfigMask(uint16_t mask)
{
  uint16_t tmp = getConfigRegister();
  tmp &= ~mask;
  setConfigRegister(tmp);
}


// -- END OF FILE --

