#pragma once
//
//    FILE: MAX14661.h
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-29
// VERSION: 0.1.2
// PURPOSE: Arduino library for MAX14661 16 channel I2C multiplexer
//     URL: https://github.com/RobTillaart/MAX14661
//


#include "Arduino.h"
#include "Wire.h"


#define MAX14661_LIB_VERSION     (F("0.1.2"))


class MAX14661
{
public:
  explicit MAX14661(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(uint8_t sda, uint8_t scl);
#endif
  bool     begin();
  bool     isConnected();

  //
  // PAIR INTERFACE
  // - keeps A and B line in sync, ideal for an I2C bus or Serial.
  // - returns false if channel nr > 15
  //
  // open ==> connect
  bool     openChannel(uint8_t channel);
  // close ==> disconnect
  bool     closeChannel(uint8_t channel);
  // returns true if channel is opened
  bool     isOpenChannel(uint8_t channel);

  // open A and B lines of all channels
  void     openAllChannels();
  // closes A and B lines of all channels
  void     closeAllChannels();

  // set channels with a bit mask
  void     setChannels(uint16_t mask);
  // returns channel state as bit mask
  uint16_t getChannels();


  //
  // SHADOW INTERFACE
  // - experimental - not tested.
  // - prepares channels to be set in one activateShadow().
  //
  void     shadowClear();
  void     activateShadow();   // should we have activateShadowA() and activateShadowB() ?

  void     setShadowChannelMaskA(uint16_t mask);
  uint16_t getShadowChannelMaskA();
  void     setShadowChannelMaskB(uint16_t mask);
  uint16_t getShadowChannelMaskB();

  bool     openShadowChannelA(uint8_t channel);
  bool     closeShadowChannelA(uint8_t channel);
  bool     isOpenShadowChannelA(uint8_t channel);

  bool     openShadowChannelB(uint8_t channel);
  bool     closeShadowChannelB(uint8_t channel);
  bool     isOpenShadowChannelB(uint8_t channel);


  //
  // MUX INTERFACE
  // - allows only one channel simultaneously open
  // - opening a channel closes any other.
  //
  void     MUXA(uint8_t channel);  // 0..15, else ==> off
  uint8_t  getMUXA();
  void     MUXB(uint8_t channel);  // 0..15, else ==> off
  uint8_t  getMUXB();


  //
  // FULL CONTROL PER A B LINE
  // - selective open and close A and B
  // - returns false if channel nr > 15
  //
  bool     openA(uint8_t channel);
  bool     openB(uint8_t channel);
  bool     closeA(uint8_t channel);
  bool     closeB(uint8_t channel);


  // LOW LEVEL CONTROL
  // optional optimizations.
  // uint8_t  getRegister(uint8_t reg, uint8_t bit);
  // uint8_t  setRegister(uint8_t reg, uint8_t bit);
  // uint8_t  clrRegister(uint8_t reg, uint8_t bit);
  // uint16_t readRegister2(uint8_t reg);  // 2 bytes
  // int      writeRegister2(uint8_t reg, uint16_t value);  // 2 bytes

  uint8_t  readRegister(uint8_t reg);
  int      writeRegister(uint8_t reg, uint8_t value);
  int      lastError();

private:
  uint8_t  _address;
  TwoWire* _wire;

  int      _error;

  //  cache direct registers?
};


// -- END OF FILE --

