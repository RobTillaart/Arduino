//
//    FILE: AS7331.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-08-28
// VERSION: 0.3.0
// PURPOSE: Arduino library for AS7331 UV sensor
//     URL: https://github.com/RobTillaart/AS7331


#include "AS7331.h"


//  REGISTERS CONFIGURATION MODE
const uint8_t AS7331_REG_OSR    = 0x00;
const uint8_t AS7331_REG_AGEN   = 0x02;
const uint8_t AS7331_REG_CREG1  = 0x06;
const uint8_t AS7331_REG_CREG2  = 0x07;
const uint8_t AS7331_REG_CREG3  = 0x08;
const uint8_t AS7331_REG_BREAK  = 0x09;
const uint8_t AS7331_REG_EDGES  = 0x0A;
const uint8_t AS7331_REG_OPTREG = 0x0B;


//  REGISTERS MEASUREMENT MODE
const uint8_t AS7331_REG_STATUS   = 0x00;
const uint8_t AS7331_REG_TEMP     = 0x01;
const uint8_t AS7331_REG_MRES1    = 0x02;
const uint8_t AS7331_REG_MRES2    = 0x03;
const uint8_t AS7331_REG_MRES3    = 0x04;
const uint8_t AS7331_REG_OUTCONVL = 0x05;
const uint8_t AS7331_REG_OUTCONVH = 0x06;


AS7331::AS7331(uint8_t address, TwoWire *wire)
{
  _address  = address;
  _wire     = wire;
  //  default values at startup
  _error    = AS7331_OK;
  _mode     = AS7331_MODE_MANUAL;
  _gain     = AS7331_GAIN_16x;
  _convTime = AS7331_CONV_064;
}

bool AS7331::begin()
{
  //  reset variables
  _error = AS7331_OK;
  if (! isConnected())
  {
    return false;
  }
  softwareReset();
  powerUp();
  setConfigurationMode();
  setMode(AS7331_MODE_MANUAL);
  setGain(AS7331_GAIN_16x);
  setConversionTime(AS7331_CONV_064);
  return true;
}

bool AS7331::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t AS7331::getAddress()
{
  return _address;
}

void AS7331::softwareReset()
{
  _writeRegister8(AS7331_REG_OSR, 0x0A);
  delay(2);
  //  reset internals to defaults
  _error    = AS7331_OK;
  _mode     = AS7331_MODE_MANUAL;
  _gain     = AS7331_GAIN_16x;
  _convTime = AS7331_CONV_064;
  _adjustGainTimeFactor();
}


/////////////////////////////////////////////
//
//  MODE
//
bool AS7331::setMode(uint8_t mode)
{
  if (mode > 3) return false;
  _mode = mode;
  uint8_t value = _readRegister8(AS7331_REG_CREG3);
  value &= 0x3F;
  value |= (_mode << 6);
  _writeRegister8(AS7331_REG_CREG3, value);
  return true;
}

uint8_t AS7331::getMode()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG3);
  _mode = value >> 6;
  return _mode;
}


/////////////////////////////////////////////
//
//  STAND BY
//
void AS7331::setStandByOn()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG3);
  value &= ~0x10;
  _writeRegister8(AS7331_REG_CREG3, value);
}

void AS7331::setStandByOff()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG3);
  value |= 0x10;
  _writeRegister8(AS7331_REG_CREG3, value);
}

uint8_t AS7331::getStandByMode()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG3);
  return (value & 0x10) > 0;
}


/////////////////////////////////////////////
//
//  GAIN
//
bool AS7331::setGain(uint8_t gain)
{
  if (gain > 11) return false;
  _gain = gain;
  _adjustGainTimeFactor();
  //  write gain and conversion time to register
  uint8_t value = (_gain << 4) | _convTime;
  _writeRegister8(AS7331_REG_CREG1, value);
  return true;
}

uint8_t AS7331::getGain()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG1);
  _gain = (value >> 4) & 0x0F;
  return _gain;
}

bool AS7331::setConversionTime(uint8_t convTime)
{
  if (convTime > 15) return false;
  _convTime = convTime;
  //  handle _convTime == 15 pragmatically for now
  if (_convTime == 15) _convTime = 0;

  _adjustGainTimeFactor();
  //  write gain and conversion time to register
  uint8_t value = (_gain << 4) | _convTime;
  _writeRegister8(AS7331_REG_CREG1, value);
  return true;
}

uint8_t AS7331::getConversionTime()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG1);
  _convTime = value & 0x0F;
  return _convTime;
}


