#pragma once
//
//    FILE: DS2438.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2023-07-28
// PURPOSE: Arduino Library for DS2438 battery monitor
//     URL: https://github.com/RobTillaart/DS2438
//
//                    DS2438
//               +------------------+
//               | 1  GND           |
//               | 2  Vsense+       |
//               | 3  Vsense-       |
//               | 4  VAD           |
//               | 5  VDD           |
//               | 6  NC            |
//               | 7  NC            |
//               | 8  DQ            |
//               +------------------+
//
//  |  Pin     |  Description                        |  Connect to  |
//  |:--------:|:------------------------------------|:-------------|
//  |  DQ      |  Data In/Out                        |  processor   |
//  |  VAD     |  General A/D input                  |              |
//  |  VSENS+  |  Battery current monitor input (+)  |  Battery     |
//  |  VSENS-  |  Battery current monitor input (-)  |  Battery     |
//  |  VDD     |  Power Supply (2.4V to 10.0V)       |  +5V         |
//  |  GND     |  Ground                             |  processor   |
//  |  NC      |  No connect                         |  -           |


#include "Arduino.h"
#include "OneWire.h"

#define DS2438_LIB_VERSION        (F("0.2.0"))

#define DS2438_INVALID             -999


//  bits configuration register (do not change)
const uint8_t DS2438_CONFIG_IAD = 0;
const uint8_t DS2438_CONFIG_CA  = 1;
const uint8_t DS2438_CONFIG_EE  = 2;
const uint8_t DS2438_CONFIG_AD  = 3;


typedef uint8_t DeviceAddress[8];


class DS2438
{
public:
  DS2438(OneWire * ow);

  bool     begin(uint8_t retries = 3);
  bool     isConnected(uint8_t retries = 3);


  //  TEMPERATURE
  //  unit is degrees Celsius
  float    readTemperature();
  float    getTemperature();


  //  VOLTAGE
  //  enable the AD voltage selector,
  //  read pin 4 as the selected voltage or read VDD as voltage
  void    enableVoltageSelector();
  void    disableVoltageSelector();
  //  unit is Volts
  float    readVDD();
  float    getVDD();  //  from cache
  float    readVAD();
  float    getVAD();  //  from cache


  //  CURRENT
  void     setResistor(float resistor = 0.01);  //  in Ohm
  void     enableCurrentMeasurement();
  void     disableCurrentMeasurement();
  //  unit is Ampere
  float    readCurrent();
  float    getCurrent();  //  from cache
  //  datasheet p.6
  //  to write, measurements must be disabled.
  void     writeCurrentOffset(int value);
  int      readCurrentOffset();


  //  ICA + THRESHOLD
  //  Integrated Current Accumulator.
  float    readRemaining();
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
  uint32_t readDisconnectTime();
  uint32_t readEndOfChargeTime();


  //  EEPROM
  void     writeEEPROM(uint8_t address, uint8_t value);
  uint8_t  readEEPROM(uint8_t address);


  //  CCA / DCA
  //  Charging + Discharge Current Accumulator
  //  unit = mVHr
  void     enableCCA();  //  enables both CCA and DCA
  void     disableCCA();

  //  enable shadow CCA / DCA
  void     enableCCAShadow();
  void     disableCCAShadow();
  //  experimental
  bool     setCCA(float CCA);    //  blocks 10+ ms
  bool     setDCA(float DCA);    //  blocks 10+ ms
  void     resetAccumulators();  //  blocks 10+ ms
  //  read works only meaningful if shadow to EEPROM is enabled.
  float    readCCA();
  float    readDCA();


  //  CONFIG REGISTER
  void     setConfigBit(uint8_t bit);
  void     clearConfigBit(uint8_t bit);
  uint8_t  getConfigRegister();
  //  STATUS
  bool     busy();
  bool     busyTemperature();
  bool     busyNVRAM();
  bool     busyADC();


private:
  OneWire * _oneWire;
  uint8_t  _scratchPad[9];
  uint8_t  _address[8];
  bool     _addressFound;

  float    _temperature;
  float    _vad;
  float    _vdd;
  float    _current;
  float    _inverseR;   //  1/(4096*resistor) optimized.
  float    _RICA;       //  1/(2048*resistor) optimized.

  void     readScratchPad(uint8_t page);
  void     writeScratchPad(uint8_t page);
};


//  -- END OF FILE --

