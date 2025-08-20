#pragma once
//    FILE: INA228.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
//    DATE: 2024-05-09
// PURPOSE: Arduino library for the INA228, I2C, 20 bit, voltage, current and power sensor.
//     URL: https://github.com/RobTillaart/INA228
//          https://www.adafruit.com/product/5832           ( 10 A version)
//          https://www.mateksys.com/?portfolio=i2c-ina-bm  (200 A version))
//
//
//  Read the datasheet for the details


#include "Arduino.h"
#include "Wire.h"


#define INA228_LIB_VERSION          (F("0.4.0"))


//  for setMode() and getMode()
enum ina228_mode_enum {
  INA228_MODE_SHUTDOWN            = 0x00,
  INA228_MODE_TRIG_BUS            = 0x01,
  INA228_MODE_TRIG_SHUNT          = 0x02,
  INA228_MODE_TRIG_BUS_SHUNT      = 0x03,
  INA228_MODE_TRIG_TEMP           = 0x04,
  INA228_MODE_TRIG_TEMP_BUS       = 0x05,
  INA228_MODE_TRIG_TEMP_SHUNT     = 0x06,
  INA228_MODE_TRIG_TEMP_BUS_SHUNT = 0x07,

  INA228_MODE_SHUTDOWN2           = 0x08,
  INA228_MODE_CONT_BUS            = 0x09,
  INA228_MODE_CONT_SHUNT          = 0x0A,
  INA228_MODE_CONT_BUS_SHUNT      = 0x0B,
  INA228_MODE_CONT_TEMP           = 0x0C,
  INA228_MODE_CONT_TEMP_BUS       = 0x0D,
  INA228_MODE_CONT_TEMP_SHUNT     = 0x0E,
  INA228_MODE_CONT_TEMP_BUS_SHUNT = 0x0F
};


//  for setAverage() and getAverage()
enum ina228_average_enum {
    INA228_1_SAMPLE     = 0,
    INA228_4_SAMPLES    = 1,
    INA228_16_SAMPLES   = 2,
    INA228_64_SAMPLES   = 3,
    INA228_128_SAMPLES  = 4,
    INA228_256_SAMPLES  = 5,
    INA228_512_SAMPLES  = 6,
    INA228_1024_SAMPLES = 7
};


//  for Bus, shunt and temperature conversion timing.
enum ina228_timing_enum {
    INA228_50_us   = 0,
    INA228_84_us   = 1,
    INA228_150_us  = 2,
    INA228_280_us  = 3,
    INA228_540_us  = 4,
    INA228_1052_us = 5,
    INA228_2074_us = 6,
    INA228_4120_us = 7
};


//  for diagnose/alert() bit fields.
//  TODO bit masks?
enum ina228_diag_enum {
  INA228_DIAG_MEMORY_STATUS      = 0,
  INA228_DIAG_CONVERT_COMPLETE   = 1,
  INA228_DIAG_POWER_OVER_LIMIT   = 2,
  INA228_DIAG_BUS_UNDER_LIMIT    = 3,
  INA228_DIAG_BUS_OVER_LIMIT     = 4,
  INA228_DIAG_SHUNT_UNDER_LIMIT  = 5,
  INA228_DIAG_SHUNT_OVER_LIMIT   = 6,
  INA228_DIAG_TEMP_OVER_LIMIT    = 7,
  INA228_DIAG_RESERVED           = 8,
  INA228_DIAG_MATH_OVERFLOW      = 9,
  INA228_DIAG_CHARGE_OVERFLOW    = 10,
  INA228_DIAG_ENERGY_OVERFLOW    = 11,
  INA228_DIAG_ALERT_POLARITY     = 12,
  INA228_DIAG_SLOW_ALERT         = 13,
  INA228_DIAG_CONVERT_READY      = 14,
  INA228_DIAG_ALERT_LATCH        = 15
};


class INA228
{
public:
  //  address between 0x40 and 0x4F
  explicit INA228(const uint8_t address, TwoWire *wire = &Wire);

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

  //  raw integer interface.
  int32_t  getShuntVoltageRAW();
  
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

