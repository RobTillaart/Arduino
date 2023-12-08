//
//    FILE: MCP4725.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for 12 bit I2C DAC - MCP4725
// VERSION: 0.4.0
//     URL: https://github.com/RobTillaart/MCP4725


#include "MCP4725.h"


//  registerMode
#define MCP4725_DAC             0x40
#define MCP4725_DACEEPROM       0x60

//  page 22
#define MCP4725_GC_RESET        0x06
#define MCP4725_GC_WAKEUP       0x09


MCP4725::MCP4725(const uint8_t deviceAddress, TwoWire *wire)
{
  _deviceAddress   = deviceAddress;
  _wire            = wire;
  _lastValue       = 0;
  _powerDownMode   = 0;
  _lastWriteEEPROM = 0;
  _maxVoltage      = 5.0;
}


bool MCP4725::begin()
{
  if ((_deviceAddress < 0x60) || (_deviceAddress > 0x67)) return false;
  if (! isConnected()) return false;

  _lastValue = readDAC();
  _powerDownMode = readPowerDownModeDAC();
  return true;
}


bool MCP4725::isConnected()
{
  _wire->beginTransmission(_deviceAddress);
  return (_wire->endTransmission() == 0);
}


uint8_t MCP4725::getAddress()
{
  return _deviceAddress;
}


int MCP4725::setValue(const uint16_t value)
{
  if (value == _lastValue) return MCP4725_OK;
  if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;
  int rv = _writeFastMode(value);
  if (rv == 0) _lastValue = value;
  return rv;
}


uint16_t MCP4725::getValue()
{
  return _lastValue;
}


int MCP4725::setPercentage(float percentage)
{
  if ((percentage > 100) || (percentage < 0)) return MCP4725_VALUE_ERROR;
  return setValue(round(percentage * (0.01 * MCP4725_MAXVALUE)));
}


float MCP4725::getPercentage()
{
  return getValue() * (100.0 / MCP4725_MAXVALUE);
}


void MCP4725::setMaxVoltage(float v)
{
  _maxVoltage = v;
}


float MCP4725::getMaxVoltage()
{
  return _maxVoltage;
}


int MCP4725::setVoltage(float v)
{
  return setValue(round((v * MCP4725_MAXVALUE) / _maxVoltage));
}


float MCP4725::getVoltage()
{
  return getValue() * (_maxVoltage / MCP4725_MAXVALUE);
}


//  unfortunately it is not possible to write a different value
//  to the DAC and EEPROM simultaneously or write EEPROM only.
int MCP4725::writeDAC(const uint16_t value, const bool EEPROM)
{
  if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;
  while(!ready());
  int rv = _writeRegisterMode(value, EEPROM ? MCP4725_DACEEPROM : MCP4725_DAC);
  if (rv == 0) _lastValue = value;
  return rv;
}


//  ready checks if the last write to EEPROM has been written.
//  until ready all writes to the MCP4725 are ignored!
bool MCP4725::ready()
{
  yield();
  uint8_t buffer[1];
  _readRegister(buffer, 1);
  return ((buffer[0] & 0x80) > 0);
}


uint16_t MCP4725::readDAC()
{
  while(!ready());
  uint8_t buffer[3];
  _readRegister(buffer, 3);
  uint16_t value = buffer[1];
  value = value << 4;
  value = value + (buffer[2] >> 4);
  return value;
}


uint16_t MCP4725::readEEPROM()
{
  while(!ready());
  uint8_t buffer[5];
  _readRegister(buffer, 5);
  uint16_t value = buffer[3] & 0x0F;
  value = value << 8;
  value = value + buffer[4];
  return value;
}


uint32_t MCP4725::getLastWriteEEPROM()
{
  return _lastWriteEEPROM;
};


//  depending on bool EEPROM the value of PDM is written to
//  (false) DAC or
//  (true) DAC & EEPROM,
int MCP4725::writePowerDownMode(const uint8_t PDM, const bool EEPROM)
{
  _powerDownMode = (PDM & 0x03); // mask PDM bits only (written later low level)
  return writeDAC(_lastValue, EEPROM);
}


uint8_t MCP4725::readPowerDownModeEEPROM()
{
  while(!ready());
  uint8_t buffer[4];
  _readRegister(buffer, 4);
  uint8_t value = (buffer[3] >> 5) & 0x03;
  return value;
}


uint8_t MCP4725::readPowerDownModeDAC()
{
  while(!ready());  //  TODO needed?
  uint8_t buffer[1];
  _readRegister(buffer, 1);
  uint8_t value = (buffer[0] >> 1) & 0x03;
  return value;
}


//  PAGE 22 - experimental
//  DAC value is reset to EEPROM value
//  need to reflect this in cached value
int MCP4725::powerOnReset()
{
  int rv = _generalCall(MCP4725_GC_RESET);
  _lastValue = readDAC(); //  update cache to actual value;
  return rv;
}


//  PAGE 22 - experimental
//  _powerDownMode DAC resets to 0 -- PDM EEPROM stays same !!!
//  need to reflect this in cached value
int MCP4725::powerOnWakeUp()
{
  int rv = _generalCall(MCP4725_GC_WAKEUP);
  _powerDownMode = readPowerDownModeDAC();  //  update to actual value;
  return rv;
}


//  PAGE 18 DATASHEET
int MCP4725::_writeFastMode(const uint16_t value)
{
  uint8_t l = value & 0xFF;
  uint8_t h = ((value / 256) & 0x0F);  //  set C0 = C1 = 0, no PDmode
  h = h | (_powerDownMode << 4);

  _wire->beginTransmission(_deviceAddress);
  _wire->write(h);
  _wire->write(l);
  return _wire->endTransmission();
}


//  PAGE 19 DATASHEET
//  reg = MCP4725_DAC | MCP4725_EEPROM
int MCP4725::_writeRegisterMode(const uint16_t value, uint8_t reg)
{
  if (reg & MCP4725_DACEEPROM)
  {
    _lastWriteEEPROM = millis();
  }
  uint8_t h = (value / 16);
  uint8_t l = (value & 0x0F) << 4;
  _wire->beginTransmission(_deviceAddress);
  reg = reg | (_powerDownMode << 1);
  _wire->write(reg);
  _wire->write(h);
  _wire->write(l);
  return _wire->endTransmission();
}


//  PAGE 20 DATASHEET
//  typical 3 or 5 bytes
uint8_t MCP4725::_readRegister(uint8_t* buffer, const uint8_t length)
{
  _wire->beginTransmission(_deviceAddress);
  int rv = _wire->endTransmission();
  if (rv != 0) return 0;  //  error

  //  readBytes will always be equal or smaller to length
  uint8_t readBytes = _wire->requestFrom(_deviceAddress, length);
  uint8_t cnt = 0;
  while (cnt < readBytes)
  {
    buffer[cnt++] = _wire->read();
  }
  return readBytes;
}


//  name comes from datasheet
int MCP4725::_generalCall(const uint8_t gc)
{
  _wire->beginTransmission(0);  //  _deviceAddress
  _wire->write(gc);
  return _wire->endTransmission();
}


//  -- END OF FILE --

