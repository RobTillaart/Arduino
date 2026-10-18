#pragma once
//    FILE: INA239.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
//    DATE: 2024-12-05
// PURPOSE: Arduino library for the INA239, SPI, 16 bit, voltage, current and power sensor.
//     URL: https://github.com/RobTillaart/INA239
//
//  Read the datasheet for the details


#include "Arduino.h"
#include "SPI.h"


#define INA239_LIB_VERSION          (F("0.4.0"))


#ifndef __SPI_CLASS__
  //  MBED must be tested before RP2040
  #if defined(ARDUINO_ARCH_MBED)
  #define __SPI_CLASS__   SPIClass
  #elif defined(ARDUINO_ARCH_RP2040)
  #define __SPI_CLASS__   SPIClassRP2040
  #else
  #define __SPI_CLASS__   SPIClass
  #endif
#endif


//  for setMode() and getMode()
enum INA239_mode_enum {
  INA239_MODE_SHUTDOWN            = 0x00,
  INA239_MODE_TRIG_BUS            = 0x01,
  INA239_MODE_TRIG_SHUNT          = 0x02,
  INA239_MODE_TRIG_BUS_SHUNT      = 0x03,
  INA239_MODE_TRIG_TEMP           = 0x04,
  INA239_MODE_TRIG_TEMP_BUS       = 0x05,
  INA239_MODE_TRIG_TEMP_SHUNT     = 0x06,
  INA239_MODE_TRIG_TEMP_BUS_SHUNT = 0x07,

  INA239_MODE_SHUTDOWN2           = 0x08,
  INA239_MODE_CONT_BUS            = 0x09,
  INA239_MODE_CONT_SHUNT          = 0x0A,
  INA239_MODE_CONT_BUS_SHUNT      = 0x0B,
  INA239_MODE_CONT_TEMP           = 0x0C,
  INA239_MODE_CONT_TEMP_BUS       = 0x0D,
  INA239_MODE_CONT_TEMP_SHUNT     = 0x0E,
  INA239_MODE_CONT_TEMP_BUS_SHUNT = 0x0F
};


//  for setAverage() and getAverage()
enum INA239_average_enum {
    INA239_1_SAMPLE     = 0,
    INA239_4_SAMPLES    = 1,
    INA239_16_SAMPLES   = 2,
    INA239_64_SAMPLES   = 3,
    INA239_128_SAMPLES  = 4,
    INA239_256_SAMPLES  = 5,
    INA239_512_SAMPLES  = 6,
    INA239_1024_SAMPLES = 7
};


//  for Bus, shunt and temperature conversion timing.
enum INA239_timing_enum {
    INA239_50_us   = 0,
    INA239_84_us   = 1,
    INA239_150_us  = 2,
    INA239_280_us  = 3,
    INA239_540_us  = 4,
    INA239_1052_us = 5,
    INA239_2074_us = 6,
    INA239_4120_us = 7
};


//  for diagnose/alert() bit fields.
//  TODO bit masks?
enum INA239_diag_enum {
  INA239_DIAG_MEMORY_STATUS     = 0,
  INA239_DIAG_CONVERT_COMPLETE  = 1,
  INA239_DIAG_POWER_OVER_LIMIT  = 2,
  INA239_DIAG_BUS_UNDER_LIMIT   = 3,
  INA239_DIAG_BUS_OVER_LIMIT    = 4,
  INA239_DIAG_SHUNT_UNDER_LIMIT = 5,
  INA239_DIAG_SHUNT_OVER_LIMIT  = 6,
  INA239_DIAG_TEMP_OVER_LIMIT   = 7,
  INA239_DIAG_RESERVED          = 8,
  INA239_DIAG_MATH_OVERFLOW     = 9,
  INA239_DIAG_CHARGE_OVERFLOW   = 10,
  INA239_DIAG_ENERGY_OVERFLOW   = 11,
  INA239_DIAG_ALERT_POLARITY    = 12,
  INA239_DIAG_SLOW_ALERT        = 13,
  INA239_DIAG_CONVERT_READY     = 14,
  INA239_DIAG_ALERT_LATCH       = 15
};


enum INA239_register_enum
{
//   REGISTERS           ADDRESS    BITS  RW  //  names same as in INA228
  INA239_CONFIG        = 0x00,   //  16   RW
  INA239_ADC_CONFIG    = 0x01,   //  16   RW
  INA239_SHUNT_CAL     = 0x02,   //  16   RW
  INA239_SHUNT_VOLTAGE = 0x04,   //  16   R-
  INA239_BUS_VOLTAGE   = 0x05,   //  16   R-
  INA239_TEMPERATURE   = 0x06,   //  16   R-
  INA239_CURRENT       = 0x07,   //  16   R-
  INA239_POWER         = 0x08,   //  24   R-
  INA239_DIAG_ALERT    = 0x0B,   //  16   RW
  INA239_SOVL          = 0x0C,   //  16   RW
  INA239_SUVL          = 0x0D,   //  16   RW
  INA239_BOVL          = 0x0E,   //  16   RW
  INA239_BUVL          = 0x0F,   //  16   RW
  INA239_TEMP_LIMIT    = 0x10,   //  16   RW
  INA239_POWER_LIMIT   = 0x11,   //  16   RW
  INA239_MANUFACTURER  = 0x3E,   //  16   R-
  INA239_DEVICE_ID     = 0x3F    //  16   R-
};


