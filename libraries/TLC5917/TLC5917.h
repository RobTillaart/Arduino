#pragma once
//
//    FILE: TLC5917.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2024-03-17
// PURPOSE: Arduino library for TLC5917 8-Channel Constant-Current LED Sink Drivers.
//     URL: https://github.com/RobTillaart/TLC5917


#define TLC5917_LIB_VERSION             (F("0.2.0"))


#include "Arduino.h"


//  non Arduino environment need to fix these.
/*
#include <stdint.h>
#include <cstdlib>

#define pinMode(X, Y)        {}
#define digitalWrite(X, Y)   {}
#define digitalRead(X)       (1)

#define HIGH    1
#define LOW     0
#define OUTPUT  0
*/

#define TLC5917_OK                      0x0000
#define TLC5917_CHANNEL_ERROR           0xFFFF

#define TLC5917_NORMAL_MODE             0x00
#define TLC5917_SPECIAL_MODE            0x01


class TLC5917
{
public:
  //  single device constructor
  //  LE = Latch Enable
  //  OE = Output Enable
  TLC5917(uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE);
  //  multi device constructor 
  //  - for daisy chaining
  TLC5917(int deviceCount, uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE);
  virtual ~TLC5917();

  bool     begin();
  int      channelCount();

  bool     setChannel(uint8_t channel, bool on);
  //       size array must be equal or larger than deviceCount.
  //       one bit per channel.
  bool     setChannel(uint8_t * array);
  bool     setAll(bool on);
  bool     getChannel(uint8_t channel);

  //       write the internal buffer to the TLC5917 device(s).
  void     write(int channels);
  void     write();

  //       control the outputEnable (OE) line.
  void     enable();
  void     disable();
  bool     isEnabled();  //  returns status

  //       GAIN configuration mode
  //       TODO test if this works for single device.
  //       TODO test if this works for cascaded devices.
  void     setSpecialMode();
  void     setNormalMode();
  uint8_t  getMode();

  //       writes the same configuration to all devices.
  void     writeConfiguration(uint8_t configuration);
  uint8_t  getConfiguration();
  bool     setGain(bool CM, bool HC, uint8_t CC);  //  CC 0..63
  bool     setCurrentGain(float n);  //  n = 0.250 - 3.000
  float    getVoltageGain();
  float    getCurrentGain();


protected:
  int       _channelCount;
  uint8_t * _buffer;

  uint8_t   _clock;
  uint8_t   _data;
  uint8_t   _le;  //  latch enable
  uint8_t   _oe;  //  output enable

  uint8_t   _mode;
  uint8_t   _configuration;
};


/////////////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
class TLC5916 : public TLC5917
{
public:
  //  single device constructor
  TLC5916(uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE);
  //  multi device constructor - for daisy chaining)
  TLC5916(int deviceCount, uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE);
  virtual ~TLC5916() {};
};


//  -- END OF FILE --

