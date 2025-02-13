//
//    FILE: DAC53001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-12
// VERSION: 0.1.0
// PURPOSE: Arduino library for I2C DAC53001 10 bit DAC.
//     URL: https://github.com/RobTillaart/DAC53001
//


#include "DAC53001.h"


////////////////////////////////////////////////////////
//
//  I2C REGISTERS - datasheet Page 55-69
//  note missing register addresses

const uint8_t DAC53001_NOP                    = 0x00;
const uint8_t DAC53001_DAC_1_MARGIN_HIGH      = 0x01;
const uint8_t DAC53001_DAC_1_MARGIN_LOW       = 0x02;
const uint8_t DAC53001_DAC_1_VOUT_CMP_CONFIG  = 0x03;
const uint8_t DAC53001_DAC_1_IOUT_MISC_CONFIG = 0x04;
const uint8_t DAC53001_DAC_1_CMP_MODE_CONFIG  = 0x05;
const uint8_t DAC53001_DAC_1_FUNC_CONFIG      = 0x06;

const uint8_t DAC53001_DAC_0_MARGIN_HIGH      = 0x13;
const uint8_t DAC53001_DAC_0_MARGIN_LOW       = 0x14;
const uint8_t DAC53001_DAC_0_VOUT_CMP_CONFIG  = 0x15;
const uint8_t DAC53001_DAC_0_IOUT_MISC_CONFIG = 0x16;
const uint8_t DAC53001_DAC_0_CMP_MODE_CONFIG  = 0x17;
const uint8_t DAC53001_DAC_0_FUNC_CONFIG      = 0x18;

const uint8_t DAC53001_DAC_1_DATA             = 0x19;
const uint8_t DAC53001_DAC_0_DATA             = 0x1C;

const uint8_t DAC53001_COMMON_CONFIG          = 0x1F;
const uint8_t DAC53001_COMMON_TRIGGER         = 0x20;
const uint8_t DAC53001_COMMON_DAC_TRIG        = 0x21;
const uint8_t DAC53001_GENERAL_STATUS         = 0x22;
const uint8_t DAC53001_CMP_STATUS             = 0x23;
const uint8_t DAC53001_GPIO_CONFIG            = 0x24;
const uint8_t DAC53001_DEVICE_MODE_CONFIG     = 0x25;
const uint8_t DAC53001_INTERFACE_CONFIG       = 0x26;
const uint8_t DAC53001_SRAM_CONFIG            = 0x2B;
const uint8_t DAC53001_SRAM_DATA              = 0x2C;
const uint8_t DAC53001_BRDCAST_DATA           = 0x50;



////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
DAC53001::DAC53001(const uint8_t address, TwoWire * wire)
{
  _address  = address;
  _wire     = wire;
  _channels = 1;
  _maxValue = 1023;
  _error    = DAC53001_OK;
}

bool DAC53001::begin()
{
  if (! isConnected()) return false;
  return true;
}

bool DAC53001::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}

uint8_t DAC53001::getAddress()
{
  return _address;
}

uint16_t DAC53001::getMaxValue()
{
  return _maxValue;
}

uint8_t DAC53001::getChannels()
{
  return _channels;
}


////////////////////////////////////////////////////////
//
//  VOLTAGE REFERENCE
//
void DAC53001::setReference(DACX300X_reference mode, uint8_t channel)
{
  if (channel >= _channels) return;
  if (mode > 0x05) return;

  //  COMMON-CONFIG page 62 for internal ref bit 12
  uint8_t reg = DAC53001_COMMON_CONFIG;
  uint16_t mask = _read16(reg);
  mask &= 0xEFFF;    //  disable internal reference
  if (mode > 1)
  {
    mask |= 0x1000;  //   enable internal reference
  }
  _write16(reg, mask);

  reg = DAC53001_DAC_0_VOUT_CMP_CONFIG;
  if (channel == 1) reg = DAC53001_DAC_1_VOUT_CMP_CONFIG;
  mask = _read16(reg);
  mask &= 0xE3FF;        //  clear bits
  mask |= (mode << 10);  //  set mode
  _write16(reg, mask);
}

uint8_t DAC53001::getReference(uint8_t channel)
{
  if (channel >= _channels) return 0;
  //  COMMON-CONFIG page 62 for internal ref bit 12
  uint8_t reg = DAC53001_DAC_0_VOUT_CMP_CONFIG;
  if (channel == 1) reg = DAC53001_DAC_1_VOUT_CMP_CONFIG;
  uint16_t mode = _read16(reg);
  mode >>= 10;
  mode &= 0x0007;
  return mode;
}


////////////////////////////////////////////////////////
//
//  CURRENT RANGE
//
void DAC53001::setCurrentRange(uint8_t range, uint8_t channel)
{
  if (channel >= _channels) return;
  if (range > 0x0B) return;
  uint8_t reg = DAC53001_DAC_0_IOUT_MISC_CONFIG;
  if (channel == 1) reg = DAC53001_DAC_1_IOUT_MISC_CONFIG;
  uint16_t mask = range << 9;
  _write16(reg, mask);
}

