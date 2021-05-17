//
//    FILE: rotaryDecoder.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-05-08
// PURPOSE: rotary decoder library for Arduino
//     URL: https://github.com/RobTillaart/rotaryDecoder
//
//  HISTORY:
//  0.1.0   2021-05-08  initial version
//


#include "rotaryDecoder.h"


/////////////////////////////////////////////////////
//
// CONSTRUCTORS
//
rotaryDecoder::rotaryDecoder(const int8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool rotaryDecoder::begin(uint8_t sda, uint8_t scl, uint8_t cnt)
{
  _cnt = cnt;
  _wire = &Wire;
  _wire->begin(sda, scl);
  if (! isConnected()) return false;
  return true;
}
#endif


bool rotaryDecoder::begin(uint8_t cnt)
{
  _cnt = cnt;
  _wire->begin();
  if (! isConnected()) return false;
  return true;
}


bool rotaryDecoder::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


void rotaryDecoder::readInitialState()
{
  uint8_t val = _read8();
  _lastVal = val;
  for (uint8_t i = 0; i < _cnt; i++)
  {
    _lastPos[i] = val & 0x03;
    val >>= 2;
  }
}


bool rotaryDecoder::checkChange()
{
  uint8_t val = _read8();
  return (_lastVal != val);
}


bool rotaryDecoder::update()
{
  uint8_t val = _read8();
  if (_lastVal == val) return false;
 _lastVal = val;
  for (uint8_t i = 0; i < _cnt; i++, val >>= 2)
  {
    uint8_t currentpos = (val & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentpos;
    switch (change)
    {
      case 0b0001:  // fall through..
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
  uint8_t val = _read8();
  if (_lastVal == val) return false;
 _lastVal = val;
 
  for (uint8_t i = 0; i < _cnt; i++, val >>= 2)
  {
    uint8_t currentpos = (val & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentpos;
    switch (change)
    {
      case 0b0001:  // fall through..
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


uint8_t rotaryDecoder::_read8()
{
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


// -- END OF FILE --
