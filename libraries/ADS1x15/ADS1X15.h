#pragma once
//
//    FILE: ADS1X15.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.1
//    DATE: 2013-03-24
// PURPOSE: Arduino library for ADS1015 and ADS1115
//     URL: https://github.com/RobTillaart/ADS1X15
//


#include "Arduino.h"
#include "Wire.h"

#define ADS1X15_LIB_VERSION               (F("0.4.1"))

//  allow compile time default address
//  address in { 0x48, 0x49, 0x4A, 0x4B }, no test...
#ifndef ADS1015_ADDRESS
#define ADS1015_ADDRESS                   0x48
#endif

#ifndef ADS1115_ADDRESS
#define ADS1115_ADDRESS                   0x48
#endif


#define ADS1X15_OK                        0
#define ADS1X15_INVALID_VOLTAGE           -100
#define ADS1X15_INVALID_GAIN              0xFF
#define ADS1X15_INVALID_MODE              0xFE


class ADS1X15
{
public:
  void     reset();

  bool     begin();
  bool     isConnected();

  //           GAIN
  //  0  =  +- 6.144V  default
  //  1  =  +- 4.096V
  //  2  =  +- 2.048V
  //  4  =  +- 1.024V
  //  8  =  +- 0.512V
  //  16 =  +- 0.256V
  void     setGain(uint8_t gain = 0);    //  invalid values are mapped to 0 (default).
  uint8_t  getGain();                    //  0xFF == invalid gain error.


  //  both may return ADS1X15_INVALID_VOLTAGE if the gain is invalid.
  float    toVoltage(int16_t value = 1); //   converts raw to voltage
  float    getMaxVoltage();              //   -100 == invalid voltage error


  //  0  =  CONTINUOUS
  //  1  =  SINGLE      default
  void     setMode(uint8_t mode = 1);    //  invalid values are mapped to 1 (default)
  uint8_t  getMode();                    //  0xFE == invalid mode error.


  //  0  =  slowest
  //  7  =  fastest
  //  4  =  default
  void     setDataRate(uint8_t dataRate = 4);  //  invalid values are mapped on 4 (default)
  uint8_t  getDataRate();                      //  actual speed depends on device


  int16_t  readADC(uint8_t pin = 0);
  int16_t  readADC_Differential_0_1();

  //  used by continuous mode and async mode.
  [[deprecated("Use getValue() instead")]]
  int16_t  getLastValue() { return getValue(); };  //  will be obsolete in the future 0.4.0
  int16_t  getValue();


  //  ASYNC INTERFACE
  //  requestADC(pin) -> isBusy() or isReady() -> getValue();
  //  see examples
  void     requestADC(uint8_t pin = 0);
  void     requestADC_Differential_0_1();
  bool     isBusy();
  bool     isReady();


  //  returns a pin 0x0[0..3] or 
  //          a differential "mode" 0x[pin second][pin first] or
  //          0xFF (no request / invalid request)
  uint8_t   lastRequest();


  //  COMPARATOR
  //  0    = TRADITIONAL   > high          => on      < low   => off
  //  else = WINDOW        > high or < low => on      between => off
  void     setComparatorMode(uint8_t mode);
  uint8_t  getComparatorMode();

  //  0    = LOW (default)
  //  else = HIGH
  void     setComparatorPolarity(uint8_t pol);
  uint8_t  getComparatorPolarity();

  //  0    = NON LATCH
  //  else = LATCH
  void     setComparatorLatch(uint8_t latch);
  uint8_t  getComparatorLatch();

  //  0   = trigger alert after 1 conversion
  //  1   = trigger alert after 2 conversions
  //  2   = trigger alert after 4 conversions
  //  3   = Disable comparator =  default, also for all other values.
  void     setComparatorQueConvert(uint8_t mode);
  uint8_t  getComparatorQueConvert();

  void     setComparatorThresholdLow(int16_t lo);
  int16_t  getComparatorThresholdLow();
  void     setComparatorThresholdHigh(int16_t hi);
  int16_t  getComparatorThresholdHigh();


