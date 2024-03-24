//
//    FILE: TLC5917.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-03-17
// PURPOSE: Arduino library for TLC5917 8-Channel Constant-Current LED Sink Drivers.
//     URL: https://github.com/RobTillaart/TLC5917


#include "TLC5917.h"


TLC5917::TLC5917(uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE)
{
  TLC5917(1, clock, data, LE, OE);
}


TLC5917::TLC5917(int deviceCount, uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE)
{
  if (deviceCount <= 0) deviceCount = 1;
  _channels = deviceCount * 8;
  _clock    = clock;
  _data     = data;
  _le       = LE;
  _oe       = OE;
  _buffer   = (uint8_t *) calloc(_channels, sizeof(uint8_t));
}


TLC5917::~TLC5917()
{
  if (_buffer) free(_buffer);
}


bool TLC5917::begin()
{
  pinMode(_clock, OUTPUT);
  pinMode(_data,  OUTPUT);
  pinMode(_le, OUTPUT);
  pinMode(_oe, OUTPUT);
  digitalWrite(_clock, LOW);
  digitalWrite(_data, LOW);
  digitalWrite(_le, LOW);
  //  disable by default, safest option.
  disable();
  return true;
}


int TLC5917::getChannels()
{
  return _channels;
}


bool TLC5917::setChannel(uint8_t channel, bool on)
{
  if (channel >= _channels) return false;
  if (on) _buffer[channel / 8] |=  (1 << channel & 0x07);
  else    _buffer[channel / 8] &= ~(1 << channel & 0x07);
  return true;
}


bool TLC5917::setChannel(uint8_t * array)
{
  for (int i = 0; i < _channels / 8; i++)
  {
    _buffer[i] = array[i];
  }
  return true;
}


bool TLC5917::setAll(bool on)
{
  uint8_t mask = on ? 0xFF : 0x00;
  for (int i = 0; i < _channels / 8; i++)
  {
    _buffer[i] = mask;
  }
  return true;
}


bool TLC5917::getChannel(uint8_t channel)
{
  if (channel >= _channels) return false;
  return (_buffer[channel / 8] & (1 << (channel & 0x07))) > 0;
}


//////////////////////////////////////////////////
//
//  WRITE
//
//  MAX speed single device 30 MHz
//             multi device 15 MHz   CHECK TODO
void TLC5917::write()
{
  write(_channels);
}


void TLC5917::write(int chan)
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
    for (uint8_t mask = 0x80;  mask; mask >>= 1)
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
    for (uint8_t mask = 0x80;  mask; mask >>= 1)
    {
      digitalWrite(_clk, LOW);
      digitalWrite(_dat, _buffer[channel] & mask ? HIGH : LOW);
      digitalWrite(_clk, HIGH);
    }
  }
  digitalWrite(_clk, LOW);

#endif

  //  pulse latch to hold the signals
  digitalWrite(_le, HIGH);
  digitalWrite(_le, LOW);
}


//////////////////////////////////////////////////
//
//  ENABLE
//
void TLC5917::enable()
{
  digitalWrite(_oe, LOW);
}


void TLC5917::disable()
{
  digitalWrite(_oe, HIGH);
}


bool TLC5917::isEnabled()
{
  return (digitalRead(_oe) == LOW);
}


//////////////////////////////////////////////////
//
//  CONFIGURATION
//
//  NOT OPTIMIZED
//
//  Page 19
void TLC5917::setCurrentAdjustMode()
{
  digitalWrite(_le, LOW);
  digitalWrite(_oe, HIGH);

  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);

  digitalWrite(_oe, LOW);
  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);

  digitalWrite(_oe, HIGH);
  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);

  digitalWrite(_le, HIGH);
  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);

  digitalWrite(_le, LOW);
  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);
}


//  Page 19
void TLC5917::setNormalMode()
{
  digitalWrite(_le, LOW);
  digitalWrite(_oe, HIGH);
  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);

  digitalWrite(_oe, LOW);
  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);

  digitalWrite(_oe, HIGH);
  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);

  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);

  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);
}


void TLC5917::writeConfiguration(uint8_t config)
{
  uint8_t _clk = _clock;
  uint8_t _dat = _data;
  uint8_t _devices = _channels/8;

  //  write same config to all devices
  for (int i = 0; i < _devices; i++)
  {
    for (uint8_t mask = 0x80;  mask; mask >>= 1)
    {
      digitalWrite(_clk, LOW);
      digitalWrite(_dat, config & mask ? HIGH : LOW);
      digitalWrite(_clk, HIGH);
    }
    digitalWrite(_clk, LOW);
  }

  //  pulse latch to hold the signals in configuration register.
  //  not exactly like Page 18 figure 13.
  digitalWrite(_le, HIGH);
  digitalWrite(_le, LOW);
}



/////////////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
TLC5916::TLC5916(uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE)
        :TLC5917(clock, data, LE, OE)
{
  //  optional code, later.
  //  type field?
}


TLC5916::TLC5916(int deviceCount, uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE)
        :TLC5917(deviceCount, clock, data, LE, OE)
{
}


//  -- END OF FILE --

