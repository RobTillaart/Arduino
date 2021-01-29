#pragma once
//
//    FILE: PCF8591.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-03-12
// VERSION: 0.1.1
// PURPOSE: I2C PCF8591 library for Arduino
//     URL: https://github.com/RobTillaart/PCF8591
//
// HISTORY:
// see PCF8591.cpp file
//


#include "Arduino.h"
#include "Wire.h"


#define PCF8591_LIB_VERSION       (F("0.1.1"))

#define PCF8591_OK                0x00
#define PCF8591_PIN_ERROR         0x81
#define PCF8591_I2C_ERROR         0x82
#define PCF8591_MODE_ERROR        0x83
#define PCF8591_CHANNEL_ERROR     0x84
#define PCF8591_ADDRESS_ERROR     0x85


// INTERNAL USE ONLY
#define PCF8591_DAC_FLAG          0x40
#define PCF8591_INCR_FLAG         0x04

class PCF8591
{
public:
  explicit PCF8591(const uint8_t address = 0x48, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(uint8_t sda, uint8_t scl, uint8_t val = 0);
#endif
  bool     begin(uint8_t val = 0);

  bool     isConnected();

  // ADC PART
  // auto increment not tested ==> use with care!
  void     enableINCR()     { _control |= PCF8591_INCR_FLAG; };
  void     disableINCR()    { _control &= ~PCF8591_INCR_FLAG; };
  bool     isINCREnabled()  { return ((_control & PCF8591_INCR_FLAG) > 0); };

  uint8_t  analogRead(uint8_t channel, uint8_t mode = 0);
  uint8_t  analogRead4();  // returns PCF8591_OK or error code.
  uint8_t  lastRead(uint8_t channel) { return _adc[channel]; };

  // DAC PART
  void     enableDAC()      { _control |= PCF8591_DAC_FLAG; };
  void     disableDAC()     { _control &= ~PCF8591_DAC_FLAG; };
  bool     isDACEnabled()   { return ((_control & PCF8591_DAC_FLAG) > 0); };

  bool     analogWrite(uint8_t value = 0);       // returns true on success.
  uint8_t  lastWrite()      { return _dac; };    // last successful write

  int      lastError();

private:
  uint8_t  _address;
  uint8_t  _control;
  uint8_t  _dac;
  uint8_t  _adc[4];
  int      _error;
  
  TwoWire* _wire;
};

// END OF FILE
