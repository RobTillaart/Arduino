//
//    FILE: BH1750FVI.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: library for BH1750FVI lux sensor Arduino
//     URL: https://github.com/RobTillaart/BH1750FVI_RT


#include "BH1750FVI.h"


// COMMANDS P5
#define BH1750FVI_POWER_ON                    0x00
#define BH1750FVI_POWER_OFF                   0x01
#define BH1750FVI_RESET                       0x07
#define BH1750FVI_CONT_HIGH                   0x10
#define BH1750FVI_CONT_HIGH2                  0x11
#define BH1750FVI_CONT_LOW                    0x13
#define BH1750FVI_ONCE_HIGH                   0x20
#define BH1750FVI_ONCE_HIGH2                  0x21
#define BH1750FVI_ONCE_LOW                    0x23


BH1750FVI::BH1750FVI(const uint8_t address, TwoWire *wire)
{
  _address            = address;
  _wire               = wire;
  _data               = 0;
  _error              = BH1750FVI_OK;
  _sensitivityFactor  = BH1750FVI_REFERENCE_TIME;
  _mode               = BH1750FVI_MODE_HIGH;
}


bool BH1750FVI::begin()
{
  _data               = 0;
  _error              = BH1750FVI_OK;
  _sensitivityFactor  = BH1750FVI_REFERENCE_TIME;
  _mode               = BH1750FVI_MODE_HIGH;
  return isConnected();
}


bool BH1750FVI::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


bool BH1750FVI::isReady()
{
  //  max times from datasheet P2 + P11;
  uint8_t timeout[3] = { 16, 120, 120 };
  if (_mode < 3)
  {
    float f = timeout[_mode] * _sensitivityFactor / BH1750FVI_REFERENCE_TIME;
    return (millis() - _requestTime) > f;
  }
  return false;
}


float BH1750FVI::getRaw(void)
{
  return readData() * 0.833333333333f;    //  == 1 / 1.2;
}


float BH1750FVI::getLux(void)
{
  //  lux without mode correction
  float lux = getRaw();

  //  sensitivity factor
  if (_sensitivityFactor != BH1750FVI_REFERENCE_TIME)
  {
    lux *= (1.0 * BH1750FVI_REFERENCE_TIME) / _sensitivityFactor;
  }
  //  angle compensation
  if (_angle != 0)
  {
    lux *= _angleFactor;
  }
  //  temperature compensation. 20 C is default.
  if (_temperature != 20)
  {
    lux *= _tempFactor;
  }
  //  wavelength compensation.
  if (_waveLength != 580)
  {
    lux *= _waveLengthFactor;
  }
  if (_mode == BH1750FVI_MODE_HIGH2)
  {
    lux *= 0.5f;  //  P11
  }
  return lux;
}


int BH1750FVI::getError()
{
  int e = _error;
  _error = BH1750FVI_OK;
  return e;
}


void BH1750FVI::powerOn()
{
  command(BH1750FVI_POWER_ON);
}


void BH1750FVI::powerOff()
{
  command(BH1750FVI_POWER_OFF);
}


void BH1750FVI::reset()
{
  command(BH1750FVI_RESET);
}


////////////////////////////////////////////
//
//  operational mode
//
void BH1750FVI::setContHighRes()
{
  _mode = BH1750FVI_MODE_HIGH;
  command(BH1750FVI_CONT_HIGH);
  _requestTime = millis();
};


void BH1750FVI::setContHigh2Res()
{
  _mode = BH1750FVI_MODE_HIGH2;
  command(BH1750FVI_CONT_HIGH2);
  _requestTime = millis();
};


void BH1750FVI::setContLowRes()
{
  _mode = BH1750FVI_MODE_LOW;
  command(BH1750FVI_CONT_LOW);
  _requestTime = millis();
};


void BH1750FVI::setOnceHighRes()
{
  _mode = BH1750FVI_MODE_HIGH;
  command(BH1750FVI_ONCE_HIGH);
  _requestTime = millis();
};


void BH1750FVI::setOnceHigh2Res()
{
  _mode = BH1750FVI_MODE_HIGH2;
  command(BH1750FVI_ONCE_HIGH2);
  _requestTime = millis();
};


void BH1750FVI::setOnceLowRes()
{
  _mode = BH1750FVI_MODE_LOW;
  command(BH1750FVI_ONCE_LOW);
  _requestTime = millis();
};


////////////////////////////////////////////
//
//  measurement timing
//
//  P11 datasheet
void BH1750FVI::changeTiming(uint8_t time)
{
  time = constrain(time, 31, 254);
  _sensitivityFactor = time;
  //  P5 instruction set table
  uint8_t Hbits = 0x40 | (time >> 5);
  uint8_t Lbits = 0x60 | (time & 0x1F);
  command(Hbits);
  command(Lbits);
}


uint8_t BH1750FVI::setCorrectionFactor(float factor)
{
  //  31 .. 254 are range P11 - constrained in changeTIming call
  uint8_t timingValue = round(BH1750FVI_REFERENCE_TIME * factor);
  changeTiming(timingValue);
  return _sensitivityFactor;
}


float BH1750FVI::getCorrectionFactor()
{
  float f = 1.0f / BH1750FVI_REFERENCE_TIME;
  return _sensitivityFactor * f;
}


float BH1750FVI::setTemperature(int temp)
{
  _temperature = temp;
  //  _tempFactor = 1.0f - (_temperature - 20.0f) / 2000.0f;
  _tempFactor = 1.0f - (_temperature - 20.0f) * 0.0005f;
  return _tempFactor;
}


float BH1750FVI::setAngle(float degrees)
{
  _angle = constrain(degrees, -89.9, 89.9);
  //  Lambert's Law.
  _angleFactor = 1.0f / cos(_angle * (PI / 180.0f));
  return _angleFactor;
}


//  interpolation tables uses more RAM (versus PROGMEM)
float BH1750FVI::setWaveLength(int waveLength)
{
  _waveLength = constrain(waveLength, 400, 715);
  float tmp = 1.0f;
  if      (_waveLength < 400)  tmp = 0.01f;
  else if (_waveLength < 440)  tmp = 0.01f + (_waveLength - 400) * 0.09f / 40.0f;
  else if (_waveLength < 510)  tmp = 0.10f + (_waveLength - 440) * 0.80f / 70.0f;
  else if (_waveLength < 545)  tmp = 0.90f - (_waveLength - 510) * 0.10f / 35.0f;
  else if (_waveLength < 580)  tmp = 0.80f + (_waveLength - 545) * 0.20f / 35.0f;
  else if (_waveLength < 700)  tmp = 1.00f - (_waveLength - 580) * 0.93f / 120.0f;
  else if (_waveLength < 715)  tmp = 0.07f - (_waveLength - 700) * 0.07f / 15.0f;
  else if (_waveLength >= 715) tmp = 0.01f;
  _waveLengthFactor = 1.0f / tmp;
  return _waveLengthFactor;
}


///////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint16_t BH1750FVI::readData()
{
  if (_wire->requestFrom(_address, (uint8_t) 2) != 2)
  {
    _error = BH1750FVI_ERROR_WIRE_REQUEST;
    return _data;  //  last value
  }
  _data = _wire->read();
  _data <<= 8;
  _data += _wire->read();
  return _data;
}


void BH1750FVI::command(uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(value);
  _error = _wire->endTransmission();
}


//  --- END OF FILE ---

