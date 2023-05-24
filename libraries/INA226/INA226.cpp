//    FILE: INA226.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.3
//    DATE: 2021-05-18
// PURPOSE: Arduino library for INA226 power sensor
//     URL: https://github.com/RobTillaart/INA226


#include "INA226.h"

//  REGISTERS
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


//  CONFIGURATION MASKS
#define INA226_CONF_RESET_MASK      0x8000
#define INA226_CONF_AVERAGE_MASK    0x0E00
#define INA226_CONF_BUSVC_MASK      0x01C0
#define INA226_CONF_SHUNTVC_MASK    0x0038
#define INA226_CONF_MODE_MASK       0x0007


////////////////////////////////////////////////////////
//
//  Constructor
//
INA226::INA226(const uint8_t address, TwoWire *wire)
{
  _address     = address;
  _wire        = wire;
  //  not calibrated values by default.
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


uint8_t INA226::getAddress()
{
  return _address;
};


////////////////////////////////////////////////////////
//
//  Core functions
//
float INA226::getShuntVoltage()
{
  int16_t val = _readRegister(INA226_SHUNT_VOLTAGE);
  return val * 2.5e-6;   //  fixed 2.50 uV
}


float INA226::getBusVoltage()
{
  uint16_t val = _readRegister(INA226_BUS_VOLTAGE);
  return val * 1.25e-3;  //  fixed 1.25 mV
}


float INA226::getPower()
{
  uint16_t val = _readRegister(INA226_POWER);
  return val * 25 * _current_LSB;  //  fixed 25 Watt
}


float INA226::getCurrent()
{
  int16_t val = _readRegister(INA226_CURRENT);
  return val * _current_LSB;
}


////////////////////////////////////////////////////////
//
//  Configuration
//
void INA226::reset()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask |= INA226_CONF_RESET_MASK;
  _writeRegister(INA226_CONFIGURATION, mask);
  //  reset calibration
  _current_LSB = 0;
  _maxCurrent  = 0;
  _shunt       = 0;
}


bool INA226::setAverage(uint8_t avg)
{
  if (avg > 7) return false;
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= ~INA226_CONF_AVERAGE_MASK;
  mask |= (avg << 9);
  _writeRegister(INA226_CONFIGURATION, mask);
  return true;
}


uint8_t INA226::getAverage()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= INA226_CONF_AVERAGE_MASK;
  mask >>= 9;
  return mask;
}


bool INA226::setBusVoltageConversionTime(uint8_t bvct)
{
  if (bvct > 7) return false;
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= ~INA226_CONF_BUSVC_MASK;
  mask |= (bvct << 6);
  _writeRegister(INA226_CONFIGURATION, mask);
  return true;
}


uint8_t INA226::getBusVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= INA226_CONF_BUSVC_MASK;
  mask >>= 6;
  return mask;
}


bool INA226::setShuntVoltageConversionTime(uint8_t svct)
{
  if (svct > 7) return false;
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= ~INA226_CONF_SHUNTVC_MASK;
  mask |= (svct << 3);
  _writeRegister(INA226_CONFIGURATION, mask);
  return true;
}


uint8_t INA226::getShuntVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= INA226_CONF_SHUNTVC_MASK;
  mask >>= 3;
  return mask;
}


////////////////////////////////////////////////////////
//
//  Calibration
//
int INA226::setMaxCurrentShunt(float maxCurrent, float shunt, bool normalize)
{
  //  #define printdebug true

  //  fix #16 - datasheet 6.5 Electrical Characteristics
  //            rounded value to 80 mV
  float shuntVoltage = abs(maxCurrent * shunt);
  if (shuntVoltage > 0.080)         return INA226_ERR_SHUNTVOLTAGE_HIGH;
  if (maxCurrent < 0.001)           return INA226_ERR_MAXCURRENT_LOW;
  if (shunt < INA226_MINIMAL_SHUNT) return INA226_ERR_SHUNT_LOW;

  _current_LSB = maxCurrent * 3.0517578125e-5;      // maxCurrent / 32768;

  #ifdef printdebug
    Serial.println();
    Serial.print("normalize:\t");
    Serial.println(normalize ? " true":" false");
    Serial.print("initial current_LSB:\t");
    Serial.print(_current_LSB, 8);
    Serial.println(" uA / bit");
  #endif

  uint32_t calib  = 0;
  uint32_t factor = 1;

  //  normalize the LSB to a round number
  //  LSB will increase
  if (normalize)
  {
    calib = round(0.00512 / (_current_LSB * shunt));
    _current_LSB = 0.00512 / (calib * shunt);

    #ifdef printdebug
      Serial.print("Prescale current_LSB:\t");
      Serial.print(_current_LSB, 8);
      Serial.println(" uA / bit");
    #endif

    //  auto scale current_LSB
    factor = 1;
    while (_current_LSB < 1)
    {
      _current_LSB *= 10;
      factor *= 10;
    }
    _current_LSB = 1.0 / factor;
  }

  //  auto scale calibration
  calib = round(0.00512 / (_current_LSB * shunt));
  while (calib > 65535)
  {
    _current_LSB *= 10;
    calib /= 10;
  }
  _writeRegister(INA226_CALIBRATION, calib);

  _maxCurrent = _current_LSB * 32768;
  _shunt = shunt;

  #ifdef printdebug
    Serial.print("factor:\t");
    Serial.println(factor);
    Serial.print("Final current_LSB:\t");
    Serial.print(_current_LSB, 8);
    Serial.println(" uA / bit");
    Serial.print("Calibration:\t");
    Serial.println(calib);
    Serial.print("Max current:\t");
    Serial.print(_maxCurrent);
    Serial.println(" A");
    Serial.print("Shunt:\t");
    Serial.print(_shunt, 8);
    Serial.println(" ohm");
    Serial.print("ShuntV:\t");
    Serial.print(shuntVoltage, 4);
    Serial.println(" Volt");
  #endif

  return INA226_ERR_NONE;
}


////////////////////////////////////////////////////////
//
//  operating mode
//
bool INA226::setMode(uint8_t mode)
{
  if (mode > 7) return false;
  uint16_t config = _readRegister(INA226_CONFIGURATION);
  config &= ~INA226_CONF_MODE_MASK;
  config |= mode;
  _writeRegister(INA226_CONFIGURATION, config);
  return true;
}


uint8_t INA226::getMode()
{
  uint16_t mode = _readRegister(INA226_CONFIGURATION);
  mode &= INA226_CONF_MODE_MASK;
  return mode;
}


////////////////////////////////////////////////////////
//
//  alert
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
//  meta information
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
//  PRIVATE
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


//  -- END OF FILE --

