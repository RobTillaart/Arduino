#pragma once
//    FILE: INA238.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-06-11
// PURPOSE: Arduino library for the INA238, I2C, 16 bit, voltage, current and power sensor.
//     URL: https://github.com/RobTillaart/INA238
//          https://www.adafruit.com/product/6349
//
//  Read the datasheet for the details


#include "Arduino.h"
#include "Wire.h"


#define INA238_LIB_VERSION          (F("0.1.0"))


//  for setMode() and getMode()
enum INA238_mode_enum {
  INA238_MODE_SHUTDOWN            = 0x00,
  INA238_MODE_TRIG_BUS            = 0x01,
  INA238_MODE_TRIG_SHUNT          = 0x02,
  INA238_MODE_TRIG_BUS_SHUNT      = 0x03,
  INA238_MODE_TRIG_TEMP           = 0x04,
  INA238_MODE_TRIG_TEMP_BUS       = 0x05,
  INA238_MODE_TRIG_TEMP_SHUNT     = 0x06,
  INA238_MODE_TRIG_TEMP_BUS_SHUNT = 0x07,

  INA238_MODE_SHUTDOWN2           = 0x08,
  INA238_MODE_CONT_BUS            = 0x09,
  INA238_MODE_CONT_SHUNT          = 0x0A,
  INA238_MODE_CONT_BUS_SHUNT      = 0x0B,
  INA238_MODE_CONT_TEMP           = 0x0C,
  INA238_MODE_CONT_TEMP_BUS       = 0x0D,
  INA238_MODE_CONT_TEMP_SHUNT     = 0x0E,
  INA238_MODE_CONT_TEMP_BUS_SHUNT = 0x0F
};


//  for setAverage() and getAverage()
enum INA238_average_enum {
    INA238_1_SAMPLE     = 0,
    INA238_4_SAMPLES    = 1,
    INA238_16_SAMPLES   = 2,
    INA238_64_SAMPLES   = 3,
    INA238_128_SAMPLES  = 4,
    INA238_256_SAMPLES  = 5,
    INA238_512_SAMPLES  = 6,
    INA238_1024_SAMPLES = 7
};


//  for Bus, shunt and temperature conversion timing.
enum INA238_timing_enum {
    INA238_50_us   = 0,
    INA238_84_us   = 1,
    INA238_150_us  = 2,
    INA238_280_us  = 3,
    INA238_540_us  = 4,
    INA238_1052_us = 5,
    INA238_2074_us = 6,
    INA238_4120_us = 7
};


//  for diagnose/alert() bit fields.
//  TODO bit masks?
enum INA238_diag_enum {
  INA238_DIAG_MEMORY_STATUS      = 0,
  INA238_DIAG_CONVERT_COMPLETE   = 1,
  INA238_DIAG_POWER_OVER_LIMIT   = 2,
  INA238_DIAG_BUS_UNDER_LIMIT    = 3,
  INA238_DIAG_BUS_OVER_LIMIT     = 4,
  INA238_DIAG_SHUNT_UNDER_LIMIT  = 5,
  INA238_DIAG_SHUNT_OVER_LIMIT   = 6,
  INA238_DIAG_TEMP_OVER_LIMIT    = 7,
  INA238_DIAG_RESERVED           = 8,
  INA238_DIAG_MATH_OVERFLOW      = 9,
  INA238_DIAG_CHARGE_OVERFLOW    = 10,
  INA238_DIAG_ENERGY_OVERFLOW    = 11,
  INA238_DIAG_ALERT_POLARITY     = 12,
  INA238_DIAG_SLOW_ALERT         = 13,
  INA238_DIAG_CONVERT_READY      = 14,
  INA238_DIAG_ALERT_LATCH        = 15
};


