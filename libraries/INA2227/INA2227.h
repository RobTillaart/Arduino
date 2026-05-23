#pragma once
//    FILE: INA2227.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-05-18
// PURPOSE: Arduino library for the INA2227, I2C, 16 bit, dual channel, voltage, current, power and energy sensor.
//     URL: https://github.com/RobTillaart/INA2227
//
//  Read the datasheet for the details


#include "Arduino.h"
#include "Wire.h"

//  WORK IN PROGRESS
//  NOT TESTED WITH HARDWARE
//  FEEDBACK WELCOME


#define INA2227_LIB_VERSION                (F("0.1.0"))


//  set by setAlertRegister
#define INA2227_SHUNT_OVER_VOLTAGE         1
#define INA2227_SHUNT_UNDER_VOLTAGE        2
#define INA2227_BUS_OVER_VOLTAGE           3
#define INA2227_BUS_UNDER_VOLTAGE          4
#define INA2227_POWER_OVER_LIMIT           5


//  returned by setMaxCurrentShunt
#define INA2227_ERR_NONE                   0x0000
#define INA2227_ERR_SHUNTVOLTAGE_HIGH      0x8000
#define INA2227_ERR_MAXCURRENT_LOW         0x8001
#define INA2227_ERR_SHUNT_LOW              0x8002
#define INA2227_ERR_NORMALIZE_FAILED       0x8003
#define INA2227_ERR_CHANNEL_RANGE          0x8004

//  See INA226 issue #26 + INA2227 issue #8
#ifndef INA2227_MINIMAL_SHUNT
#define INA2227_MINIMAL_SHUNT              0.001
#endif

#define INA2227_MAX_WAIT_MS                600   //  millis


//  for setAverage() and getAverage()
enum INA2227_average_enum {
    INA2227_1_SAMPLE     = 0,
    INA2227_4_SAMPLES    = 1,
    INA2227_16_SAMPLES   = 2,
    INA2227_64_SAMPLES   = 3,
    INA2227_128_SAMPLES  = 4,
    INA2227_256_SAMPLES  = 5,
    INA2227_512_SAMPLES  = 6,
    INA2227_1024_SAMPLES = 7
};


//  for BVCT and SVCT conversion timing.
enum INA2227_timing_enum {
    INA2227_140_us  = 0,
    INA2227_204_us  = 1,
    INA2227_332_us  = 2,
    INA2227_588_us  = 3,
    INA2227_1100_us = 4,
    INA2227_2100_us = 5,
    INA2227_4200_us = 6,
    INA2227_8300_us = 7
};


enum INA2227_mode_enum {
    INA2227_MODE_SHUTDOWN       = 0,
    INA2227_MODE_TRIG_BUS       = 1,
    INA2227_MODE_TRIG_SHUNT     = 2,
    INA2227_MODE_TRIG_BUS_SHUNT = 3,
    INA2227_MODE_SHUTDOWN2      = 4,  //  for completeness
    INA2227_MODE_CONT_BUS       = 5,
    INA2227_MODE_CONT_SHUNT     = 6,
    INA2227_MODE_CONT_BUS_SHUNT = 7,
};


