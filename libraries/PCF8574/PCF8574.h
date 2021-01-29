#pragma once
//
//    FILE: PCF8574.H
//  AUTHOR: Rob Tillaart
//    DATE: 02-febr-2013
// VERSION: 0.3.0
// PURPOSE: Arduino library for PCF8574 - 8 channel I2C IO expander
//     URL: https://github.com/RobTillaart/PCF8574
//          http://forum.arduino.cc/index.php?topic=184800
//
// HISTORY:
// see PCF8574.cpp file
//

#include "Arduino.h"
#include "Wire.h"

#define PCF8574_LIB_VERSION     (F("0.3.0"))

#ifndef PCF8574_INITIAL_VALUE
#define PCF8574_INITIAL_VALUE    0xFF
#endif

#define PCF8574_OK              0x00
#define PCF8574_PIN_ERROR       0x81
#define PCF8574_I2C_ERROR       0x82


class PCF8574
{
public:
  explicit PCF8574(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool    begin(uint8_t sda, uint8_t scl, uint8_t val = PCF8574_INITIAL_VALUE);
#endif
  bool    begin(uint8_t val = PCF8574_INITIAL_VALUE);
  bool    isConnected();

  uint8_t read8();
  uint8_t read(uint8_t pin);
  uint8_t value() const { return _dataIn; };

  void    write8(const uint8_t value);
  void    write(const uint8_t pin, const uint8_t value);
  uint8_t valueOut() const { return _dataOut; }

  //added 0.1.07/08 Septillion
  inline uint8_t readButton8()  { return PCF8574::readButton8(_buttonMask); }
  uint8_t        readButton8(const uint8_t mask);
  uint8_t        readButton(const uint8_t pin);
  inline void    setButtonMask(uint8_t mask) { _buttonMask = mask; };

  // rotate, shift, toggle, reverse expect all lines are output
  void    toggle(const uint8_t pin);
  void    toggleMask(const uint8_t mask = 0xFF);    // default 0xFF ==> invertAll()
  void    shiftRight(const uint8_t n = 1);
  void    shiftLeft(const uint8_t n = 1);
  void    rotateRight(const uint8_t n = 1);
  void    rotateLeft(const uint8_t n = 1);
  void    reverse();

  int     lastError();

private:
  uint8_t _address;
  uint8_t _dataIn;
  uint8_t _dataOut;
  uint8_t _buttonMask;
  int     _error;

  TwoWire*  _wire;
};

// -- END OF FILE --
