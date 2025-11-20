#pragma once
//    FILE: INA260.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2025-02-18
// PURPOSE: Arduino library for INA260 power sensor
//     URL: https://github.com/RobTillaart/INA260
//
//  Read the datasheet for the details


#include "Arduino.h"
#include "Wire.h"


#define INA260_LIB_VERSION                (F("0.1.2"))


//  set by setAlertRegister
#define INA260_SHUNT_OVER_CURRENT         0x8000
#define INA260_SHUNT_UNDER_CURRENT        0x4000
#define INA260_BUS_OVER_VOLTAGE           0x2000
#define INA260_BUS_UNDER_VOLTAGE          0x1000
#define INA260_POWER_OVER_LIMIT           0x0800
#define INA260_CONVERSION_READY           0x0400


//  returned by getAlertRegister
#define INA260_ALERT_FUNCTION_FLAG        0x0010
#define INA260_CONVERSION_READY_FLAG      0x0008
#define INA260_MATH_OVERFLOW_FLAG         0x0004
#define INA260_ALERT_POLARITY_FLAG        0x0002
#define INA260_ALERT_LATCH_ENABLE_FLAG    0x0001


// //  returned by setMaxCurrentShunt
// #define INA260_ERR_NONE                   0x0000
// #define INA260_ERR_SHUNTVOLTAGE_HIGH      0x8000
// #define INA260_ERR_MAXCURRENT_LOW         0x8001
// #define INA260_ERR_SHUNT_LOW              0x8002
// #define INA260_ERR_NORMALIZE_FAILED       0x8003


#define INA260_MAX_WAIT_MS                600   //  millis


//  for setAverage() and getAverage()
enum INA260_average_enum {
    INA260_1_SAMPLE     = 0,
    INA260_4_SAMPLES    = 1,
    INA260_16_SAMPLES   = 2,
    INA260_64_SAMPLES   = 3,
    INA260_128_SAMPLES  = 4,
    INA260_256_SAMPLES  = 5,
    INA260_512_SAMPLES  = 6,
    INA260_1024_SAMPLES = 7
};


//  for BVCT and SVCT conversion timing.
enum INA260_timing_enum {
    INA260_140_us  = 0,
    INA260_204_us  = 1,
    INA260_332_us  = 2,
    INA260_588_us  = 3,
    INA260_1100_us = 4,
    INA260_2100_us = 5,
    INA260_4200_us = 6,
    INA260_8300_us = 7
};


//  ALERT Pin Polarity definition
enum ina260_alert_pin_polarity_enum {
    INA226_ACTIVE_LOW  = 0,
    INA226_ACTIVE_HIGH = 1
};


//  ALERT Pin Latch definition
enum ina260_alert_latch_enum {
    INA226_LATCH_TRANSPARENT = 0,
    INA226_LATCH_ENABLED     = 1
};


class INA260
{
public:
  //  address between 0x40 and 0x4F
  explicit INA260(const uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  Core functions
  float    getBusVoltage();       //  Volt
  float    getShuntVoltage();     //  Volt
  float    getCurrent();          //  Ampere
  float    getPower();            //  Watt
  //  See #35
  bool     isConversionReady();   //  conversion ready flag is set.
  bool     waitConversionReady(uint32_t timeout = INA260_MAX_WAIT_MS);


  //  Scale helpers milli range
  float    getBusVoltage_mV()   { return getBusVoltage()   * 1e3; };
  float    getShuntVoltage_mV() { return getShuntVoltage() * 1e3; };
  float    getCurrent_mA()      { return getCurrent()      * 1e3; };
  float    getPower_mW()        { return getPower()        * 1e3; };
  //  Scale helpers micro range
  float    getBusVoltage_uV()   { return getBusVoltage()   * 1e6; };
  float    getShuntVoltage_uV() { return getShuntVoltage() * 1e6; };
  float    getCurrent_uA()      { return getCurrent()      * 1e6; };
  float    getPower_uW()        { return getPower()        * 1e6; };


  //  Configuration
  bool     reset();
  bool     setAverage(uint8_t avg = INA260_1_SAMPLE);
  uint8_t  getAverage();
  bool     setBusVoltageConversionTime(uint8_t bvct = INA260_1100_us);
  uint8_t  getBusVoltageConversionTime();
  bool     setShuntCurrentConversionTime(uint8_t scct = INA260_1100_us);
  uint8_t  getShuntCurrentConversionTime();


  //  Calibration
  //  The INA260 has a fixed shunt of 2 mOhm and can do 15 Amps.
  //  so it cannot be calibrated.
  float    getCurrentLSB()    { return _current_LSB;       };
  float    getCurrentLSB_mA() { return _current_LSB * 1e3; };
  float    getCurrentLSB_uA() { return _current_LSB * 1e6; };
  float    getShunt()         { return _shunt;             };
  float    getMaxCurrent()    { return _maxCurrent;        };


  //  Operating mode  (TODO slightly diff)
  bool     setMode(uint8_t mode = 7);  //  default ModeShuntBusContinuous
  uint8_t  getMode();
  bool     shutDown()                  { return setMode(0); };
  bool     setModeShuntTrigger()       { return setMode(1); };
  bool     setModeBusTrigger()         { return setMode(2); };
  bool     setModeShuntBusTrigger()    { return setMode(3); };
  bool     setModeShuntContinuous()    { return setMode(5); };
  bool     setModeBusContinuous()      { return setMode(6); };
  bool     setModeShuntBusContinuous() { return setMode(7); };  //  default.


  //  ALERT REGISTER
  //  (not tested)
  bool     setAlertRegister(uint16_t mask);
  uint16_t getAlertRegister();
  bool     setAlertLatchEnable(bool latch = false);
  bool     getAlertLatchEnable();
  bool     setAlertPolarity(bool inverted = false);
  bool     getAlertPolarity();

  //  ALERT LIMIT
  //  (not tested)
  bool     setAlertLimit(uint16_t limit);
  uint16_t getAlertLimit();


  //  Meta information
  //
  //                               typical value
  uint16_t getManufacturerID();  //  0x5449
  uint16_t getDieID();           //  0x2270


  //  DEBUG
  uint16_t getRegister(uint8_t reg) { return _readRegister(reg); };

  //
  //  ERROR HANDLING
  //
  int      getLastError();


  //  OBSOLETE
  [[deprecated("Use getAlertRegister()")]]
  uint16_t getAlertFlag();


private:

  uint16_t _readRegister(uint8_t reg);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);

  const float _current_LSB = 1.25e-3;  //  mA
  const float _shunt       = 0.002;    //  Ohm
  const float _maxCurrent  = 15.0;     //  Ampere

  uint8_t   _address;
  TwoWire * _wire;

  int       _error;
};


//  -- END OF FILE --

