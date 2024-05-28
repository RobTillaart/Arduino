#pragma once
//    FILE: INA236.h
//  AUTHOR: Rob Tillaart
//          ported from INA226 to INA236 by Josef Tremmel
// VERSION: 0.1.0
//    DATE: 2024-05-27
// PURPOSE: Arduino library for INA236 current and power sensor.
//     URL: https://github.com/RobTillaart/INA236
//
//  Read the datasheet for the details


#include "Arduino.h"
#include "Wire.h"


#define INA236_LIB_VERSION              "0.1.0"


//  set by setAlertRegister
#define INA236_SHUNT_OVER_VOLTAGE         0x8000
#define INA236_SHUNT_UNDER_VOLTAGE        0x4000
#define INA236_BUS_OVER_VOLTAGE           0x2000
#define INA236_BUS_UNDER_VOLTAGE          0x1000
#define INA236_POWER_OVER_LIMIT           0x0800
#define INA236_CONVERSION_READY           0x0400


//  returned by getAlertFlag
#define INA236_ALERT_FUNCTION_FLAG        0x0010
#define INA236_CONVERSION_READY_FLAG      0x0008
#define INA236_MATH_OVERFLOW_FLAG         0x0004
#define INA236_ALERT_POLARITY_FLAG        0x0002
#define INA236_ALERT_LATCH_ENABLE_FLAG    0x0001


//  returned by setMaxCurrentShunt
#define INA236_ERR_NONE                   0x0000
#define INA236_ERR_SHUNTVOLTAGE_HIGH      0x8000
#define INA236_ERR_MAXCURRENT_LOW         0x8001
#define INA236_ERR_SHUNT_LOW              0x8002
#define INA236_ERR_NORMALIZE_FAILED       0x8003

//  See INA226 issue #26
#define INA236_MINIMAL_SHUNT              0.001

#define INA236_MAX_WAIT_MS                600   //  millis


//  for setAverage() and getAverage()
enum ina236_average_enum {
    INA236_1_SAMPLE     = 0,
    INA236_4_SAMPLES    = 1,
    INA236_16_SAMPLES   = 2,
    INA236_64_SAMPLES   = 3,
    INA236_128_SAMPLES  = 4,
    INA236_256_SAMPLES  = 5,
    INA236_512_SAMPLES  = 6,
    INA236_1024_SAMPLES = 7
};


//  for BVCT and SVCT conversion timing.
enum ina236_timing_enum {
    INA236_140_us  = 0,
    INA236_204_us  = 1,
    INA236_332_us  = 2,
    INA236_588_us  = 3,
    INA236_1100_us = 4,
    INA236_2100_us = 5,
    INA236_4200_us = 6,
    INA236_8300_us = 7
};


class INA236
{
public:
  //  address between 0x40 and 0x4F
  explicit INA236(const uint8_t address, TwoWire *wire = &Wire);

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
  bool     waitConversionReady(uint32_t timeout = INA236_MAX_WAIT_MS);


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
  bool     setAverage(uint8_t avg = INA236_1_SAMPLE);
  uint8_t  getAverage();
  bool     setBusVoltageConversionTime(uint8_t bvct = INA236_1100_us);
  uint8_t  getBusVoltageConversionTime();
  bool     setShuntVoltageConversionTime(uint8_t svct = INA236_1100_us);
  uint8_t  getShuntVoltageConversionTime();
  bool     setADCRange(uint8_t adcRange);
  uint8_t  getADCRange();



  //  Calibration
  //  mandatory to set these!
  //  shunt * maxCurrent < 81 mV  (or 20mV depends on ADCrange set)
  //  maxCurrent >= 0.001
  //  shunt      >= 0.001
  int      setMaxCurrentShunt(float maxCurrent = 20.0, float shunt = 0.002, bool normalize = true);
  bool     isCalibrated()     { return _current_LSB != 0.0; };

  //  These functions return zero if not calibrated!
  float    getCurrentLSB()    { return _current_LSB;       };
  float    getCurrentLSB_mA() { return _current_LSB * 1e3; };
  float    getCurrentLSB_uA() { return _current_LSB * 1e6; };
  float    getShunt()         { return _shunt;             };
  float    getMaxCurrent()    { return _maxCurrent;        };


  //  Operating mode
  bool     setMode(uint8_t mode = 7);  //  default ModeShuntBusContinuous
  uint8_t  getMode();
  bool     shutDown()                  { return setMode(0); };
  bool     setModeShuntTrigger()       { return setMode(1); };
  bool     setModeBusTrigger()         { return setMode(2); };
  bool     setModeShuntBusTrigger()    { return setMode(3); };
  bool     setModeShuntContinuous()    { return setMode(5); };
  bool     setModeBusContinuous()      { return setMode(6); };
  bool     setModeShuntBusContinuous() { return setMode(7); };  //  default.


  //  Alert
  //  - separate functions per flag?
  //  - what is a reasonable limit?
  //  - which units to define a limit per mask ?
  //    same as voltage registers ?
  //  - how to test
  bool     setAlertRegister(uint16_t mask);
  uint16_t getAlertFlag();
  bool     setAlertLimit(uint16_t limit);
  uint16_t getAlertLimit();


  //  Meta information
  uint16_t getManufacturerID();   //  should return 0x5449
  uint16_t getDieID();            //  should return 0xA080


  //  DEBUG
  uint16_t getRegister(uint8_t reg)  { return _readRegister(reg); };


private:

  uint16_t _readRegister(uint8_t reg);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);
  float    _current_LSB;
  float    _shunt;
  float    _maxCurrent;
  float    _voltage_LSB;

  uint8_t   _address;
  TwoWire * _wire;
};


//  -- END OF FILE --

