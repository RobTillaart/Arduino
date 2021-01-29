//
//    FILE: AD524X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: I2C digital potentiometer AD5241 AD5242
//    DATE: 2013-10-12
//     URL: https://github.com/RobTillaart/AD524X
//

#include "AD524X.h"

#define AS524X_RDAC0    0x00
#define AS524X_RDAC1    0x80
#define AS524X_RESET    0x40
#define AS524X_SHUTDOWN 0x20
#define AS524X_O1_HIGH  0x10
#define AS524X_O2_HIGH  0x08


AD524X::AD524X(const uint8_t address, TwoWire *wire)
{
  // address: 0x01011xx = 0x2C - 0x2F
  _address = address;
  _wire = wire;
  _lastValue[0] = _lastValue[1] = 127; // power on reset => mid position
  _O1 = _O2 = 0;
  _pmCount = 2;
}


#if defined (ESP8266) || defined(ESP32)
bool AD524X::begin(uint8_t dataPin, uint8_t clockPin)
{
  _wire = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  reset();
  return true;
}
#endif


bool AD524X::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  reset();
  return true;
}


bool AD524X::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t AD524X::reset()
{
  write(0, 127, LOW, LOW);
  return write(1, 127);
}


uint8_t AD524X::zeroAll()
{
  write(0, 0, LOW, LOW);
  return write(1, 0);
}

uint8_t AD524X::write(const uint8_t rdac, const uint8_t value)
{
  if (rdac >= _pmCount) return AS524X_ERROR;

  uint8_t cmd = (rdac == 0) ? AS524X_RDAC0 : AS524X_RDAC1;
  // apply the output lines
  cmd = cmd | _O1 | _O2;
  _lastValue[rdac] = value;
  return send(cmd, value);
}

uint8_t AD524X::write(const uint8_t rdac, const uint8_t value, const uint8_t O1, const uint8_t O2)
{
  if (rdac >= _pmCount) return AS524X_ERROR;

  uint8_t cmd = (rdac == 0) ? AS524X_RDAC0 : AS524X_RDAC1;
  _O1 = (O1 == LOW) ? 0 : AS524X_O1_HIGH;
  _O2 = (O2 == LOW) ? 0 : AS524X_O2_HIGH;
  // apply the output lines
  cmd = cmd | _O1 | _O2;
  _lastValue[rdac] = value;
  return send(cmd, value);
}

uint8_t AD524X::setO1(const uint8_t value)
{
  _O1 = (value == LOW) ? 0 : AS524X_O1_HIGH;
  uint8_t cmd = AS524X_RDAC0 | _O1 | _O2;
  return send(cmd, _lastValue[0]);
}

uint8_t AD524X::setO2(const uint8_t value)
{
  _O2 = (value == LOW) ? 0: AS524X_O2_HIGH;
  uint8_t cmd = AS524X_RDAC0 | _O1 | _O2;
  return send(cmd, _lastValue[0]);
}

uint8_t AD524X::getO1()
{
  return (_O1 > 0);
}

uint8_t AD524X::getO2()
{
  return (_O2 > 0);
}

uint8_t AD524X::read(const uint8_t rdac)
{
  return _lastValue[rdac];
}

uint8_t AD524X::readBackRegister()
{
  Wire.beginTransmission(_address);
  Wire.endTransmission();
  Wire.requestFrom(_address, (uint8_t)1);
  return Wire.read();
}

uint8_t AD524X::midScaleReset(const uint8_t rdac)
{
  if (rdac >= _pmCount) return AS524X_ERROR;

  uint8_t cmd = AS524X_RESET;
  if (rdac == 1) cmd |= AS524X_RDAC1;
  cmd = cmd | _O1 | _O2;
  _lastValue[rdac] = 127;
  return send(cmd, _lastValue[rdac]);
}

// read datasheet P.15 
uint8_t AD524X::shutDown()
{
  uint8_t cmd = AS524X_SHUTDOWN;  // TODO TEST & VERIFY
  return send(cmd, 0);
}


//////////////////////////////////////////////////////////
//
// PRIVATE
//
uint8_t AD524X::send(const uint8_t cmd, const uint8_t value)
{
  Wire.beginTransmission(_address);
  Wire.write(cmd);
  Wire.write(value);
  return Wire.endTransmission();
}

/////////////////////////////////////////////////////////////////////////////


AD5241::AD5241(const uint8_t address, TwoWire *wire) : AD524X(address, wire)
{
  _pmCount = 1;
};

AD5242::AD5242(const uint8_t address, TwoWire *wire) : AD524X(address, wire)
{
  _pmCount = 2;
};

// -- END OF FILE --
