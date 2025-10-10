//
//    FILE: SHT4x.cpp
//  AUTHOR: Samuel Cuerrier Auclair
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.3
//    DATE: 2025-08-11
// PURPOSE: Arduino library for the SHT4x temperature and humidity sensor. High precision sensor with I2C interface.
//          This is a fork of the SHT31 library by Rob Tillaart, modified to work with the SHT4x series.
//          https://www.adafruit.com/product/2857
//     URL: https://github.com/RobTillaart/SHT4x


#include "SHT4x.h"


//  SUPPORTED COMMANDS
static constexpr uint8_t SHT4x_SOFT_RESET        = 0x94;
static constexpr uint8_t SHT4x_GET_SERIAL_NUMBER = 0x89;


SHT4x::SHT4x(uint8_t address, TwoWire *wire)
{
  _address          = address;
  _wire             = wire;
  _lastRead         = 0;
  _rawTemperature   = 0;
  _rawHumidity      = 0;
  _error            = SHT4x_OK;
  _delay            = 0;
  _heatProtection   = true;
  _heatInterval     = 0;
  _lastHeatRequest  = 0;
}


bool SHT4x::begin()
{
  if ((_address < 0x44) || (_address > 0x46))
  {
    _error = SHT4x_ERR_INVALID_ADDRESS;
    return false;   //  invalid address
  }
  return reset();
}


bool SHT4x::isConnected()
{
  _wire->beginTransmission(_address);
  int rv = _wire->endTransmission();
  if (rv != 0) _error = SHT4x_ERR_NOT_CONNECT;
  return (rv == 0);
}


uint8_t SHT4x::getAddress()
{
  return _address;
}


bool SHT4x::read(measType measurementType, bool CRCCheck)
{
  if (!requestData(measurementType))
  {
    //  _error is set in requestData().
    return false;
  }
  delay(_delay);  //  calls yield() for RTOS internally
  return readData(CRCCheck);
}


uint32_t SHT4x::lastRead()
{
  return _lastRead;
}


bool SHT4x::reset(bool fast)
{
  bool b = writeCommand((uint8_t) SHT4x_SOFT_RESET);
  if (b == false)
  {
    return false;
  }
  if (fast == false) delay(1);   //  table 5 datasheet
  return true;
}


float SHT4x::getHumidity()
{
  constexpr float SCALE = 125.0f / 65535.0f;
  constexpr float OFFSET = 6.0f;

  float hum = _rawHumidity * SCALE - OFFSET;

  constexpr float HUM_MIN = 0.0f;
  constexpr float HUM_MAX = 100.0f;

  if (hum > HUM_MAX) hum = HUM_MAX;
  else if (hum < HUM_MIN) hum = HUM_MIN;

  return hum;
}


float SHT4x::getTemperature()
{
  constexpr float SCALE  = 175.0f / 65535.0f;
  constexpr float OFFSET = 45.0f;

  return _rawTemperature * SCALE - OFFSET;
}


float SHT4x::getFahrenheit()
{
  constexpr float SCALE  = 315.0f / 65535.0f;
  constexpr float OFFSET = 49.0f;

  return _rawTemperature * SCALE - OFFSET;
}


uint16_t SHT4x::getRawHumidity()
{
  return _rawHumidity;
}


uint16_t SHT4x::getRawTemperature()
{
  return _rawTemperature;
}


/////////////////////////////////////////////////////////////////
//
//  ASYNCHRONUOUS INTERFACE
//
bool SHT4x::requestData(measType measurementType)
{
  //  check heat protection
  bool isheatcmd = isHeatCmd(measurementType);
  if (_heatProtection && isheatcmd)
  {
    if (!heatingReady())
    {
      _error = SHT4x_ERR_HEATER_COOLDOWN;
      return false;
    }
  }
  // Send command
  if (writeCommand((uint8_t)measurementType) == false)
  {
    return false;
  }
  // Update required data
  _lastRequest = millis();
  setDelay(measurementType);
  if (isheatcmd)
  {
    setHeatInterval(measurementType);
    _lastHeatRequest = _lastRequest;
  }
  return true;
}


bool SHT4x::dataReady()
{
  return ((millis() - _lastRequest) > _delay);
}


bool SHT4x::readData(bool CRCCheck)
{
  uint8_t buffer[6];
  if (readBytes(6, (uint8_t*) &buffer[0]) == false)
  {
    _error = SHT4x_ERR_READBYTES;
    return false;
  }

  if (CRCCheck)
  {
    if (buffer[2] != crc8(buffer, 2))
    {
      _error = SHT4x_ERR_CRC_TEMP;
      return false;
    }
    if (buffer[5] != crc8(buffer + 3, 2))
    {
      _error = SHT4x_ERR_CRC_HUM;
      return false;
    }
  }

  _rawTemperature = (buffer[0] << 8) + buffer[1];
  _rawHumidity    = (buffer[3] << 8) + buffer[4];

  _lastRead = millis();
  return true;
}


/////////////////////////////////////////////////////////////////
//
//  MISC
//
int SHT4x::getError()
{
  int rv = _error;
  _error = SHT4x_OK;
  return rv;
}


