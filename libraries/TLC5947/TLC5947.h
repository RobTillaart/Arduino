#pragma once
//
//    FILE: TLC5947.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2023-06-17
// PURPOSE: Arduino library for the TLC5947 24 channel PWM device
//     URL: https://github.com/RobTillaart/TLC5947


#define TLC5947_LIB_VERSION             (F("0.2.0"))


#include "Arduino.h"


#define  TLC5947_OK                     0x0000
#define  TLC5947_CHANNEL_ERROR          0xFFFF


class TLC5947
{
public:
  TLC5947(uint8_t clock, uint8_t data, uint8_t latch, uint8_t blank);
  ~TLC5947();

  bool     begin();

  //  fill the internal buffer with PWM values
  //  call write() after all channels are updated (or per channel).
  int      setPWM(uint8_t channel, uint16_t PWM);
  void     setAll(uint16_t PWM);
  //  get PWM value from the buffer, might differ from TLC5947 device!
  uint16_t getPWM(uint8_t channel);

  //  percentage wrappers
  int      setPercentage(uint8_t channel, float percentage);
  void     setPercentageAll(float percentage);
  float    getPercentage(uint8_t channel);

  //  write the buffer to the TLC5947 device
  void     write();

  //  control the blank line.
  void     enable();
  void     disable();
  bool     isEnabled();  //  returns status

  //  RGB interface, you need to call write() afterwards.
  int      setRGB(uint8_t led, uint16_t R,  uint16_t G,  uint16_t B);
  int      getRGB(uint8_t led, uint16_t &R,  uint16_t &G,  uint16_t &B);


private:
  uint16_t *_buffer;
  uint8_t  _clock;
  uint8_t  _data;
  uint8_t  _latch;
  uint8_t  _blank;
};


//  -- END OF FILE --

