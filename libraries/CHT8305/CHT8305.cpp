//
//    FILE: CHT8305.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: Arduino library for CHT8305 temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CHT8305


#include "CHT8305.h"


/////////////////////////////////////////////////////
//
// PUBLIC
//
CHT8305::CHT8305(const uint8_t address, TwoWire *wire)
{
  _wire    = wire;
  _address = address;
  _error   = CHT8305_OK;
}


int CHT8305::begin()
{
  if ((_address < 0x40) || (_address > 0x43))
  {
    _error = CHT8305_ERROR_ADDR;
    return _error;
  }
  if (! isConnected())
  {
    _error = CHT8305_ERROR_CONNECT;
    return _error;
  }
  _error = CHT8305_OK;
  return _error;
}


bool CHT8305::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t CHT8305::getAddress()
{
  return _address;
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
    _error = CHT8305_ERROR_LASTREAD;
    return _error;
  }
  _lastRead = millis();

  uint8_t data[4] = {0, 0, 0, 0 };
  if (_readRegister(CHT8305_REG_TEMPERATURE, &data[0], 4) != CHT8305_OK)
  {
    return _error;
  }

  uint16_t tmp = (data[0] << 8) | data[1];
  _temperature = tmp * (165.0f / 65535.0f) - 40.0f;

   tmp = (data[2] << 8) | data[3];
  _humidity    = tmp * (1.0f / 655.35f);  //  == / 65535 * 100%

  if (_tempOffset != 0.0f) _temperature += _tempOffset;
  if (_humOffset  != 0.0f)
  {
    _humidity += _humOffset;
    if (_humidity < 0.0f)   _humidity = 0.0f;
    if (_humidity > 100.0f) _humidity = 100.0f;
  }

  _error = CHT8305_OK;
  return _error;
}


int CHT8305::readTemperature()
{
  //  do not read too fast
  if (millis() - _lastRead < 1000)
  {
    _error = CHT8305_ERROR_LASTREAD;
    return _error;
  }
  _lastRead = millis();

  uint8_t data[2] = {0, 0};
  if (_readRegister(CHT8305_REG_TEMPERATURE, &data[0], 2) != CHT8305_OK)
  {
    return _error;
  }

  uint16_t tmp = (data[0] << 8) | data[1];
  _temperature = tmp * (165.0f / 65535.0f) - 40.0f;

  if (_tempOffset != 0.0f)
  {
    _temperature += _tempOffset;
  }

  _error = CHT8305_OK;
  return _error;
}


int CHT8305::readHumidity()
{
  //  do not read too fast
  if (millis() - _lastRead < 1000)
  {
    _error = CHT8305_ERROR_LASTREAD;
    return _error;
  }
  _lastRead = millis();

  uint8_t data[2] = {0, 0};
  if (_readRegister(CHT8305_REG_HUMIDITY, &data[0], 2) != CHT8305_OK)
  {
    return _error;
  }

  uint16_t tmp = (data[0] << 8) | data[1];
  _humidity    = tmp * (1.0f / 655.35f);  //  == / 65535 * 100%

  if (_humOffset  != 0.0f)
  {
    _humidity += _humOffset;
    if (_humidity < 0.0f)   _humidity = 0.0f;
    if (_humidity > 100.0f) _humidity = 100.0f;
  }

  _error = CHT8305_OK;
  return _error;
}


//  MilliSeconds since start sketch
uint32_t CHT8305::lastRead()
{
  return _lastRead;
};


float CHT8305::getHumidity()
{
  return _humidity;
};


float CHT8305::getTemperature()
{
  return _temperature;
};


void CHT8305::setConversionDelay(uint8_t cd)
{
  if (cd < 8) cd = 8;
  _conversionDelay = cd;
}


uint8_t CHT8305::getConversionDelay()
{
  return _conversionDelay;
}


void CHT8305::setHumidityOffset(float offset)
{
  _humOffset = offset;
};


void CHT8305::setTemperatureOffset(float offset)
{
  _tempOffset = offset;
};


float CHT8305::getHumidityOffset()
{
  return _humOffset;
};


float CHT8305::getTemperatureOffset()
{
  return _tempOffset;
};


////////////////////////////////////////////////
//
//  CONFIGURATION REGISTER
//
bool CHT8305::setConfigRegister(uint16_t bitmask)
{
  uint8_t data[2];
  data[0] = bitmask >> 8;
  data[1] = bitmask & 0xFF;
  if (_writeRegister(2, &data[0], 2) != CHT8305_OK)
  {
    return false;
  }
  return true;
}


