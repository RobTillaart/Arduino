//
//    FILE: PCF8575.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-20
// VERSION: 0.1.1
// PURPOSE: Arduino library for PCF8575 - 16 channel I2C IO expander
//     URL: https://github.com/RobTillaart/PCF8575
//
//  HISTORY:
//  0.0.1  2020-07-20  initial version
//  0.0.2  2020-07-21  fix reverse(); refactor;
//  0.0.3  2020-07-29  fix #5 reverse() + refactor.
//  0.1.0  2021-01-03  add Arduino-CI + unit tests
//  0.1.1  2021-04-23  fix for platformIO compatibility

#include "PCF8575.h"


PCF8575::PCF8575(const uint8_t deviceAddress, TwoWire *wire)
{
  _address    = deviceAddress;
  _wire       = wire;
  _dataIn     = 0;
  _dataOut    = 0xFFFF;
  _buttonMask = 0xFFFF;
  _error      = PCF8575_OK;
}

#if defined (ESP8266) || defined(ESP32)
bool PCF8575::begin(uint8_t dataPin, uint8_t clockPin, uint16_t val)
{
  _wire      = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  PCF8575::write16(val);
  return true;
}
#endif


bool PCF8575::begin(uint16_t val)
{
  _wire->begin();
  if (! isConnected()) return false;
  PCF8575::write16(val);
  return true;
}

bool PCF8575::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}

uint16_t PCF8575::read16()
{
  if (_wire->requestFrom(_address, (uint8_t)2) != 2)
  {
    _error = PCF8575_I2C_ERROR;
    return _dataIn; // last value
  }
  _dataIn = _wire->read();            // low 8 bits
  _dataIn |= (_wire->read() << 8);    // high 8 bits
  return _dataIn;
}

void PCF8575::write16(const uint16_t value)
{
  _dataOut = value;
  _wire->beginTransmission(_address);
  _wire->write(_dataOut & 0xFF);      // low 8 bits
  _wire->write(_dataOut >> 8);        // high 8 bits
  _error = _wire->endTransmission();
}

uint8_t PCF8575::read(const uint8_t pin)
{
  if (pin > 15)
  {
    _error = PCF8575_PIN_ERROR;
    return 0;
  }
  PCF8575::read16();
  return (_dataIn & (1 << pin)) > 0;
}

void PCF8575::write(const uint8_t pin, const uint8_t value)
{
  if (pin > 15)
  {
    _error = PCF8575_PIN_ERROR;
    return;
  }
  if (value == LOW)
  {
    _dataOut &= ~(1 << pin);
  }
  else
  {
    _dataOut |= (1 << pin);
  }
  write16(_dataOut);
}

void PCF8575::toggle(const uint8_t pin)
{
  if (pin > 15)
  {
    _error = PCF8575_PIN_ERROR;
    return;
  }
  toggleMask(1 << pin);
}

void PCF8575::toggleMask(const uint16_t mask)
{
  _dataOut ^= mask;
  PCF8575::write16(_dataOut);
}

void PCF8575::shiftRight(const uint8_t n)
{
  if ((n == 0) || (_dataOut == 0)) return;
  if (n > 15)         _dataOut = 0;    // shift 8++ clears all, valid...
  if (_dataOut != 0) _dataOut >>= n;   // only shift if there are bits set
  PCF8575::write16(_dataOut);
}

void PCF8575::shiftLeft(const uint8_t n)
{
  if ((n == 0) || (_dataOut == 0)) return;
  if (n > 15)        _dataOut = 0;    // shift 8++ clears all, valid...
  if (_dataOut != 0) _dataOut <<= n;  // only shift if there are bits set
  PCF8575::write16(_dataOut);
}

int PCF8575::lastError()
{
  int e = _error;
  _error = PCF8575_OK;  // reset error after read, is this wise?
  return e;
}

void PCF8575::rotateRight(const uint8_t n)
{
  uint8_t r = n & 15;
  if (r == 0) return;
  _dataOut = (_dataOut >> r) | (_dataOut << (15 - r));
  PCF8575::write16(_dataOut);
}

void PCF8575::rotateLeft(const uint8_t n)
{
  rotateRight(16 - (n & 15));
}

void PCF8575::reverse()   // quite fast
{                                                     //     1 char === 1 bit
  uint16_t x = _dataOut;                              // x = 0123456789ABCDEF 
  x = (((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1));    // x = 1032547698BADCFE
  x = (((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2));    // x = 32107654BA98FEDC
  x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));    // x = 76543210FEDCBA98
  x = (x >> 8) | ( x << 8);                           // x = FEDCBA9876543210
  PCF8575::write16(x);
}

//added 0.1.07/08 Septillion
uint16_t PCF8575::readButton16(const uint16_t mask)
{
  uint16_t temp = _dataOut;
  PCF8575::write16(mask | _dataOut);  // read only selected lines
  PCF8575::read16();
  PCF8575::write16(temp);             // restore
  return _dataIn;
}

//added 0.1.07 Septillion
uint8_t PCF8575::readButton(const uint8_t pin)
{
  if (pin > 15)
  {
    _error = PCF8575_PIN_ERROR;
    return 0;
  }
  uint16_t temp = _dataOut;
  PCF8575::write(pin, HIGH);
  uint8_t rtn = PCF8575::read(pin);
  PCF8575::write16(temp);
  return rtn;
}

// -- END OF FILE --
