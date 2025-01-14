//
//    FILE: rotaryDecoderSwitch5.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-01-13
// PURPOSE: Arduino library for a PCF8575 based rotary decoder (with switch)
//     URL: https://github.com/RobTillaart/rotaryDecoderSwitch5


#include "rotaryDecoderSwitch5.h"


/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
//
rotaryDecoderSwitch5::rotaryDecoderSwitch5(const int8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


bool rotaryDecoderSwitch5::begin(uint8_t count)
{
  _count = count;
  if (_count > ROTDEC_MAX_COUNT) _count = ROTDEC_MAX_COUNT;

  if (! isConnected()) return false;
  return true;
}


bool rotaryDecoderSwitch5::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t rotaryDecoderSwitch5::getRECount()
{
  return _count;
}


void rotaryDecoderSwitch5::reset()
{
  for (int i = 0 ; i < ROTDEC_MAX_COUNT; i++)
  {
    _lastPos[i] = 0;
    _encoder[i] = 0;
  }
  _lastValue = 0;
}


uint16_t rotaryDecoderSwitch5::readInitialState()
{
  uint16_t value = read16();
  _lastValue = value;
  for (uint8_t i = 0; i < _count; i++)
  {
    _lastPos[i] = value & 0x03;
    value >>= 3;
  }
  return _lastValue;
}


bool rotaryDecoderSwitch5::checkChange()
{
  uint16_t value = read16();
  return (_lastValue != value);
}


bool rotaryDecoderSwitch5::update()
{
  uint16_t value = read16();
  if (_lastValue == value)
  {
    return false;
  }

 _lastValue = value;
  for (uint8_t i = 0; i < _count; i++, value >>= 3)
  {
    uint8_t currentPos = (value & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentPos;
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
    _lastPos[i] = currentPos;
  }
  return true;
}


bool rotaryDecoderSwitch5::updateSingle()
{
  uint16_t value = read16();
  if (_lastValue == value)
  {
    return false;
  }

 _lastValue = value;
  for (uint8_t i = 0; i < _count; i++, value >>= 3)
  {
    uint8_t currentPos = (value & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentPos;
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
    _lastPos[i] = currentPos;
  }
  return true;
}


int32_t rotaryDecoderSwitch5::getValue(uint8_t re)
{
  if (re >= ROTDEC_MAX_COUNT) return 0;
  return _encoder[re];
}


bool rotaryDecoderSwitch5::setValue(uint8_t re, int32_t value)
{
  if (re >= ROTDEC_MAX_COUNT) return false;
  _encoder[re] = value;
  return true;
}


bool rotaryDecoderSwitch5::isKeyPressed(uint8_t re)
{
  if (re >= ROTDEC_MAX_COUNT) return false;
  uint16_t mask = 0x04 << (re * 3);
  return (_lastValue & mask) == 0;
}


/////////////////////////////////////////////////////
//
//  READ - WRITE interface
//
uint8_t rotaryDecoderSwitch5::read1(uint8_t pin)
{
  uint16_t mask = 1 << pin;
  uint16_t tmp = read16();
  return (tmp & mask) > 0 ? HIGH : LOW;
}


bool rotaryDecoderSwitch5::write1(uint8_t pin, uint8_t value)
{
  uint16_t mask = 1 << pin;
  uint16_t tmp = read16();
  if (value == LOW) tmp &= ~mask;
  else tmp |= mask;
  return write16(tmp);
}


uint16_t rotaryDecoderSwitch5::read16()
{
  _wire->requestFrom(_address, (uint8_t)1);
  uint16_t a = _wire->read();  //  LSB
  uint16_t b = _wire->read();  //  MSB
  return (b << 8) + a;
}


bool rotaryDecoderSwitch5::write16(uint16_t bitmask)
{
  _wire->beginTransmission(_address);
  _wire->write(bitmask & 0xFF);  //  LSB
  _wire->write(bitmask >> 8);    //  MSB
  return (_wire->endTransmission() == 0);
}


/////////////////////////////////////////////////////
//
//  DEBUG
//
uint8_t rotaryDecoderSwitch5::getLastPosition(uint8_t re)
{
  if (re >= ROTDEC_MAX_COUNT) return 0;
  return _lastPos[re];
}


/////////////////////////////////////////////////////
//
//  PROTECTED
//



//  -- END OF FILE --

