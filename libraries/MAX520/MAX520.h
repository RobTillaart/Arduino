#pragma once
//
//    FILE: MAX520.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-03-06
// VERSION: 0.1.1
// PURPOSE: Arduino library for MAX520 and MAX521 4/8 channel 8 bit DAC.
//     URL: https://github.com/RobTillaart/MAX520


#include "Arduino.h"
#include "Wire.h"


#define MAX520_LIB_VERSION         (F("0.1.1"))

#define MAX520_OK                  0x00
#define MAX520_CHANNEL_ERROR       0x81
#define MAX520_I2C_ERROR           0x82


class MAX520
{
public:
  explicit MAX520(uint8_t deviceAddress = 0x20, TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();


  //  note: setting the address corrupt internal buffer values
  //  a read8() / write8() call updates them.
  bool    setAddress(uint8_t deviceAddress);
  uint8_t getAddress();

  uint8_t getChannels();

  int     write(uint8_t channel, uint8_t value);
  int     write(uint8_t * values);  //  write 4/8 values at once.
  int     read(uint8_t channel);

  int     reset();
  int     powerDown();
  int     wakeUp();

  int     lastError();

protected:
  uint8_t _address;
  uint8_t _channels;
  uint8_t _values[8];
  int     _error;

  TwoWire*  _wire;
};


class MAX521 : public MAX520
{
public:
  MAX521(uint8_t deviceAddress = 0x20, TwoWire *wire = &Wire);
};



//  -- END OF FILE --

