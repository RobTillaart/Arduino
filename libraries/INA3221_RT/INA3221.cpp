//    FILE: INA3221.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2024-02-05
// PURPOSE: Arduino library for the I2C INA3221 3 channel voltage and current sensor.
//     URL: https://github.com/RobTillaart/INA3221_RT
//
//  Read the datasheet for the details


#include "INA3221.h"


//  REGISTERS
#define INA3221_CONFIGURATION              (0x00)
#define INA3221_SHUNT_VOLTAGE(x)           (0x01 + (x*2))
#define INA3221_BUS_VOLTAGE(x)             (0x02 + (x*2))
#define INA3221_CRITICAL_ALERT(x)          (0x07 + (x*2))
#define INA3221_WARNING_ALERT(x)           (0x08 + (x*2))
#define INA3221_SHUNT_VOLTAGE_SUM          (0x0D)
#define INA3221_SHUNT_VOLTAGE_LIMIT        (0x0E)
#define INA3221_MASK_ENABLE                (0x0F)
#define INA3221_POWER_VALID_UPPER          (0x10)
#define INA3221_POWER_VALID_LOWER          (0x11)
#define INA3221_MANUFACTURER               (0xFE)
#define INA3221_DIE_ID                     (0xFF)


//  CONFIGURATION MASKS (not used)
//  #define INA3221_CONF_RESET_MASK            0x8000
//  #define INA3221_CONF_CHANNEL_ENABLE_MASK   0x7000
//  #define INA3221_CONF_AVERAGE_MASK          0x0E00
//  #define INA3221_CONF_BUSVC_MASK            0x01C0
//  #define INA3221_CONF_SHUNTVC_MASK          0x0038
//  #define INA3221_CONF_MODE_MASK             0x0007


#define INA3221_SHUNT_LSB                  40


////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
INA3221::INA3221(const uint8_t address, TwoWire *wire)
{
  _address     = address;
  _wire        = wire;
  _shunt[0]    = 0.1;  //  Ohm
  _shunt[1]    = 0.1;  //  Ohm
  _shunt[2]    = 0.1;  //  Ohm
}

bool INA3221::begin()
{
  if (! isConnected()) return false;
  return true;
}

bool INA3221::isConnected()
{
  if ((_address < 0x40) || (_address > 0x43)) return false;
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}

uint8_t INA3221::getAddress()
{
  return _address;
};


////////////////////////////////////////////////////////
//
//  CORE
//
float INA3221::getBusVoltage(uint8_t channel)
{
  if (channel > 2) return -1;
  uint16_t value = _readRegister(INA3221_BUS_VOLTAGE(channel));
  return (value >> 3) * 8.0e-3;  //  fixed 8 mV  (Page 6)
}

float INA3221::getShuntVoltage(uint8_t channel)
{
  if (channel > 2) return -1;
  int16_t val = _readRegister(INA3221_SHUNT_VOLTAGE(channel));
  return (val >> 3) * 40e-6;   //  fixed 40 uV  (Page 6)
}

float INA3221::getCurrent(uint8_t channel)
{
  if (channel > 2) return -1;
  return getShuntVoltage(channel) / _shunt[channel];  //  Ohms law
}

float INA3221::getPower(uint8_t channel)
{
  if (channel > 2) return -1;
  return getBusVoltage(channel) * getCurrent(channel);
}


////////////////////////////////////////////////////////
//
//  CONFIGURATION
//

////////////////////////////////////////////////////////
//
//  SHUNT
//
int INA3221::setShuntR(uint8_t channel, float ohm)
{
  if (channel > 2) return -1;
  _shunt[channel] = ohm;
  return 0;
}

float INA3221::getShuntR(uint8_t channel)
{
  if (channel > 2) return -1;
  return _shunt[channel];
}


////////////////////////////////////////////////////////
//
//  SHUNT ALERT WARNINGS & CRITICAL
//
int INA3221::setCriticalAlert(uint8_t channel, uint32_t microVolt)
{
  if (channel > 2) return -1;
  // Check for the full scale voltage = 163.8 mV == 163800 uV
  if (microVolt > 163800) return -2;
  uint16_t value = (microVolt / 40) << 3;  //  LSB 40uV  shift 3
  return _writeRegister(INA3221_CRITICAL_ALERT(channel), value);
}

uint32_t INA3221::getCriticalAlert(uint8_t channel)
{
  if (channel > 2) return -1;
  uint32_t value = _readRegister(INA3221_CRITICAL_ALERT(channel));
  return (value >> 3) * 40;  //  LSB 40uV
}

int INA3221::setWarningAlert(uint8_t channel, uint32_t microVolt)
{
  if (channel > 2) return -1;
  // Check for the full scale voltage = 163.8 mV == 163800 uV
  if (microVolt > 163800) return -2;
  uint16_t value = (microVolt / 40) << 3;  //  LSB 40uV  shift 3
  return _writeRegister(INA3221_WARNING_ALERT(channel), value);
}

uint32_t INA3221::getWarningAlert(uint8_t channel)
{
  if (channel > 2) return -1;
  uint32_t value = _readRegister(INA3221_WARNING_ALERT(channel));
  return (value >> 3) * 40;  //  LSB 40uV
}

//  mA wrappers

int INA3221::setCriticalCurrent(uint8_t channel, float milliAmpere)
{
  return setCriticalAlert(channel, 1000.0 * milliAmpere * _shunt[channel]);
}

float INA3221::getCriticalCurrent(uint8_t channel)
{
  return getCriticalAlert(channel) * 0.001 / _shunt[channel];
}

int INA3221::setWarningCurrent(uint8_t channel, float milliAmpere)
{
  return setWarningAlert(channel, 1000.0 * milliAmpere * _shunt[channel]);
}