uint8_t DAC53001::getCurrentRange(uint8_t channel)
{
  if (channel >= _channels) return 0;
  uint8_t reg = DAC53001_DAC_0_IOUT_MISC_CONFIG;
  if (channel == 1) reg = DAC53001_DAC_1_IOUT_MISC_CONFIG;
  uint16_t mask = _read16(reg);
  return (mask >> 9) & 0x000F;
}


////////////////////////////////////////////////////////
//
//  OUTPUT MODE
//
void DAC53001::setOutputMode(uint8_t mode, uint8_t channel)
{
  if (channel >= _channels) return;
  if ((mode == 0x00) || (mode > 0x07)) return;
  uint8_t reg = DAC53001_COMMON_CONFIG;
  uint16_t mask = _read16(reg);
  if (channel == 0)
  {
    mask |= 0x0E00;  //  disable output DAC0
    mask |= (mode << 9);
  }
  if (channel == 1)
  {
    mask |= 0x0007;  //  disable output DAC1
    mask |= (mode);
  }
  _write16(reg, mask);
}

uint8_t DAC53001::getOutputMode(uint8_t channel)
{
  if (channel >= _channels) return 0;
  uint8_t reg = DAC53001_COMMON_CONFIG;
  uint16_t mask = _read16(reg);
  uint8_t mode = 0;
  if (channel == 0)
  {
    mode = (mask & 0x0E00) >> 9;
  }
  if (channel == 1)
  {
    mode = (mask & 0x0007);
  }
  return mode;
}


////////////////////////////////////////////////////////
//
//  GENERAL STATUS
//
uint16_t DAC53001::getStatus()
{
  return _read16(DAC53001_GENERAL_STATUS);
}

uint16_t DAC53001::getDeviceID()
{
  uint16_t deviceId = _read16(DAC53001_GENERAL_STATUS);
  // translate 08 = 63002, 09 = 63001, 10 = 53002, 11 = 53001  ?
  return (deviceId & 0x000F) >> 2;
}

uint16_t DAC53001::getVersionID()
{
  uint16_t versionId = _read16(DAC53001_GENERAL_STATUS);
  return versionId & 0x03;
}


////////////////////////////////////////////////////////
//
//  SETDAC
//
uint16_t DAC53001::setDAC(uint16_t value, uint8_t channel)
{
  if (channel >= _channels) return 0;
  uint8_t reg = DAC53001_DAC_0_DATA;
  if (channel == 1) reg = DAC53001_DAC_1_DATA;
  return _write16(reg, value << 4);  //  bit 4-15
}

uint16_t DAC53001::getDAC(uint8_t channel)
{
  if (channel >= _channels) return 0;
  uint8_t reg = DAC53001_DAC_0_DATA;
  if (channel == 1) reg = DAC53001_DAC_1_DATA;
  return _read16(reg) >> 4;  //  bit 4-15
}

uint16_t DAC53001::lastError()
{
  uint16_t e = _error;
  _error = DAC53001_OK;
  return e;
}


////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint16_t DAC53001::_read16(uint8_t reg)
{
  _error = DAC53001_OK;
  //  improve the odds that IO will not interrupted.
  yield();

  _wire->beginTransmission(_address);
  _wire->write(reg);
  if (_wire->endTransmission() != 0)
  {
    _error = DAC53001_I2C_ERROR;
    return 0xFFFF;
  }
  if (2 != _wire->requestFrom(_address, (uint8_t)2))
  {
    _error = DAC53001_I2C_ERROR;
    return 0xFFFF;
  }
  uint16_t value = _wire->read();
  value <<= 8;
  value += _wire->read();
  return value;
}

uint16_t DAC53001::_write16(uint8_t reg, uint16_t value)
{
  _error = DAC53001_OK;
  //  improve the odds that IO will not interrupted.
  yield();

  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value >> 8);
  _wire->write(value & 0xFF);
  if (_wire->endTransmission() != 0)
  {
    _error = DAC53001_I2C_ERROR;
  }
  return _error;
}



////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
//  TODO - DAC53002 - DAC63001 - DAC63002 ??
DAC53002::DAC53002(const uint8_t address, TwoWire * wire)
        : DAC53001(address, wire)
{
  _channels = 2;
  _maxValue = 1023;
}

DAC63001::DAC63001(const uint8_t address, TwoWire * wire)
        : DAC53001(address, wire)
{
  _channels = 1;
  _maxValue = 4095;
}

DAC63002::DAC63002(const uint8_t address, TwoWire * wire)
        : DAC53001(address, wire)
{
  _channels = 2;
  _maxValue = 4095;
}


//  -- END OF FILE --

