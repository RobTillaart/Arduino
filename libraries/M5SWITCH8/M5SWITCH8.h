#pragma once
//
//    FILE: M5SWITCH8.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-06-16
// PURPOSE: Arduino library for the I2C M5 SWITCH8 and BUTTON8 devices.
//     URL: https://github.com/RobTillaart/M5SWITCH8
//          https://docs.m5stack.com/en/unit/Unit%20ByteSwitch


#include "Arduino.h"
#include "Wire.h"


#define M5SWITCH8_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
constexpr int M5SWITCH8_OK            = 0;
constexpr int M5SWITCH8_NO_DATA       = -1;
constexpr int M5SWITCH8_REQUEST_ERROR = -2;


class M5SWITCH8
{
public:
  M5SWITCH8(uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //       READ
  uint8_t  readAll();
  //  switch = 0..7
  uint8_t  readSwitch(uint8_t sw);

  //       LED
  //  led = 0..8
  void     setBrightness(uint8_t led, uint8_t value);
  uint8_t  getBrightness(uint8_t led);

  //  mode = 0 => manual
  //  mode = 1 => system (automatic)
  void     setMode(uint8_t mode);
  uint8_t  getMode();
  
  //  manual define
  void     setColor(uint8_t led, uint32_t bgr);
  uint32_t getColor(uint8_t led);

  //  system define (follows switch automatically)
  void     setOffColor(uint8_t led, uint32_t bgr);
  uint32_t getOffColor(uint8_t led);
  void     setOnColor(uint8_t led, uint32_t bgr);
  uint32_t getOnColor(uint8_t led);


  //       INTERRUPTS
  void     enableInterrupts();
  void     disableInterrupts();
  uint8_t  isEnabled();  //  name ?

  //       MISCELLANEOUS
  void     writeToFlash();
  uint8_t  getFirmwareVersion();
  void     setAddress(uint8_t addr);

  //       DEBUG
  int      getLastError();


protected:
  uint8_t  _address;
  TwoWire* _wire;

  int      _command(uint8_t reg, uint8_t value);
  int      _command(uint8_t reg, uint8_t * arr, uint8_t size);
  int      _request(uint8_t reg, uint8_t * arr, uint8_t size);

  uint8_t  _error;
};


//////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
class M5BUTTON8 : public M5SWITCH8
{
  public:
  M5BUTTON8(uint8_t address, TwoWire *wire = &Wire) :
  M5SWITCH8(address, wire)
  {
  };

};

//  -- END OF FILE --





