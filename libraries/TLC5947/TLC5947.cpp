//
//    FILE: TLC5947.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2023-06-17
// PURPOSE: Arduino library for the TLC5947 24 channel PWM device
//     URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"


TLC5947::TLC5947(uint8_t clock, uint8_t data, uint8_t latch, uint8_t blank)
{
  TLC5947(1, clock, data, latch, blank);
}


TLC5947::TLC5947(int deviceCount, uint8_t clock, uint8_t data, uint8_t latch, uint8_t blank)
{
  if (deviceCount == 0) deviceCount = 1;
  _channels = deviceCount * 24;
  _clock    = clock;
  _data     = data;
  _latch    = latch;
  _blank    = blank;
  _buffer   = (uint16_t *) calloc(_channels, 2);
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
  //  disable PWM by default - datasheet P7
  //  safest option.
  disable();
  return true;
}


int TLC5947::getChannels()
{
  return _channels;
}


//////////////////////////////////////////////////
//
//  PWM
//
int TLC5947::setPWM(uint8_t channel, uint16_t PWM)
{
  if (channel >= _channels) return TLC5947_CHANNEL_ERROR;
  _buffer[channel] = PWM > MAXPWM ? MAXPWM : PWM;
  return TLC5947_OK;
}


uint16_t TLC5947::getPWM(uint8_t channel)
{
  if (channel >= _channels) return TLC5947_CHANNEL_ERROR;
  return _buffer[channel] & 0x0FFF;
}


void TLC5947::setAll(uint16_t PWM)
{
  uint16_t pwm = PWM > MAXPWM ? MAXPWM : PWM;
  for (int channel = 0; channel < _channels; channel++)
  {
    _buffer[channel] = pwm;
  }
  write();
}


int TLC5947::setPercentage(uint8_t channel, float percentage)
{
  if (percentage < 0) percentage = 0;
  if (percentage > 100) percentage = 100;
  return setPWM(channel, round(percentage * (MAXPWM * 0.01)));
}


void TLC5947::setPercentageAll(float percentage)
{
  if (percentage < 0) percentage = 0;
  if (percentage > 100) percentage = 100;
  setAll(round(percentage * (MAXPWM * 0.01)));
}


float TLC5947::getPercentage(uint8_t channel)
{
  return getPWM(channel) * (100.0 / MAXPWM);
}


//////////////////////////////////////////////////
//
//  WRITE
//
//  MAX speed single device 30 MHz
//             multi device 15 MHz
void TLC5947::write()
{
  write(_channels);
}


void TLC5947::write(int chan)
{
  if (chan > _channels) chan = _channels;
  if (chan < 0) return; 

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

  for (int channel = chan - 1; channel >= 0; channel--)
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

  for (int channel = chan - 1; channel >= 0; channel--)
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

  //  pulse latch to hold the signals
  digitalWrite(_latch, HIGH);
  digitalWrite(_latch, LOW);
}


void TLC5947::enable()
{
  digitalWrite(_blank, LOW);
}


void TLC5947::disable()
{
  digitalWrite(_blank, HIGH);
}


bool TLC5947::isEnabled()
{
  return (digitalRead(_blank) == LOW);
}


//////////////////////////////////////////////////
//
//  RGB
//
int TLC5947::setRGB(uint8_t led, uint16_t R,  uint16_t G,  uint16_t B)
{
  if ((led * 3) >= _channels) return TLC5947_CHANNEL_ERROR;
  uint8_t channel = 3 * led;
  _buffer[channel++] = R > MAXPWM ? MAXPWM : R;
  _buffer[channel++] = G > MAXPWM ? MAXPWM : G;
  _buffer[channel]   = B > MAXPWM ? MAXPWM : B;
  return TLC5947_OK;
}


int TLC5947::getRGB(uint8_t led, uint16_t &R,  uint16_t &G,  uint16_t &B)
{
  if ((led * 3) >= _channels) return TLC5947_CHANNEL_ERROR;
  uint8_t channel = 3 * led;
  R = _buffer[channel++];
  G = _buffer[channel++];
  B = _buffer[channel];
  return TLC5947_OK;
}


//  -- END OF FILE --