/////////////////////////////////////////////
//
//  DEVICE-ID
//
uint8_t AS7331::getDeviceID()
{
  uint8_t value = _readRegister8(AS7331_REG_AGEN);
  return value;
}


/////////////////////////////////////////////
//
//  REGISTER 0x00 OSR  (8.2.1)
//
void AS7331::stopMeasurement()
{
  uint8_t value = _readRegister8(AS7331_REG_OSR);
  value &= ~0x80;
  _writeRegister8(AS7331_REG_OSR, value);
}

void AS7331::startMeasurement()
{
  // uint8_t value = _readRegister8(AS7331_REG_OSR);
  // value |= 0x80;
  //  Force 0x83 -> might change in future
  _writeRegister8(AS7331_REG_OSR, 0x83);
}

void AS7331::powerDown()
{
  uint8_t value = _readRegister8(AS7331_REG_OSR);
  value |= 0x40;
  _writeRegister8(AS7331_REG_OSR, value);
}

void AS7331::powerUp()
{
  uint8_t value = _readRegister8(AS7331_REG_OSR);
  value &= ~0x40;
  _writeRegister8(AS7331_REG_OSR, value);
}

void AS7331::setConfigurationMode()
{
  uint8_t value = _readRegister8(AS7331_REG_OSR);
  value &= ~0x07;
  value |=  0x02;
  _writeRegister8(AS7331_REG_OSR, value);
}

void AS7331::setMeasurementMode()
{
  uint8_t value = _readRegister8(AS7331_REG_OSR);
  value &= ~0x07;
  value |=  0x03;
  _writeRegister8(AS7331_REG_OSR, value);
}


/////////////////////////////////////////////
//
//  READY PIN
//
void AS7331::setRDYOpenDrain()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG3);
  value &= ~0x04;
  _writeRegister8(AS7331_REG_CREG3, value);
}

void AS7331::setRDYPushPull()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG3);
  value |= 0x04;
  _writeRegister8(AS7331_REG_CREG3, value);
}


/////////////////////////////////////////////
//
//  CLOCK FREQUENCY
//
//  Figure 33 Page 39
//
bool AS7331::setClockFrequency(uint8_t CCLK)
{
  if (CCLK > 0x03) return false;
  uint8_t value = _readRegister8(AS7331_REG_CREG3);
  value &= ~0x03;
  value |= CCLK;
  _writeRegister8(AS7331_REG_CREG3, value);
  return true;
}

uint8_t AS7331::getClockFrequency()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG3);
  value &= 0x03;
  return value;
}


/////////////////////////////////////////////
//
//  STATUS
//
uint8_t AS7331::readOSR()
{
  uint8_t value = _readRegister8(AS7331_REG_OSR);
  return value;
}

uint16_t AS7331::readStatus()
{
  //  LOW byte  == OSR (page 59)
  //  HIGH byte == status
  uint16_t value = _readRegister16(AS7331_REG_STATUS);
  return value;
}

bool AS7331::conversionReady()
{
  uint16_t value = _readRegister16(AS7331_REG_STATUS);
  if (_error != 0) return false;
  return (value & 0x0800) > 0;
}


/////////////////////////////////////////////
//
//  READ - datasheet chapter 7
//
//  Math 7.4
//
float AS7331::getUVA_uW()
{
  //  Page 32
  //  note: in table LSB_UVA = 1000/1024 * FSR_UVA, sort of.
  //  might be to convert to 'per second'?
  //  FSR = Full Scale Range
  //  LSB = Least Significant Bit = value per bit
  //  const float FSR_UVA = 348160.0f;  //  figure 27, 28
  const float LSB_UVA = 340000.0f;
  uint16_t raw = _readRegister16(AS7331_REG_MRES1);
  float microWatt = raw * LSB_UVA * _GainTimeFactor;
  return microWatt;
}

float AS7331::getUVB_uW()
{
  //  const float FSR_UVB = 387072.0f;  //  figure 29, 30
  const float LSB_UVB = 378000.0f;
  uint16_t raw = _readRegister16(AS7331_REG_MRES2);
  float microWatt = raw * LSB_UVB * _GainTimeFactor;
  return microWatt;
}

float AS7331::getUVC_uW()
{
  //  const float FSR_UVC = 169984.0f;  //  figure 31, 32
  const float LSB_UVC = 166000.0f;
  uint16_t raw = _readRegister16(AS7331_REG_MRES3);
  float microWatt = raw * LSB_UVC * _GainTimeFactor;
  return microWatt;
}

