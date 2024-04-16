#pragma once
//
//    FILE: DAC8571.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-04-16
// VERSION: 0.1.0
// PURPOSE: Arduino library for DAC8571 I2C 16 bit DAC.
//     URL: https://github.com/RobTillaart/DAC8571


#include "Arduino.h"
#include "Wire.h"


#define DAC8571_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
#define DAC8571_OK                  0x00
#define DAC8571_I2C_ERROR           0x81
#define DAC8571_ADDRESS_ERROR       0x82
#define DAC8571_BUFFER_ERROR        0x83


//  WRITE MODI
#define DAC8571_MODE_STORE_CACHE    0x00
#define DAC8571_MODE_NORMAL         0x01
#define DAC8571_MODE_WRITE_CACHE    0x02
#define DAC8571_MODE_BRCAST_0       0x03     //  not supported.
#define DAC8571_MODE_BRCAST_1       0x04     //  not supported.
#define DAC8571_MODE_BRCAST_2       0x05     //  not supported.


//  VALUES
#define DAC8571_VALUE_MIN           0x0000
#define DAC8571_VALUE_MIDDLE        0x8000
#define DAC8571_VALUE_MAX           0xFFFF


class DAC8571
{
public:
  explicit DAC8571(uint8_t address = 0x4C, TwoWire *wire = &Wire);

  //       set initial value for DAC, default 0
  bool     begin(uint16_t value = 0);
  bool     isConnected();
  //       convenience
  uint8_t  getAddress();

  //       DAC
  bool     write(uint16_t value = 0);  //  returns true on success.
  uint16_t lastWrite();   //  returns last successful write from cache.
  uint16_t read();        //  returns last successful write from device.

  //       length is max 6 (depends on internal I2C BUFFER; to be investigated)
  //       to be used to do a fast pulse or ramp up.
  bool     write(uint16_t * arr, uint8_t length);  //  returns true on success.

  //       MODE (see defines above)
  void     setWriteMode(uint8_t mode = DAC8571_MODE_NORMAL);
  uint8_t  getWriteMode();  // 0..4  from last write (cached)

  //       POWER DOWN
  void     powerDown(uint8_t pMode = 0);  //  default PD mode
  void     wakeUp(uint16_t value = 0);    //  wake up, default with value zero.

  //       ERROR HANDLING
  int      lastError();


protected:
  uint8_t  _address;
  uint8_t  _control;
  uint16_t _dac;
  int      _error;

  TwoWire* _wire;
};


//  -- END OF FILE --

