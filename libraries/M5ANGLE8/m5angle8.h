#pragma once
//
//    FILE: m5angle8.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library for M58ANGLE 8x12 bit potentiometers
//     URL: https://github.com/RobTillaart/M5ANGLE8


#include "Arduino.h"
#include "Wire.h"

#define M5ANGLE8_LIB_VERSION          (F("0.3.0"))

#define M5ANGLE8_DEFAULT_ADDRESS      0x43

//  prelim error handling
#define M5ANGLE8_OK                   0x0000
#define M5ANGLE8_ERR_CHANNEL          0xFF00
#define M5ANGLE8_ERROR                0xFFFF


class M5ANGLE8
{
public:
  M5ANGLE8(uint8_t address = M5ANGLE8_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();

  //  address = 8..119 (NXP spec)
  bool    setAddress(uint8_t address = M5ANGLE8_DEFAULT_ADDRESS);
  uint8_t getAddress();
  uint8_t getVersion();


  //  ANALOGREAD PART
  //  channel    = 0..7
  //  resolution = 1..12 (max 0..4095)
  uint16_t analogRead(uint8_t channel, uint8_t resolution = 12);
  //  reverse potentiometers range
  //  false = 0..n
  //  true  = n..0
  void     setReverse(bool reverse);
  bool     getReverse();
  //  maps the analogRead upon 0..steps-1 steps.
  uint16_t selectorRead(uint8_t channel, uint8_t steps);


  //  INPUT SWITCH PART
  uint8_t  inputSwitch();


  //  LED PART
  //  channel    = 0..7
  //  R,G,B      = 0..255
  //  brightness = 0..100 (will be constrained).
  bool     writeRGB(uint8_t channel, uint8_t R, uint8_t G, uint8_t B, uint8_t brightness);
  bool     setAll(uint8_t R, uint8_t G, uint8_t B, uint8_t brightness);
  bool     allOff();

  bool     writeBrightness(uint8_t channel, uint8_t brightness);


private:
  uint8_t  _address;
  bool     _reverse;
  int      _error;

  TwoWire* _wire;

  bool     write8(uint8_t reg, uint8_t value);
  uint8_t  read8(uint8_t reg);
  uint16_t read16(uint8_t reg);
  bool     write32(uint8_t reg, uint8_t R, uint8_t G, uint8_t B, uint8_t brightness);

};


//  -- END OF FILE --
