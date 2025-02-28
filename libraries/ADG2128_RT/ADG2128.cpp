//
//    FILE: ADG2128.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-28
// VERSION: 0.1.0
// PURPOSE: Arduino library for ADG2128 8x8 (cross-point) matrix switch with I2C.
//     URL: https://github.com/RobTillaart/ADG2128



#include "ADG2128.h"

#define ADG2128_LATCHED_MODE        0x00
#define ADG2128_DIRECT_MODE         0x01


ADG2128::ADG2128(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _error = 0;
  _mode  = ADG2128_DIRECT_MODE;
  _reset = 255;
}

bool ADG2128::begin()
{
  //  reset variables
  _error = 0;

  if ((_address < 0x70) || (_address > 0x77))
  {
    _error = -1;
    return false;
  }
  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool ADG2128::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t ADG2128::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  SWITCHES
//
void ADG2128::on(uint8_t row, uint8_t col)
{
  if ((row > 7 ) || (col > 11)) return;
  uint8_t pins = 0x80;  //  0x80 == ON
  if (col < 6) pins |= (col << 3) + row;
  else pins |= ((col + 2) << 3) + row;
  _send(pins, _mode);
}

void ADG2128::off(uint8_t row, uint8_t col)
{
  if ((row > 7 ) || (col > 11)) return;
  uint8_t pins = 0x00;  //  0x00 == OFF
  if (col < 6) pins |= (col << 3) + row;
  else pins |= ((col + 2) << 3) + row;

  _send(pins, _mode);
}

bool ADG2128::isOn(uint8_t row, uint8_t col)
{
  if ((row > 7 ) || (col > 11)) return false;
  uint8_t value = isOn(col);
  return (value & (1 << row)) > 0;
}

uint8_t ADG2128::isOnMask(uint8_t col)
{
  if (col > 11) return false;
  //  Table 8 datasheet
  uint8_t mask = 0x34;  //  == 0b00110100;
  if (col & 0x08) mask |= 0x02;
  if (col & 0x04) mask |= 0x01;
  if (col & 0x02) mask |= 0x40;
  if (col & 0x01) mask |= 0x08;

  return _readback(mask);
}


/////////////////////////////////////////////
//
//  MODE
//
//  default direct (transparent) mode
void ADG2128::setMode(bool latched)
{
  _mode = latched ? ADG2128_LATCHED_MODE : ADG2128_DIRECT_MODE;
}

bool ADG2128::isLatchedMode()
{
  return _mode == ADG2128_LATCHED_MODE;
}

bool ADG2128::isDirectMode()
{
  return _mode == ADG2128_DIRECT_MODE;
}


/////////////////////////////////////////////
//
//  RESET
//
void ADG2128::setResetPin(uint8_t resetPin)
{
  _reset = resetPin;
  pinMode(_reset, OUTPUT);
  digitalWrite(_reset, HIGH);
}


void ADG2128::pulseResetPin()
{
  digitalWrite(_reset, LOW);
  //  need delay(1);
  digitalWrite(_reset, HIGH);
}


/////////////////////////////////////////////
//
//  DEBUG
//
int ADG2128::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//

int ADG2128::_send(uint8_t pins, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(pins);
  _wire->write(value);
  _error = _wire->endTransmission();
  return _error;
}


int ADG2128::_readback(uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(value);
  _error = _wire->endTransmission();
  uint8_t bytes = _wire->requestFrom(_address, (uint8_t)2);
  if (bytes != 2)
  {
    _error = -1;
    return 0;
  }
  _wire->read();  //  skip dummy data
  return _wire->read();
}


//  -- END OF FILE --

