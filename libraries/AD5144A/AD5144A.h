#pragma once
//
//    FILE: AD5144A.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.7
// PURPOSE: I2C digital PotentioMeter AD5144A
//    DATE: 2021-04-30
//     URL: https://github.com/RobTillaart/AD5144A
//
//  Datasheet: REV-C  7/2019

#include "Arduino.h"
#include "Wire.h"


#define AD51XXA_VERSION           (F("0.1.7"))


#define AD51XXA_OK                0
#define AD51XXA_ERROR             100
#define AD51XXA_INVALID_POT       101
#define AD51XXA_INVALID_VALUE     102


class AD51XX
{
public:
  explicit AD51XX(const uint8_t address, TwoWire *wire = &Wire);

  //  default the reset function will be called in begin(), 
  //  by setting doReset to false one can skip this explicitly.
#if defined (ESP8266) || defined(ESP32)
  bool    begin(int dataPin, int clockPin, bool doReset = true);
#endif
  bool    begin(bool doReset = true);
  bool    isConnected();

  uint8_t reset();

  //  BASE functions
  //  rdac = 0..3  - zero based indexing...
  uint8_t write(const uint8_t rdac, const uint8_t value);
  //  fast read from cache
  uint8_t read(const uint8_t rdac) { return _lastValue[rdac]; };


  //  EEPROM functions
  //  defines power up value; copies between RDAC and EEPROM
  uint8_t storeEEPROM(const uint8_t rdac);
  uint8_t storeEEPROM(const uint8_t rdac, const uint8_t value);
  uint8_t recallEEPROM(const uint8_t rdac);


  //  ASYNC functions
  uint8_t writeAll(const uint8_t value);  // set all channels to same value
  uint8_t zeroAll()     { return writeAll(0); };
  uint8_t midScaleAll() { return writeAll((_maxValue + 1)/2); };
  uint8_t maxAll()      { return writeAll(_maxValue); };
  uint8_t zero(const uint8_t rdac)      { return write(rdac, 0); };
  uint8_t midScale(const uint8_t rdac)  { return write(rdac,  (_maxValue + 1)/2); };
  uint8_t mid(const uint8_t rdac)       { return midScale(rdac); };    // will be obsolete
  uint8_t maxValue(const uint8_t rdac)  { return write(rdac,  _maxValue); };


  //  page 27
  uint8_t setTopScale(const uint8_t rdac);
  uint8_t clrTopScale(const uint8_t rdac);
  uint8_t setTopScaleAll();
  uint8_t clrTopScaleAll();
  uint8_t setBottomScale(const uint8_t rdac);
  uint8_t clrBottomScale(const uint8_t rdac);
  uint8_t setBottomScaleAll();
  uint8_t clrBottomScaleAll();


  //  page 27-28
  uint8_t setLinearMode(const uint8_t rdac);
  uint8_t setPotentiometerMode(const uint8_t rdac);
  //  0 = potentiometer, 1 = linear
  uint8_t getOperationalMode(const uint8_t rdac);

  uint8_t incrementLinear(const uint8_t rdac);
  uint8_t incrementLinearAll();
  uint8_t decrementLineair(const uint8_t rdac);
  uint8_t decrementLineairAll();
  uint8_t increment6dB(const uint8_t rdac);
  uint8_t increment6dBAll();
  uint8_t decrement6dB(const uint8_t rdac);
  uint8_t decrement6dBAll();


  //  SYNC functions
  //  preload registers to change all channels synchronous
  uint8_t preload(const uint8_t rdac, const uint8_t value);
  uint8_t preloadAll(const uint8_t value);
  //  copy the preloads to the channels. The bit mask indicates which channels
  //  b00001101 would indicate channel 0, 2 and 3;
  //  sync should not have a default mask as one doesn't know which preloads 
  //  are set and which not.
  uint8_t sync(const uint8_t mask);


  //  MISC
  uint8_t pmCount()  { return _potCount; };
  uint8_t maxValue() { return _maxValue; };
  uint8_t shutDown();


  //  returns the value from internal registers.
  uint8_t readBackINPUT(const uint8_t rdac)   { return readBack(rdac, 0x00); };
  uint8_t readBackEEPROM(const uint8_t rdac)  { return readBack(rdac, 0x01); };
  uint8_t readBackCONTROL(const uint8_t rdac) { return readBack(rdac, 0x02); };
  uint8_t readBackRDAC(const uint8_t rdac)    { return readBack(rdac, 0x03); };


  //  USE WITH CARE - READ DATASHEET
  //  write to control register
  //
  //  value :       0                   1
  //  bit 0 : FREEZE RDAC's       normal operation
  //  bit 1 : EEPROM DISABLED     normal operation
  //  bit 2 : normal operation    LINEAR GAIN MODE
  //  bit 3 : normal operation    BURST MODE
  //
  uint8_t writeControlRegister(uint8_t mask);
  //  TODO separate get set functions ?
  //  uint8_t writeControlRegisterBit(uint8_t mask);


protected:
  uint8_t _potCount = 4;    // unknown, default max
  uint8_t _maxValue = 255;  // unknown, default max


private:
  uint8_t send(const uint8_t cmd, const uint8_t value);
  uint8_t readBack(const uint8_t rdac, const uint8_t mask);

  uint8_t _address;
  uint8_t _lastValue[4];

  TwoWire*  _wire;
};


//////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class AD5123 : public AD51XX
{
public:
  AD5123(const uint8_t address, TwoWire *wire = &Wire);
};


class AD5124 : public AD51XX
{
public:
  AD5124(const uint8_t address, TwoWire *wire = &Wire);
};


class AD5143 : public AD51XX
{
public:
  AD5143(const uint8_t address, TwoWire *wire = &Wire);
};


class AD5144 : public AD51XX
{
public:
  AD5144(const uint8_t address, TwoWire *wire = &Wire);
};


class AD5144A : public AD51XX
{
public:
  AD5144A(const uint8_t address, TwoWire *wire = &Wire);
};


class AD5122A : public AD51XX
{
public:
  AD5122A(const uint8_t address, TwoWire *wire = &Wire);
};


class AD5142A : public AD51XX
{
public:
  AD5142A(const uint8_t address, TwoWire *wire = &Wire);
};


class AD5121 : public AD51XX
{
public:
  AD5121(const uint8_t address, TwoWire *wire = &Wire);
};


class AD5141 : public AD51XX
{
public:
  AD5141(const uint8_t address, TwoWire *wire = &Wire);
};


// -- END OF FILE --
