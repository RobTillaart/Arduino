#pragma once
//
//    FILE: M5SWITCH8.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2026-06-16
// PURPOSE: Arduino library for the I2C M5 SWITCH8 and BUTTON8 devices.
//     URL: https://github.com/RobTillaart/M5SWITCH8
//          https://docs.m5stack.com/en/unit/Unit%20ByteSwitch


#include "Arduino.h"
#include "Wire.h"


#define M5SWITCH8_LIB_VERSION         (F("0.1.2"))

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
  //  switch = 0..7; returns 255 if out of range 0 / 1 otherwise.
  uint8_t  readSwitch(uint8_t sw);

  //       LED
  //       led = 0..8
  void     setBrightnessAll(uint8_t value);
  void     setBrightness(uint8_t led, uint8_t value);
  uint8_t  getBrightness(uint8_t led);

  //  manual mode = 0 
  //  system mode = 1 (all non-zero => 1)
  void     setMode(uint8_t mode);
  uint8_t  getMode();
  
  //  manual mode
  void     setColor(uint8_t led, uint32_t bgr);
  void     setColorRGB(uint8_t led, uint8_t R, uint8_t G, uint8_t B);
  //  to test (should return BGR)
  uint32_t getColor(uint8_t led);
  //  fast colour setting, reduced colour range.
  void     setColor233(uint8_t led, uint8_t value);
  uint8_t  getColor233(uint8_t led);

  //  system mode == follows switch / button automatically
  //  user still needs to read the status of the switches / buttons.
  void     setOffColor(uint8_t led, uint32_t bgr);
  uint32_t getOffColor(uint8_t led);
  void     setOnColor(uint8_t led, uint32_t bgr);
  uint32_t getOnColor(uint8_t led);

  //       INTERRUPTS
  //       see readme.md
  void     enableInterrupts();
  void     disableInterrupts();
  uint8_t  isEnabled();

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
  //  button = 0..7; returns 255 if out of range 0 / 1 otherwise.
  inline uint8_t readButton(uint8_t button)
  {
    return readSwitch(button);
  };
  inline bool isPressed(uint8_t button)
  {
    return (readSwitch(button) == 0);
  };

};

//  -- END OF FILE --





