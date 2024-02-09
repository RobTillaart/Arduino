//
//    FILE: TLC5947.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
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



//////////////////////////////////////////////////
//
//  PWM
//
int TLC5947::setPWM(uint8_t channel, uint16_t PWM)
{
  if (channel >= 24) return TLC5947_CHANNEL_ERROR;
  _buffer[channel] = PWM > 4095 ? 4095 : PWM;
  return TLC5947_OK;
}


uint16_t TLC5947::getPWM(uint8_t channel)
{
  if (channel >= 24) return TLC5947_CHANNEL_ERROR;
  return _buffer[channel] & 0x0FFF;
}


void TLC5947::setAll(uint16_t PWM)
{
  uint16_t pwm = PWM > 4095 ? 4095 : PWM;
  for (int channel = 0; channel < 24; channel++)
  {
    _buffer[channel] = pwm;
  }
  write();
}


int TLC5947::setPercentage(uint8_t channel, float percentage)
{
  if (percentage < 0) percentage = 0;
  if (percentage > 100) percentage = 100;
  return setPWM(channel, round(percentage * 40.95));
}


void TLC5947::setPercentageAll(float percentage)
{
  if (percentage < 0) percentage = 0;
  if (percentage > 100) percentage = 100;
  setAll(round(percentage * 40.95));
}


float TLC5947::getPercentage(uint8_t channel)
{
  return getPWM(channel) * (100.0 / 4095);
}


//////////////////////////////////////////////////
//
//  WRITE
//
void TLC5947::write()
{
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  //  register level optimized AVR
  uint8_t port     = digitalPinToPort(_data);
  volatile uint8_t *_dataOutRegister = portOutputRegister(port);
  uint8_t outmask1 = digitalPinToBitMask(_data);
  uint8_t outmask2 = ~outmask1;

  port             = digitalPinToPort(_clock);
  volatile uint8_t *_clockRegister = portOutputRegister(port);
  uint8_t cbmask1  = digitalPinToBitMask(_clock);
  uint8_t cbmask2  = ~cbmask1;

  for (int channel = 23; channel >= 0; channel--)
  {
    for (int mask = 0x0800;  mask; mask >>= 1)
    {
      *_clockRegister &= cbmask2;
      if (_buffer[channel] & mask)
      {
        *_dataOutRegister |= outmask1;
      }
      else
      {
        *_dataOutRegister &= outmask2;
      }
      *_clockRegister |= cbmask1;
    }
  }
  *_clockRegister &= cbmask2;

#else

  //  also write when blank == LOW
  //       to "preload the registers"
  //  local variables to maximize speed.
  uint8_t _clk = _clock;
  uint8_t _dat = _data;

  for (int channel = 23; channel >= 0; channel--)
  {
    for (int mask = 0x0800;  mask; mask >>= 1)
    {
      digitalWrite(_clk, LOW);
      digitalWrite(_dat, _buffer[channel] & mask ? HIGH : LOW);
      digitalWrite(_clk, HIGH);
    }
  }
  digitalWrite(_clk, LOW);

#endif

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


bool TLC5947::isEnabled()
{
  return digitalRead(_blank) == HIGH;
}


//////////////////////////////////////////////////
//
//  RGB
//
int TLC5947::setRGB(uint8_t led, uint16_t R,  uint16_t G,  uint16_t B)
{
  if (led > 7) return TLC5947_CHANNEL_ERROR;
  uint8_t channel = 3 * led;
  _buffer[channel++] = R > 4095 ? 4095 : R;
  _buffer[channel++] = G > 4095 ? 4095 : G;
  _buffer[channel]   = B > 4095 ? 4095 : B;
  return TLC5947_OK;
}


int TLC5947::getRGB(uint8_t led, uint16_t &R,  uint16_t &G,  uint16_t &B)
{
  if (led > 7) return TLC5947_CHANNEL_ERROR;
  uint8_t channel = 3 * led;
  R = _buffer[channel++];
  G = _buffer[channel++];
  B = _buffer[channel];
  return TLC5947_OK;
}


//  -- END OF FILE --

