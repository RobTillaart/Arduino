#pragma once
//
//    FILE: PCF8591.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-03-12
// VERSION: 0.4.0
// PURPOSE: Arduino Library for PCF8591 I2C 4 channel 8 bit ADC + 1 channel 8 bit DAC.
//     URL: https://github.com/RobTillaart/PCF8591


#include "Arduino.h"
#include "Wire.h"


#define PCF8591_LIB_VERSION                 (F("0.4.0"))

#define PCF8591_OK                          0x00
#define PCF8591_PIN_ERROR                   0x81
#define PCF8591_I2C_ERROR                   0x82
#define PCF8591_MODE_ERROR                  0x83
#define PCF8591_CHANNEL_ERROR               0x84
#define PCF8591_ADDRESS_ERROR               0x85

//  datasheet figure 4 page 6
#define PCF8591_FOUR_SINGLE_CHANNEL         0x00  //  default
#define PCF8591_THREE_DIFFERENTIAL          0x01
#define PCF8591_MIXED                       0x02
#define PCF8591_TWO_DIFFERENTIAL            0x03


class PCF8591
{
public:
  explicit PCF8591(uint8_t address = 0x48, TwoWire *wire = &Wire);

  //       set initial value for DAC, default 0
  bool     begin(uint8_t value = 0);
  bool     isConnected();
  uint8_t  getAddress();


  //       ADC PART
  //       auto increment not tested ==> use with care!
  void     enableINCR();
  void     disableINCR();
  bool     isINCREnabled();

  //       read() returns the value.
  //       mode 0 = PCF8591_FOUR_SINGLE_CHANNEL
  uint8_t  read(uint8_t channel, uint8_t mode = 0);
  //       read4() returns PCF8591_OK or an error code.
  uint8_t  read4();
  //       access the 4 channels read with read4()
  uint8_t  lastRead(uint8_t channel);

  //       datasheet par 8.2 figure 4
  //       not for PCF8591_MIXED mode.
  //       comparator calls need testing.
  int      readComparator_01();  //  channel 0  mode 3
  int      readComparator_23();  //  channel 1  mode 3
  int      readComparator_03();  //  channel 0  mode 1
  int      readComparator_13();  //  channel 1  mode 1


  //       DAC PART
  void     enableDAC();
  void     disableDAC();
  bool     isDACEnabled();
  bool     write(uint8_t value = 0);   //  returns true on success.
  uint8_t  lastWrite();                //  returns last successful write

  //       ERROR HANDLING
  int      lastError();


private:
  uint8_t  _address;
  uint8_t  _control;
  uint8_t  _dac;
  uint8_t  _adc[4];
  int      _error;

  TwoWire* _wire;

};


//  -- END OF FILE --

