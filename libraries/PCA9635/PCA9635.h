#pragma once
//
//    FILE: PCA9635.H
//  AUTHOR: Rob Tillaart
//    DATE: 23-apr-2016
// VERSION: 0.2.0
// PURPOSE: Arduino library for PCA9635 I2C LED driver
//     URL: https://github.com/RobTillaart/PCA9635
//

#include "Arduino.h"

#define PCA9635_LIB_VERSION "0.2.0"

#define PCA9635_MODE1       0x00
#define PCA9635_MODE2       0x01
#define PCA9635_PWM(x)      (0x82+(x))

#define PCA9635_GRPPWM      0x12
#define PCA9635_GRPFREQ     0x13

// check datasheet for details
#define PCA9635_LEDOUT_BASE 0x14    // 0x14..0x17
#define PCA9635_LEDOFF      0x00    // default @ startup
#define PCA9635_LEDON       0x01
#define PCA9635_LEDPWM      0x02
#define PCA9635_LEDGRPPWM   0x03

#define PCA9635_OK          0x00
#define PCA9635_ERROR       0xFF
#define PCA9635_ERR_WRITE   0xFE
#define PCA9635_ERR_CHAN    0xFD
#define PCA9635_ERR_MODE    0xFC
#define PCA9635_ERR_REG     0xFB
#define PCA9635_ERR_I2C     0xFA

// NOT IMPLEMENTED YET
#define PCA9635_SUBADR(x)   (0x17+(x))  // x = 1..3
#define PCA9635_ALLCALLADR  0x1B

class PCA9635
{
public:
  explicit PCA9635(const uint8_t deviceAddress);

#if defined (ESP8266) || defined(ESP32)
  void    begin(uint8_t sda, uint8_t scl);
#endif
  void    begin();
  void    reset();
  
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
  void     setGroupPWM(uint8_t value) { writeReg(PCA9635_GRPPWM, value); }
  uint8_t  getGroupPWM() { return readReg(PCA9635_GRPPWM); }

  // TODO set time in millisec and round to nearest value?
  void     setGroupFREQ(uint8_t value) { writeReg(PCA9635_GRPFREQ, value); }
  uint8_t  getGroupFREQ() { return readReg(PCA9635_GRPFREQ); }

  int      lastError();

private:
  // DIRECT CONTROL
  void     writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);

  uint8_t  _address;
  uint8_t  _register;
  uint8_t  _data;
  int      _error;
};

// -- END OF FILE --
