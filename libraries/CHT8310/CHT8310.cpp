//
//    FILE: CHT8310.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library for CHT8310 temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CHT8310


#include "CHT8310.h"


//  REGISTERS
#define CHT8310_REG_TEMPERATURE          0x00
#define CHT8310_REG_HUMIDITY             0x01
#define CHT8310_REG_STATUS               0x02
#define CHT8310_REG_CONFIG               0x03
#define CHT8310_REG_CONVERT_RATE         0x04
#define CHT8310_REG_TEMP_HIGH_LIMIT      0x05
#define CHT8310_REG_TEMP_LOW_LIMIT       0x06
#define CHT8310_REG_HUM_HIGH_LIMIT       0x07
#define CHT8310_REG_HUM_LOW_LIMIT        0x08
#define CHT8310_REG_ONESHOT              0x0F

#define CHT8310_REG_SWRESET              0xFC
#define CHT8310_REG_MANUFACTURER         0xFF



/////////////////////////////////////////////////////
//
// PUBLIC
//
CHT8310::CHT8310(const uint8_t address, TwoWire *wire)
{
  _wire    = wire;
  _address = address;
}


int CHT8310::begin()
{
  //  address = 0x40, 0x44, 0x48, 0x4C
  if ((_address != 0x40) && (_address != 0x44) && (_address != 0x48) && (_address != 0x4C))
  {
    return CHT8310_ERROR_ADDR;
  }
  if (! isConnected()) return CHT8310_ERROR_CONNECT;
  return CHT8310_OK;
}


bool CHT8310::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t CHT8310::getAddress()
{
  return _address;
}


////////////////////////////////////////////////
//
//  READ THE SENSOR
//
int CHT8310::read()
{
  //  do not read too fast
  if (millis() - _lastRead < 1000)
  {
    return CHT8310_ERROR_LASTREAD;
  }
  _lastRead = millis();

  //  TEMPERATURE PART
  uint8_t data[2] = { 0, 0 };
  int status = _readRegister(CHT8310_REG_TEMPERATURE, &data[0], 2);
  if (status != CHT8310_OK)
  {
    return status;
  }

  //  DATASHEET P13
  int16_t tmp = (data[0] << 8 | data[1]);
  if (_resolution == 13)
  {
    _temperature = (tmp >> 3) * 0.03125;
  }
  else  //  _resolution == 14
  {
    _temperature = (tmp >> 2) * 0.03125;
  }
  //  Handle temperature offset.
  if (_tempOffset != 0.0) _temperature += _tempOffset;


  //  HUMIDITY PART
  status = _readRegister(CHT8310_REG_HUMIDITY, &data[0], 2);
  if (status != CHT8310_OK)
  {
    return status;
  }
  //  DATASHEET P14
  tmp = data[0] << 8 | data[1];
  if (tmp & 0x8000)  //  test overflow bit
  {
    _humidity = 100.0;
    return CHT8310_ERROR_HUMIDITY;
  }
  tmp &= 0x7FFF;
  _humidity = tmp * (1.0 / 327.67);  //  == / 32767 * 100%
  //  Handle humidity offset.
  if (_humOffset  != 0.0)
  {
    _humidity += _humOffset;
    //  handle out of range.
    if (_humidity < 0.0)   _humidity = 0.0;
    if (_humidity > 100.0) _humidity = 100.0;
  }

  return CHT8310_OK;
}


int CHT8310::readTemperature()
{
  _lastRead = millis();

  int16_t tmp = readRegister(CHT8310_REG_TEMPERATURE);
  //  DATASHEET P13
  if (_resolution == 13)
  {
    _temperature = (tmp >> 3) * 0.03125;
  }
  else  //  _resolution == 14
  {
    _temperature = (tmp >> 2) * 0.03125;
  }

  if (_tempOffset != 0.0)
  {
    _temperature += _tempOffset;
  }

  return CHT8310_OK;
}


int CHT8310::readHumidity()
{
  _lastRead = millis();

  int16_t tmp = readRegister(CHT8310_REG_HUMIDITY);

  //  DATASHEET P14
  if (tmp & 0x8000)  //  test overflow bit
  {
    _humidity = 100.0;
    return CHT8310_ERROR_HUMIDITY;
  }
  tmp &= 0x7FFF;
  _humidity = tmp * (1.0 / 327.67);  //  == / 32767 * 100%
  //  Handle humidity offset.
  if (_humOffset  != 0.0)
  {
    _humidity += _humOffset;
    //  handle out of range.
    if (_humidity < 0.0)   _humidity = 0.0;
    if (_humidity > 100.0) _humidity = 100.0;
  }

  return CHT8310_OK;
}