float AS7331::getCelsius()
{
  //  datasheet 7.7
  //  validity / resolution depends on timing and gain.
  uint16_t raw = _readRegister16(AS7331_REG_TEMP);
  float Celsius = (raw * 0.05) - 66.9;
  return Celsius;
}


///////////////////////////////////////////////////
//
//  BREAKTIME
//
void AS7331::setBreakTime(uint8_t breakTime)
{
  _writeRegister8(AS7331_REG_BREAK, breakTime);
}

uint8_t AS7331::getBreakTime()
{
  return _readRegister8(AS7331_REG_BREAK);
}


///////////////////////////////////////////////////
//
//  EDGES - synd
//
void AS7331::setEdges(uint8_t edges)
{
  _writeRegister8(AS7331_REG_EDGES, edges);
}

uint8_t AS7331::getEdges()
{
  return _readRegister8(AS7331_REG_EDGES);
}


/////////////////////////////////////////////
//
//  DEBUG
//
int AS7331::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}



///////////////////////////////////////////////////
//
//  FUTURE - CREG2
//

void AS7331::enableTemperature()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG2);
  value |= 0x40;
  _writeRegister8(AS7331_REG_CREG2, value);
}

void AS7331::disableTemperature()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG2);
  value &= ~0x40;
  _writeRegister8(AS7331_REG_CREG2, value);
}

bool AS7331::isEnabledTemperature()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG2);
  return (value & 0x40) > 0;
}


void AS7331::enableDivider()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG2);
  value |= 0x08;
  _writeRegister8(AS7331_REG_CREG2, value);
}

void AS7331::disableDivider()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG2);
  value &= ~0x08;
  _writeRegister8(AS7331_REG_CREG2, value);
}

bool AS7331::isEnabledDivider()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG2);
  return (value & 0x08) > 0;
}


bool AS7331::setDivider(uint8_t div)
{
  if (div > 7) return false;
  uint8_t value = _readRegister8(AS7331_REG_CREG2);
  value &= ~0x07;
  value |= div;
  _writeRegister8(AS7331_REG_CREG2, value);
  return true;
}

uint8_t AS7331::getDivider()
{
  uint8_t value = _readRegister8(AS7331_REG_CREG2);
  return (value & 0x07);
}


///////////////////////////////////////////////////
//
//  OPTIONS, REGISTER 0x0B OPTREG
//
void AS7331::setInitIdx()
{
  _writeRegister8(AS7331_REG_OPTREG, 0x01);
}

void AS7331::clrInitIdx()
{
  _writeRegister8(AS7331_REG_OPTREG, 0x00);
}


///////////////////////////////////////////////////
//
//  OUTCONV, REGISTER 0x05 OUTCONV_L, 0x06 OUTCONV_H
//
uint32_t AS7331::getOUTCONV()
{
  uint32_t value = _readRegister16(AS7331_REG_OUTCONVH);
  value <<= 16;
  value |= _readRegister16(AS7331_REG_OUTCONVL);
  return value;
}



///////////////////////////////////////////////////
//
//  PRIVATE
//
void AS7331::_adjustGainTimeFactor()
{
  _GainTimeFactor = pow(0.5, (11 - _gain) + _convTime);
  //  opt: _GainTimeFactor = pow(0.5, (11 - _gain)) * pow(0.5, _convTime);
  //  ref: _GainTimeFactor = 1.0 / pow(2, (11 - _gain)) * 1.0 / pow(2, _convTime);
}

int AS7331::_writeRegister8(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return _error;
}

uint8_t AS7331::_readRegister8(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission(false);
  if (_error != 0)
  {
    return 0xFF;
  }
  if (_wire->requestFrom((uint8_t)_address, (uint8_t)1) != 1)
  {
    _error = AS7331_REQUEST_ERROR;
    return 0xFF;
  }
  uint8_t value = _wire->read();
  return value;
}

uint16_t AS7331::_readRegister16(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission(false);
  if (_error != 0)
  {
    return 0;
  }
  if (_wire->requestFrom((uint8_t)_address, (uint8_t)2) != 2)
  {
    _error = AS7331_REQUEST_ERROR;
    return 0;
  }
  uint16_t value = _wire->read();  //  LOW BYTE first
  value |= (_wire->read() << 8);   //  HIGH BYTE
  return value;
}


//  -- END OF FILE --

