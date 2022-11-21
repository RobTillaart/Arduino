#pragma once
//
//    FILE: PCF8591.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-03-12
// VERSION: 0.1.3
// PURPOSE: I2C PCF8591 library for Arduino
//     URL: https://github.com/RobTillaart/PCF8591


#include "Arduino.h"
#include "Wire.h"


#define PCF8591_LIB_VERSION             (F("0.1.3"))

#define PCF8591_OK                      0x00
#define PCF8591_PIN_ERROR               0x81
#define PCF8591_I2C_ERROR               0x82
#define PCF8591_MODE_ERROR              0x83
#define PCF8591_CHANNEL_ERROR           0x84
#define PCF8591_ADDRESS_ERROR           0x85


class PCF8591
{
public:
  explicit PCF8591(const uint8_t address = 0x48, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(uint8_t sda, uint8_t scl, uint8_t value = 0);
#endif
  bool     begin(uint8_t value = 0);

  bool     isConnected();


  //       ADC PART
  //       auto increment not tested ==> use with care!
  void     enableINCR();
  void     disableINCR();
  bool     isINCREnabled();

  //       analogRead() returns the value.
  uint8_t  analogRead(uint8_t channel, uint8_t mode = 0); 
  //       analogRead4() returns PCF8591_OK or an error code.  
  uint8_t  analogRead4();  
  //       access the 4 channels read with analogRead4()
  uint8_t  lastRead(uint8_t channel);


  //       DAC PART
  void     enableDAC();
  void     disableDAC();
  bool     isDACEnabled();

  bool     analogWrite(uint8_t value = 0);  //  returns true on success.
  uint8_t  lastWrite();                     //  returns last successful write

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

