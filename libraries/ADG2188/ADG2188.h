#pragma once
//
//    FILE: ADG2188.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-28
// VERSION: 0.2.0
// PURPOSE: Arduino library for ADG2188 8x8 (cross-point) matrix switch with I2C.
//     URL: https://github.com/RobTillaart/ADG2188
//


#include "Arduino.h"
#include "Wire.h"


#define ADG2188_LIB_VERSION             (F("0.2.0"))

#define ADG2188_DEFAULT_ADDRESS         0x70

//  ERROR CODES
//  values <> 0 are errors.
#define ADG2188_OK                      0x00
#define ADG2188_CRC_ERROR               0x80
#define ADG2188_NOT_READY               0x81
#define ADG2188_REQUEST_ERROR           0x82
#define ADG2188_ADDRESS_ERROR           0x83


class ADG2188
{
public:
  ADG2188(uint8_t address = ADG2188_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  SWITCH
  //  row == X = 0..7, column == Y = 0..7
  bool     on(uint8_t row, uint8_t column);
  bool     off(uint8_t row, uint8_t column);
  bool     isOn(uint8_t row, uint8_t column);
  //  get multi status in a bit mask
  uint8_t  isOnRow(uint8_t row);        //  get a whole row at once as bit mask.
  //  uint16_t isOnColumn(uint8_t column);  //  get a whole column at once as bit mask.

  //  WRAPPERS
  //  e.g  switch 29 ==> row (X) = 3  column (Y) = 5
  bool     on(uint8_t sw)   { return on(sw / 8, sw % 8); };
  bool     off(uint8_t sw)  { return off(sw / 8, sw % 8); };
  uint8_t  isOn(uint8_t sw) { return isOn(sw / 8, sw % 8); };


  //  MODE
  //  default direct (transparent) mode
  void     setDirectMode();
  void     setLatchMode();
  bool     isLatchedMode();
  bool     isDirectMode();


  //       RESET
  void     setResetPin(uint8_t resetPin);
  //       reset ==> all switches off, registers ==> 0.
  void     pulseResetPin();


  //       DEBUG
  int      getLastError();


private:
  uint8_t  _address;
  TwoWire* _wire;

  int      _send(uint8_t pins, uint8_t value);
  int      _readback(uint8_t row);

  int      _error;
  uint8_t  _mode;
  uint8_t  _reset;
};


//  -- END OF FILE --





