#pragma once
//
//    FILE: PCA9634.h
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-03
// VERSION: 0.4.1
// PURPOSE: Arduino library for PCA9634 I2C LED driver, 8 channel
//     URL: https://github.com/RobTillaart/PCA9634


#include "Arduino.h"
#include "Wire.h"


#define PCA9634_LIB_VERSION         (F("0.4.1"))


//  mode codes
#define PCA963X_MODE1               0x00
#define PCA963X_MODE2               0x01


//  0x80 bit ==> Auto-Increment for all registers.
//               used in writeN() - see issue #9
#define PCA963X_PWM(x)              (0x82+(x))
#define PCA963X_GRPPWM              0x0A
#define PCA963X_GRPFREQ             0x0B


//  check datasheet for details
#define PCA963X_LEDOUT_BASE         0x0C  //  0x0C..0x0D
#define PCA963X_LEDOFF              0x00  //  default @ startup
#define PCA963X_LEDON               0x01
#define PCA963X_LEDPWM              0x02
#define PCA963X_LEDGRPPWM           0x03


//  Error codes
#define PCA963X_OK                  0x00
#define PCA963X_ERROR               0xFF
#define PCA963X_ERR_WRITE           0xFE
#define PCA963X_ERR_CHAN            0xFD
#define PCA963X_ERR_MODE            0xFC
#define PCA963X_ERR_REG             0xFB
#define PCA963X_ERR_I2C             0xFA


//  Configuration bits MODE1 register
#define PCA963X_MODE1_AUTOINCR2     0x80  //  ReadOnly,  0 = disable  1 = enable
#define PCA963X_MODE1_AUTOINCR1     0x40  //  ReadOnly,  bit1
#define PCA963X_MODE1_AUTOINCR0     0x20  //  ReadOnly,  bit0
#define PCA963X_MODE1_SLEEP         0x10  //  0 = normal       1 = sleep
#define PCA963X_MODE1_SUB1          0x08  //  0 = disable      1 = enable
#define PCA963X_MODE1_SUB2          0x04  //  0 = disable      1 = enable
#define PCA963X_MODE1_SUB3          0x02  //  0 = disable      1 = enable
#define PCA963X_MODE1_ALLCALL       0x01  //  0 = disable      1 = enable
#define PCA963X_MODE1_NONE          0x00


//  Configuration bits MODE2 register
#define PCA963X_MODE2_BLINK         0x20  //  0 = dim          1 = blink
#define PCA963X_MODE2_INVERT        0x10  //  0 = normal       1 = inverted
#define PCA963X_MODE2_ACK           0x08  //  0 = on STOP      1 = on ACK
#define PCA963X_MODE2_TOTEMPOLE     0x04  //  0 = open drain   1 = totem-pole
#define PCA963X_MODE2_NONE          0x00


//  Registers in which the ALLCALL and sub-addresses are stored
#define PCA963X_SUBADR(x)           (0x0D +(x))  //  x = 1..3
#define PCA963X_ALLCALLADR          0x11


//  Standard ALLCALL and sub-addresses --> only work for write commands and NOT for read commands
#define PCA963X_ALLCALL             0x70  //  TDS of chip says 0xE0, however,
                                          //  in this library the LSB is added during the write command
                                          //                 (0xE0 --> 0b11100000, 0x70 --> 0b1110000)
#define PCA963X_SUB1                0x71  //  see line above (0xE2 --> 0x71)
#define PCA963X_SUB2                0x72  //  see line above (0xE4 --> 0x72)
#define PCA963X_SUB3                0x74  //  see line above (0xE8 --> 0x74)



class PCA9634
{
public:
  explicit PCA9634(const uint8_t deviceAddress, TwoWire *wire = &Wire);

  bool     begin(uint8_t mode1_mask = PCA963X_MODE1_ALLCALL,
                 uint8_t mode2_mask = PCA963X_MODE2_NONE);
  bool     isConnected();
  uint8_t  getAddress();


  /////////////////////////////////////////////////////
  //
  //  CONFIGURATION
  //
  uint8_t  configure(uint8_t mode1_mask, uint8_t mode2_mask);
  uint8_t  channelCount();