class INA238
{
public:
  //  address between 0x40 and 0x4F
  explicit INA238(const uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //
  //  CORE FUNCTIONS + scale wrappers.
  //
  //       BUS VOLTAGE
  float    getBusVoltage();     //  Volt
  float    getBusVolt()         { return getBusVoltage(); };
  float    getBusMilliVolt()    { return getBusVoltage()   * 1e3; };
  float    getBusMicroVolt()    { return getBusVoltage()   * 1e6; };

  //       SHUNT VOLTAGE
  float    getShuntVoltage();   //  Volt
  float    getShuntVolt()       { return getShuntVoltage(); };
  float    getShuntMilliVolt()  { return getShuntVoltage() * 1e3; };
  float    getShuntMicroVolt()  { return getShuntVoltage() * 1e6; };

  //       SHUNT CURRENT
  float    getCurrent();        //  Ampere
  float    getAmpere()          { return getCurrent(); };
  float    getMilliAmpere()     { return getCurrent()      * 1e3; };
  float    getMicroAmpere()     { return getCurrent()      * 1e6; };

  //       POWER
  float    getPower();          //  Watt
  float    getWatt()            { return getPower(); };
  float    getMilliWatt()       { return getPower()        * 1e3; };
  float    getMicroWatt()       { return getPower()        * 1e6; };
  float    getKiloWatt()        { return getPower()        * 1e-3; };

  //       TEMPERATURE
  float    getTemperature();    //  Celsius


  //
  //  CONFIG REGISTER 0
  //  read datasheet for details, section 7.6.1.1, page 21
  //
  void     reset();
  //  Conversion delay in 0..255 steps of 2 ms
  void     setConversionDelay(uint8_t steps);
  uint8_t  getConversionDelay();
  //  flag = false => ~163.84 mV, true => ~40.96 mV
  void     setADCRange(bool flag);
  bool     getADCRange();


  //
  //  CONFIG ADC REGISTER 1
  //  read datasheet for details, section 7.6.1.2, page 21++
  //
  bool     setMode(uint8_t mode = INA238_MODE_CONT_TEMP_BUS_SHUNT);
  uint8_t  getMode();
  //  default value = ~1 milliseconds for all.
  bool     setBusVoltageConversionTime(uint8_t bvct = INA238_1052_us);
  uint8_t  getBusVoltageConversionTime();
  bool     setShuntVoltageConversionTime(uint8_t svct = INA238_1052_us);
  uint8_t  getShuntVoltageConversionTime();
  bool     setTemperatureConversionTime(uint8_t tct = INA238_1052_us);
  uint8_t  getTemperatureConversionTime();
  bool     setAverage(uint8_t avg = INA238_1_SAMPLE);
  uint8_t  getAverage();

  //
  //  SHUNT CALIBRATION REGISTER 2
  //  read datasheet for details, section 7.6.1.3, page 23
  //  use with care.
  //  maxCurrent <= 204, (in fact no limit)
  //  shunt >= 0.0001.
  //  returns error code => 0 == OK;
  int      setMaxCurrentShunt(float maxCurrent, float shunt);
  bool     isCalibrated()    { return _current_LSB > 0.0; };
  float    getMaxCurrent();
  float    getShunt();
  float    getCurrentLSB();  //  <= 0.0 means not calibrated.


  //
  //  DIAGNOSE ALERT REGISTER 11  (0x0B)
  //  read datasheet for details, section 7.6.1.9, page 24++
  //
  void     setDiagnoseAlert(uint16_t flags);
  uint16_t getDiagnoseAlert();
  //  INA238.h has an enum for the bit fields.
  //  See INA238_diag_enum above
  void     setDiagnoseAlertBit(uint8_t bit);
  void     clearDiagnoseAlertBit(uint8_t bit);
  uint16_t getDiagnoseAlertBit(uint8_t bit);


  //
  //  THRESHOLD AND LIMIT REGISTERS 12-17
  //  read datasheet for details, section 7.3.6, page 16++
  //                              section 7.6.1.10, page 26++
  //
  //  TODO - design and implement better API?
  //
  void     setShuntOvervoltageTH(uint16_t threshold);
  uint16_t getShuntOvervoltageTH();
  void     setShuntUndervoltageTH(uint16_t threshold);
  uint16_t getShuntUndervoltageTH();
  void     setBusOvervoltageTH(uint16_t threshold);
  uint16_t getBusOvervoltageTH();
  void     setBusUndervoltageTH(uint16_t threshold);
  uint16_t getBusUndervoltageTH();
  void     setTemperatureOverLimitTH(uint16_t threshold);
  uint16_t getTemperatureOverLimitTH();
  void     setPowerOverLimitTH(uint16_t threshold);
  uint16_t getPowerOverLimitTH();


  //
  //  MANUFACTURER and ID REGISTER 3E and 3F
  //  read datasheet for details, section 7.6.1.16, page 27
  //
  //                               typical value
  uint16_t getManufacturer();  //  0x5449 ("TI" in ASCII)
  uint16_t getDieID();         //  0x0238
  uint16_t getRevision();      //  0x0001

  //
  //  ERROR HANDLING
  //
  int      getLastError();


protected:
  //  max 4 bytes
  uint32_t _readRegister(uint8_t reg, uint8_t bytes);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);

  float    _current_LSB;
  float    _shunt;
  float    _maxCurrent;
  bool     _ADCRange;

  uint8_t   _address;
  TwoWire * _wire;

  int       _error;
};


//////////////////////////////////////////////////////////////
//
//  DERIVED INA237
//
class INA237 : public INA238
{
public:
  INA237(const uint8_t address, TwoWire *wire = &Wire);
};


//  -- END OF FILE --


