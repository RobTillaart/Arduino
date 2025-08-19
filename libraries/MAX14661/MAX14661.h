#pragma once
//
//    FILE: MAX14661.h
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-29
// VERSION: 0.3.0
// PURPOSE: Arduino library for MAX14661 16 channel I2C multiplexer
//     URL: https://github.com/RobTillaart/MAX14661


#include "Arduino.h"
#include "Wire.h"


#define MAX14661_LIB_VERSION                (F("0.3.0"))

#define MAX14661_OK                         0x00
#define MAX14661_ERR_I2C_READ               0x80
#define MAX14661_ERR_I2C_REQUEST            0x81
#define MAX14661_ERR_CHANNEL                0x90
#define MAX14661_ERR_ADDRESS                0x91



class MAX14661
{
public:
  explicit MAX14661(const uint8_t deviceAddress, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  PAIR INTERFACE
  //  - there are 8 pairs { (0,1), (2,3), (4,5), ... (14,15) }
  //  - connecting a pair connects one of the pair with COM-A 
  //    and the other with COM-B
  //  - keeps the A and B line in sync, ideal for an I2C bus or Serial.
  //  - returns false if channel > 7
  //  - verify with lastError().
  //
  bool     connectPair(uint8_t pair);
  bool     disconnectPair(uint8_t pair);
  bool     isConnectedPair(uint8_t pair);
  //  closes A and B lines of all pairs
  bool     disconnectAllPairs();


  //  SHADOW INTERFACE
  //  - experimental - not tested.
  //  - prepares channels to be set in one activateShadow().
  //
  void     shadowClear();
  //  should we have activateShadowA() and activateShadowB() ?
  void     activateShadow();

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


  //  MUX INTERFACE
  //  - allows only one channel simultaneously open
  //  - opening a channel closes any other.
  //
  void     MUXA(uint8_t channel);  //  0..15, else ==> all off
  uint8_t  getMUXA();
  void     MUXB(uint8_t channel);  //  0..15, else ==> all off
  uint8_t  getMUXB();


  //  FULL CONTROL
  //  - selective connect to COM-A and COM-B
  //  - returns false if channel > 15
  //
  bool     connectA(uint8_t channel);
  bool     connectB(uint8_t channel);
  bool     disconnectA(uint8_t channel);
  bool     disconnectB(uint8_t channel);
  bool     disconnectAll();  //  close all channels as fast as possible


  //  LOW LEVEL CONTROL
  //  optional optimizations.
  //  uint8_t  getRegister(uint8_t reg, uint8_t bit);
  //  uint8_t  setRegister(uint8_t reg, uint8_t bit);
  //  uint8_t  clrRegister(uint8_t reg, uint8_t bit);
  //  uint16_t readRegister2(uint8_t reg);  //  2 bytes
  //  int      writeRegister2(uint8_t reg, uint16_t value);  // 2  bytes
  //
  uint8_t  readRegister(uint8_t reg);
  int      writeRegister(uint8_t reg, uint8_t value);


  //  ERROR HANDLING
  //
  int      lastError();


private:
  uint8_t  _address;
  TwoWire* _wire;

  int      _error;
};


//  -- END OF FILE --