class INA239
{
public:
  //  HARDWARE SPI
  INA239(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  INA239(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  bool     begin();

  //
  //  CORE FUNCTIONS + scale wrappers.
  //
  //       BUS VOLTAGE - section 7.6.1.4, page 22
  float    getBusVoltage();     //  Volt
  float    getBusVolt()         { return getBusVoltage(); };
  float    getBusMilliVolt()    { return getBusVoltage()   * 1e3f; };
  float    getBusMicroVolt()    { return getBusVoltage()   * 1e6f; };

  //       SHUNT VOLTAGE - section 7.6.1.3, page 22
  float    getShuntVoltage();   //  Volt
  float    getShuntVolt()       { return getShuntVoltage(); };
  float    getShuntMilliVolt()  { return getShuntVoltage() * 1e3f; };
  float    getShuntMicroVolt()  { return getShuntVoltage() * 1e6f; };

  //       SHUNT CURRENT - section 7.6.1.7, page 23
  float    getCurrent();        //  Ampere
  float    getAmpere()          { return getCurrent(); };
  float    getMilliAmpere()     { return getCurrent()      * 1e3f; };
  float    getMicroAmpere()     { return getCurrent()      * 1e6f; };

  //       POWER - section 7.6.1.8, page 23
  float    getPower();          //  Watt
  float    getWatt()            { return getPower(); };
  float    getMilliWatt()       { return getPower()        * 1e3f; };
  float    getMicroWatt()       { return getPower()        * 1e6f; };
  float    getKiloWatt()        { return getPower()        * 1e-3f; };

  //       TEMPERATURE - section 7.6.1.6, page 23
  float    getTemperature();    //  Celsius


  //  CONFIGURE BUSVOLTAGE LSB - see issue #13
  //  use when a voltage divider is in front of VBUS.
  //  affects getBusVoltage() and getPower();
  //  default are the factory default values.
  void     setBusVoltageLSB(float LSB = 3.125e-3f);
  float    getBusVoltageLSB();
  void     setVoltageRatio(float ratio = 1.0f);
  float    getVoltageRatio();


  //
  //  CONFIG REGISTER 0
  //  read datasheet for details, section 7.6.1.1, page 20
  //
  void     reset();
  //  Conversion delay in 0..255 steps of 2 ms
  void     setConversionDelay(uint8_t steps);
  uint8_t  getConversionDelay();
  //  flag = false => 164 mV, true => 41 mV
  bool     setADCRange(bool flag);
  bool     getADCRange();


  //
  //  CONFIG ADC REGISTER 1
  //  read datasheet for details, section 7.6.1.2, page 20++
  //
  bool     setMode(uint8_t mode = INA239_MODE_CONT_TEMP_BUS_SHUNT);
  uint8_t  getMode();
  //  default value = ~1 milliseconds for all.
  bool     setBusVoltageConversionTime(uint8_t bvct = INA239_1052_us);
  uint8_t  getBusVoltageConversionTime();
  bool     setShuntVoltageConversionTime(uint8_t svct = INA239_1052_us);
  uint8_t  getShuntVoltageConversionTime();
  bool     setTemperatureConversionTime(uint8_t tct = INA239_1052_us);
  uint8_t  getTemperatureConversionTime();
  bool     setAverage(uint8_t avg = INA239_1_SAMPLE);
  uint8_t  getAverage();


  //
  //  SHUNT CALIBRATION REGISTER 2
  //  read datasheet for details. use with care.
  //  maxCurrent <= 204, (in fact no limit)
  //  shunt >= 0.0001.
  //  returns _current_LSB;
  int      setMaxCurrentShunt(float maxCurrent, float shunt);
  bool     isCalibrated()    { return _current_LSB != 0.0f; };
  float    getMaxCurrent();
  float    getShunt();
  float    getCurrentLSB();
  float    getCurrentLSB_mA() { return _current_LSB * 1e3f; };
  float    getCurrentLSB_uA() { return _current_LSB * 1e6f; };


  //
  //  DIAGNOSE ALERT REGISTER 11  (0x0B)
  //  read datasheet for details, section 7.6.1.9, page 23.
  //
  void     setDiagnoseAlert(uint16_t flags);
  uint16_t getDiagnoseAlert();
  //  INA239.h has an enum for the bit fields.
  //  See INA239_diag_enum above
  void     setDiagnoseAlertBit(uint8_t bit);
  void     clearDiagnoseAlertBit(uint8_t bit);
  uint16_t getDiagnoseAlertBit(uint8_t bit);


  //
  //  THRESHOLD AND LIMIT REGISTERS 12-17
  //  read datasheet for details, section 7.6.1.10-15, page 25++
  //
  //  use getVoltageLSB() to map thresholds to voltage
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
  uint16_t getDieID();         //  0x0239
  uint16_t getRevision();      //  0x0001


  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();

  //       Debugging
  bool     usesHWSPI();
  uint32_t readRegister(uint8_t reg, uint8_t bytes)
  {
    return _readRegister(reg, bytes);
  };
  uint32_t writeRegister(uint8_t reg, uint16_t value)
  {
    return _writeRegister(reg, value);
  };


private:
  //  max 4 bytes
  uint32_t _readRegister(uint8_t reg, uint8_t bytes);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);

  float    _bus_LSB;
  float    _current_LSB;
  float    _power_LSB;
  float    _shunt;
  float    _maxCurrent;
  bool     _ADCRange;

  uint8_t  _dataIn = 255;
  uint8_t  _dataOut= 255;
  uint8_t  _clock  = 255;
  uint8_t  _select = 255;
  bool     _hwSPI  = false;
  uint32_t _SPIspeed = 10000000;  //  max speed

  uint8_t  swSPI_transfer(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


//  -- END OF FILE --


