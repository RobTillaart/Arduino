//
//    FILE: TLC5947.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-06-17
// PURPOSE: Arduino library for the TLC5947 24 channel PWM device
//     URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"


TLC5947::TLC5947(uint8_t clock, uint8_t data, uint8_t latch, uint8_t blank)
{
  _clock  = clock;
  _data   = data;
  _latch  = latch;
  _blank  = blank;
  _buffer = (uint16_t *) calloc(24, 2);
}


TLC5947::~TLC5947()
{
  if(_buffer) free(_buffer);
}


void TLC5947::setPWM(uint8_t channel, uint16_t PWM)
{
  _buffer[channel] = PWM > 4095 ? 4095 : PWM;
}


bool TLC5947::begin()
{
  pinMode(_clock, OUTPUT);
  pinMode(_data,  OUTPUT);
  pinMode(_latch, OUTPUT);
  pinMode(_blank, OUTPUT);
  digitalWrite(_clock, LOW);
  digitalWrite(_data, LOW);
  digitalWrite(_latch, LOW);
  digitalWrite(_blank, HIGH);  //  enable PWM mode
  return true;
}


uint16_t TLC5947::getPWM(uint8_t channel)
{
  if (channel >= 24) return 0xFFFF;
  return _buffer[channel] & 0x0FFF;
}


void TLC5947::setAll(uint16_t PWM)
{
  uint16_t pwm = PWM > 4095 ? 4095 : PWM;
  for (int chan = 0; chan < 24; chan++)
  {
    _buffer[chan] = pwm;
  }
  write();
}


void TLC5947::write()
{
  //  also write when blank == LOW 
  //       to "preload the registers"
  //  local vars to maximize speed.
  uint8_t _clk = _clock;
  uint8_t _dat = _data;

  for (int chan = 23; chan >= 0; chan--)
  {
    for (int mask = 0x1000;  mask; mask >>= 1)
    {
      digitalWrite(_clk, LOW);
      digitalWrite(_dat, _buffer[chan] & mask ? HIGH : LOW); 
      digitalWrite(_clk, HIGH);
    }
  }
  digitalWrite(_clk, LOW);
  //  enable
  digitalWrite(_latch, HIGH);
  digitalWrite(_latch, LOW);
}

void TLC5947::enable()
{
  digitalWrite(_blank, HIGH);
}


void TLC5947::disable()
{
  digitalWrite(_blank, LOW);
}


//  -- END OF FILE --

