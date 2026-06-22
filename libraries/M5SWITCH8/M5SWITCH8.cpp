//
//    FILE: M5SWITCH8.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2026-06-16
// PURPOSE: Arduino library for M5STACK SWITCH8 and BUTTON8 devices.
//     URL: https://github.com/RobTillaart/M5SWITCH8


#include "M5SWITCH8.h"


//  REGISTERS
constexpr uint8_t M5SWITCH8_REG_READALL      = 0x00;
constexpr uint8_t M5SWITCH8_REG_BRIGHTNESS   = 0x10;
constexpr uint8_t M5SWITCH8_REG_MODE         = 0x19;
constexpr uint8_t M5SWITCH8_REG_COLOR        = 0x20;
constexpr uint8_t M5SWITCH8_REG_COLOR233     = 0x50;
constexpr uint8_t M5SWITCH8_REG_READSWITCH   = 0x60;
constexpr uint8_t M5SWITCH8_REG_AUTOCOLOROFF = 0x70;
constexpr uint8_t M5SWITCH8_REG_AUTOCOLORON  = 0x90;
constexpr uint8_t M5SWITCH8_REG_WRITETOFLASH = 0xF0;
constexpr uint8_t M5SWITCH8_REG_INTERRUPTS   = 0xF1;
constexpr uint8_t M5SWITCH8_REG_FIRMWARE     = 0xFE;
constexpr uint8_t M5SWITCH8_REG_ADDRESS      = 0xFF;


M5SWITCH8::M5SWITCH8(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _error = M5SWITCH8_OK;
}

bool M5SWITCH8::begin()
{
  //  reset variables
  _error = M5SWITCH8_OK;

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
  _request(M5SWITCH8_REG_READALL, &value, 1);
  return value;
}

uint8_t M5SWITCH8::readSwitch(uint8_t sw)
{
  if (sw > 7) return 255;
  uint8_t value = 0;
  _request(M5SWITCH8_REG_READSWITCH + sw, &value, 1);
  return value;
}


/////////////////////////////////////////////
//
//  LED
//
void M5SWITCH8::setBrightnessAll(uint8_t B)
{
  uint8_t bright[9] = {B,B,B, B,B,B, B,B,B};
  _command(M5SWITCH8_REG_BRIGHTNESS, bright, 9);
}

void M5SWITCH8::setBrightness(uint8_t led, uint8_t value)
{
  if (led > 8) return;
  _command(M5SWITCH8_REG_BRIGHTNESS + led, value);
}

uint8_t M5SWITCH8::getBrightness(uint8_t led)
{
  if (led > 8) return 0;
  uint8_t value = 0;
  _request(M5SWITCH8_REG_BRIGHTNESS + led, &value, 1);
  return value;
}

void M5SWITCH8::setMode(uint8_t mode)
{
  _command(M5SWITCH8_REG_MODE, mode == 0 ? 0 : 1);
}

uint8_t M5SWITCH8::getMode()
{
  uint8_t value = 0;
  _request(M5SWITCH8_REG_MODE, &value, 1);
  return value;
}

//
//  MANUAL MODE
//
void M5SWITCH8::setColor(uint8_t led, uint32_t bgr)
{
  if (led > 8) return;
  uint8_t reg = M5SWITCH8_REG_COLOR + 4 * led;
  _command(reg, (uint8_t *) &bgr, 3);
}

void M5SWITCH8::setColorRGB(uint8_t led, uint8_t R, uint8_t G, uint8_t B)
{
  if (led > 8) return;
  uint8_t colors[3] = {R, G, B};
  uint8_t reg = M5SWITCH8_REG_COLOR + 4 * led;
  _command(reg, colors, 3);
}

uint32_t M5SWITCH8::getColor(uint8_t led)
{
  if (led > 8) return 0;
  uint32_t bgr = 0;
  uint8_t reg = M5SWITCH8_REG_COLOR + 4 * led;
  _request(reg, (uint8_t *) &bgr, 3);
  return bgr;
}

void M5SWITCH8::setColor233(uint8_t led, uint8_t value)
{
  if (led > 8) return;
  uint8_t reg = M5SWITCH8_REG_COLOR233 + led;
  _command(reg, value);
}

uint8_t M5SWITCH8::getColor233(uint8_t led)
{
  if (led > 8) return 0;
  uint8_t value = 0;
  uint8_t reg = M5SWITCH8_REG_COLOR233 + led;
  _request(reg, (uint8_t *) &value, 1);
  return value;
}

//
//  SYSTEM MODE
//
void M5SWITCH8::setOffColor(uint8_t led, uint32_t bgr)
{
  if (led > 7) return;
  uint8_t reg = M5SWITCH8_REG_AUTOCOLOROFF + 4 * led;
  _command(reg, (uint8_t *) &bgr, 3);
}

uint32_t M5SWITCH8::getOffColor(uint8_t led)
{
  if (led > 7) return 0;
  uint32_t bgr = 0;
  uint8_t reg = M5SWITCH8_REG_AUTOCOLOROFF + 4 * led;
  _request(reg, (uint8_t *) &bgr, 3);
  return bgr;
}

void M5SWITCH8::setOnColor(uint8_t led, uint32_t bgr)
{
  if (led > 7) return;
  uint8_t reg = M5SWITCH8_REG_AUTOCOLORON + 4 * led;
  _command(reg, (uint8_t *) &bgr, 3);
}

uint32_t M5SWITCH8::getOnColor(uint8_t led)
{
  if (led > 7) return 0;
  uint32_t bgr = 0;
  uint8_t reg = M5SWITCH8_REG_AUTOCOLORON + 4 * led;
  _request(reg, (uint8_t *) &bgr, 3);
  return bgr;
}


/////////////////////////////////////////////
//
//  MISCELLANEOUS
//
void M5SWITCH8::writeToFlash()
{
  _command(M5SWITCH8_REG_WRITETOFLASH, 1);
}

void M5SWITCH8::enableInterrupts()
{
  _command(M5SWITCH8_REG_INTERRUPTS, 1);
}

void M5SWITCH8::disableInterrupts()
{
  _command(M5SWITCH8_REG_INTERRUPTS, 0);
}

uint8_t M5SWITCH8::isEnabled()
{
  uint8_t value = 0;
  _request(M5SWITCH8_REG_INTERRUPTS, &value, 1);
  return value;
}

uint8_t M5SWITCH8::getFirmwareVersion()
{
  uint8_t value = 0;
  _request(M5SWITCH8_REG_FIRMWARE, &value, 1);
  return value;
}

void M5SWITCH8::setAddress(uint8_t addr)
{
  _command(M5SWITCH8_REG_ADDRESS, addr);
}


/////////////////////////////////////////////
//
//  DEBUG
//
int M5SWITCH8::getLastError()
{
  int e = _error;
  _error = M5SWITCH8_OK;
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
  _error = M5SWITCH8_OK;
  return _error;
}


//  -- END OF FILE --

