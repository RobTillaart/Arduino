//
//    FILE: PCF8574.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 7-febr-2013
//
// PUPROSE:
//

#include "PCF8574.h"

#include <Wire.h>

PCF8574::PCF8574(int address) 
{
  _address = address;
  Wire.begin();
}

int PCF8574::read8()
{
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 1);
#if (ARDUINO <  100)
   _data = Wire.receive();
#else
   _data = Wire.read();
#endif
  _status = Wire.endTransmission();
  return _data;
}

int PCF8574::value()
{
  return _data;
}

void PCF8574::write8(int value)
{
  Wire.beginTransmission(_address);
  _data = value;
  Wire.write(_data);
  _status = Wire.endTransmission();
}

int PCF8574::read(int pin)
{
  PCF8574::read8();
  return (_data & (1<<pin)) == (1<<pin);
}

void PCF8574::write(int pin, int value)
{
  PCF8574::read8();
  if (value == LOW) 
  {
    _data = _data & ~(1<<pin);
  }
  else 
  {
    _data = _data | (1<<pin);
  }
  PCF8574::write8(_data); 
}

void PCF8574::toggle(int pin)
{
  PCF8574::read8();
  _data = _data ^ (1 << pin);
  PCF8574::write8(_data); 
}

void PCF8574::shiftRight()
{
  PCF8574::read8();
  _data = _data >> 1;
  PCF8574::write8(_data); 
}

void PCF8574::shiftLeft()
{
  PCF8574::read8();
  _data = _data << 1;
  PCF8574::write8(_data); 
}

int PCF8574::getStatus()
{
  return _status;
}

