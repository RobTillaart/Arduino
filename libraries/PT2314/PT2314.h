#pragma once
//
//    FILE: PT2314.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-30
// VERSION: 0.2.1
// PURPOSE: Arduino library for PT2314 i2C 4 channel audio processor.
//     URL: https://github.com/RobTillaart/PT2314


#include "Arduino.h"
#include "Wire.h"


#define PT2314_LIB_VERSION                   (F("0.2.1"))


class PT2314
{
public:
  PT2314(TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();

  //  CHANNEL = 0..3
  void    setChannel(uint8_t channel = 0);
  uint8_t getChannel();

  void    setMute(bool mute = true);
  bool    getMute();
  void    setLoudness(bool loudness = true);
  bool    getLoudness();

  //  VOLUME = 0..63
  void    setVolume(uint8_t volume = 0);
  uint8_t getVolume();
  //  BASS = -14..14
  void    setBass(int8_t bass = 0);
  int8_t  getBass();
  //  TREBLE = -14..14
  void    setTreble(int8_t treble = 0);
  int8_t  getTreble();

  //  GAIN = 0..3
  void    setGain(uint8_t gain = 0);
  uint8_t getGain();

  //  ATTENUATION = 0..31
  void    setAttnLeft(uint8_t attn = 31);
  uint8_t getAttnLeft();
  void    setAttnRight(uint8_t attn = 31);
  uint8_t getAttnRight();
  //  set all to same level
  void    setAttn(uint8_t attn);


protected:
  void     write(const uint8_t value);
  void     updateAudioRegister();

  TwoWire  *_wire;
  uint8_t  _address   = 0x44;

  uint8_t  _channel   = 0;
  bool     _mute      = false;
  bool     _loudness  = false;
  uint8_t  _volume    = 0;
  int8_t   _bass      = 0;
  int8_t   _treble    = 0;
  uint8_t  _gain      = 0;
  uint8_t  _attnLeft  = 0;
  uint8_t  _attnRight = 0;
  // to be elaborated.
  int      _error     = 0;
};


///////////////////////////////////////////////////////////////
//
//  DERIVED
//
class PT7314 : public PT2314
{
public:
  PT7314(TwoWire *wire = &Wire);
};


//  3 input  2 output version
class PT7313 : public PT2314
{
public:
  PT7313(TwoWire *wire = &Wire);

  void    setMute(bool mute);
  //  CHANNEL = 0..2
  void    setChannel(uint8_t channel = 0);

  //  ATTENUATION = 0..31
  void    setAttnLeftBack(uint8_t attn = 31);
  uint8_t getAttnLeftBack();
  void    setAttnRightBack(uint8_t attn = 31);
  uint8_t getAttnRightBack();
  //  FRONT = 0..31
  void    setAttnLeftFront(uint8_t attn = 31);
  uint8_t getAttnLeftFront();
  void    setAttnRightFront(uint8_t attn = 31);
  uint8_t getAttnRightFront();
  //  ALL = 0..31
  void    setAttn(uint8_t attn);

protected:
  uint8_t  _attnLeftFront  = 0;
  uint8_t  _attnRightFront = 0;
};


//  -- END OF FILE --

