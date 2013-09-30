//
//    FILE: PCF8574.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 7-febr-2013
//
// PUPROSE:
//

#include <Wire.h>
#include "PCF8574.h"

PCF8574::PCF8574(uint8_t address) 
{
  _address = address;
  Wire.begin();
}

uint8_t PCF8574::read8()
{
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 1);
  _data = Wire.read();
  Wire.endTransmission(); // check error?
  return _data;
}

void PCF8574::write8(uint8_t value)
{
  Wire.beginTransmission(_address);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t PCF8574::read(uint8_t pin)
{
  PCF8574::read8();
  return (_data & (1<<pin)) == (1<<pin)
}

void PCF8574::write(uint8_t pin, uint8_t value)
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

void PCF8574::toggle(uint8_t pin)
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



