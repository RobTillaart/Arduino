#pragma once
//
//    FILE: PT2258.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-07-24
// VERSION: 0.1.1
// PURPOSE: Arduino library for PT2258 I2C 6 channel audio volume processor.
//     URL: https://github.com/RobTillaart/PT2258


#include "Arduino.h"
#include "Wire.h"


#define PT2258_LIB_VERSION                   (F("0.1.1"))


class PT2258
{
public:
  PT2258(uint8_t address, TwoWire * wire = &Wire)
  {
    _address = address;
    _wire = wire;
  }

  bool begin()
  {
    if (! isConnected()) return false;
    //  page 9, datasheet send 0xC0 first.
    initRegisters();
    //  minimize all
    setVolumeAll(79);
    return true;
  }

  uint8_t getAddress()
  {
    return _address;
  }

  bool isConnected()
  {
    _wire->beginTransmission(_address);
    return ( _wire->endTransmission() == 0);
  }

  int setVolumeAll(uint8_t volume)
  {
    if (volume > 79) volume = 79;
    return setAttenuationAll(79 - volume);
  }

  int setAttenuationAll(uint8_t attn)
  {
    if (attn > 79) attn = 79;
    uint8_t tens = attn / 10;
    uint8_t ones = attn - tens * 10;

    _error = write(0xD0 | ones, 0xE0 | tens);
    if (_error != 0) return _error;
    //  update cache
    for (int channel = 0; channel < 6; channel++) 
    {
      _attn[channel] = attn;
    }
    return 0;
  }

  //  datasheet uses 1..6, library uses 0..5
  int setVolume(uint8_t channel, uint8_t volume)
  {
    if (volume > 79) volume = 79;
    return setAttenuation(channel, 79 - volume);
  }
  
  int setAttenuation(uint8_t channel, uint8_t attn)
  {
    if (channel > 5) return 0x8001;
    //  constrain attenuation
    if (attn > 79) attn = 79;
    uint8_t tens = attn / 10;
    uint8_t ones = attn - tens * 10;
    switch (channel)
    {
      case 0:
        ones = 0x90 | ones;
        tens = 0x80 | tens;
        break;
      case 1:
        ones = 0x50 | ones;
        tens = 0x40 | tens;
        break;
      case 2:
        ones = 0x10 | ones;
        tens = 0x00 | tens;
        break;
      case 3:
        ones = 0x30 | ones;
        tens = 0x20 | tens;
        break;
      case 4:
        ones = 0x70 | ones;
        tens = 0x60 | tens;
        break;
      case 5:
        ones = 0xB0 | ones;
        tens = 0xA0 | tens;
        break;
    }

    _error = write(ones, tens);
    if (_error != 0) return _error;
    //  update cache
    _attn[channel] = attn;
    return 0;
  }

  int getVolume(uint8_t channel)
  {
    if (channel > 5) return 0x8001;
    return 79 - _attn[channel];
  }

  int getAttenuation(uint8_t channel)
  {
    if (channel > 5) return 0x8001;
    return _attn[channel];
  }

  int mute(bool on)
  {
    uint8_t mute = 0xF8;
    if (on) mute |= 0x01;
    _error = write(mute, mute);
    //  keep cached channel values
    return _error;
  }

  int getLastError()
  {
    int e = _error;
    _error = 0;
    return e;
  }


private:
  int initRegisters()
  {
    _wire->beginTransmission(_address);
    _wire->write(0xC0);
    return _wire->endTransmission();
  }
  
  int write(uint8_t attn1, uint8_t attn2)
  {
    _wire->beginTransmission(_address);
    _wire->write(attn1);
    _wire->write(attn2);
    return _wire->endTransmission();
  }
  
  uint8_t   _address;
  TwoWire * _wire;


  uint8_t _attn[6] = {0,0,0,0,0,0};
  int     _error;
};


// -- END OF FILE --

