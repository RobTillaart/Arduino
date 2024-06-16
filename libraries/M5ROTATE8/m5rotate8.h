#pragma once
//
//    FILE: m5rotate8.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: Arduino library for M5 8ROTATE 8x rotary encoders
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "Arduino.h"
#include "Wire.h"

#define M5ROTATE8_LIB_VERSION          (F("0.4.0"))

#define M5ROTATE8_DEFAULT_ADDRESS      0x41

//  prelim error handling
#define M5ROTATE8_OK                   0x0000
#define M5ROTATE8_ERR_CHANNEL          0xFF00
#define M5ROTATE8_ERROR                0xFFFF


class M5ROTATE8
{
public:
  M5ROTATE8(uint8_t address = M5ROTATE8_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();

  //       META
  bool     setAddress(uint8_t address = M5ROTATE8_DEFAULT_ADDRESS);
  uint8_t  getAddress();
  uint8_t  getVersion();

  //       ROTARY ENCODER PART
  //       channel = 0..7
  int32_t  getAbsCounter(uint8_t channel);
  bool     setAbsCounter(uint8_t channel, int32_t value);
  int32_t  getRelCounter(uint8_t channel);
  bool     getKeyPressed(uint8_t channel);
  bool     resetCounter(uint8_t channel);
  void     resetAll();

  //       INPUT SWITCH PART
  uint8_t  inputSwitch();

  //       LED PART
  //       channel = 0..7
  //       R,G,B   = 0..255
  bool     writeRGB(uint8_t channel, uint8_t R, uint8_t G, uint8_t B);
  uint32_t readRGB(uint8_t channel);
  bool     setAll(uint8_t R, uint8_t G, uint8_t B);
  bool     allOff();


  //       FIRMWARE V2 functions (to be verified)
  //       use getVersion() to check.
  //       channel = 0..7
  //       value   = 0..255
  //       register 0x58..0x5F
  bool     setButtonToggleCount(uint8_t channel, uint8_t value = 0);
  uint8_t  getButtonToggleCount(uint8_t channel);
  //       register 0x61, 0x62
  //       0 = no change, 1 = changed
  uint8_t  getEncoderChangeMask();
  //       0 = not pressed, 1 = pressed (inverted the datasheetV2 specification)
  //       seems to be more logical.
  uint8_t  getButtonChangeMask();


private:
  uint8_t  _address;

  int      _error;

  TwoWire* _wire;

  bool     write8(uint8_t reg, uint8_t value);
  uint8_t  read8(uint8_t reg);

  bool     write24(uint8_t reg, uint8_t R, uint8_t G, uint8_t B);
  uint32_t read24(uint8_t reg);

  bool     write32(uint8_t reg, uint32_t value);
  uint32_t read32(uint8_t reg);
};


//  -- END OF FILE --
