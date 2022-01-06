//
//    FILE: PCA9685.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 24-apr-2016
// VERSION: 0.3.4
// PURPOSE: Arduino library for I2C PCA9685 16 channel PWM 
//     URL: https://github.com/RobTillaart/PCA9685_RT
//
//  HISTORY:
//  0.1.0  2016-04-24  initial BETA version
//  0.1.1  2019-01-30  testing && fixing
//  0.2.0  2020-05-25  refactor; ESP32 begin(sda,scl)
//  0.2.1  2020-06-19  fix library.json
//  0.2.2  2020-09-21  fix #1 + add getFrequency()
//  0.2.3  2020-11-21  fix digitalWrite (internal version only)
//  0.3.0  2020-11-22  fix setting frequency
//  0.3.1  2021-01-05  Arduino-CI + unit test
//  0.3.2  2021-01-14  WireN support
//  0.3.3  2021-12-23  update library.json, license, readme, minor edits
//  0.3.4  2022-01-03  add channelCount()


#include "PCA9685.h"


// REGISTERS CONFIGURATION - check datasheet for details
#define PCA9685_MODE1       0x00
#define PCA9685_MODE2       0x01

// MODE1 REGISTERS
#define PCA9685_RESTART     0x80
#define PCA9685_EXTCLK      0x40
#define PCA9685_AUTOINCR    0x20
#define PCA9685_SLEEP       0x10
#define PCA9685_SUB1        0x08
#define PCA9685_SUB2        0x04
#define PCA9685_SUB3        0x02
#define PCA9685_ALLCALL     0x01

// MODE2 REGISTERS (see datasheet)
#define PCA9685_INVERT      0x10
#define PCA9685_OCH         0x08
#define PCA9685_OUTDRV      0x04
#define PCA9685_OUTNE       0x03

// REGISTERS - CHANNELS
#define PCA9685_CHANNEL_0   0x06   //  0x06 + 4*channel is base per channel

// REGISTERS - FREQUENCY
#define PCA9685_PRE_SCALER  0xFE

// REGISTERS - Subaddressing I2C - not implemented
#define PCA9685_SUBADR(x)   (0x01+(x))  // x = 1..3
#define PCA9685_ALLCALLADR  0x05

// REGISTERS - ALL_ON ALL_OFF - partly implemented
#define PCA9685_ALL_ON_L    0xFA
#define PCA9685_ALL_ON_H    0xFB
#define PCA9685_ALL_OFF_L   0xFC
#define PCA9685_ALL_OFF_H   0xFD   // used for allOFF()

// NOT IMPLEMENTED YET
#define PCA9685_TESTMODE    0xFF   // do not be use. see datasheet.


//////////////////////////////////////////////////////////////
//
// Constructor
//
PCA9685::PCA9685(const uint8_t deviceAddress, TwoWire *wire)
{
  _address = deviceAddress;
  _wire    = wire;
  _error   = 0;
}


#if defined (ESP8266) || defined(ESP32)
bool PCA9685::begin(uint8_t sda, uint8_t scl)
{
  _wire = &Wire;
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  reset();
  return true;
}
#endif


bool PCA9685::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  reset();
  return true;
}


bool PCA9685::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


void PCA9685::reset()
{
  _error = PCA9685_OK;
  writeMode(PCA9685_MODE1, PCA9685_AUTOINCR | PCA9685_ALLCALL);
  writeMode(PCA9685_MODE2, PCA9685_OUTDRV);
}


void PCA9685::writeMode(uint8_t reg, uint8_t value)
{
  _error = PCA9685_OK;
  if ((reg != PCA9685_MODE1) && (reg != PCA9685_MODE2))
  {
    _error = PCA9685_ERR_MODE;
    return;
  }
  writeReg(reg, value);
}


uint8_t PCA9685::readMode(uint8_t reg)
{
  _error = PCA9685_OK;
  if ((reg != PCA9685_MODE1) && (reg != PCA9685_MODE2))
  {
    _error = PCA9685_ERR_MODE;
    return 0;
  }
  uint8_t value = readReg(reg);
  return value;
}


