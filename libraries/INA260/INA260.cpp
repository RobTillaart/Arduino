//    FILE: INA260.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-02-18
// PURPOSE: Arduino library for INA260 power sensor
//     URL: https://github.com/RobTillaart/INA260
//
//  Read the datasheet for the details


#include "INA260.h"

//  REGISTERS
#define INA260_CONFIGURATION              0x00
#define INA260_CURRENT                    0x01
#define INA260_BUS_VOLTAGE                0x02
#define INA260_POWER                      0x03

#define INA260_MASK_ENABLE                0x06
#define INA260_ALERT_LIMIT                0x07
#define INA260_MANUFACTURER               0xFE
#define INA260_DIE_ID                     0xFF


//  CONFIGURATION MASKS
#define INA260_CONF_RESET_MASK            0x8000
#define INA260_CONF_AVERAGE_MASK          0x0E00
#define INA260_CONF_BUSVC_MASK            0x01C0
#define INA260_CONF_SHUNTCC_MASK          0x0038
#define INA260_CONF_MODE_MASK             0x0007


////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
INA260::INA260(const uint8_t address, TwoWire *wire)
{
  _address     = address;
  _wire        = wire;
}


bool INA260::begin()
{
  if (! isConnected()) return false;
  return true;
}


bool INA260::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t INA260::getAddress()
{
  return _address;
};


////////////////////////////////////////////////////////
//
//  CORE FUNCTIONS
//
float INA260::getBusVoltage()  //  8.6.3
{
  uint16_t val = _readRegister(INA260_BUS_VOLTAGE);
  return val * 1.25e-3;       //  1.25 mV
}


float INA260::getShuntVoltage()  //  8.6.2
{
  return getCurrent() * _shunt;
}


float INA260::getCurrent()  //  8.6.2
{
  int16_t val = _readRegister(INA260_CURRENT);
  return val * _current_LSB;     //  1.25 mA
}


float INA260::getPower()  //  8.6.4
{
  uint16_t val = _readRegister(INA260_POWER);
  return val * 10.0e-3;  //  fixed 10 mW
}


bool INA260::isConversionReady()  //  8.6.5
{
  uint16_t mask = _readRegister(INA260_MASK_ENABLE);
  return (mask & INA260_CONVERSION_READY_FLAG) == INA260_CONVERSION_READY_FLAG;
}


bool INA260::waitConversionReady(uint32_t timeout)  //  8.6.5
{
  uint32_t start = millis();
  while ( (millis() - start) <= timeout)
  {
    if (isConversionReady()) return true;
    delay(1);  //  implicit yield();
  }
  return false;
}


////////////////////////////////////////////////////////
//
//  CONFIGURATION
//
bool INA260::reset()  //  8.6.1
{
  uint16_t mask = _readRegister(INA260_CONFIGURATION);
  mask |= INA260_CONF_RESET_MASK;
  uint16_t result = _writeRegister(INA260_CONFIGURATION, mask);
  //  Serial.println(result);
  if (result != 0) return false;
  return true;
}


bool INA260::setAverage(uint8_t avg)  //  8.6.1
{
  if (avg > 7) return false;
  uint16_t mask = _readRegister(INA260_CONFIGURATION);
  mask &= ~INA260_CONF_AVERAGE_MASK;
  mask |= (avg << 9);
  _writeRegister(INA260_CONFIGURATION, mask);
  return true;
}


uint8_t INA260::getAverage()  //  8.6.1
{
  uint16_t mask = _readRegister(INA260_CONFIGURATION);
  mask &= INA260_CONF_AVERAGE_MASK;
  mask >>= 9;
  return mask;
}


bool INA260::setBusVoltageConversionTime(uint8_t bvct)  //  8.6.1
{
  if (bvct > 7) return false;
  uint16_t mask = _readRegister(INA260_CONFIGURATION);
  mask &= ~INA260_CONF_BUSVC_MASK;
  mask |= (bvct << 6);
  _writeRegister(INA260_CONFIGURATION, mask);
  return true;
}


uint8_t INA260::getBusVoltageConversionTime()  //  8.6.1
{
  uint16_t mask = _readRegister(INA260_CONFIGURATION);
  mask &= INA260_CONF_BUSVC_MASK;
  mask >>= 6;
  return mask;
}


bool INA260::setShuntCurrentConversionTime(uint8_t scct)  //  8.6.1
{
  if (scct > 7) return false;
  uint16_t mask = _readRegister(INA260_CONFIGURATION);
  mask &= ~INA260_CONF_SHUNTCC_MASK;
  mask |= (scct << 3);
  _writeRegister(INA260_CONFIGURATION, mask);
  return true;
}


uint8_t INA260::getShuntCurrentConversionTime()  //  8.6.1
{
  uint16_t mask = _readRegister(INA260_CONFIGURATION);
  mask &= INA260_CONF_SHUNTCC_MASK;
  mask >>= 3;
  return mask;
}


////////////////////////////////////////////////////////
//
//  OPERATING MODE
//
bool INA260::setMode(uint8_t mode)  //  8.6.1
{
  if (mode > 7) return false;
  uint16_t config = _readRegister(INA260_CONFIGURATION);
  config &= ~INA260_CONF_MODE_MASK;
  config |= mode;
  _writeRegister(INA260_CONFIGURATION, config);
  return true;
}


uint8_t INA260::getMode()  //  8.6.1
{
  uint16_t mode = _readRegister(INA260_CONFIGURATION);
  mode &= INA260_CONF_MODE_MASK;
  return mode;
}


////////////////////////////////////////////////////////
//
//  ALERT
//
bool INA260::setAlertRegister(uint16_t mask)  //  8.6.5
{
  uint16_t result = _writeRegister(INA260_MASK_ENABLE, (mask & 0xFC00));
  //  Serial.println(result);
  if (result != 0) return false;
  return true;
}


uint16_t INA260::getAlertFlag()  //  8.6.5
{
  return _readRegister(INA260_MASK_ENABLE) & 0x001F;
}


bool INA260::setAlertLimit(uint16_t limit)  //  8.6.6
{
  uint16_t result = _writeRegister(INA260_ALERT_LIMIT, limit);
  //  Serial.println(result);
  if (result != 0) return false;
  return true;
}


uint16_t INA260::getAlertLimit()  //  8.6.6
{
  return _readRegister(INA260_ALERT_LIMIT);
}


////////////////////////////////////////////////////////
//
//  META INFORMATION
//
uint16_t INA260::getManufacturerID()  //  8.6.7
{
  return _readRegister(INA260_MANUFACTURER);
}


uint16_t INA260::getDieID()  //  8.6.7
{
  return _readRegister(INA260_DIE_ID);
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint16_t INA260::_readRegister(uint8_t reg)
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


uint16_t INA260::_writeRegister(uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value >> 8);
  _wire->write(value & 0xFF);
  return _wire->endTransmission();
}


//  -- END OF FILE --

