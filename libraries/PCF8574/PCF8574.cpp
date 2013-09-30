//
//    FILE: PCF8574.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 02-febr-2013
// VERSION: 0.1.02
// PURPOSE: I2C PCF8574 library for Arduino
//     URL: 
//
// HISTORY:
// 0.1.02 replaced ints with uint8_t to reduce footprint;
//        added default value for shiftLeft() and shiftRight()
//        renamed status() to lastError();
// 0.1.01 added value(); returns last read 8 bit value (cached); 
//        value() does not always reflect the latest state of the pins!
// 0.1.00 initial version
// 

#include "PCF8574.h"

#include <Wire.h>

PCF8574::PCF8574(int address) 
{
  _address = address;
  Wire.begin();
}

uint8_t PCF8574::read8()
{
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 1);
#if (ARDUINO <  100)
   _data = Wire.receive();
#else
   _data = Wire.read();
#endif
  _error = Wire.endTransmission();
  return _data;
}

uint8_t PCF8574::value()
{
  return _data;
}

void PCF8574::write8(uint8_t value)
{
  Wire.beginTransmission(_address);
  _data = value;
  Wire.write(_data);
  _error = Wire.endTransmission();
}

uint8_t PCF8574::read(uint8_t pin)
{
  PCF8574::read8();
  return (_data & (1<<pin)) > 0;
}

void PCF8574::write(uint8_t pin, uint8_t value)
{
  PCF8574::read8();
  if (value == LOW) 
  {
    _data &= ~(1<<pin);
  }
  else 
  {
    _data |= (1<<pin);
  }
  PCF8574::write8(_data); 
}

void PCF8574::toggle(uint8_t pin)
{
  PCF8574::read8();
  _data ^=  (1 << pin);
  PCF8574::write8(_data); 
}

void PCF8574::shiftRight(uint8_t n)
{
  if (n == 0 || n > 7 ) return;
  PCF8574::read8();
  _data >>= n;
  PCF8574::write8(_data); 
}

void PCF8574::shiftLeft(uint8_t n)
{
  if (n == 0 || n > 7) return;
  PCF8574::read8();
  _data <<= n;
  PCF8574::write8(_data); 
}

int PCF8574::lastError()
{
  int e = _error;
  _error = 0;
  return e;
}
//
// END OF FILE
//