/**
 * See https://sensirion.com/media/documents/E5762713/63D103C2/Sensirion_electronic_identification_code_SHT3x.pdf
 */
bool SHT4x::getSerialNumber(uint32_t &serial, bool CRCCheck) {
  if (writeCommand((uint8_t)SHT4x_GET_SERIAL_NUMBER) == false) {
      return false;
  }
  delay(1);
  uint8_t buffer[6];
  if (readBytes(6, &buffer[0]) == false) {
    return false;
  }

  if (CRCCheck)
  {
    if (buffer[2] != crc8(buffer, 2)) {
    _error = SHT4x_ERR_SERIAL_NUMBER_CRC;
    return false;
    }
    if (buffer[5] != crc8(buffer + 3, 2)) {
    _error = SHT4x_ERR_SERIAL_NUMBER_CRC;
    return false;
    }
  }
  serial = buffer[0];
  serial <<= 8;
  serial += buffer[1];
  serial <<= 8;
  serial += buffer[3];
  serial <<= 8;
  serial += buffer[4];
  return true;
}


/////////////////////////////////////////////////////////////////
//
//   HEAT PROTECTION
//
bool SHT4x::heatingReady()
{
  return ((millis() - _lastHeatRequest) > _heatInterval);
}

void SHT4x::setHeatProtection(bool activateHeatProtection)
{
  _heatProtection = activateHeatProtection;
}


/////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
void SHT4x::setDelay(measType measurementType)
{
  //  table 5 datasheet
  switch(measurementType)
  {
    case SHT4x_MEASUREMENT_SLOW:
      _delay = 9;
      break;
    case SHT4x_MEASUREMENT_MEDIUM:
      _delay = 5;
      break;
    case SHT4x_MEASUREMENT_FAST:
      _delay = 2;
      break;
    case SHT4x_MEASUREMENT_LONG_HIGH_HEAT:
    case SHT4x_MEASUREMENT_LONG_MEDIUM_HEAT:
    case SHT4x_MEASUREMENT_LONG_LOW_HEAT:
      _delay = 1100;
      break;
    case SHT4x_MEASUREMENT_SHORT_HIGH_HEAT:
    case SHT4x_MEASUREMENT_SHORT_MEDIUM_HEAT:
    case SHT4x_MEASUREMENT_SHORT_LOW_HEAT:
      _delay = 110;
      break;
  }
}


void SHT4x::setHeatInterval(measType measurementType)
{
  //  From a 10% duty cycle for 200 mW. 
  //  Linear interpolation for lower heat power.
  switch(measurementType)
  {
    case SHT4x_MEASUREMENT_LONG_HIGH_HEAT:
      _heatInterval = 10000;
      break;
    case SHT4x_MEASUREMENT_LONG_MEDIUM_HEAT:
      _heatInterval = 5500;
      break;
    case SHT4x_MEASUREMENT_LONG_LOW_HEAT:
      _heatInterval = 0;
      break;
    case SHT4x_MEASUREMENT_SHORT_HIGH_HEAT:
      _heatInterval = 1000;
      break;
    case SHT4x_MEASUREMENT_SHORT_MEDIUM_HEAT:
      _heatInterval = 550;
      break;
    case SHT4x_MEASUREMENT_SHORT_LOW_HEAT:
      _heatInterval = 0;
      break;
  }
}


bool SHT4x::isHeatCmd(measType measurementType)
{
  switch(measurementType)
  {
    case SHT4x_MEASUREMENT_LONG_HIGH_HEAT:
    case SHT4x_MEASUREMENT_LONG_MEDIUM_HEAT:
    case SHT4x_MEASUREMENT_LONG_LOW_HEAT:
    case SHT4x_MEASUREMENT_SHORT_HIGH_HEAT:
    case SHT4x_MEASUREMENT_SHORT_MEDIUM_HEAT:
    case SHT4x_MEASUREMENT_SHORT_LOW_HEAT:
      return true;
  }
  return false;
}


uint8_t SHT4x::crc8(const uint8_t *data, uint8_t length)
{
  //  CRC-8 formula from page 14 of SHT spec pdf
  const uint8_t POLY(0x31);
  uint8_t crc(0xFF);

  for (uint8_t j = length; j; --j)
  {
    crc ^= *data++;

    for (uint8_t i = 8; i; --i)
    {
      crc = (crc & 0x80) ? (crc << 1) ^ POLY : (crc << 1);
    }
  }
  return crc;
}


bool SHT4x::writeCommand(uint8_t command)
{
  _wire->beginTransmission(_address);
  _wire->write(command);
  if (_wire->endTransmission() != 0)
  {
    _error = SHT4x_ERR_WRITECMD;
    return false;
  }
  _error = SHT4x_OK;
  return true;
}


bool SHT4x::readBytes(uint8_t n, uint8_t *data)
{
  int rv = _wire->requestFrom(_address, (uint8_t) n);
  if (rv == n)
  {
    for (uint8_t i = 0; i < n; i++)
    {
      data[i] = _wire->read();
    }
    _error = SHT4x_OK;
    return true;
  }
  _error = SHT4x_ERR_READBYTES;
  return false;
}


//  -- END OF FILE --
