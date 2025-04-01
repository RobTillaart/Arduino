#pragma once
//
//    FILE: PCA9671.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-03-16
// VERSION: 0.1.2
// PURPOSE: Arduino library for the PCA9671 and PCA9673, I2C 16-bit I/O expander.
//     URL: https://github.com/RobTillaart/PCA9671
//          https://github.com/RobTillaart/PCF8575
//
//  The PCA9671 is a pin compatible replacement for the PCF8575
//  so the API is 100% based upon the PCF8575 library.
//  the only difference is that the interrupt pin is
//  replaced by an external reset pin.


#include "Arduino.h"
#include "Wire.h"


#define PCA9671_LIB_VERSION         (F("0.1.2"))


#ifndef PCA9671_INITIAL_VALUE
#define PCA9671_INITIAL_VALUE       0xFFFF
#endif


//  ERROR CODES
//  values <> 0 are errors.
#define PCA9671_OK                  0x00
#define PCA9671_PIN_ERROR           0x81
#define PCA9671_I2C_ERROR           0x82


class PCA9671
{
public:
  PCA9671(uint8_t address, TwoWire *wire = &Wire);

  bool     begin(uint16_t value = PCA9671_INITIAL_VALUE);
  bool     isConnected();


  //  note: setting the address may corrupt internal buffer values
  //        and should not be used unless it is needed.
  //  a read16() / write16() call updates them.
  bool     setAddress(const uint8_t deviceAddress);
  uint8_t  getAddress();


  //       READ
  uint16_t read16();
  uint8_t  read(const uint8_t pin);
  uint16_t value();


  //       WRITE
  void     write16(const uint16_t value);
  void     write(const uint8_t pin, const uint8_t value);
  uint16_t valueOut();


  //       READ BUTTON
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


  //       SELECT
  void     select(const uint8_t pin);
  void     selectN(const uint8_t pin);
  void     selectNone();
  void     selectAll();

  //       MISCELLANEOUS
  int      lastError();
  uint32_t deviceID();


private:
  uint8_t  _address;
  uint16_t _dataIn;
  uint16_t _dataOut;
  uint16_t _buttonMask;
  int      _error;

  TwoWire*  _wire;
};


////////////////////////////////////////////////////////
//
//  DERIVED PCA9673
//
class PCA9673 : public PCA9671
{
public:
  PCA9673(uint8_t address, TwoWire *wire = &Wire);
};


//  -- END OF FILE --