// write value to single PWM channel
void PCA9685::setPWM(uint8_t channel, uint16_t onTime, uint16_t offTime)
{
  _error = PCA9685_OK;
  if (channel >= _channelCount)
  {
    _error = PCA9685_ERR_CHANNEL;
    return;
  }
  offTime &= 0x0FFFF;   // non-doc feature - to easy set figure 8 P.17
  uint8_t reg = PCA9685_CHANNEL_0 + (channel << 2);
  writeReg2(reg, onTime, offTime);
}


// write value to single PWM channel
void PCA9685::setPWM(uint8_t channel, uint16_t offTime)
{
  setPWM(channel, 0, offTime);
}


// read value from single PWM channel
void PCA9685::getPWM(uint8_t channel, uint16_t* onTime, uint16_t* offTime)
{
  _error = PCA9685_OK;
  if (channel >= _channelCount)
  {
    _error = PCA9685_ERR_CHANNEL;
    return;
  }
  uint8_t reg = PCA9685_CHANNEL_0 + (channel << 2);
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_wire->requestFrom(_address, (uint8_t)4) != 4)
  {
    _error = PCA9685_ERR_I2C;
    return;
  }
  uint16_t _data = _wire->read();
  *onTime = (_wire->read() * 256) + _data;
  _data = _wire->read();
  *offTime = (_wire->read() * 256) + _data;
}


// set update frequency for all channels
void PCA9685::setFrequency(uint16_t freq, int offset)
{
  _error = PCA9685_OK;
  _freq = freq;
  //  limits frequency see page 25 datasheet
  if (_freq < PCA9685_MIN_FREQ) _freq = PCA9685_MIN_FREQ;
  if (_freq > PCA9685_MAX_FREQ) _freq = PCA9685_MAX_FREQ;
  // removed float operation for speed
  // faster but equal accurate
  // uint8_t scaler = round(25e6 / (_freq * 4096)) - 1;
  uint8_t scaler = 48828 / (_freq * 8) - 1;

  uint8_t mode1 = readMode(PCA9685_MODE1);
  writeMode(PCA9685_MODE1, mode1 | PCA9685_SLEEP);
  scaler += offset;
  writeReg(PCA9685_PRE_SCALER, scaler);
  writeMode(PCA9685_MODE1, mode1);
}


int PCA9685::getFrequency(bool cache)
{
  _error = PCA9685_OK;
  if (cache) return _freq;
  uint8_t scaler = readReg(PCA9685_PRE_SCALER);
  scaler++;
  _freq = 48828 / scaler;
  _freq /= 8;
  return _freq;
}


// datasheet P.18 - fig. 9:  
// Note: bit[11-0] ON should NOT equal timer OFF in ON mode
// in OFF mode it doesn't matter.
void PCA9685::digitalWrite(uint8_t channel, uint8_t mode)
{
  _error = PCA9685_OK;
  if (channel >= _channelCount)
  {
    _error = PCA9685_ERR_CHANNEL;
    return;
  }
  uint8_t reg = PCA9685_CHANNEL_0 + (channel << 2);
  if (mode != LOW) writeReg2(reg, 0x1000, 0x0000);
  else writeReg2(reg, 0x0000, 0x0000);
}


void PCA9685::allOFF()
{
  _error = PCA9685_OK;
  writeReg(PCA9685_ALL_OFF_H, 0x10);
}


int PCA9685::lastError()
{
  int e = _error;
  _error = 0;
  return e;
}


//////////////////////////////////////////////////////////////
//
// PRIVATE
//
void PCA9685::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
}


void PCA9685::writeReg2(uint8_t reg, uint16_t a, uint16_t b)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(a & 0xFF);
  _wire->write((a >> 8) & 0x1F);
  _wire->write(b & 0xFF);
  _wire->write((b >> 8) & 0x1F);
  _error = _wire->endTransmission();
}


uint8_t PCA9685::readReg(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9685_ERR_I2C;
    return 0;
  }
  uint8_t _data = _wire->read();
  return _data;
}

// -- END OF FILE --