  /////////////////////////////////////////////////////
  //
  //  LED DRIVER MODE
  //
  uint8_t  setLedDriverModeAll(uint8_t mode);
  uint8_t  setLedDriverMode(uint8_t channel, uint8_t mode);
  uint8_t  getLedDriverMode(uint8_t channel);


  /////////////////////////////////////////////////////
  //
  //  WRITE MODE REGISTERS
  //
  //  values == masks see defines above
  //  check datasheet for detailed meaning
  uint8_t  setMode1(uint8_t value);
  uint8_t  setMode2(uint8_t value);
  uint8_t  getMode1();
  uint8_t  getMode2();


  /////////////////////////////////////////////////////
  //
  //  GROUP REGISTERS
  //
  uint8_t  setGroupPWM(uint8_t value);
  uint8_t  getGroupPWM();
  uint8_t  setGroupFREQ(uint8_t value);
  uint8_t  getGroupFREQ();


  /////////////////////////////////////////////////////
  //
  //  WRITE
  //
  //  write single PWM registers
  uint8_t  write1(uint8_t channel, uint8_t value);

  //  write three consecutive PWM registers, RGB setting
  uint8_t  write3(uint8_t channel, uint8_t R, uint8_t G, uint8_t B);

  //  generic worker, write N consecutive PWM registers
  uint8_t  writeN(uint8_t channel, uint8_t * arr, uint8_t count);

  //  array at least 8 elements
  uint8_t  writeAll(uint8_t * arr);  
  uint8_t  allOff();

  //  generic worker, write N consecutive PWM registers without Stop command
  uint8_t  writeN_noStop(uint8_t channel, uint8_t * arr, uint8_t count);

  //  write stop command to end transmission
  uint8_t  writeStop();


  /////////////////////////////////////////////////////
  //
  //  SUB CALL
  //
  //  nr = { 1, 2, 3 }
  bool     enableSubCall(uint8_t nr);
  bool     disableSubCall(uint8_t nr);
  bool     isEnabledSubCall(uint8_t nr);
  bool     setSubCallAddress(uint8_t nr, uint8_t address);
  uint8_t  getSubCallAddress(uint8_t nr);
  //
  //  ALL CALL
  //
  bool     enableAllCall();
  bool     disableAllCall();
  bool     isEnabledAllCall();
  bool     setAllCallAddress(uint8_t address);
  uint8_t  getAllCallAddress();


  /////////////////////////////////////////////////////
  //
  //  OE - Output Enable control
  //
  bool     setOutputEnablePin(uint8_t pin);
  bool     setOutputEnable(bool on);
  uint8_t  getOutputEnable();


  /////////////////////////////////////////////////////
  //
  //  EXPERIMENTAL
  //
  //  0.2.2
  //  method = 0 or 1  See implementation
  int I2C_SoftwareReset(uint8_t method);
  //  0.2.7
  //  writing reg 12-13  LEDOUT
  //  reg   LEDS
  //  0     0..3
  //  1     4..7
  uint8_t  writeLedOut(uint8_t reg, uint8_t mask);
  uint8_t  readLedOut(uint8_t reg);


  /////////////////////////////////////////////////////
  //
  //  ERROR
  //
  //  note error flag is reset after read!
  int      lastError();


  /////////////////////////////////////////////////////
  //
  //  OBSOLETE future
  //
  [[deprecated("Use setLedDriverModeAll(mode) instead")]]
  uint8_t  setLedDriverMode(uint8_t mode);

  [[deprecated("use setMode1(value) or setMode2(value) instead")]]
  uint8_t  writeMode(uint8_t reg, uint8_t value);
  uint8_t  readMode(uint8_t reg);


private:
  //  DIRECT CONTROL
  uint8_t  writeRegister(uint8_t reg, uint8_t value);  //  returns error status.
  uint8_t  readRegister(uint8_t reg);

  uint8_t  _address;
  TwoWire * _wire;
  int      _error = PCA963X_OK;
  uint8_t  _channelCount = 8;
  uint8_t  _OutputEnablePin;
};


//  -- END OF FILE --

