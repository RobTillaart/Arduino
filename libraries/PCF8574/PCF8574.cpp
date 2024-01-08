//
//    FILE: PCF8574.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 02-febr-2013
// VERSION: 0.4.1
// PURPOSE: Arduino library for PCF8574 - 8 channel I2C IO expander
//     URL: https://github.com/RobTillaart/PCF8574
//          http://forum.arduino.cc/index.php?topic=184800


#include "PCF8574.h"


PCF8574::PCF8574(const uint8_t deviceAddress, TwoWire *wire)
{
  _address    = deviceAddress;
  _wire       = wire;
  _dataIn     = 0;
  _dataOut    = 0xFF;
  _buttonMask = 0xFF;
  _error      = PCF8574_OK;
}


bool PCF8574::begin(uint8_t value)
{
  if (! isConnected()) return false;
  PCF8574::write8(value);
  return true;
}


bool PCF8574::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


bool PCF8574::setAddress(const uint8_t deviceAddress)
{
  _address = deviceAddress;
  return isConnected();
}


uint8_t PCF8574::getAddress()
{
  return _address;
}


//  removed _wire->beginTransmission(_address);
//  with    @100 KHz -> 265 micros()
//  without @100 KHz -> 132 micros()
//  without @400 KHz -> 52 micros()
//  TODO    @800 KHz -> ??
uint8_t PCF8574::read8()
{
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCF8574_I2C_ERROR;
    return _dataIn;  //  last value
  }
  _dataIn = _wire->read();
  return _dataIn;
}


void PCF8574::write8(const uint8_t value)
{
  _dataOut = value;
  _wire->beginTransmission(_address);
  _wire->write(_dataOut);
  _error = _wire->endTransmission();
}


uint8_t PCF8574::read(const uint8_t pin)
{
  if (pin > 7)
  {
    _error = PCF8574_PIN_ERROR;
    return 0;
  }
  PCF8574::read8();
  return (_dataIn & (1 << pin)) > 0;
}


void PCF8574::write(const uint8_t pin, const uint8_t value)
{
  if (pin > 7)
  {
    _error = PCF8574_PIN_ERROR;
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
  write8(_dataOut);
}


void PCF8574::toggle(const uint8_t pin)
{
  if (pin > 7)
  {
    _error = PCF8574_PIN_ERROR;
    return;
  }
  toggleMask(1 << pin);
}


void PCF8574::toggleMask(const uint8_t mask)
{
  _dataOut ^= mask;
  PCF8574::write8(_dataOut);
}


void PCF8574::shiftRight(const uint8_t n)
{
  if ((n == 0) || (_dataOut == 0)) return;
  if (n > 7)         _dataOut = 0;     //  shift 8++ clears all, valid...
  if (_dataOut != 0) _dataOut >>= n;   //  only shift if there are bits set
  PCF8574::write8(_dataOut);
}


void PCF8574::shiftLeft(const uint8_t n)
{
  if ((n == 0) || (_dataOut == 0)) return;
  if (n > 7)         _dataOut = 0;    //  shift 8++ clears all, valid...
  if (_dataOut != 0) _dataOut <<= n;  //  only shift if there are bits set
  PCF8574::write8(_dataOut);
}


int PCF8574::lastError()
{
  int e = _error;
  _error = PCF8574_OK;  //  reset error after read, is this wise?
  return e;
}


void PCF8574::rotateRight(const uint8_t n)
{
  uint8_t r = n & 7;
  if (r == 0) return;
  _dataOut = (_dataOut >> r) | (_dataOut << (8 - r));
  PCF8574::write8(_dataOut);
}


void PCF8574::rotateLeft(const uint8_t n)
{
  rotateRight(8 - (n & 7));
}


void PCF8574::reverse()  //  quite fast: 4 and, 14 shifts, 3 or, 3 assignment.
{
  uint8_t x = _dataOut;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x =          ((x >> 4) | (x << 4));
  PCF8574::write8(x);
}


//  added 0.1.07/08 Septillion
uint8_t PCF8574::readButton8(const uint8_t mask)
{
  uint8_t temp = _dataOut;
  PCF8574::write8(mask | _dataOut);  //  read only selected lines
  PCF8574::read8();
  PCF8574::write8(temp);             //  restore
  return _dataIn;
}


//  added 0.1.07 Septillion
uint8_t PCF8574::readButton(const uint8_t pin)
{
  if (pin > 7)
  {
    _error = PCF8574_PIN_ERROR;
    return 0;
  }

  uint8_t temp = _dataOut;
  PCF8574::write(pin, HIGH);
  uint8_t value = PCF8574::read(pin);
  PCF8574::write8(temp);
  return value;
}


void PCF8574::select(const uint8_t pin)
{
  uint8_t n = 0x00;
  if (pin < 8) n = 1 << pin;
  write8(n);
};


void PCF8574::selectN(const uint8_t pin)
{
  uint8_t n = 0xFF;
  if (pin < 8) n = (2 << pin) - 1;
  write8(n);
};


//  -- END OF FILE --

