//
//    FILE: AS56000.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for AS5600 magnetic rotation meter
//    DATE: 2022-05-28
//     URL: https://github.com/RobTillaart/AS5600

//  0.1.0   2022-05-28  initial version
//  0.1.1   2022-05-31  Add readReg2() to speed up reading 2 byte values.
//                      Fix clock wise and counter clock wise
//                      Fix shift-direction @ getZPosition, getMPosition, 
//                          getMaxAngle and getConfigure 
//  0.1.2   2022-06-02  Add getAngularSpeed()
//


// TODO
//  Power-up time  1 minute
//  check  Timing Characteristics



#include "AS5600.h"


//  CONFIGURATION REGISTERS
#define AS5600_ZMCO                     0x00
#define AS5600_ZPOS                     0x01  // + 0x02
#define AS5600_MPOS                     0x03  // + 0x04
#define AS5600_MANG                     0x05  // + 0x06
#define AS5600_CONF                     0x07  // + 0x08

//  CONFIGURATION BIT MASKS - byte level
#define AS5600_CONF_POWER_MODE          0x03
#define AS5600_CONF_HYSTERESIS          0x0C
#define AS5600_CONF_OUTPUT_MODE         0x30
#define AS5600_CONF_PWM_FREQUENCY       0xC0
#define AS5600_CONF_SLOW_FILTER         0x03
#define AS5600_CONF_FAST_FILTER         0x1C
#define AS5600_CONF_WATCH_DOG           0x20


//  UNKNOWN REGISTERS 0x09-0x0A

//  OUTPUT REGISTERS
#define AS5600_RAW_ANGLE                0x0C  // + 0x0D
#define AS5600_ANGLE                    0x0E  // + 0x0F

//  STATUS REGISTERS
#define AS5600_STATUS                   0x0B
#define AS5600_AGC                      0x1A
#define AS5600_MAGNITUDE                0x1B  // + 0x1C
#define AS5600_BURN                     0xFF

//  STATUS BITS
#define AS5600_MAGNET_HIGH              0x08
#define AS5600_MAGNET_LOW               0x10
#define AS5600_MAGNET_DETECT            0x20


