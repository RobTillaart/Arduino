#pragma once
//
//    FILE: PCA9698.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-06
// VERSION: 0.1.0
// PURPOSE: Arduino library for the PCA9698 - I2C, 40 channel IO expander.
//     URL: https://github.com/RobTillaart/PCA9698_RT


#include "Arduino.h"
#include "Wire.h"


#define PCA9698_LIB_VERSION         (F("0.1.0"))

#define PCA9698_OK                  0x00
#define PCA9698_PIN_ERROR           0x81
#define PCA9698_I2C_ERROR           0x82
#define PCA9698_BANK_ERROR          0x83


class PCA9698
{
public:
  explicit PCA9698(const uint8_t deviceAddress = 0x20, TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();
  uint8_t getAddress() const { return _address; }


  //
  //  DATA_IO
  //
  //  bank = 0..5
  uint8_t read8(uint8_t bank, uint8_t & bitmask);
  uint8_t write8(uint8_t bank, uint8_t bitmask);
  uint8_t toggle8(uint8_t bank, uint8_t bitmask);

  //  pin  = 0..39
  uint8_t read1(uint8_t pin);
  uint8_t write1(uint8_t pin, uint8_t value);
  uint8_t toggle1(uint8_t pin);

  //  40 interface
  uint8_t read40(uint8_t * buf);
  uint8_t write40(uint8_t * buf);

  //  select
  void    select(uint8_t pin);  //  select single pin
  void    selectN(uint8_t n);   //  select 0..n-1 pins (VU)


  //
  //  POLARITY - datasheet 7.4.3
  //
  //  40 bits at once.
  //  0 bit = NON-INVERTED, 1 bit = INVERTED
  uint8_t setPolarity40(uint8_t * buf);
  uint8_t getPolarity40(uint8_t * buf);
  //
  //  CONFIG - datasheet 7.4.4
  //
  //  40 bits at once.
  //  0 bit = OUTPUT, 1 bit = INPUT
  uint8_t setPinMode40(uint8_t * buf);
  uint8_t getPinMode40(uint8_t * buf);
  //
  //  INTERRUPT - datasheet 7.4.5
  //
  //  40 bits at once.
  //  0 bit = INTERRUPT ON, 1 bit = INTERRUPT OFF
  uint8_t setInterrupt40(uint8_t * buf);
  uint8_t getInterrupt40(uint8_t * buf);


  //
  //  OUTPUT CONFIG - datasheet 7.4.6
  //
  //  see datasheet for details bit mask
  //  set open drain / totem pole per bank
  uint8_t setOutputConfig(uint8_t mask);
  uint8_t getOutputConfig();
  //
  //  ALLBANK - datasheet 7.4.7
  //
  //  see datasheet for details bit mask
  uint8_t setAllBank(uint8_t mask);
  uint8_t getAllBank();
  //
  //  MODE - datasheet 7.4.8
  //
  //  see datasheet for details bit mask
  //  TODO mode bits.
  uint8_t setMode(uint8_t mode);
  uint8_t getMode();
  //
  //  DEVICEID - datasheet 7.5
  //
  //  deviceID == 12 bite manufacturer, 9 bits part, 3 bits revision
  //  TODO test
  uint32_t getDeviceID();


  //
  //  ERROR
  //
  int      lastError();


private:
  int     _error {PCA9698_OK};
  uint8_t _address;

  TwoWire*  _wire;

  uint8_t _read(uint8_t reg, uint8_t & value);
  uint8_t _write(uint8_t reg, uint8_t value);
  uint8_t _read40(uint8_t reg, uint8_t * buf);
  uint8_t _write40(uint8_t reg, uint8_t * buf);
};


//  -- END OF FILE --

