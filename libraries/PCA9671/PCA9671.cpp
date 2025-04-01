//
//    FILE: PCA9671.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-03-16
// VERSION: 0.1.2
// PURPOSE: Arduino library for the PCA9671 and PCA9673, I2C 16-bit I/O expander.
//     URL: https://github.com/RobTillaart/PCA9671


#include "PCA9671.h"


PCA9671::PCA9671(const uint8_t deviceAddress, TwoWire *wire)
{
  _address    = deviceAddress;
  _wire       = wire;
  _dataIn     = 0;
  _dataOut    = 0xFFFF;
  _buttonMask = 0xFFFF;
  _error      = PCA9671_OK;
}


bool PCA9671::begin(uint16_t value)
{
  if (! isConnected()) return false;
  PCA9671::write16(value);
  return true;
}


bool PCA9671::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


bool PCA9671::setAddress(const uint8_t deviceAddress)
{
  //  no address testing due to very wide range.
  _address = deviceAddress;
  return isConnected();
}


uint8_t PCA9671::getAddress()
{
  return _address;
}


uint16_t PCA9671::read16()
{
  if (_wire->requestFrom(_address, (uint8_t)2) != 2)
  {
    _error = PCA9671_I2C_ERROR;
    return _dataIn;                   //  last value
  }
  _dataIn = _wire->read();            //  low 8 bits
  _dataIn |= (_wire->read() << 8);    //  high 8 bits
  return _dataIn;
}


uint8_t PCA9671::read(const uint8_t pin)
{
  if (pin > 15)
  {
    _error = PCA9671_PIN_ERROR;
    return 0;
  }
  PCA9671::read16();
  return (_dataIn & (1 << pin)) > 0;
}


uint16_t PCA9671::value()
{
  return _dataIn;
}


void PCA9671::write16(const uint16_t value)
{
  _dataOut = value;
  _wire->beginTransmission(_address);
  _wire->write(_dataOut & 0xFF);      //  low 8 bits
  _wire->write(_dataOut >> 8);        //  high 8 bits
  _error = _wire->endTransmission();
}


void PCA9671::write(const uint8_t pin, const uint8_t value)
{
  if (pin > 15)
  {
    _error = PCA9671_PIN_ERROR;
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
  PCA9671::write16(_dataOut);
}


uint16_t PCA9671::valueOut()
{
  return _dataOut;
}


void PCA9671::toggle(const uint8_t pin)
{
  if (pin > 15)
  {
    _error = PCA9671_PIN_ERROR;
    return;
  }
  toggleMask(1 << pin);
}


void PCA9671::toggleMask(const uint16_t mask)
{
  _dataOut ^= mask;
  PCA9671::write16(_dataOut);
}


void PCA9671::shiftRight(const uint8_t n)
{
  if ((n == 0) || (_dataOut == 0)) return;
  if (n > 15)        _dataOut = 0;     //  shift 15++ clears all, valid...
  if (_dataOut != 0) _dataOut >>= n;   //  only shift if there are bits set
  PCA9671::write16(_dataOut);
}


void PCA9671::shiftLeft(const uint8_t n)
{
  if ((n == 0) || (_dataOut == 0)) return;
  if (n > 15)        _dataOut = 0;    //  shift 15++ clears all, valid...
  if (_dataOut != 0) _dataOut <<= n;  //  only shift if there are bits set
  PCA9671::write16(_dataOut);
}


void PCA9671::rotateRight(const uint8_t n)
{
  uint8_t r = n & 15;
  if (r == 0) return;
  _dataOut = (_dataOut >> r) | (_dataOut << (15 - r));
  PCA9671::write16(_dataOut);
}


void PCA9671::rotateLeft(const uint8_t n)
{
  rotateRight(16 - (n & 15));
}


void PCA9671::reverse()   //  quite fast
{                                                     //      1 char === 1 bit
  uint16_t x = _dataOut;                              //  x = 0123456789ABCDEF
  x = (((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1));    //  x = 1032547698BADCFE
  x = (((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2));    //  x = 32107654BA98FEDC
  x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));    //  x = 76543210FEDCBA98
  x = (x >> 8) | ( x << 8);                           //  x = FEDCBA9876543210
  PCA9671::write16(x);
}


//////////////////////////////////////////////////
//
//  READBUTTON
//
uint16_t PCA9671::readButton16(const uint16_t mask)
{
  uint16_t temp = _dataOut;
  PCA9671::write16(mask | _dataOut);  //  read only selected lines
  PCA9671::read16();
  PCA9671::write16(temp);             //  restore
  return _dataIn;
}


uint16_t PCA9671::readButton16()
{
  return readButton16(_buttonMask);
}


uint8_t PCA9671::readButton(const uint8_t pin)
{
  if (pin > 15)
  {
    _error = PCA9671_PIN_ERROR;
    return 0;
  }
  uint16_t temp = _dataOut;
  PCA9671::write(pin, HIGH);
  uint8_t rtn = PCA9671::read(pin);
  PCA9671::write16(temp);
  return rtn;
}


void PCA9671::setButtonMask(uint16_t mask)
{
  _buttonMask = mask;
}


uint16_t PCA9671::getButtonMask()
{
  return _buttonMask;
}


//////////////////////////////////////////////////
//
//  SELECT
//
void PCA9671::select(const uint8_t pin)
{
  uint16_t n = 0x0000;
  if (pin < 16) n = 1L << pin;
  PCA9671::write16(n);
}


void PCA9671::selectN(const uint8_t pin)
{
  uint16_t n = 0xFFFF;
  if (pin < 16) n = (2L << pin) - 1;
  PCA9671::write16(n);
}


void PCA9671::selectNone()
{
  PCA9671::write16(0x0000);
}


void PCA9671::selectAll()
{
  PCA9671::write16(0xFFFF);
}


//////////////////////////////////////////////////
//
//  MISCELLANEOUS
//
int PCA9671::lastError()
{
  int e = _error;
  _error = PCA9671_OK;  //  reset error after read, is this wise?
  return e;
}


//  TODO get this working
uint32_t PCA9671::deviceID()
{
  uint8_t DEVICEID_ADDRESS = 0x7C;
  _wire->beginTransmission(DEVICEID_ADDRESS);
  _wire->write(_address << 1);             //  address of the PCA9671, shifted one bit
  _error = _wire->endTransmission(false);  //  explicit send a restart.
  if (_error != 0)
  {
    _error = PCA9671_I2C_ERROR;
    return 0xFFFFFFFF;
  }
  if (_wire->requestFrom(DEVICEID_ADDRESS, (uint8_t)3) != 3)
  {
    _error = PCA9671_I2C_ERROR;
    return 0xFFFFFFFF;
  }
  _error = PCA9671_OK;
  uint32_t deviceId = _wire->read();
  deviceId <<= 8;
  deviceId |= _wire->read();
  deviceId <<= 8;
  deviceId |= _wire->read();
  return deviceId;
}



////////////////////////////////////////////////////////
//
//  DERIVED PCA9673
//
PCA9673::PCA9673(uint8_t address, TwoWire *wire)
        :PCA9671(address, wire)
{
  //  identical for now
  //  PCA9673 has interrupt pin.
}



//  -- END OF FILE --