uint16_t CHT8305::getConfigRegister()
{
  uint8_t data[2] = { 0, 0};
  if (_readRegister(CHT8305_REG_CONFIG, &data[0], 2) != CHT8305_OK)
  {
    return 0;
  }
  uint16_t tmp = (data[0] << 8) | data[1];
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


void CHT8305::setTemperatureResolution(uint8_t res)
{
  if (res == 1) _setConfigMask(CHT8305_CFG_TEMP_RES);
  else          _clrConfigMask(CHT8305_CFG_TEMP_RES);
}


uint8_t CHT8305::getTemperatureResolution()
{
  if (getConfigRegister() & CHT8305_CFG_TEMP_RES) return 1;
  return 0;
}


void CHT8305::setHumidityResolution(uint8_t res)
{
  _clrConfigMask(CHT8305_CFG_HUMI_RES); //  set bits to 00
  if (res == 2)_setConfigMask(0x0200);  //   8 bit
  if (res == 1)_setConfigMask(0x0100);  //  11 bit
  //  default == 00 if not 1 or 2       //  14 bit
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
//  ALERT (configuration register)
//
bool CHT8305::setAlertTriggerMode(uint8_t mode)
{
  if (mode > 3) return false;   //  check 0,1,2,3
  _clrConfigMask(CHT8305_CFG_ALERT_MODE);
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

  uint16_t tmp  = humidity * (127.0f / 100.0f);
  uint16_t mask = tmp << 9;

  tmp = (temperature + 40.0f) * (511.0f / 165.0f);
  mask |= tmp;
  if (_writeRegister(CHT8305_REG_ALERT, (uint8_t *)&mask, 2) != CHT8305_OK)
  {
    return false;
  }
  return true;
}


float CHT8305::getAlertLevelTemperature()
{
  uint16_t data = 0;
  if (_readRegister(CHT8305_REG_ALERT, (uint8_t *)&data, 2) != CHT8305_OK)
  {
    return CHT8305_ERROR_GENERIC;
  }
  data &= 0x01FF;
  data <<= 7;
  return data * (165.0f / 65535.0f) - 40.0f;
}


float CHT8305::getAlertLevelHumidity()
{
  uint16_t data = 0;
  if (_readRegister(CHT8305_REG_ALERT, (uint8_t *)&data, 2) != CHT8305_OK)
  {
    return CHT8305_ERROR_GENERIC;
  }
  data &= 0xFE00;
  return data * (100.0f / 65535.0f);
}


////////////////////////////////////////////////
//
//  VOLTAGE
//
float CHT8305::getVoltage()
{
  uint8_t data[2] = { 0, 0};
  if (_readRegister(CHT8305_REG_VOLTAGE, &data[0], 2) != CHT8305_OK)
  {
    return CHT8305_ERROR_GENERIC;
  }
  uint16_t tmp = (data[0] << 8) | data[1];
  return tmp * (5.0f / 32768.0f);   //  best guess
}


////////////////////////////////////////////////
//
//  META DATA
//
uint16_t CHT8305::getManufacturer()
{
  uint8_t data[2] = { 0, 0};
  if (_readRegister(CHT8305_REG_MANUFACTURER, &data[0], 2) != CHT8305_OK)
  {
    return 0xFFFF;
  }
  uint16_t tmp = (data[0] << 8) | data[1];
  return tmp;
}


uint16_t CHT8305::getVersionID()
{
  uint8_t data[2] = { 0, 0};
  if (_readRegister(CHT8305_REG_VERSION, &data[0], 2) != CHT8305_OK)
  {
    return 0xFFFF;
  }
  uint16_t tmp = (data[0] << 8) | data[1];
  return tmp;
}


int CHT8305::getLastError()
{
  int e = _error;
  _error = CHT8305_OK;
  return e;
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
  if (n != 0)
  {
    _error = CHT8305_ERROR_I2C;
    return _error;
  }

  if (reg == CHT8305_REG_TEMPERATURE)  //  wait for conversion...
  {
    delay(_conversionDelay);  //  2x 6.5 ms @ 14 bit = 14  (10 works).
  }

  n = _wire->requestFrom(_address, size);
  if (n != size)
  {
    _error = CHT8305_ERROR_BUFSIZE;
    return _error;
  }
  for (uint8_t i = 0; i < size; i++)
  {
    buf[i] = _wire->read();
  }
  _error = CHT8305_OK;
  return _error;
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
  if (n != 0)
  {
    _error = CHT8305_ERROR_I2C;
    return _error;
  }
  _error = CHT8305_OK;
  return _error;
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


//  -- END OF FILE --

