//
//    FILE: ADG2188.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-28
// VERSION: 0.2.0
// PURPOSE: Arduino library for ADG2188 8x8 (cross-point) matrix switch with I2C.
//     URL: https://github.com/RobTillaart/ADG2188



#include "ADG2188.h"

#define ADG2188_LATCHED_MODE        0x00
#define ADG2188_DIRECT_MODE         0x01


ADG2188::ADG2188(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _error = ADG2188_OK;
  _mode  = ADG2188_DIRECT_MODE;
  _reset = 255;
}

bool ADG2188::begin()
{
  //  reset variables
  _error = ADG2188_OK;

  if ((_address < 0x70) || (_address > 0x77))
  {
    _error = ADG2188_ADDRESS_ERROR;
    return false;
  }
  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool ADG2188::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t ADG2188::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  SWITCHES
//
bool ADG2188::on(uint8_t row, uint8_t column)
{
  if ((row > 7 ) || (column > 7)) return false;
  //  Table 7 datasheet
  uint8_t mask = 0x80;  //  0x80 == ON
  if (row < 6) mask |= (row << 3) + column;
  else mask |= ((row + 2) << 3) + column;
  _send(mask, _mode);
  return true;
}

bool ADG2188::off(uint8_t row, uint8_t column)
{
  if ((row > 7 ) || (column > 7)) return false;
  //  Table 7 datasheet
  uint8_t mask = 0x00;  //  0x80 == OFF
  if (row < 6) mask |= (row << 3) + column;
  else mask |= ((row + 2) << 3) + column;
  _send(mask, _mode);
  return true;
}

bool ADG2188::isOn(uint8_t row, uint8_t column)
{
  if ((row > 7 ) || (column > 7)) return false;
  uint8_t value = isOnRow(row);
  return (value & (1 << column)) > 0;
}

uint8_t ADG2188::isOnRow(uint8_t row)
{
  if (row > 7) return false;
  //  Table 8 datasheet
  //  0x34 == 0b00110100 - These bits are always set.
  uint8_t mask = 0x34;
  if (row & 0x04) mask |= 0x01;
  if (row & 0x02) mask |= 0x40;
  if (row & 0x01) mask |= 0x08;

  return _readback(mask);
}


//  need some thoughts
// bool ADG2128::Latch()
// {
//   //  send last data with one time overrule DIRECT flag
//   _send(_pins, ADG2128_DIRECT_MODE);
// }


/////////////////////////////////////////////
//
//  MODE
//
//  default direct (transparent) mode
void ADG2188::setDirectMode()
{
  _mode = ADG2188_DIRECT_MODE;
}

void ADG2188::setLatchMode()
{
  _mode = ADG2188_LATCHED_MODE;
}

bool ADG2188::isLatchedMode()
{
  return _mode == ADG2188_LATCHED_MODE;
}

bool ADG2188::isDirectMode()
{
  return _mode == ADG2188_DIRECT_MODE;
}


/////////////////////////////////////////////
//
//  RESET
//
void ADG2188::setResetPin(uint8_t resetPin)
{
  _reset = resetPin;
  pinMode(_reset, OUTPUT);
  digitalWrite(_reset, HIGH);
}


void ADG2188::pulseResetPin()
{
  digitalWrite(_reset, LOW);
  //  need delay(1);
  digitalWrite(_reset, HIGH);
}


/////////////////////////////////////////////
//
//  DEBUG
//
int ADG2188::getLastError()
{
  int e = _error;
  _error = ADG2188_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//

int ADG2188::_send(uint8_t mask, uint8_t latchFlag)
{
  //  _latchMask = mask;  //  remember last mask for latch().
  _wire->beginTransmission(_address);
  _wire->write(mask);
  _wire->write(latchFlag);
  _error = _wire->endTransmission();
  return _error;
}


int ADG2188::_readback(uint8_t row)
{
  _wire->beginTransmission(_address);
  _wire->write(row);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = ADG2188_REQUEST_ERROR;
    return 0;
  }
  uint8_t bytes = _wire->requestFrom(_address, (uint8_t)2);
  if (bytes != 2)
  {
    _error = ADG2188_REQUEST_ERROR;
    return 0;
  }
  _wire->read();  //  skip dummy data
  return _wire->read();
}


//  -- END OF FILE --

