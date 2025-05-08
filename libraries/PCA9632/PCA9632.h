#pragma once
//
//    FILE: PCA9632.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-25
// VERSION: 0.1.1
// PURPOSE: Arduino library for PCA9632 and PCA9633 I2C 8 bit PWM LED driver, 4 channel.
//     URL: https://github.com/RobTillaart/PCA9632


#include "Arduino.h"
#include "Wire.h"


#define PCA9632_LIB_VERSION         (F("0.1.1"))

//  REGISTERS PCA9632
#define PCA9632_MODE1               0x00
#define PCA9632_MODE2               0x01
#define PCA9632_PWM0                0x02
#define PCA9632_PWM1                0x03
#define PCA9632_PWM2                0x04
#define PCA9632_PWM3                0x05
#define PCA9632_GRPPWM              0x06
#define PCA9632_GRPFREQ             0x07

#define PCA9632_LEDOUT              0x08
#define PCA9632_SUBADR1             0x09
#define PCA9632_SUBADR2             0x0A
#define PCA9632_SUBADR3             0x0B
#define PCA9632_SUBADR(x)           (0x08 +(x))  //  x = 0..3
#define PCA9632_ALLCALLADR          0x0C


//  ERROR CODES - compatible with PCA9634
#define PCA9632_OK                  0x00
#define PCA9632_ERROR               0xFF
#define PCA9632_ERR_WRITE           0xFE
#define PCA9632_ERR_CHAN            0xFD
#define PCA9632_ERR_MODE            0xFC
#define PCA9632_ERR_REG             0xFB
#define PCA9632_ERR_I2C             0xFA


//  Configuration bits MODE1 REGISTER
#define PCA9632_MODE1_AUTOINCR2     0x80  //  ReadOnly,  0 = disable  1 = enable
#define PCA9632_MODE1_AUTOINCR1     0x40  //  ReadOnly,  bit1
#define PCA9632_MODE1_AUTOINCR0     0x20  //  ReadOnly,  bit0
#define PCA9632_MODE1_SLEEP         0x10  //  0 = normal       1 = sleep
#define PCA9632_MODE1_SUB1          0x08  //  0 = disable      1 = enable
#define PCA9632_MODE1_SUB2          0x04  //  0 = disable      1 = enable
#define PCA9632_MODE1_SUB3          0x02  //  0 = disable      1 = enable
#define PCA9632_MODE1_ALLCALL       0x01  //  0 = disable      1 = enable
#define PCA9632_MODE1_NONE          0x00
#define PCA9632_MODE1_DEFAULT       0x81


//  Configuration bits MODE2 REGISTER
#define PCA9632_MODE2_BLINK         0x20  //  0 = dim          1 = blink
#define PCA9632_MODE2_INVERT        0x10  //  0 = normal       1 = inverted
#define PCA9632_MODE2_ACK           0x08  //  0 = on STOP      1 = on ACK
#define PCA9632_MODE2_TOTEMPOLE     0x04  //  0 = open drain   1 = totem-pole
#define PCA9632_MODE2_NONE          0x00
#define PCA9632_MODE2_DEFAULT       0x02  //  fix #2

//  modi for LEDOUT REGISTER (4x shifted))
#define PCA9632_LEDOFF              0x00  //  default @ startup
#define PCA9632_LEDON               0x01
#define PCA9632_LEDPWM              0x02
#define PCA9632_LEDGRPPWM           0x03



class PCA9632
{
public:
  explicit PCA9632(const uint8_t deviceAddress, TwoWire *wire = &Wire);

  bool     begin(uint8_t mode1_mask = PCA9632_MODE1_DEFAULT,
                 uint8_t mode2_mask = PCA9632_MODE2_DEFAULT);
  bool     isConnected();
  uint8_t  getAddress();


  /////////////////////////////////////////////////////
  //
  //  CONFIGURATION
  //
  uint8_t  channelCount();


  /////////////////////////////////////////////////////
  //
  //  WRITE MODE REGISTERS
  //
  uint8_t setMode1(uint8_t value);
  uint8_t setMode2(uint8_t value);
  uint8_t getMode1();
  uint8_t getMode2();


  /////////////////////////////////////////////////////
  //
  //  GROUP REGISTERS
  //
  uint8_t setGroupPWM(uint8_t value);
  uint8_t getGroupPWM();
  uint8_t setGroupFREQ(uint8_t value);
  uint8_t getGroupFREQ();


  /////////////////////////////////////////////////////
  //
  //  WRITE
  //
  //  write single PWM registers
  uint8_t  writeR(uint8_t R);
  uint8_t  writeG(uint8_t G);
  uint8_t  writeB(uint8_t B);
  uint8_t  writeW(uint8_t W);
  //  if not thinking in RGBW but in channels 0..3
  uint8_t  write(uint8_t channel, uint8_t value);

  //  RGBW setting, write four PWM registers, last has default to get "writeRGB()"
  uint8_t  write(uint8_t R, uint8_t G, uint8_t B, uint8_t W = 0);
  uint8_t  write(uint8_t * arr);  //  array of at least 4 elements.
  uint8_t  allOff();


  /////////////////////////////////////////////////////
  //
  //  SUB CALL
  //  not tested yet, synced from PCA9634
  //
  //  nr = { 1, 2, 3 }
  bool    enableSubCall(uint8_t nr);
  bool    disableSubCall(uint8_t nr);
  bool    isEnabledSubCall(uint8_t nr);
  bool    setSubCallAddress(uint8_t nr, uint8_t address);
  uint8_t getSubCallAddress(uint8_t nr);
  //
  //  ALL CALL
  //  not tested yet, synced from PCA9634
  //
  bool    enableAllCall();
  bool    disableAllCall();
  bool    isEnabledAllCall();
  bool    setAllCallAddress(uint8_t address);
  uint8_t getAllCallAddress();


  /////////////////////////////////////////////////////
  //
  //  LED DRIVER MODE REGISTERS
  //
  uint8_t setLedDriverModeAll(uint8_t mode);
  uint8_t setLedDriverMode(uint8_t channel, uint8_t mode);
  uint8_t getLedDriverMode(uint8_t channel);


  /////////////////////////////////////////////////////
  //
  //  ERROR
  //
  //  note error flag is reset after read!
  int      lastError();


protected:
  //  DIRECT CONTROL
  uint8_t  writeRegister(uint8_t reg, uint8_t value);  //  returns error status.
  uint8_t  readRegister(uint8_t reg);

  uint8_t _address;
  TwoWire * _wire;
  int     _error = PCA9632_OK;
};



/////////////////////////////////////////////////////
//
//  DERIVED CLASS PCA9633
//
class PCA9633 : public PCA9632
{
public:
  PCA9633(const uint8_t deviceAddress, TwoWire *wire = &Wire);
};


//  -- END OF FILE --