  //  the Energy and Charge functions are returning double as they have higher accuracy.
  //       ENERGY
  double   getEnergy();         //  Joule or watt second
  double   getJoule()           { return getEnergy(); };
  double   getMegaJoule()       { return getEnergy()       * 1e-6; };
  double   getKiloJoule()       { return getEnergy()       * 1e-3; };
  double   getMilliJoule()      { return getEnergy()       * 1e3; };
  double   getMicroJoule()      { return getEnergy()       * 1e6; };
  double   getWattHour()        { return getEnergy()       * (1.0  / 3600.0); };
  double   getKiloWattHour()    { return getEnergy()       * (1e-3 / 3600.0); };

  //       CHARGE
  double   getCharge();         //  Coulombs
  double   getCoulomb()         { return getCharge(); };
  double   getMilliCoulomb()    { return getCharge()       * 1e3; };
  double   getMicroCoulomb()    { return getCharge()       * 1e6; };


  //
  //  CONFIG REGISTER 0
  //  read datasheet for details, section 7.6.1.1, page 22
  //
  void     reset();
  //  value: 0 == normal operation,  1 = clear registers
  //   bool     resetEnergyCharge(uint8_t value);  better name for setAccumulation()??
  //  [[deprecated("Use ")]]  ??
  bool     setAccumulation(uint8_t value);  //  idem
  bool     getAccumulation();
  //  Conversion delay in 0..255 steps of 2 ms
  void     setConversionDelay(uint8_t steps);
  uint8_t  getConversionDelay();
  void     setTemperatureCompensation(bool on);
  bool     getTemperatureCompensation();
  //  flag = false => 164 mV, true => 41 mV
  bool     setADCRange(bool flag);
  bool     getADCRange();

  //
  //  CONFIG ADC REGISTER 1
  //  read datasheet for details, section 7.6.1.2, page 22++
  //
  bool     setMode(uint8_t mode = INA228_MODE_CONT_TEMP_BUS_SHUNT);
  uint8_t  getMode();
  //  default value = ~1 milliseconds for all.
  bool     setBusVoltageConversionTime(uint8_t bvct = INA228_1052_us);
  uint8_t  getBusVoltageConversionTime();
  bool     setShuntVoltageConversionTime(uint8_t svct = INA228_1052_us);
  uint8_t  getShuntVoltageConversionTime();
  bool     setTemperatureConversionTime(uint8_t tct = INA228_1052_us);
  uint8_t  getTemperatureConversionTime();
  bool     setAverage(uint8_t avg = INA228_1_SAMPLE);
  uint8_t  getAverage();

  //
  //  SHUNT CALIBRATION REGISTER 2
  //  read datasheet for details. use with care.
  //  maxCurrent <= 204, (in fact no limit)
  //  shunt >= 0.0001.
  //  returns _current_LSB;
  int      setMaxCurrentShunt(float maxCurrent, float shunt);
  bool     isCalibrated()    { return _current_LSB != 0.0; };
  float    getMaxCurrent();
  float    getShunt();
  float    getCurrentLSB();

  //
  //  SHUNT TEMPERATURE COEFFICIENT REGISTER 3
  //  read datasheet for details, page 16.
  //  ppm = 0..16383.
  bool     setShuntTemperatureCoefficent(uint16_t ppm = 0);
  uint16_t getShuntTemperatureCoefficent();


  //
  //  DIAGNOSE ALERT REGISTER 11  (0x0B)
  //  read datasheet for details, section 7.6.1.12, page 26++.
  //
  void     setDiagnoseAlert(uint16_t flags);
  uint16_t getDiagnoseAlert();
  //  INA228.h has an enum for the bit fields.
  //  See ina228_diag_enum above
  void     setDiagnoseAlertBit(uint8_t bit);
  void     clearDiagnoseAlertBit(uint8_t bit);
  uint16_t getDiagnoseAlertBit(uint8_t bit);


  //
  //  THRESHOLD AND LIMIT REGISTERS 12-17
  //  read datasheet for details, section 7.3.7, page 16++
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
  //
  //                               typical value
  uint16_t getManufacturer();  //  0x5449
  uint16_t getDieID();         //  0x0228
  uint16_t getRevision();      //  0x0001

  //
  //  ERROR HANDLING
  //
  int      getLastError();

private:
  //  max 4 bytes
  uint32_t _readRegister(uint8_t reg, uint8_t bytes);
  //  always 5 bytes, mode == U ==> unsigned, otherwise signed
  double   _readRegisterF(uint8_t reg, char mode);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);

  float    _current_LSB;
  float    _shunt;
  float    _maxCurrent;
  bool     _ADCRange;

  uint8_t   _address;
  TwoWire * _wire;

  int       _error;
};


//  -- END OF FILE --


