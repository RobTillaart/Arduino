//
//    FILE: rotaryDecoder8.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
//    DATE: 2025-01-06
// PURPOSE: Arduino library for a PCF8575 based rotary decoder
//     URL: https://github.com/RobTillaart/rotaryDecoder8


#include "rotaryDecoder8.h"


/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
//
rotaryDecoder8::rotaryDecoder8(const int8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


bool rotaryDecoder8::begin(uint8_t deviceCount)
{
  _deviceCount = deviceCount;
  if (_deviceCount > ROTDEC_MAX_COUNT) _deviceCount = ROTDEC_MAX_COUNT;

  if (! isConnected()) return false;
  return true;
}


bool rotaryDecoder8::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t rotaryDecoder8::getRECount()
{
  return _deviceCount;
}


void rotaryDecoder8::reset()
{
  for (int i = 0; i < ROTDEC_MAX_COUNT; i++)
  {
    _encoder[i] = 0;
  }
  //  update last positions.
  _lastValue = readInitialState();
}


bool rotaryDecoder8::reset(uint8_t re)
{
  if (re >= ROTDEC_MAX_COUNT) return false;
  _encoder[re] = 0;
  //  update last positions.
  _lastValue = readInitialState();
  return true;
}


uint16_t rotaryDecoder8::readInitialState()
{
  uint16_t value = read16();
  _lastValue = value;
  for (uint8_t i = 0; i < _deviceCount; i++)
  {
    _lastPos[i] = value & 0x03;
    value >>= 2;
  }
  return _lastValue;
}


bool rotaryDecoder8::checkChange()
{
  uint16_t value = read16();
  return (_lastValue != value);
}


bool rotaryDecoder8::update()
{
  uint16_t value = read16();
  if (_lastValue == value)
  {
    return false;
  }

  _lastValue = value;
  for (uint8_t i = 0; i < _deviceCount; i++, value >>= 2)
  {
    uint8_t currentPos = (value & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentPos;
    switch (change)
    {
      case 0b0001:  //  fall through
      case 0b0111:
      case 0b1110:
      case 0b1000:
        _encoder[i]++;
        break;
      //  case 0b0011:
      //  case 0b0110:
      //  case 0b1001:
      //  case 0b1100:
      //    _encoder[i] += ?;  //  +2 or -2 undecidable
      //    break;
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


bool rotaryDecoder8::updateSingle()
{
  uint16_t value = read16();
  if (_lastValue == value)
  {
    return false;
  }

  _lastValue = value;
  for (uint8_t i = 0; i < _deviceCount; i++, value >>= 2)
  {
    uint8_t currentPos = (value & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentPos;
    switch (change)
    {
      case 0b0001:  //  fall through
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


int32_t rotaryDecoder8::getValue(uint8_t re)
{
  if (re >= ROTDEC_MAX_COUNT) return 0;
  return _encoder[re];
}


bool rotaryDecoder8::setValue(uint8_t re, int32_t value)
{
  if (re >= ROTDEC_MAX_COUNT) return false;
  _encoder[re] = value;
  return true;
}


/////////////////////////////////////////////////////
//
//  CLICKS API 0.1.4 #7
//
int32_t rotaryDecoder8::getClicks(uint8_t re)
{
  if (re >= ROTDEC_MAX_COUNT) return 0;
  //  test if 1?
  return _encoder[re] / _stepsPerClick[re];
}

bool rotaryDecoder8::setClicks(uint8_t re, int32_t clicks)
{
  return setValue(re, clicks * _stepsPerClick[re]);
}

//  configure per channel.
bool rotaryDecoder8::setStepsPerClick(uint8_t re, uint8_t spc)
{
  if (re >= ROTDEC_MAX_COUNT) return false;
  if (spc == 0) return false;
  _stepsPerClick[re] = spc;
  return true;
}

uint8_t rotaryDecoder8::getStepsPerClick(uint8_t re)
{
  if (re >= ROTDEC_MAX_COUNT) return 0;
  return _stepsPerClick[re];
}


/////////////////////////////////////////////////////
//
//  READ - WRITE interface
//
uint8_t rotaryDecoder8::read1(uint8_t pin)
{
  uint16_t mask = 1 << pin;
  uint16_t tmp = read16();
  return (tmp & mask) > 0 ? HIGH : LOW;
}


bool rotaryDecoder8::write1(uint8_t pin, uint8_t value)
{
  uint16_t mask = 1 << pin;
  uint16_t tmp = read16();
  if (value == LOW) tmp &= ~mask;
  else tmp |= mask;
  return write16(tmp);
}


uint16_t rotaryDecoder8::read16()
{
  _wire->requestFrom(_address, (uint8_t)2);
  uint16_t a = _wire->read();  //  LSB
  uint16_t b = _wire->read();  //  MSB
  return (b << 8) + a;
}


bool rotaryDecoder8::write16(uint16_t bitMask)
{
  _wire->beginTransmission(_address);
  _wire->write(bitMask & 0xFF);  //  LSB
  _wire->write(bitMask >> 8);    //  MSB
  return (_wire->endTransmission() == 0);
}


/////////////////////////////////////////////////////
//
//  DEBUG
//
uint8_t rotaryDecoder8::getLastPosition(uint8_t re)
{
  if (re >= ROTDEC_MAX_COUNT) return 0;
  return _lastPos[re];
}


/////////////////////////////////////////////////////
//
//  PROTECTED
//



//  -- END OF FILE --