float INA3221::getWarningCurrent(uint8_t channel)
{
  return getWarningAlert(channel) * 0.001 / _shunt[channel];
}


////////////////////////////////////////////////////////
//
//  SHUNT VOLTAGE SUM
//
//  LSB 40 uV;
//
int32_t INA3221::getShuntVoltageSum()
{
  int16_t value = _readRegister(INA3221_SHUNT_VOLTAGE_SUM);
  return (value >> 1) * 40L;
}

int INA3221::setShuntVoltageSumLimit(int32_t microVolt)
{
  //  15 bit signed.
  if (abs(microVolt) > (16383L * 40L)) return -2;
  int16_t value = (microVolt / 40) << 1;
  return _writeRegister(INA3221_SHUNT_VOLTAGE_LIMIT, value);
}

int32_t INA3221::getShuntVoltageSumLimit()
{
  int32_t value = _readRegister(INA3221_SHUNT_VOLTAGE_LIMIT);
  return (value >> 1) * 40L;
}


////////////////////////////////////////////////////////
//
//  CONFIGURATION
//
int INA3221::setConfiguration(uint16_t mask)
{
  return _writeRegister(INA3221_CONFIGURATION, mask);
}

uint16_t INA3221::getConfiguration()
{
  return _readRegister(INA3221_CONFIGURATION);
}

int INA3221::reset()
{
  return _writeRegister(INA3221_CONFIGURATION, 0xF127);
}

int INA3221::enableChannel(uint8_t channel)
{
  if (channel > 2) return -1;
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  mask |= (1 << (14 - channel));
  return _writeRegister(INA3221_CONFIGURATION, mask);
}

int INA3221::disableChannel(uint8_t channel)
{
  if (channel > 2) return -1;
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  mask &= ~(1 << (14 - channel));
  return _writeRegister(INA3221_CONFIGURATION, mask);
}

int INA3221::getEnableChannel(uint8_t channel)
{
  if (channel > 2) return -1;
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  return (mask & (1 << (14 - channel))) > 0;
}

int INA3221::setAverage(uint8_t avg)
{
  if (avg > 7) return -10;
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  mask &= ~(7 << 9);
  mask |= (avg << 9);
  //  in one line mask &= ~((~avg) << 9)
  return _writeRegister(INA3221_CONFIGURATION, mask);
}

int INA3221::getAverage()
{
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  return (mask >> 9) & 7;
}

int INA3221::setBusVoltageConversionTime(uint8_t bvct)
{
  if (bvct > 7) return -10;
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  mask &= ~(7 << 6);
  mask |= (bvct << 6);
  return _writeRegister(INA3221_CONFIGURATION, mask);
}

int INA3221::getBusVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  return (mask >> 6) & 7;
}

int INA3221::setShuntVoltageConversionTime(uint8_t svct)
{
  if (svct > 7) return -10;
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  mask &= ~(7 << 3);
  mask |= (svct << 3);
  return _writeRegister(INA3221_CONFIGURATION, mask);
}

int INA3221::getShuntVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  return (mask >> 3) & 7;
}


//  operating mode
int INA3221::setMode(uint8_t mode)
{
  if (mode > 7) return -10;
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  mask &= ~7;
  mask |= mode;
  return _writeRegister(INA3221_CONFIGURATION, mask);
}

int INA3221::getMode()
{
  uint16_t mask = _readRegister(INA3221_CONFIGURATION);
  return mask & 7;
}


////////////////////////////////////////////////////////
//
//  MASK/ENABLE
//
int INA3221::setMaskEnable(uint16_t mask)
{
  return _writeRegister(INA3221_MASK_ENABLE, mask);
}

uint16_t INA3221::getMaskEnable()
{
  return _readRegister(INA3221_MASK_ENABLE);
}


////////////////////////////////////////////////////////
//
//  POWER LIMIT
//
//  LSB 8mV  shift 3
//
int INA3221::setPowerUpperLimit(int16_t milliVolt)
{
  //  int16_t is always within the range (after masking) 32760
  //  if (milliVolt > 4095 * 8) return -10;    //  LSB 8mV  shift 3
  int16_t value = milliVolt & 0xFFF8;  //  mask reserved bits
  return _writeRegister(INA3221_POWER_VALID_UPPER, value);
}

int16_t INA3221::getPowerUpperLimit()
{
  int16_t value = _readRegister(INA3221_POWER_VALID_UPPER);
  //  (value >> 3) * 8mV;  shift 3 compensates 8 mV
  return value;
}

int INA3221::setPowerLowerLimit(int16_t milliVolt)
{
  //  int16_t is always within the range (after masking) 32760
  //  if (milliVolt > 4095 * 8) return -10;    //  LSB 8mV  shift 3
  int16_t value = milliVolt & 0xFFF8;
  return _writeRegister(INA3221_POWER_VALID_LOWER, value);
}

int16_t INA3221::getPowerLowerLimit()
{
  int16_t value = _readRegister(INA3221_POWER_VALID_LOWER);
  //  (value >> 3) * 8mV;  shift 3 compensates 8 mV
  return value;
}


////////////////////////////////////////////////////////
//
//  META information
//
uint16_t INA3221::getManufacturerID()
{
  return _readRegister(INA3221_MANUFACTURER);
}


uint16_t INA3221::getDieID()
{
  return _readRegister(INA3221_DIE_ID);
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint16_t INA3221::_readRegister(uint8_t reg)
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


uint16_t INA3221::_writeRegister(uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value >> 8);
  _wire->write(value & 0xFF);
  return _wire->endTransmission();
}


//  -- END OF FILE --

