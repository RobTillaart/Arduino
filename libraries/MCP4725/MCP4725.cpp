//
//    FILE: MCP4725.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for 12 bit I2C DAC - MCP4725 
// VERSION: 0.3.0
//     URL: https://github.com/RobTillaart/MCP4725
//
//  HISTORY:
//  0.1.00  2013-11-24  initial version
//  0.1.01  2013-11-30  added readDAC() & writeDAC (registerwrite)
//  0.1.02  2013-12-01  added readEEPROM() & RDY()
//  0.1.03  2013-12-01  added powerDownMode code
//  0.1.04  2013-12-04  improved the generalCall code (still experimental)
//  0.1.05  2015-03-06  refactoring, stricter interfaces
//  0.1.6   2017-04-19  refactor + remove timeout - https://github.com/RobTillaart/Arduino/issues/63
//  0.1.7   2017-04-20  refactor the removed timeout (Thanks to Koepel)
//  0.1.8   2018-10-24  fix read only var #115 (kudos to perl1234)
//  0.1.9   2019-10-14  replace AVR specific TWBR with _wire->setClock() #131
//  0.2.0   2020-06-20  #pragma; remove pre 1.0 support; refactor a lot
//                      RDY() -> ready()
//  0.2.1   2020-07-04  Add yield(); add getLastWriteEEPROM(); 
//                      update readme.md + keywords.txt
//  0.2.2   2020-07-05  add get/setPercentage();
//  0.2.3   2020-12-26  arduino-CI, bool isConnected(), bool begin()
//  0.3.0   2021-01-15  Add WireN support (e.g. teensy)


#include "MCP4725.h"


// registerMode
#define MCP4725_DAC             0x40
#define MCP4725_DACEEPROM       0x60

// page 22
#define MCP4725_GC_RESET        0x06
#define MCP4725_GC_WAKEUP       0x09


MCP4725::MCP4725(const uint8_t deviceAddress, TwoWire *wire)
{
  _deviceAddress   = deviceAddress;
  _wire            = wire;
  _lastValue       = 0;
  _powerDownMode   = 0;
  _lastWriteEEPROM = 0;
}


#if defined(ESP8266) || defined(ESP32)
bool MCP4725::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  _wire  = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  if (isConnected())
  {
    _lastValue = readDAC();
    _powerDownMode = readPowerDownModeDAC();
    return true;
  }
  return false;
}
#endif


bool MCP4725::begin()
{
  _wire->begin();
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


int MCP4725::setValue(const uint16_t value)
{
  if (value == _lastValue) return 0;
  if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;
  int rv = _writeFastMode(value);
  if (rv == 0) _lastValue = value;
  return rv;
}


uint16_t MCP4725::getValue()
{
  return _lastValue;
}


// unfortunately it is not possible to write a different value
// to the DAC and EEPROM simultaneously or write EEPROM only.
int MCP4725::writeDAC(const uint16_t value, const bool EEPROM)
{
  if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;
  while(!ready());
  int rv = _writeRegisterMode(value, EEPROM ? MCP4725_DACEEPROM : MCP4725_DAC);
  if (rv == 0) _lastValue = value;
  return rv;
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


// depending on bool EEPROM the value of PDM is written to
// (false) DAC or
// (true) DAC & EEPROM,
int MCP4725::writePowerDownMode(const uint8_t PDM, const bool EEPROM)
{
  _powerDownMode = (PDM & 0x03); // mask pdm bits only (written later low level)
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
  while(!ready());  // TODO needed?
  uint8_t buffer[1];
  _readRegister(buffer, 1);
  uint8_t value = (buffer[0] >> 1) & 0x03;
  return value;
}


// PAGE 22 - experimental
// DAC value is reset to EEPROM value
// need to reflect this in cached value
int MCP4725::powerOnReset()
{
  int rv = _generalCall(MCP4725_GC_RESET);
  _lastValue = readDAC(); // update cache to actual value;
  return rv;
}


// PAGE 22 - experimental
// _powerDownMode DAC resets to 0 -- pdm EEPROM stays same !!!
// need to reflect this in cached value
int MCP4725::powerOnWakeUp()
{
  int rv = _generalCall(MCP4725_GC_WAKEUP);
  _powerDownMode = readPowerDownModeDAC();  // update to actual value;
  return rv;
}

// PAGE 18 DATASHEET
int MCP4725::_writeFastMode(const uint16_t value)
{
  uint8_t l = value & 0xFF;
  uint8_t h = ((value / 256) & 0x0F);  // set C0 = C1 = 0, no PDmode
  h = h | (_powerDownMode << 4);

  _wire->beginTransmission(_deviceAddress);
  _wire->write(h);
  _wire->write(l);
  return _wire->endTransmission();
}


// ready checks if the last write to EEPROM has been written.
// until ready all writes to the MCP4725 are ignored!
bool MCP4725::ready()
{
  yield();
  uint8_t buffer[1];
  _readRegister(buffer, 1);
  return ((buffer[0] & 0x80) > 0);
}


// PAGE 19 DATASHEET
// reg = MCP4725_DAC | MCP4725_EEPROM
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


// PAGE 20 DATASHEET
// typical 3 or 5 bytes
uint8_t MCP4725::_readRegister(uint8_t* buffer, const uint8_t length)
{
  _wire->beginTransmission(_deviceAddress);
  int rv = _wire->endTransmission();
  if (rv != 0) return 0;  // error

  // readbytes will always be equal or smaller to length
  uint8_t readBytes = _wire->requestFrom(_deviceAddress, length);
  uint8_t cnt = 0;
  while (cnt < readBytes)
  {
    buffer[cnt++] = _wire->read();
  }
  return readBytes;
}


// name comes from datasheet
int MCP4725::_generalCall(const uint8_t gc)
{
  _wire->beginTransmission(0);  // _deviceAddress
  _wire->write(gc);
  return _wire->endTransmission();
}

// -- END OF FILE --