AS5600::AS5600(TwoWire *wire)
{
  _wire = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool AS5600::begin(int dataPin, int clockPin, int directionPin)
{
  _directionPin = directionPin;
  pinMode(_directionPin, OUTPUT);
  setDirection(AS5600_CLOCK_WISE);

  _wire = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  return true;
}
#endif


bool AS5600::begin(int directionPin)
{
  _directionPin = directionPin;
  pinMode(_directionPin, OUTPUT);
  setDirection(AS5600_CLOCK_WISE);

  _wire->begin();
  if (! isConnected()) return false;
  return true;
}


bool AS5600::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


/////////////////////////////////////////////////////////
//
//  CONFIGURATION REGISTERS + direction pin
//
void AS5600::setDirection(uint8_t direction)
{
  digitalWrite(_directionPin, direction);
}


uint8_t AS5600::getDirection()
{
  return digitalRead(_directionPin);
}


uint8_t AS5600::getZMCO()
{
  uint8_t value = readReg(AS5600_ZMCO);
  return value;
}


void AS5600::setZPosition(uint16_t value)
{
  writeReg(AS5600_ZPOS, (value >> 8) & 0x0F);
  writeReg(AS5600_ZPOS + 1, value & 0xFF);
}


uint16_t AS5600::getZPosition()
{
  uint16_t value = (readReg(AS5600_ZPOS) & 0x0F) << 8;
  value += readReg(AS5600_ZPOS + 1);
  return value;
}


void AS5600::setMPosition(uint16_t value)
{
  writeReg(AS5600_MPOS, (value >> 8) & 0x0F);
  writeReg(AS5600_MPOS + 1, value & 0xFF);
}


uint16_t AS5600::getMPosition()
{
  uint16_t value = (readReg(AS5600_MPOS) & 0x0F) << 8;
  value += readReg(AS5600_MPOS + 1);
  return value;
}


void AS5600::setMaxAngle(uint16_t value)
{
  writeReg(AS5600_MANG, (value >> 8) & 0x0F);
  writeReg(AS5600_MANG + 1, value & 0xFF);
}


uint16_t AS5600::getMaxAngle()
{
  uint16_t value = (readReg(AS5600_MANG) & 0x0F) << 8;
  value += readReg(AS5600_MANG + 1);
  return value;
}


void AS5600::setConfigure(uint16_t value)
{
  writeReg(AS5600_CONF, (value >> 8) & 0x0F);
  writeReg(AS5600_CONF + 1, value & 0xFF);
}


uint16_t AS5600::getConfigure()
{
  uint16_t value = (readReg(AS5600_CONF) & 0x2F) << 8;
  value += readReg(AS5600_CONF + 1);
  return value;
}


//  details configure
void AS5600::setPowerMode(uint8_t powerMode)
{
  if (powerMode > 3) return;
  uint8_t value = readReg(AS5600_CONF + 1);
  value &= ~AS5600_CONF_POWER_MODE;
  value |= powerMode;
  writeReg(AS5600_CONF + 1, value);
}

uint8_t AS5600::getPowerMode()
{
  return readReg(AS5600_CONF + 1) & 0x03;
}

void AS5600::setHysteresis(uint8_t hysteresis)
{
  if (hysteresis > 3) return;
  uint8_t value = readReg(AS5600_CONF + 1);
  value &= ~AS5600_CONF_HYSTERESIS;
  value |= (hysteresis << 2);
  writeReg(AS5600_CONF + 1, value);
}

uint8_t AS5600::getHysteresis()
{
  return (readReg(AS5600_CONF + 1) >> 2) & 0x03;
}

void AS5600::setOutputMode(uint8_t outputMode)
{
  if (outputMode > 2) return;
  uint8_t value = readReg(AS5600_CONF + 1);
  value &= ~AS5600_CONF_OUTPUT_MODE;
  value |= (outputMode << 4);
  writeReg(AS5600_CONF + 1, value);
}

uint8_t AS5600::getOutputMode()
{
  return (readReg(AS5600_CONF + 1) >> 4) & 0x03;
}

void AS5600::setPWMFrequency(uint8_t pwmFreq)
{
  if (pwmFreq > 3) return;
  uint8_t value = readReg(AS5600_CONF + 1);
  value &= ~AS5600_CONF_PWM_FREQUENCY;
  value |= (pwmFreq << 6);
  writeReg(AS5600_CONF + 1, value);
}

uint8_t AS5600::getPWMFrequency()
{
  return (readReg(AS5600_CONF + 1) >> 6) & 0x03;
}

void AS5600::setSlowFilter(uint8_t mask)
{
  if (mask > 3) return;
  uint8_t value = readReg(AS5600_CONF);
  value &= ~AS5600_CONF_SLOW_FILTER;
  value |= mask;
  writeReg(AS5600_CONF, value);
}

uint8_t AS5600::getSlowFilter()
{
  return readReg(AS5600_CONF) & 0x03;
}

void AS5600::setFastFilter(uint8_t mask)
{
  if (mask > 7) return;
  uint8_t value = readReg(AS5600_CONF);
  value &= ~AS5600_CONF_FAST_FILTER;
  value |= (mask << 2);
  writeReg(AS5600_CONF, value);
}

uint8_t AS5600::getFastFilter()
{
  return (readReg(AS5600_CONF) >> 2) & 0x07;
}

void AS5600::setWatchDog(uint8_t mask)
{
  if (mask > 1) return;
  uint8_t value = readReg(AS5600_CONF);
  value &= ~AS5600_CONF_WATCH_DOG;
  value |= (mask << 5);
  writeReg(AS5600_CONF, value);
}

uint8_t AS5600::getWatchDog()
{
  return (readReg(AS5600_CONF) >> 5) & 0x01;
}


/////////////////////////////////////////////////////////
//
//  OUTPUT REGISTERS
//
uint16_t AS5600::rawAngle()
{
  uint16_t value = readReg2(AS5600_RAW_ANGLE) & 0x0FFF;
  return value;
}


uint16_t AS5600::readAngle()
{
  uint16_t value = readReg2(AS5600_ANGLE) & 0x0FFF;
  return value;
}


/////////////////////////////////////////////////////////
//
//  STATUS REGISTERS
//
uint8_t AS5600::readStatus()
{
  uint8_t value = readReg(AS5600_STATUS);
  return value;
}


uint8_t AS5600::readAGC()
{
  uint8_t value = readReg(AS5600_AGC);
  return value;
}


uint16_t AS5600::readMagnitude()
{
  uint16_t value = readReg2(AS5600_MAGNITUDE) & 0x0FFF;
  return value;
}


bool AS5600::detectMagnet()
{
  return (readStatus() & AS5600_MAGNET_DETECT) > 1;
}


/////////////////////////////////////////////////////////
//
//  BURN COMMANDS
//
//  DO NOT UNCOMMENT - USE AT OWN RISK - READ DATASHEET
//
//  void AS5600::burnAngle()
//  {
//    writeReg(AS5600_BURN, x0x80);
//  }
//
//
//  void AS5600::burnSetting()
//  {
//    writeReg(AS5600_BURN, x0x40);
//  }


float AS5600::getAngularSpeed()
{
  uint32_t now     = micros();
  int      angle   = readAngle();
  uint32_t deltaT  = now - _lastMeasurement;
  int      deltaA  = angle - _lastAngle;
  _lastMeasurement = now;
  _lastAngle       = angle;
  return (deltaA * 1e6 * AS5600_RAW_TO_DEGREES) / deltaT;
}


/////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t AS5600::readReg(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();

  _wire->requestFrom(_address, (uint8_t)1);
  uint8_t _data = _wire->read();
  return _data;
}


uint16_t AS5600::readReg2(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();

  _wire->requestFrom(_address, (uint8_t)2);
  uint16_t _data = _wire->read();
  _data <<= 8;
  _data += _wire->read();
  return _data;
}


uint8_t AS5600::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return _error;
}


//  -- END OF FILE --


