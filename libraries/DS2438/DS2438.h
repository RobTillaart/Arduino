#pragma once
//
//    FILE: DS2438.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-07-28
// PURPOSE: Arduino Library for DS2438 battery monitor
//     URL: https://github.com/RobTillaart/DS2438


#include "Arduino.h"
#include "OneWire.h"

#define DS2438_LIB_VERSION        (F("0.1.0"))

#define DS2438_INVALID             -999


typedef uint8_t DeviceAddress[8];


class DS2438
{
public:
  DS2438(OneWire * ow);

  bool     begin(uint8_t retries = 3);
  bool     isConnected(uint8_t retries = 3);


  //  TEMPERATURE
  float    readTemperature();  //  scratchPad 1 = LSB, 2 = MSB
  float    getTemperature();


  //  VOLTAGE
  float    readVoltage();  //  scratchPad 3 = LSB, 4 = MSB
  float    getVoltage();


  //  CURRENT
  void     setResistor(float resistor = 0.01);  // in OHM
  void     enableCurrentMeasurement();
  void     disableCurrentMeasurement();
  float    readCurrent();  //  scratchPad 5 = LSB, 6 = MSB
  float    getCurrent();


  //  CURRENT OFFSET
  void     writeCurrentOffset(int value);
  int      readCurrentOffset();


  //  THRESHOLD
  void     writeThreshold(uint8_t value);
  uint8_t  readThreshold();

  //     only 4 values used.
  //  |  value  |  THRESHOLD       |
  //  |:-------:|:----------------:|
  //  |  0x00   |  None (default)  |
  //  |  0x40   |  ±2 LSB          |
  //  |  0x80   |  ±4 LSB          |
  //  |  0xC0   |  ±8 LSB          |


  //  TIME
  void     writeElapsedTimeMeter(uint32_t seconds);
  uint32_t readElapsedTimeMeter();


  //  EEPROM
  void     writeEEPROM(uint8_t address, uint8_t value);
  uint8_t  readEEPROM(uint8_t address);


  //  CONFIG REGISTER
  void     setConfigBit(uint8_t bit);
  void     clearConfigBit(uint8_t bit);
  uint8_t  getConfigByte();


private:
  OneWire * _oneWire;
  uint8_t  _scratchPad[9];
  uint8_t  _address[8];
  bool     _addressFound;

  float    _temperature;
  float    _voltage;
  float    _current;
  float    _inverseR;   //  1/(4096*resistor) optimized.

  void     readScratchPad(uint8_t page);
  void     writeScratchPad(uint8_t page);
};


//  -- END OF FILE --

