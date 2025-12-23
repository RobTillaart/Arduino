#pragma once
//
//    FILE: LC7822.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-12-20
// VERSION: 0.2.0
// PURPOSE: Arduino library for the LC7822 8 channel analogue switch.
//     URL: https://github.com/RobTillaart/LC7822


#include "Arduino.h"

#define LC7822_LIB_VERSION                (F("0.2.0"))


//  base class
class LC782X
{
public:
  LC782X(uint8_t dataPin, uint8_t clockPin, uint8_t cePin,
          uint8_t sPin = 255, uint8_t resetPin = 255);

  bool    begin(uint8_t address);
  bool    reset();
  uint8_t getAddress() { return _address; };

  bool    setAll(uint8_t value);
  uint8_t getAll();
  bool    setSwitch(uint8_t sw, bool val);
  bool    getSwitch(uint8_t sw);

  //  tune timing
  void    setMicroDelay(uint8_t udel) { _microDelay = udel; };
  uint8_t getMicroDelay() { return _microDelay; };


protected:
  uint8_t _address;
  uint8_t _dataPin;
  uint8_t _clockPin;
  uint8_t _cePin;
  uint8_t _sPin;
  uint8_t _resetPin;

  uint8_t _switches   = 0;  //  default all off
  uint8_t _microDelay = 5;

  void    _updateDevice();
};



///////////////////////////////////////////
//
//  DERIVED
//
class LC7821 : public LC782X
{
public:
  LC7821(uint8_t dataPin, uint8_t clockPin, uint8_t cePin,
          uint8_t sPin = 255, uint8_t resetPin = 255);
  bool begin(uint8_t address = 0x0B);
};


class LC7822 : public LC782X
{
public:
  LC7822(uint8_t dataPin, uint8_t clockPin, uint8_t cePin,
          uint8_t sPin = 255, uint8_t resetPin = 255);
  bool begin(uint8_t address = 0x0D);
};


class LC7823 : public LC782X
{
public:
  LC7823(uint8_t dataPin, uint8_t clockPin, uint8_t cePin,
          uint8_t sPin = 255, uint8_t resetPin = 255);
  bool begin(uint8_t address = 0x0F);
};



//  -- END OF FILE --





