//
//    FILE: rotaryDecoder.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2021-05-08
// PURPOSE: Arduino library for rotary decoder
//     URL: https://github.com/RobTillaart/rotaryDecoder


#include "rotaryDecoder.h"


/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
//
rotaryDecoder::rotaryDecoder(const int8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


bool rotaryDecoder::begin(uint8_t count)
{
  _count = count;
  if (_count > 4) _count = 4;

  if (! isConnected()) return false;
  return true;
}


bool rotaryDecoder::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t rotaryDecoder::readInitialState()
{
  uint8_t value = read8();
  _lastValue = value;
  for (uint8_t i = 0; i < _count; i++)
  {
    _lastPos[i] = value & 0x03;
    value >>= 2;
  }
  return _lastValue;
}


bool rotaryDecoder::checkChange()
{
  uint8_t value = read8();
  return (_lastValue != value);
}


bool rotaryDecoder::update()
{
  uint8_t value = read8();
  if (_lastValue == value)
  {
    return false;
  }

 _lastValue = value;
  for (uint8_t i = 0; i < _count; i++, value >>= 2)
  {
    uint8_t currentpos = (value & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentpos;
    switch (change)
    {
      case 0b0001:  //  fall through..
      case 0b0111:
      case 0b1110:
      case 0b1000:
        _encoder[i]++;
        break;
      case 0b0010:
      case 0b0100:
      case 0b1101:
      case 0b1011:
        _encoder[i]--;
        break;
    }
    _lastPos[i] = currentpos;
  }
  return true;
}


bool rotaryDecoder::updateSingle()
{
  uint8_t value = read8();
  if (_lastValue == value)
  {
    return false;
  }

 _lastValue = value;
  for (uint8_t i = 0; i < _count; i++, value >>= 2)
  {
    uint8_t currentpos = (value & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentpos;
    switch (change)
    {
      case 0b0001:  //  fall through..
      case 0b0111:
      case 0b1110:
      case 0b1000:
        _encoder[i] += 1;
        break;
      case 0b0011:
      case 0b0110:
      case 0b1001:
      case 0b1100:
        _encoder[i] += 2;
        break;
      case 0b0010:
      case 0b0100:
      case 0b1101:
      case 0b1011:
        _encoder[i] += 3;
        break;
    }
    _lastPos[i] = currentpos;
  }
  return true;
}


int32_t rotaryDecoder::getValue(uint8_t re)
{
  if (re > 3) return 0;
  return _encoder[re];
}


bool rotaryDecoder::setValue(uint8_t re, int32_t value)
{
  if (re > 3) return false;
  _encoder[re] = value;
  return true;
}


/////////////////////////////////////////////////////
//
//  READ - WRITE interface
//
uint8_t rotaryDecoder::read1(uint8_t pin)
{
  uint8_t mask = 1 << pin;
  uint8_t tmp = read8();
  return (tmp & mask) > 0 ? HIGH : LOW;
}


bool rotaryDecoder::write1(uint8_t pin, uint8_t value)
{
  uint8_t mask = 1 << pin;
  uint8_t tmp = read8();
  if (value == LOW) tmp &= ~mask;
  else tmp |= mask;
  return write8(tmp);
}


uint8_t rotaryDecoder::read8()
{
  _wire->requestFrom(_address, (uint8_t)1);
  uint8_t x = _wire->read();
  // Serial.println(x, HEX);
  return x;
}


bool rotaryDecoder::write8(uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(value);
  return (_wire->endTransmission() == 0);
}


/////////////////////////////////////////////////////
//
//  DEBUG
//
uint8_t rotaryDecoder::getLastPosition(uint8_t re)
{
  return _lastPos[re];
}


/////////////////////////////////////////////////////
//
//  PROTECTED
//



//  -- END OF FILE --