//  MilliSeconds since start sketch
uint32_t CHT8310::lastRead()
{
  return _lastRead;
}


float CHT8310::getHumidity()
{
  return _humidity;
}


float CHT8310::getTemperature()
{
  return _temperature;
}


void CHT8310::setConversionDelay(uint8_t cd)
{
  if (cd < 8) cd = 8;
  _conversionDelay = cd;
}


uint8_t CHT8310::getConversionDelay()
{
  return _conversionDelay;
}


////////////////////////////////////////////////
//
//  OFFSET
//
void CHT8310::setHumidityOffset(float offset)
{
  _humOffset = offset;
}


void CHT8310::setTemperatureOffset(float offset)
{
  _tempOffset = offset;
}


float CHT8310::getHumidityOffset()
{
  return _humOffset;
}


float CHT8310::getTemperatureOffset()
{
  return _tempOffset;
}


////////////////////////////////////////////////
//
//  CONFIGURATION
//
void CHT8310::setConfiguration(uint16_t mask)
{
  writeRegister(CHT8310_REG_CONFIG, mask);
}


uint16_t CHT8310::getConfiguration()
{
  return readRegister(CHT8310_REG_CONFIG);
}


////////////////////////////////////////////////
//
//  CONVERT RATE
//
void CHT8310::setConvertRate(uint8_t rate)
{
  if (rate > 7) rate = 7;
  writeRegister(CHT8310_REG_CONVERT_RATE, ((uint16_t)rate) << 8);
}


uint8_t CHT8310::getConvertRate()
{
  return (readRegister(CHT8310_REG_CONVERT_RATE) >> 8) & 0x07;
}


////////////////////////////////////////////////
//
//  ALERT
//
void CHT8310::setTemperatureHighLimit(float temperature)
{
  int16_t tmp = round(temperature * (1.0 / 0.03125));
  tmp <<= 3;
  writeRegister(CHT8310_REG_TEMP_HIGH_LIMIT, tmp);
}

void CHT8310::setTemperatureLowLimit(float temperature)
{
  int16_t tmp = round(temperature * (1.0 / 0.03125));
  tmp <<= 3;
  writeRegister(CHT8310_REG_TEMP_LOW_LIMIT, tmp);
}

void CHT8310::setHumidityHighLimit(float humidity)
{
  int16_t hum = round(humidity * 327.67);
  writeRegister(CHT8310_REG_HUM_HIGH_LIMIT, hum);
}

void CHT8310::setHumidityLowLimit(float humidity)
{
  int16_t hum = round(humidity * 327.67);
  writeRegister(CHT8310_REG_HUM_LOW_LIMIT, hum);
}


////////////////////////////////////////////////
//
//  STATUS
//
uint16_t CHT8310::getStatusRegister()
{
  return readRegister(CHT8310_REG_STATUS);
}


////////////////////////////////////////////////
//
//  ONE SHOT
//
void CHT8310::oneShotConversion()
{
  writeRegister(CHT8310_REG_ONESHOT, 0xFFFF);
}


////////////////////////////////////////////////
//
//  SOFTWARE RESET
//
void CHT8310::softwareReset()
{
  writeRegister(CHT8310_REG_SWRESET, 0xFFFF);
}


////////////////////////////////////////////////
//
//  META DATA
//
uint16_t CHT8310::getManufacturer()
{
  return readRegister(CHT8310_REG_MANUFACTURER);
}


////////////////////////////////////////////////
//
//  ACCESS REGISTERS
//
uint16_t CHT8310::readRegister(uint8_t reg)
{
  uint8_t data[2] = { 0, 0 };
  _readRegister(reg, &data[0], 2);
  uint16_t tmp = data[0] << 8 | data[1];
  return tmp;
}


int CHT8310::writeRegister(uint8_t reg, uint16_t value)
{
  uint8_t data[2];
  data[1] = value & 0xFF;
  data[0] = value >> 8;
  return _writeRegister(reg, data, 2);
}


////////////////////////////////////////////////
//
//  PRIVATE
//
int CHT8310::_readRegister(uint8_t reg, uint8_t * buf, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    return CHT8310_ERROR_I2C;
  }

  n = _wire->requestFrom(_address, size);
  if (n != size)
  {
    return CHT8310_ERROR_I2C;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    buf[i] = _wire->read();
  }
  return CHT8310_OK;
}


int CHT8310::_writeRegister(uint8_t reg, uint8_t * buf, uint8_t size)
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
    return CHT8310_ERROR_I2C;
  }
  return CHT8310_OK;
}


//  -- END OF FILE --

