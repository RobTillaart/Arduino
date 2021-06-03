#pragma once
//
//    FILE: MAX14661.h
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-29
// VERSION: 0.1.0
// PURPOSE: Arduino library for MAX14661 16 channel I2C multiplexer
//     URL: https://github.com/RobTillaart/MAX14661
//

// - initial version has only support for opening and closing channels 
//   by means of the direct access register.
// - no support for shadow registers 


#include "Arduino.h"
#include "Wire.h"

#define MAX14661_LIB_VERSION     (F("0.1.0"))


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
  // - keeps A and B line in sync, ideal for an I2C bus
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


  //
  // SHADOW INTERFACE
  //
  // TODO reg 0x10 ..0x13
  //
  // openShadow(channel)
  // closeShadow(channel)
  // sync () - reg 14 / 15 10001


  //
  // MUX INTERFACE
  // - allows only one channel simultaneously
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
  uint8_t  readRegister(uint8_t reg);
  int      writeRegister(uint8_t reg, uint8_t value);
  int      lastError();

private:
  uint8_t  _address;
  TwoWire* _wire;
  
  int      _error;


  
// cache direct registers?
};





// -- END OF FILE -- 
