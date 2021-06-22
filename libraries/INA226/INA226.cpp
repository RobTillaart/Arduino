//    FILE: INA266.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2021-05-18
// PURPOSE: Arduino library for INA266 power sensor
//     URL: https://github.com/RobTillaart/INA226
//
//  HISTORY:
//  0.1.0   2021-05-18  initial version
//  0.1.1   2021-06-21  improved calibration + added functions
//  0.1.2   2021-06-22  add paramchecking of several functions + unit tests
//                      add getShunt() , getMaxCurrent()


#include "INA226.h"

#define INA226_CONFIGURATION        0x00
#define INA226_SHUNT_VOLTAGE        0x01
#define INA226_BUS_VOLTAGE          0x02
#define INA226_POWER                0x03
#define INA226_CURRENT              0x04
#define INA226_CALIBRATION          0x05
#define INA226_MASK_ENABLE          0x06
#define INA226_ALERT_LIMIT          0x07
#define INA226_MANUFACTURER         0xFE
#define INA226_DIE_ID               0xFF


////////////////////////////////////////////////////////
//
// Constructor
//
INA226::INA226(const int8_t address, TwoWire *wire)
{
  _address     = address;
  _wire        = wire;
  // as these 
  _current_LSB = 0;
  _maxCurrent  = 0;
  _shunt       = 0;
}


#if defined (ESP8266) || defined(ESP32)
bool INA226::begin(const uint8_t sda, const uint8_t scl)
{
  _wire = &Wire;
  _wire->begin(sda, scl);
  if (! isConnected()) return false;
  return true;
}
#endif


bool INA226::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  return true;
}


bool INA226::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


////////////////////////////////////////////////////////
//
// Core functions
//
float INA226::getShuntVoltage()
{
  uint16_t val = _readRegister(INA226_SHUNT_VOLTAGE);
  if (val & 0x8000)
  {
    val = val & 0x7FFF;
    val = val ^ 0x7FFF;
    val++;
    return val * -2.5e-6;
  }
  return val * 2.5e-6;   // fixed 2.50 uV
}


float INA226::getBusVoltage()
{
  uint16_t val = _readRegister(INA226_BUS_VOLTAGE);
  return val * 1.25e-3;  // fixed 1.25 mV
}


float INA226::getPower()
{
  uint16_t val = _readRegister(INA226_POWER);
  return val * 25 * _current_LSB;
}


float INA226::getCurrent()
{
  float val = _readRegister(INA226_CURRENT);
  return val * _current_LSB;
}


////////////////////////////////////////////////////////
//
// Configuration
//
void INA226::reset()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask |= 0x800;
  _writeRegister(INA226_CONFIGURATION, mask);
  // reset calibration?
}


bool INA226::setAverage(uint8_t avg)
{
  if (avg > 7) return false;
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= 0xF1FF;
  mask |= (avg << 9);
  _writeRegister(INA226_CONFIGURATION, mask);
  return true;
}


uint8_t INA226::getAverage()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask >>= 9;
  mask &= 7;
  return mask;
}


bool INA226::setBusVoltageConversionTime(uint8_t bvct)
{
  if (bvct > 7) return false;
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= 0xFE3F;
  mask |= (bvct << 6);
  _writeRegister(INA226_CONFIGURATION, mask);
  return true;
}


uint8_t INA226::getBusVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask >>= 6;
  mask &= 7;
  return mask;
}


bool INA226::setShuntVoltageConversionTime(uint8_t svct)
{
  if (svct > 7) return false;
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= 0xFFC7;
  mask |= (svct << 3);
  _writeRegister(INA226_CONFIGURATION, mask);
  return true;
}


uint8_t INA226::getShuntVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask >>= 3;
  mask &= 7;
  return mask;
}


////////////////////////////////////////////////////////
//
// Calibration
//
bool INA226::setMaxCurrentShunt(float maxCurrent, float shunt, bool normalize)
{
  if (maxCurrent > 20 || maxCurrent < 0.001) return false;
  if (shunt < 0.001) return false;
  _maxCurrent = maxCurrent;
  _shunt = shunt;

  _current_LSB = _maxCurrent * 3.0517578125e-005;  // maxCurrent / 32768;

  // normalize the LSB to a round number
  // not sure is this is more accurate / precise
  if (normalize)
  {
    // Serial.print("current_LSB:\t");
    // Serial.println(_current_LSB, 10);
    uint32_t factor = 1;
    while (_current_LSB < 1)
    {
        _current_LSB *= 10;
      factor *= 10;
    }
    _current_LSB = 10.0 / factor;
    // Serial.print("current_LSB:\t");
    // Serial.println(_current_LSB, 10);
  }

  uint16_t calib = round(0.00512 / (_current_LSB * _shunt));
  _writeRegister(INA226_CALIBRATION, calib);

  // Serial.print("Calibration:\t");
  // Serial.println(calib);
  return true;
}


////////////////////////////////////////////////////////
//
// operating mode
//
bool INA226::setMode(uint8_t mode)
{
  if (mode > 7) return false;
  uint16_t config = _readRegister(INA226_CONFIGURATION);
  config &= 0xFFF8;
  config |= mode;
  _writeRegister(INA226_CONFIGURATION, config);
  return true;
}


uint8_t INA226::getMode()
{
  return _readRegister(INA226_CONFIGURATION) & 0x0007;
}


////////////////////////////////////////////////////////
//
// alert
//
void INA226::setAlertRegister(uint16_t mask)
{
  _writeRegister(INA226_MASK_ENABLE, (mask & 0xFC00));
}


uint16_t INA226::getAlertFlag()
{
  return _readRegister(INA226_MASK_ENABLE) & 0x001F;
}


void INA226::setAlertLimit(uint16_t limit)
{
  _writeRegister(INA226_ALERT_LIMIT, limit);
}


uint16_t INA226::getAlertLimit()
{
  return _readRegister(INA226_ALERT_LIMIT);
}


////////////////////////////////////////////////////////
//
// meta information
//
uint16_t INA226::getManufacturerID()
{
  return _readRegister(INA226_MANUFACTURER);
}

uint16_t INA226::getDieID()
{
  return _readRegister(INA226_DIE_ID);
}


////////////////////////////////////////////////////////
//
// PRIVATE
//
uint16_t INA226::_readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->endTransmission();

  _wire->requestFrom(_address, (uint8_t)2);
  uint16_t value = _wire->read();
  value <<= 8;
  value |= _wire->read();
  return value;
}


uint16_t INA226::_writeRegister(uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value >> 8);
  _wire->write(value & 0xFF);
  return _wire->endTransmission();
}


// -- END OF FILE --

