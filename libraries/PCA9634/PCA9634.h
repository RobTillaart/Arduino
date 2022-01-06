#pragma once
//
//    FILE: PCA9634.h
//  AUTHOR: Rob Tillaart
//    DATE: 03-01-2022
// VERSION: 0.1.1
// PURPOSE: Arduino library for PCA9634 I2C LED driver, 8 channel
//     URL: https://github.com/RobTillaart/PCA9634


#include "Arduino.h"
#include "Wire.h"


#define PCA9634_LIB_VERSION         (F("0.1.1"))

#define PCA9634_MODE1               0x00
#define PCA9634_MODE2               0x01
#define PCA9634_PWM(x)              (0x82+(x))    // Auto-Increment for all registers.

#define PCA9634_GRPPWM              0x0A
#define PCA9634_GRPFREQ             0x0B

// check datasheet for details
#define PCA9634_LEDOUT_BASE         0x0C    // 0x0C..0x0D
#define PCA9634_LEDOFF              0x00    // default @ startup
#define PCA9634_LEDON               0x01
#define PCA9634_LEDPWM              0x02
#define PCA9634_LEDGRPPWM           0x03

//  Error codes
#define PCA9634_OK                  0x00
#define PCA9634_ERROR               0xFF
#define PCA9634_ERR_WRITE           0xFE
#define PCA9634_ERR_CHAN            0xFD
#define PCA9634_ERR_MODE            0xFC
#define PCA9634_ERR_REG             0xFB
#define PCA9634_ERR_I2C             0xFA

// NOT IMPLEMENTED YET
#define PCA9634_SUBADR(x)           (0x0E +(x))  // x = 1..3
#define PCA9634_ALLCALLADR          0x11


class PCA9634
{
public:
  explicit PCA9634(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(uint8_t sda, uint8_t scl);
#endif
  bool     begin();
  void     reset();
  bool     isConnected();

  uint8_t  channelCount() { return _channelCount; };

  uint8_t  setLedDriverMode(uint8_t channel, uint8_t mode);
  uint8_t  getLedDriverMode(uint8_t channel);

  // single PWM setting
  uint8_t  write1(uint8_t channel, uint8_t value);
  
  // RGB setting, write three consecutive PWM registers
  uint8_t  write3(uint8_t channel, uint8_t R, uint8_t G, uint8_t B);
  
  // generic worker, write N consecutive PWM registers
  uint8_t  writeN(uint8_t channel, uint8_t* arr, uint8_t count);

  // reg = 1, 2  check datasheet for values
  uint8_t  writeMode(uint8_t reg, uint8_t value);
  uint8_t  readMode(uint8_t reg);

  // TODO PWM also in %% ?
  void     setGroupPWM(uint8_t value) { writeReg(PCA9634_GRPPWM, value); }
  uint8_t  getGroupPWM() { return readReg(PCA9634_GRPPWM); }

  // TODO set time in milliseconds and round to nearest value?
  void     setGroupFREQ(uint8_t value) { writeReg(PCA9634_GRPFREQ, value); }
  uint8_t  getGroupFREQ() { return readReg(PCA9634_GRPFREQ); }

  int      lastError();

private:
  // DIRECT CONTROL
  uint8_t  writeReg(uint8_t reg, uint8_t value);  // returns error status.
  uint8_t  readReg(uint8_t reg);

  uint8_t  _address;
  uint8_t  _register;
  uint8_t  _data;
  int      _error;
  uint8_t  _channelCount = 8;

  TwoWire*  _wire;
};


// -- END OF FILE --

