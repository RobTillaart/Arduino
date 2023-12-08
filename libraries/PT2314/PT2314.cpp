//
//    FILE: PT2314.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-30
// VERSION: 0.2.0
// PURPOSE: Arduino library for PT2314 i2C 4 channel audio processor.
//     URL: https://github.com/RobTillaart/PT2314


#include "PT2314.h"


PT2314::PT2314(TwoWire *wire)
{
  _wire = wire;
}


bool PT2314::begin()
{
  if (! isConnected()) return false;
  setChannel();
  setMute();
  setLoudness();
  setVolume();
  setBass();
  setTreble();
  setGain();
  //  setAttn(31, 31);  //  already muted
  return true;
}


bool PT2314::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


void PT2314::setChannel(uint8_t channel)
{
  if (channel > 3) channel = 3;
  _channel = channel;
  updateAudioRegister();
}

uint8_t PT2314::getChannel()
{
  return _channel;
}


///////////////////////////////////////////////////
//
//  AUDIO
//
void PT2314::setMute(bool on)
{
  _mute = on;
  if (_mute)
  {
    write(0xDF);  //  left
    write(0xFF);  //  right
  }
  else
  {
    write(0xC0 | _attnLeft);
    write(0xE0 | _attnRight);
  }
}


bool PT2314::getMute()
{
  return _mute;
}


void PT2314::setLoudness(bool on)
{
  _loudness = on;
  updateAudioRegister();
}


bool PT2314::getLoudness()
{
  return _loudness;
}


void PT2314::setVolume(uint8_t volume)
{
  if (volume > 63) volume = 63;
  _volume = volume;
  write(_volume);
}


uint8_t PT2314::getVolume()
{
  return _volume;
}


void PT2314::setBass(int8_t bass)
{
  if (bass < -14) bass = -14;
  if (bass >  14) bass = 14;
  _bass = bass;
  uint8_t value;
  if (_bass <= 0) value = 7  + (_bass / 2);
  else            value = 15 - (_bass / 2);
  write(0x60 | value);
}


int8_t PT2314::getBass()
{
  return _bass;
}


void PT2314::setTreble(int8_t treble)
{
  if (treble < -14) treble = -14;
  if (treble >  14) treble = 14;
  _treble = treble;
  uint8_t value;
  if (_treble <= 0) value = 7  + (_treble / 2);
  else              value = 15 - (_treble / 2);
  write(0x70 | value);
}


int8_t PT2314::getTreble()
{
  return _treble;
}


void PT2314::setGain(uint8_t gain)
{
  if (gain > 3) gain = 3;
  _gain = gain << 3;
  updateAudioRegister();
}


uint8_t PT2314::getGain()
{
  return _gain >> 3;
}


void PT2314::setAttnLeft(uint8_t attnLeft)
{
  if (attnLeft > 31) attnLeft = 31;
  _attnLeft = attnLeft;
  write(0xC0 | _attnLeft);
}


uint8_t PT2314::getAttnLeft()
{
  return _attnLeft;
}


void PT2314::setAttnRight(uint8_t attnRight)
{
  if (attnRight > 31) attnRight = 31;
  _attnRight = attnRight;
  write(0xE0 | _attnRight);
}


uint8_t PT2314::getAttnRight()
{
  return _attnRight;
}


void PT2314::setAttn(uint8_t attn)
{
  setAttnLeft(attn);
  setAttnRight(attn);
}




///////////////////////////////////////////////////
//
//  PROTECTED
//
void PT2314::write(const uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(value);
  _error = _wire->endTransmission();
}


void PT2314::updateAudioRegister()
{
  uint8_t value = 0x40;
  value |= _channel;
  if (_loudness == false) value |= 0x04;
  value |= _gain;
  write(value);
}



///////////////////////////////////////////////////
//
//  DERIVED CLASS
//
PT7314::PT7314(TwoWire *wire) : PT2314(wire)
{
}


PT7313::PT7313(TwoWire *wire) : PT2314(wire)
{
}


void PT7313::setMute(bool on)
{
  _mute = on;
  if (_mute)
  {
    write(0xDF);  //  left  back
    write(0xFF);  //  right back
    write(0x9F);  //  left  front
    write(0xBF);  //  right front
  }
  else
  {
    write(0xC0 | _attnLeft);   //  back
    write(0xE0 | _attnRight);  //  back
    write(0x80 | _attnLeftFront);
    write(0xA0 | _attnRightFront);
  }
}

void PT7313::setChannel(uint8_t channel)
{
  if (channel > 2) channel = 2;
  _channel = channel;
  updateAudioRegister();
}


void PT7313::setAttnLeftBack(uint8_t value)
{
  setAttnLeft(value);
}


uint8_t PT7313::getAttnLeftBack()
{
  return getAttnLeft();
}


void PT7313::setAttnRightBack(uint8_t value)
{
  setAttnRight(value);
}


uint8_t PT7313::getAttnRightBack()
{
  return getAttnRight();
}


void PT7313::setAttnLeftFront(uint8_t value)
{
   if (value > 31) value = 31;
  _attnLeftFront = value;
  write(0x80 | _attnLeftFront);
}


uint8_t PT7313::getAttnLeftFront()
{
  return _attnLeftFront;
}


void PT7313::setAttnRightFront(uint8_t value)
{
   if (value > 31) value = 31;
  _attnRightFront = value;
  write(0xA0 | _attnRightFront);
}


uint8_t PT7313::getAttnRightFront()
{
  return _attnRightFront;
}


void PT7313::setAttn(uint8_t attn)
{
  setAttnLeft(attn);
  setAttnRight(attn);
  setAttnLeftFront(attn);
  setAttnRightFront(attn);
}


//  -- END OF FILE --

