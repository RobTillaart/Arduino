#pragma once
//
//    FILE: PCA9685.h
//  AUTHOR: Rob Tillaart
//    DATE: 24-apr-2016
// VERSION: 0.7.1
// PURPOSE: Arduino library for PCA9685 I2C LED driver, 16 channel PWM, 12 bit.
//     URL: https://github.com/RobTillaart/PCA9685_RT


#include "Arduino.h"
#include "Wire.h"


#define PCA9685_LIB_VERSION         (F("0.7.1"))

// ERROR CODES
#define PCA9685_OK                  0x00
#define PCA9685_ERROR               0xFF
#define PCA9685_ERR_CHANNEL         0xFE
#define PCA9685_ERR_MODE            0xFD
#define PCA9685_ERR_I2C             0xFC

//  get/setFrequency()
#define PCA9685_MIN_FREQ              24
#define PCA9685_MAX_FREQ            1526


//  REGISTERS CONFIGURATION - check datasheet for details
#define PCA9685_MODE1               0x00
#define PCA9685_MODE2               0x01

//  Configuration bits MODE1 register
#define PCA9685_MODE1_RESTART       0x80  //  0 = disable      1 = enable
#define PCA9685_MODE1_EXTCLK        0x40  //  0 = internal     1 = external (datasheet)
#define PCA9685_MODE1_AUTOINCR      0x20  //  0 = disable      1 = enable
#define PCA9685_MODE1_SLEEP         0x10  //  0 = normal       1 = sleep
#define PCA9685_MODE1_SUB1          0x08  //  0 = disable      1 = enable
#define PCA9685_MODE1_SUB2          0x04  //  0 = disable      1 = enable
#define PCA9685_MODE1_SUB3          0x02  //  0 = disable      1 = enable
#define PCA9685_MODE1_ALLCALL       0x01  //  0 = disable      1 = enable
#define PCA9685_MODE1_NONE          0x00

//  Configuration bits MODE2 register
#define PCA9685_MODE2_INVERT        0x10  //  0 = normal       1 = inverted
#define PCA9685_MODE2_ACK           0x08  //  0 = on STOP      1 = on ACK
#define PCA9685_MODE2_TOTEMPOLE     0x04  //  0 = open drain   1 = totem-pole
#define PCA9685_MODE2_OUTNE         0x03  //  datasheet
#define PCA9685_MODE2_NONE          0x00

//  (since 0.4.0)
#define PCA9685_SUBADR(x)           (0x01 + (x))  //  x = 1..3
#define PCA9685_ALLCALLADR          0x05

// REGISTERS - CHANNELS
//  0x06 + 4*channel is base per channel
#define PCA9685_CHANNEL_0           0x06
#define PCA9685_CHANNEL(x)          (0x06 + ((x) * 4))  //  x = 0..15

//  REGISTERS - ALL_ON ALL_OFF - partly implemented
#define PCA9685_ALL_ON_L            0xFA
#define PCA9685_ALL_ON_H            0xFB
#define PCA9685_ALL_OFF_L           0xFC
#define PCA9685_ALL_OFF_H           0xFD   //  used for allOFF()

// REGISTERS - FREQUENCY
#define PCA9685_PRE_SCALER          0xFE

//  NOT IMPLEMENTED
//  WARNING: DO NOT USE THIS REGISTER (see datasheet)
#define PCA9685_TESTMODE            0xFF   //  do not be use. see datasheet.



class PCA9685
{
public:
  explicit PCA9685(const uint8_t deviceAddress, TwoWire *wire = &Wire);

  bool     begin(uint8_t mode1_mask = PCA9685_MODE1_AUTOINCR | PCA9685_MODE1_ALLCALL,
                 uint8_t mode2_mask = PCA9685_MODE2_TOTEMPOLE);
  bool     isConnected();
  uint8_t  getAddress();


  /////////////////////////////////////////////////////
  //
  //  CONFIGURATION
  //
  uint8_t  configure(uint8_t mode1_mask, uint8_t mode2_mask);
  uint8_t  channelCount();

  //  reg = 1, 2  check datasheet for values
  uint8_t  writeMode(uint8_t reg, uint8_t value);
  uint8_t  readMode(uint8_t reg);

  //  convenience wrappers
  uint8_t  setMode1(uint8_t value);
  uint8_t  setMode2(uint8_t value);
  uint8_t  getMode1();
  uint8_t  getMode2();


  /////////////////////////////////////////////////////
  //
  //  WRITE / SETPWM
  //
  //  single PWM setting, channel = 0..15,
  //  onTime = 0..4095, offTime = 0..4095
  //  allows shifted PWM's e.g. 2 servo's that do not start at same time.
  //         this will distribute the (peak) load
  void     setPWM(uint8_t channel, uint16_t onTime, uint16_t offTime);
  void     getPWM(uint8_t channel, uint16_t* onTime, uint16_t* offTime);

  // single PWM setting, channel = 0..15, offTime = 0..4095  (onTime = 0)
  void     setPWM(uint8_t channel, uint16_t offTime);


  //  set update frequency for all channels
  //  freq = 24 - 1526 Hz
  //  note: as the frequency is converted to an 8 bit pre-scaler
  //       the frequency set will seldom be exact, but best effort.
  void     setFrequency(uint16_t freq, int offset = 0);
  int      getFrequency(bool cache = true);

  //  set channel  HIGH or LOW (effectively no PWM)
  void     write1(uint8_t channel, uint8_t mode);

  //  for backwards compatibility; will be removed in future
  void     setON(uint8_t channel)   { write1(channel, HIGH); };
  void     setOFF(uint8_t channel)  { write1(channel, LOW); };

  //  experimental for 0.3.0
  void     allOFF();


  /////////////////////////////////////////////////////
  //
  //  SUB CALL  -  ALL CALL  (since 0.4.0)
  //
  //  nr = { 1, 2, 3 }
  bool     enableSubCall(uint8_t nr);
  bool     disableSubCall(uint8_t nr);
  bool     isEnabledSubCall(uint8_t nr);
  bool     setSubCallAddress(uint8_t nr, uint8_t address);
  uint8_t  getSubCallAddress(uint8_t nr);

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
  //  ERROR
  //
  //  note error flag is reset after read!
  int      lastError();


  //  EXPERIMENTAL 0.4.2
  int I2C_SoftwareReset(uint8_t method);  //  0 or 1


private:
  //  DIRECT CONTROL
  void    writeReg(uint8_t reg, uint8_t value);
  void    writeReg2(uint8_t reg, uint16_t a, uint16_t b);
  uint8_t readReg(uint8_t reg);

  uint8_t _address;
  int     _error;
  int     _freq = 200;  //  default PWM frequency - P25 datasheet
  uint8_t _channelCount = 16;
  uint8_t _OutputEnablePin;

  TwoWire*  _wire;
};


//  -- END OF FILE --