  int8_t   getError();

  //  EXPERIMENTAL
  //  see https://github.com/RobTillaart/ADS1X15/issues/22
  void     setWireClock(uint32_t clockSpeed = 100000);
  //  prototype
  //  - getWireClock returns the value set by setWireClock
  //    not necessary the actual value
  uint32_t getWireClock();


protected:
  ADS1X15();

  //  CONFIGURATION
  //  BIT   DESCRIPTION
  //  0     # channels        0 == 1    1 == 4;
  //  1     0
  //  2     # resolution      0 == 12   1 == 16
  //  3     0
  //  4     has gain          0 = NO    1 = YES
  //  5     has comparator    0 = NO    1 = YES
  //  6     0
  //  7     0
  uint8_t  _config;
  uint8_t  _maxPorts;
  uint8_t  _address;
  uint8_t  _conversionDelay;
  uint8_t  _bitShift;
  uint16_t _gain;
  uint16_t _mode;
  uint16_t _datarate;

  //  COMPARATOR variables
  //  TODO merge these into one COMPARATOR MASK?  (low priority)
  //       would speed up code in _requestADC() and save 3 bytes RAM.
  //  TODO boolean flags for first three, or make it mask value that
  //       can be or-ed.   (low priority)
  uint8_t  _compMode;
  uint8_t  _compPol;
  uint8_t  _compLatch;
  uint8_t  _compQueConvert;

  //  variable to track the last pin requested, 
  //  to allow for round robin query of
  //  pins based on this state == if no last request then == 0xFFFF.
  uint16_t  _lastRequest;

  int16_t  _readADC(uint16_t readmode);
  void     _requestADC(uint16_t readmode);
  bool     _writeRegister(uint8_t address, uint8_t reg, uint16_t value);
  uint16_t _readRegister(uint8_t address, uint8_t reg);
  int8_t   _err = ADS1X15_OK;

  TwoWire*  _wire;
  uint32_t  _clockSpeed = 0;
};


///////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES from ADS1X15
//
class ADS1013 : public ADS1X15
{
public:
  ADS1013(uint8_t Address = ADS1015_ADDRESS, TwoWire *wire = &Wire);
};


class ADS1014 : public ADS1X15
{
public:
  ADS1014(uint8_t Address = ADS1015_ADDRESS, TwoWire *wire = &Wire);
};


class ADS1015 : public ADS1X15
{
public:
  ADS1015(uint8_t Address = ADS1015_ADDRESS, TwoWire *wire = &Wire);
  int16_t  readADC_Differential_0_3();
  int16_t  readADC_Differential_1_3();
  int16_t  readADC_Differential_2_3();
  int16_t  readADC_Differential_0_2();   //  not possible in async
  int16_t  readADC_Differential_1_2();   //  not possible in async
  void     requestADC_Differential_0_3();
  void     requestADC_Differential_1_3();
  void     requestADC_Differential_2_3();
};


class ADS1113 : public ADS1X15
{
public:
  ADS1113(uint8_t address = ADS1115_ADDRESS, TwoWire *wire = &Wire);
};


class ADS1114 : public ADS1X15
{
public:
  ADS1114(uint8_t address = ADS1115_ADDRESS, TwoWire *wire = &Wire);
};


class ADS1115 : public ADS1X15
{
public:
  ADS1115(uint8_t address = ADS1115_ADDRESS, TwoWire *wire = &Wire);
  int16_t  readADC_Differential_0_3();
  int16_t  readADC_Differential_1_3();
  int16_t  readADC_Differential_2_3();
  int16_t  readADC_Differential_0_2();   //  not possible in async
  int16_t  readADC_Differential_1_2();   //  not possible in async
  void     requestADC_Differential_0_3();
  void     requestADC_Differential_1_3();
  void     requestADC_Differential_2_3();
};


//  -- END OF FILE --

