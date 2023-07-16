#pragma once
//
//    FILE: PCA9553.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-16
// VERSION: 0.1.0
// PUPROSE: Arduino library for for I2C PCA9553 4 channel PWM
//     URL: https://github.com/RobTillaart/PCA9553


#include "Arduino.h"
#include "Wire.h"


#define PCA9553_LIB_VERSION         (F("0.1.0"))


//  REGISTERS
#define PCA9553_INPUT       0x00
#define PCA9553_PSC0        0x01
#define PCA9553_PWM0        0x02
#define PCA9553_PSC1        0x03
#define PCA9553_PWM1        0x04
#define PCA9553_LS0         0x05


//  LED SOURCE MASKS
//  TODO


//  ERROR CODES
#define PCA9553_OK          0x00
#define PCA9553_ERROR       0xFF
#define PCA9553_ERR_WRITE   0xFE
#define PCA9553_ERR_CHAN    0xFD
#define PCA9553_ERR_MODE    0xFC
#define PCA9553_ERR_REG     0xFB
#define PCA9553_ERR_I2C     0xFA


/////////////////////////////////////////////////////
//
//  CLASS
//
class PCA9553
{
public:
  explicit PCA9553(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(int sda, int scl);
#endif
  bool     begin();
  bool     isConnected();

  uint8_t  channelCount();

  //  input register, only lower 4 bits
  uint8_t  getInput();


  //  PRESCALERS
  void     setPrescaler0(uint8_t psc = 255);
  uint8_t  getPrescaler0();

  void     setPrescaler1(uint8_t psc = 255);
  uint8_t  getPrescaler1();


  //  PWM
  void     setPWM0(uint8_t pwm = 128);
  uint8_t  getPWM0();

  void     setPWM1(uint8_t pwm = 128);
  uint8_t  getPWM1();


  //  LED SOURCE SELECTOR
  //  led = 0..3

  //  source:
  //    00 = output is set LOW (LED on)
  //    01 = output is set high-impedance (LED off; default)
  //    10 = output blinks at PWM0 rate
  //    11 = output blinks at PWM1 rate
  bool     setLEDSource(uint8_t led, uint8_t source);
  uint8_t  getLEDSource(uint8_t led);


private:
  uint8_t  writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);

  uint8_t  _address;
  uint8_t  _error;
  TwoWire* _wire;
};


//  -- END OF FILE --

