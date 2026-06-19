//
//    FILE: M5SWITCH8.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2026-06-16
// PURPOSE: Arduino library for M5STACK SWITCH8 and BUTTON8 devices.
//     URL: https://github.com/RobTillaart/M5SWITCH8


#include "M5SWITCH8.h"


M5SWITCH8::M5SWITCH8(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _error = 0;
}

bool M5SWITCH8::begin()
{
  //  reset variables
  _error = 0;

  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool M5SWITCH8::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t M5SWITCH8::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  READ SWITCH / BUTTON
//
uint8_t M5SWITCH8::readAll()
{
  uint8_t value = 0;
  _request(0x00, &value, 1);
  return value;
}

uint8_t M5SWITCH8::readSwitch(uint8_t sw)
{
  if (sw > 7) return 255;
  uint8_t value = 0;
  _request(0x60 + sw, &value, 1);
  return value;
}


/////////////////////////////////////////////
//
//  LED
//
void M5SWITCH8::setBrightnessAll(uint8_t B)
{
  uint8_t bright[9] = {B,B,B, B,B,B, B,B,B};
  _command(0x10, bright, 9);
}

void M5SWITCH8::setBrightness(uint8_t led, uint8_t value)
{
  if (led > 8) return;
  _command(0x10 + led, value);
}

uint8_t M5SWITCH8::getBrightness(uint8_t led)
{
  if (led > 8) return 0;
  uint8_t value = 0;
  _request(0x10 + led, &value, 1);
  return value;
}

void M5SWITCH8::setMode(uint8_t mode)
{
  _command(0x19, mode == 0 ? 0 : 1);
}

uint8_t M5SWITCH8::getMode()
{
  uint8_t value = 0;
  _request(0x19, &value, 1);
  return value;
}

//
//  MANUAL MODE
//
void M5SWITCH8::setColor(uint8_t led, uint32_t bgr)
{
  if (led > 8) return;
  uint8_t reg = 0x20 + 4 * led;
  _command(reg, (uint8_t *) &bgr, 3);
}

void M5SWITCH8::setColorRGB(uint8_t led, uint8_t R, uint8_t G, uint8_t B)
{
  if (led > 8) return;
  uint8_t colors[3] = {R, G, B};
  uint8_t reg = 0x20 + 4 * led;
  _command(reg, colors, 3);
}

uint32_t M5SWITCH8::getColor(uint8_t led)
{
  if (led > 8) return 0;
  uint32_t bgr = 0;
  uint8_t reg = 0x20 + 4 * led;
  _request(reg, (uint8_t *) &bgr, 3);
  return bgr;
}

void M5SWITCH8::setColor233(uint8_t led, uint8_t value)
{
  if (led > 8) return;
  uint8_t reg = 0x50 + led;
  _command(reg, value);
}

uint8_t M5SWITCH8::getColor233(uint8_t led)
{
  if (led > 8) return 0;
  uint8_t value = 0;
  uint8_t reg = 0x50 + led;
  _request(reg, (uint8_t *) &value, 1);
  return value;
}

//
//  SYSTEM MODE
//
void M5SWITCH8::setOffColor(uint8_t led, uint32_t bgr)
{
  if (led > 7) return;
  uint8_t reg = 0x70 + 4 * led;
  _command(reg, (uint8_t *) &bgr, 3);
}

uint32_t M5SWITCH8::getOffColor(uint8_t led)
{
  if (led > 7) return 0;
  uint32_t bgr = 0;
  uint8_t reg = 0x70 + 4 * led;
  _request(reg, (uint8_t *) &bgr, 3);
  return bgr;
}

void M5SWITCH8::setOnColor(uint8_t led, uint32_t bgr)
{
  if (led > 7) return;
  uint8_t reg = 0x90 + 4 * led;
  _command(reg, (uint8_t *) &bgr, 3);
}

uint32_t M5SWITCH8::getOnColor(uint8_t led)
{
  if (led > 7) return 0;
  uint32_t bgr = 0;
  uint8_t reg = 0x90 + 4 * led;
  _request(reg, (uint8_t *) &bgr, 3);
  return bgr;
}


/////////////////////////////////////////////
//
//  MISCELLANEOUS
//
void M5SWITCH8::writeToFlash()
{
  _command(0xF0, 1);
}

void M5SWITCH8::enableInterrupts()
{
  _command(0xF1, 1);
}

void M5SWITCH8::disableInterrupts()
{
  _command(0xF1, 0);
}

uint8_t M5SWITCH8::isEnabled()
{
  uint8_t value = 0;
  _request(0xF1, &value, 1);
  return value;
}

uint8_t M5SWITCH8::getFirmwareVersion()
{
  uint8_t value = 0;
  _request(0xFE, &value, 1);
  return value;
}

void M5SWITCH8::setAddress(uint8_t addr)
{
  _command(0xFF, addr);
}


/////////////////////////////////////////////
//
//  DEBUG
//
int M5SWITCH8::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////
//
//  PROTECTED
//
int M5SWITCH8::_command(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return _error;
}

int M5SWITCH8::_command(uint8_t reg, uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  for (int i = size - 1; i >= 0; i--)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
  return _error;
}

int M5SWITCH8::_request(uint8_t reg, uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  uint8_t bytes = _wire->requestFrom(_address, size);
  if (bytes == 0)
  {
    _error = M5SWITCH8_NO_DATA;
    return _error;
  }
  if (bytes < size)
  {
    _error = M5SWITCH8_REQUEST_ERROR;
    return _error;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    arr[i] = _wire->read();
  }
  _error = 0;
  return _error;
}


//  -- END OF FILE --

