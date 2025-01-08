#pragma once
//
//    FILE: DAC8574.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-11
// VERSION: 0.1.1
// PURPOSE: Arduino library for DAC8574, I2C, 4 channel, 16 bit DAC.
//     URL: https://github.com/RobTillaart/DAC8574


#include "Arduino.h"
#include "Wire.h"

#define DAC8574_LIB_VERSION         (F("0.1.1"))

//  ERROR CODES
#define DAC8574_OK                  0x00
#define DAC8574_I2C_ERROR           0x81
#define DAC8574_ADDRESS_ERROR       0x82
#define DAC8574_BUFFER_ERROR        0x83
#define DAC8574_CHANNEL_ERROR       0x84


//  WRITE MODI
#define DAC8574_MODE_STORE_CACHE    0x00
#define DAC8574_MODE_NORMAL         0x01
#define DAC8574_MODE_WRITE_CACHE    0x02
//  broadcast modes need more investigation
#define DAC8574_MODE_BRCAST_0       0x03     //  not supported.
#define DAC8574_MODE_BRCAST_1       0x04     //  not supported.
#define DAC8574_MODE_BRCAST_2       0x05     //  not supported.


//  DAC VALUES (percentages)
#define DAC8574_VALUE_00            0x0000
#define DAC8574_VALUE_25            0x4000
#define DAC8574_VALUE_50            0x8000
#define DAC8574_VALUE_75            0xC000
#define DAC8574_VALUE_100           0xFFFF


//  POWER DOWN MODI
#define DAC8574_PD_LOW_POWER        0x00
#define DAC8574_PD_1_KOHM           0x01
#define DAC8574_PD_100_KOHM         0x02
#define DAC8574_PD_HI_Z             0x03


class DAC8574
{
public:
  explicit DAC8574(uint8_t address = 0x4C, TwoWire *wire = &Wire);

  //       set initial value for DAC, default 0
  bool     begin(uint16_t value = DAC8574_VALUE_00);
  bool     isConnected();
  //       convenience
  uint8_t  getAddress();

  //       DAC
  bool     write(uint8_t channel, uint16_t value);  //  returns true on success.
  uint16_t lastWrite(uint8_t channel);   //  returns last successful write from cache.
  uint16_t read(uint8_t channel);        //  returns last successful write from device.

  //       length is max 14 (depends on internal I2C BUFFER; to be investigated)
  //       to be used to do a fast pulse or ramp up.
  bool     write(uint8_t channel, uint16_t * arr, uint8_t length);  //  returns true on success.

  //       PERCENTAGE WRAPPER
  bool     setPercentage(uint8_t channel, float percentage);
  float    getPercentage(uint8_t channel);

  //       WRITE MODE (see defines above)
  void     setWriteMode(uint8_t mode = DAC8574_MODE_NORMAL);
  uint8_t  getWriteMode();  // 0..4  from last write (cached)

  //       EXTENDED ADDRESS (A2 A3 pin)
  bool     setExtendedAddress(uint8_t A2A3);  //  0,1,2,3 else false
  uint8_t  getExtendedAddress();  //  returns set value, default 00

  //       POWER DOWN (see defines above)
  bool     powerDown(uint8_t pdMode = DAC8574_PD_LOW_POWER);
  bool     wakeUp(uint8_t channel, uint16_t value = DAC8574_VALUE_00);

  //       ERROR HANDLING (see defines above)
  int      lastError();


protected:
  uint8_t  _address;
  uint8_t  _maxChannel;
  uint8_t  _control;
  uint16_t _dac[4];
  int      _error;

  TwoWire* _wire;
};


//  -- END OF FILE --

