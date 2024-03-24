#pragma once
//
//    FILE: TLC5917.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-03-17
// PURPOSE: Arduino library for TLC5917 8-Channel Constant-Current LED Sink Drivers.
//     URL: https://github.com/RobTillaart/TLC5917


#define TLC5917_LIB_VERSION             (F("0.1.0"))


#include "Arduino.h"


#define  TLC5917_OK                     0x0000
#define  TLC5917_CHANNEL_ERROR          0xFFFF


class TLC5917
{
public:
  //  single device constructor
  TLC5917(uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE);
  //  multi device constructor - for daisy chaining)
  TLC5917(int deviceCount, uint8_t clock, uint8_t data, uint8_t LE, uint8_t OE);
  virtual ~TLC5917();

  bool     begin();
  int      getChannels();

  bool     setChannel(uint8_t channel, bool on);
  bool     setChannel(uint8_t * array);  //  size must be deviceCount.
  bool     setAll(bool on);
  bool     getChannel(uint8_t channel);

  //  write the buffer to the TLC5917 device(s).
  void     write(int n);
  void     write();

  //  control the blank (OE) line.
  void     enable();
  void     disable();
  bool     isEnabled();  //  returns status

  //  configuration mode
  //  TODO test if this works for single device.
  //  TODO test if this works for cascaded devices.
  void     setCurrentAdjustMode();
  void     setNormalMode();
  void     writeConfiguration(uint8_t config);


protected:
  int       _channels;
  uint8_t * _buffer;
  uint8_t   _clock;
  uint8_t   _data;
  uint8_t   _le;  //  latch enable
  uint8_t   _oe;  //  output enable
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