class INA2227
{
public:
  //  address between 0x40 and 0x4F
  explicit INA2227(const uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //
  //  CORE FUNCTIONS + scale wrappers.
  //
  //       BUS VOLTAGE
  float    getBusVoltage(uint8_t ch);     //  Volt
  float    getBusVolt(uint8_t ch)         { return getBusVoltage(ch); };
  float    getBusVoltage_mV(uint8_t ch)   { return getBusVoltage(ch) * 1e3; };
  float    getBusVoltage_uV(uint8_t ch)   { return getBusVoltage(ch) * 1e6; };

  //       SHUNT VOLTAGE
  float    getShuntVoltage(uint8_t ch);   //  Volt
  float    getShuntVolt(uint8_t ch)       { return getShuntVoltage(ch); };
  float    getShuntVoltage_mV(uint8_t ch) { return getShuntVoltage(ch) * 1e3; };
  float    getShuntVoltage_uV(uint8_t ch) { return getShuntVoltage(ch) * 1e6; };

  //       SHUNT CURRENT
  float    getCurrent(uint8_t ch);        //  Ampere
  float    getAmpere(uint8_t ch)          { return getCurrent(ch); };
  float    getCurrent_mA(uint8_t ch)      { return getCurrent(ch) * 1e3; };
  float    getCurrent_uA(uint8_t ch)      { return getCurrent(ch) * 1e6; };

  //       POWER
  float    getPower(uint8_t ch);          //  Watt
  float    getWatt(uint8_t ch)            { return getPower(ch); };
  float    getPower_mW(uint8_t ch)        { return getPower(ch) * 1e3; };
  float    getPower_uW(uint8_t ch)        { return getPower(ch) * 1e6; };
  float    getPower_kW(uint8_t ch)        { return getPower(ch) * 1e-3; };

  //  the Energy functions are returning double as they have higher accuracy.
  //       ENERGY
  float    getEnergy(uint8_t ch);         //  Joule or watt second
  float    getJoule(uint8_t ch)           { return getEnergy(ch); };
  float    getMegaJoule(uint8_t ch)       { return getEnergy(ch) * 1e-6; };
  float    getKiloJoule(uint8_t ch)       { return getEnergy(ch) * 1e-3; };
  float    getMilliJoule(uint8_t ch)      { return getEnergy(ch) * 1e3; };
  float    getMicroJoule(uint8_t ch)      { return getEnergy(ch) * 1e6; };
  float    getWattHour(uint8_t ch)        { return getEnergy(ch) * (1.0  / 3600.0); };
  float    getKiloWattHour(uint8_t ch)    { return getEnergy(ch) * (1e-3 / 3600.0); };


  //  Configuration register 1
  //  default both channels are enabled.
  void     enableChannel(uint8_t ch);
  void     disableChannel(uint8_t ch);
  void     enableAllChannels();
  void     disableAllChannels();
  bool     isEnabled(uint8_t ch);

  bool     setAverage(uint8_t avg = INA2227_1_SAMPLE);
  uint8_t  getAverage();
  bool     setBusVoltageConversionTime(uint8_t bvct = INA2227_1100_us);
  uint8_t  getBusVoltageConversionTime();
  bool     setShuntVoltageConversionTime(uint8_t svct = INA2227_1100_us);
  uint8_t  getShuntVoltageConversionTime();

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


  //  Configuration register 2  (read datasheet for details)
  bool     reset();
  //  ACC_RST Energy accumulator
  bool     resetEnergyAccumulator(uint8_t ch);
  bool     getEnergyAccumulatorChannel(uint8_t ch);
  //  CNVR_MASK - ALERT pin reflects conversion ready
  bool     setAlertConvertReady(bool cnvr = false);
  bool     getAlertConvertReady();
  //  ENOF_MASK - ALERT pin reflects energy overflow
  bool     setAlertEnergyOverflow(bool enof = false);
  bool     getAlertEnergyOverflow();
  //  ALERT_LATCH - ALERT pin latches during fault
  bool     setAlertLatchEnable(bool latch = false);
  bool     getAlertLatchEnable();
  //  ALERT_POL - ALERT pin polarity
  bool     setAlertPolarity(bool inverted = false);
  bool     getAlertPolarity();
  //  flag = false => 80 mV, true => 20 mV
  bool     setADCRange(uint8_t ch, bool flag);
  uint8_t  getADCRange(uint8_t ch);


  //  FLAGS REGISTER 0x12
  bool     isConversionReady();   //  conversion ready flag is set.
  bool     waitConversionReady(uint32_t timeout = INA2227_MAX_WAIT_MS);
  bool     hasMathOverflow();
  bool     hasAlertLimit(uint8_t ch);
  bool     hasEnergyOverflow(uint8_t ch);
  uint16_t getFlags();  //  to check all at once.


  //  ALERT LIMIT REGISTER
  //  (not tested - check datasheet)
  bool     setAlertLimit(uint8_t ch, uint16_t limit);
  uint16_t getAlertLimit(uint8_t ch);

  //  ALERT CONFIG REGISTER
  //  (not tested - check datasheet)
  bool     setAlertConfig(uint8_t ch, uint16_t mask);
  uint16_t getAlertConfig(uint8_t ch);


  //  Calibration
  //  mandatory to set these!
  //  shunt * maxCurrent < 81 mV  (or 20mV depends on ADCrange set)
  //  maxCurrent >= 0.001
  //  shunt      >= 0.001
  int      setMaxCurrentShunt(uint8_t ch, float maxCurrent = 20.0, float shunt = 0.002, bool normalize = true);
  bool     isCalibrated(uint8_t ch)     { return _current_LSB[ch] != 0.0; };

  //  These functions return zero if not calibrated!
  float    getCurrentLSB(uint8_t ch)    { return _current_LSB[ch];       };
  float    getCurrentLSB_mA(uint8_t ch) { return _current_LSB[ch] * 1e3; };
  float    getCurrentLSB_uA(uint8_t ch) { return _current_LSB[ch] * 1e6; };
  float    getShunt(uint8_t ch)         { return _shunt[ch];             };
  float    getMaxCurrent(uint8_t ch)    { return _maxCurrent[ch];        };


  //  Meta information
  //
  //                               typical value
  uint16_t getManufacturerID();  //  0x5449
  uint16_t getDeviceID();        //  0x2350


  //  DEBUG
  uint16_t getRegister(uint8_t reg)  { return _readRegister(reg); };

  //
  //  ERROR HANDLING
  //
  int      getLastError();


private:

  uint16_t _readRegister(uint8_t reg);
  uint32_t _readRegister32(uint8_t reg);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);

  float    _current_LSB[2];
  float    _shunt[2];
  float    _maxCurrent[2];
  bool     _ADCRange[2];  //  per channel

  uint8_t   _address;
  TwoWire * _wire;

  int       _error;
};


//  -- END OF FILE --

