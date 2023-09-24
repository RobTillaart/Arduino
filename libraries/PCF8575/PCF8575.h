#pragma once
//
//    FILE: PCF8575.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-20
// VERSION: 0.1.10
// PURPOSE: Arduino library for PCF8575 - 16 channel I2C IO expander
//     URL: https://github.com/RobTillaart/PCF8575


#include "Arduino.h"
#include "Wire.h"


#define PCF8575_LIB_VERSION      (F("0.1.10"))


#ifndef PCF8575_INITIAL_VALUE
#define PCF8575_INITIAL_VALUE    0xFFFF
#endif

#define PCF8575_OK               0x00
#define PCF8575_PIN_ERROR        0x81
#define PCF8575_I2C_ERROR        0x82


class PCF8575
{
public:
  //  deviceAddress base = 0x20 + depends on address bits
  explicit PCF8575(const uint8_t deviceAddress = 0x20, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(int sda, int scl, uint16_t value = PCF8575_INITIAL_VALUE);
#endif
  bool     begin(uint16_t value = PCF8575_INITIAL_VALUE);
  bool     isConnected();


  //  note: setting the address may corrupt internal buffer values
  //  a read16() / write16() call updates them.
  bool     setAddress(const uint8_t deviceAddress);
  uint8_t  getAddress();


  uint16_t read16();
  uint8_t  read(uint8_t pin);
  uint16_t value();


  void     write16(const uint16_t value);
  void     write(const uint8_t pin, const uint8_t value);
  uint16_t valueOut();


  //  added 0.1.07/08 Septillion
  uint16_t readButton16();
  uint16_t readButton16(const uint16_t mask);
  uint8_t  readButton(const uint8_t pin);
  void     setButtonMask(uint16_t mask);
  uint16_t getButtonMask();


  //  rotate, shift, toggle, reverse expect all lines are output
  void     toggle(const uint8_t pin);
  void     toggleMask(const uint16_t mask = 0xFFFF);  //  0xFFFF == invertAll()
  void     shiftRight(const uint8_t n = 1);
  void     shiftLeft(const uint8_t n = 1);
  void     rotateRight(const uint8_t n = 1);
  void     rotateLeft(const uint8_t n = 1);
  void     reverse();


  void     select(const uint8_t pin);
  void     selectN(const uint8_t pin);
  void     selectNone();
  void     selectAll();


  int      lastError();


private:
  uint8_t  _address;
  uint16_t _dataIn;
  uint16_t _dataOut;
  uint16_t _buttonMask;
  int      _error;

  TwoWire*  _wire;
};


//  -- END OF FILE --

