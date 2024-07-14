//
//    FILE: TLC5917.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
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
  _channelCount = deviceCount * 8;
  _clock  = clock;
  _data   = data;
  _le     = LE;
  _oe     = OE;
  _mode   = TLC5917_NORMAL_MODE;
  _buffer = (uint8_t *) calloc(deviceCount, sizeof(uint8_t));
  _configuration = 0xFF;  //  page 23  datasheet
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


int TLC5917::channelCount()
{
  return _channelCount;
}


bool TLC5917::setChannel(uint8_t channel, bool on)
{
  if (channel >= _channelCount) return false;
  uint8_t mask = 1 << (channel & 0x07);
  if (on) _buffer[channel / 8] |=  mask;
  else    _buffer[channel / 8] &= ~mask;
  return true;
}


bool TLC5917::setChannel(uint8_t * array)
{
  for (int i = 0; i < _channelCount / 8; i++)
  {
    _buffer[i] = array[i];
  }
  return true;
}


bool TLC5917::setAll(bool on)
{
  uint8_t mask = on ? 0xFF : 0x00;
  for (int i = 0; i < _channelCount / 8; i++)
  {
    _buffer[i] = mask;
  }
  return true;
}


bool TLC5917::getChannel(uint8_t channel)
{
  if (channel >= _channelCount) return false;
  uint8_t mask = 1 << (channel & 0x07);
  return (_buffer[channel / 8] & mask) > 0;
}


//////////////////////////////////////////////////
//
//  WRITE
//
//  MAX speed single device 30 MHz
//             multi device 15 MHz   CHECK TODO
void TLC5917::write()
{
  write(_channelCount);
}


void TLC5917::write(int channels)
{
  if (channels < 0) return;
  int devices = (channels > _channelCount) ? _channelCount / 8 : channels / 8;


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

  for (int dev = devices - 1; dev >= 0; dev--)
  {
    for (uint8_t mask = 0x80;  mask; mask >>= 1)
    {
      if (_buffer[dev] & mask)
      {
        *_dataOutRegister |= outmask1;  //  digitalWrite(_dat, HIGH);
      }
      else
      {
        *_dataOutRegister &= outmask2;  //  digitalWrite(_dat, LOW);
      }
      *_clockRegister |= cbmask1;  //  digitalWrite(_clk, HIGH);
      *_clockRegister &= cbmask2;  //  digitalWrite(_clk, LOW);
    }
  }

#else

  //  also write when outputEnable == LOW
  //       to "preload the registers"
  //  local variables to maximize speed.
  uint8_t _clk = _clock;
  uint8_t _dat = _data;

  for (int dev = devices - 1; dev >= 0; dev--)
  {
    for (uint8_t mask = 0x80;  mask; mask >>= 1)
    {
      digitalWrite(_dat, _buffer[dev] & mask ? HIGH : LOW);
      digitalWrite(_clk, HIGH);
      digitalWrite(_clk, LOW);
    }
  }

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
void TLC5917::setSpecialMode()
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

  _mode = TLC5917_SPECIAL_MODE;
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

  _mode = TLC5917_NORMAL_MODE;
}


uint8_t TLC5917::getMode()
{
  return _mode;
}


//  9.4.3 Writing Configuration Code in Special Mode
void TLC5917::writeConfiguration(uint8_t configuration)
{
  uint8_t _clk = _clock;
  uint8_t _dat = _data;
  uint8_t _devices = _channelCount / 8;

  //  write same configuration to all devices
  for (int i = 0; i < _devices; i++)
  {
    //  handle bit 7- 1
    for (uint8_t mask = 0x80;  mask > 1; mask >>= 1)
    {
      digitalWrite(_dat, configuration & mask ? HIGH : LOW);
      digitalWrite(_clk, HIGH);
      digitalWrite(_clk, LOW);
    }
    //  bit 0 should have an LE pulse
    digitalWrite(_le, HIGH);
    digitalWrite(_dat, configuration & 0x01 ? HIGH : LOW);
    digitalWrite(_clk, HIGH);
    digitalWrite(_clk, LOW);
    digitalWrite(_le, LOW);
  }
  _configuration = configuration;
}


uint8_t TLC5917::getConfiguration()
{
  return _configuration;
}


//  Page 23
bool TLC5917::setGain(bool CM, bool HC, uint8_t CC)
{
  if (CC > 63) return false;
  _configuration = CC;
  if (CM) _configuration |= 0x80;
  if (HC) _configuration |= 0x40;
  writeConfiguration(_configuration);
  return true;
}


float TLC5917::getVoltageGain()
{
  uint8_t CC = _configuration & 0x3F;  //  0..63
  uint8_t HC = (_configuration & 0x40) ? 1 : 0;
  float VG = (1.0 + HC) * (1.0 + CC * 0.015625) / 4;  //  0.015625 = 1/64
  return VG;
}


float TLC5917::getCurrentGain()
{
  float CG = getVoltageGain();
  // uint8_t CM = _configuration & 0x80;
  if (_configuration & 0x80) CG *= 3;
  return CG;
}


bool TLC5917::setCurrentGain(float n)
{
  if (n < 0.250) return false;
  if (n > 3.000) return false;

  uint8_t CM = 0;
  uint8_t HC = 0;
  uint8_t CC = 0;

  //  n == (1 + HC) × (1 + D/64) / 4 * pow(3, CM - 1);
  //  handle CM=1: values 1.0 - 2.977 == 150 - 255
  //  note values 128 - 149 not used (twice in table)
  if (n >= 1.0)
  {
    CM = 1;
    n /= 3;
  }
  //  n == (1 + HC) × (1 + D/64) / 4
  //  handle HC=1: values 0.5 - 1.0 == 64 - 127
  if (n >= 0.5)
  {
    HC = 1;
    n /= 2;
  }

  //  n == (1 + CC/64)/4;
  //  values 0.25 - 0.5
  n *= 4;
  n -= 1;
  if (n < 0) n = 0;
  CC = round(n * 64);
  if (CC >= 64) CC = 63;  //  truncate at top.
  setGain(CM, HC, CC);
  return true;
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

