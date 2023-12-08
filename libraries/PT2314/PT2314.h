#pragma once
//
//    FILE: PT2314.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-30
// VERSION: 0.2.0
// PURPOSE: Arduino library for PT2314 i2C 4 channel audio processor.
//     URL: https://github.com/RobTillaart/PT2314


#include "Arduino.h"
#include "Wire.h"


#define PT2314_LIB_VERSION                   (F("0.2.0"))


class PT2314
{
public:
  PT2314(TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();

  //  AUDIO
  void    setChannel(uint8_t channel = 0);  //  0..3
  uint8_t getChannel();

  void    setMute(bool on = true);
  bool    getMute();
  void    setLoudness(bool on = true);
  bool    getLoudness();

  void    setVolume(uint8_t volume = 0);  //  0..63
  uint8_t getVolume();
  void    setBass(int8_t bass = 0);       //  -14..14
  int8_t  getBass();
  void    setTreble(int8_t treble = 0);   //  -14..14
  int8_t  getTreble();

  //      GAIN
  void    setGain(uint8_t gain = 0);      //  0..3
  uint8_t getGain();

  //      ATTENUATION
  void    setAttnLeft(uint8_t value = 31);  //  0..31
  uint8_t getAttnLeft();
  void    setAttnRight(uint8_t value = 31);  //  0..31
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

  void    setMute(bool on);
  void    setChannel(uint8_t channel = 0);        //  0..2

  //  BACK
  void    setAttnLeftBack(uint8_t value = 31);    //  0..31
  uint8_t getAttnLeftBack();
  void    setAttnRightBack(uint8_t value = 31);   //  0..31
  uint8_t getAttnRightBack();

  //  FRONT
  void    setAttnLeftFront(uint8_t value = 31);   //  0..31
  uint8_t getAttnLeftFront();
  void    setAttnRightFront(uint8_t value = 31);  //  0..31
  uint8_t getAttnRightFront();

  //  ALL
  void    setAttn(uint8_t attn);

protected:
  uint8_t  _attnLeftFront  = 0;
  uint8_t  _attnRightFront = 0;
};


//  -- END OF FILE --

