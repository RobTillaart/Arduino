#pragma once
//    FILE: INA228.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-05-09
// PURPOSE: Arduino library for INA228 power sensor
//     URL: https://github.com/RobTillaart/INA228
//
//  Read the datasheet for the details


#include "Arduino.h"
#include "Wire.h"


#define INA228_LIB_VERSION          "0.1.0"


//  TODO MOVE TO CPP  CHECK DATASHEET.

//      REGISTERS                   ADDRESS    BITS  RW
#define INA228_CONFIG               0x00    //  16   RW
#define INA228_ADC_CONFIG           0x01    //  16   RW
#define INA228_SHUNT_CAL            0x02    //  16   RW
#define INA228_SHUNT_TEMP_CO        0x03    //  16   RW
#define INA228_SHUNT_VOLTAGE        0x04    //  24   R-
#define INA228_BUS_VOLTAGE          0x05    //  24   R-
#define INA228_TEMPERATURE          0x06    //  16   R-
#define INA228_CURRENT              0x07    //  24   R-
#define INA228_POWER                0x08    //  24   R-
#define INA228_ENERGY               0x09    //  40   R-
#define INA228_CHARGE               0x0A    //  40   R-
#define INA228_DIAG_ALERT           0x0B    //  16   RW
#define INA228_SOVL                 0x0C    //  16   RW
#define INA228_SUVL                 0x0D    //  16   RW
#define INA228_BOVL                 0x0E    //  16   RW
#define INA228_BUVL                 0x0F    //  16   RW
#define INA228_TEMP_LIMIT           0x10    //  16   RW
#define INA228_POWER_LIMIT          0x11    //  16   RW
#define INA228_MANUFACTURER         0x3E    //  16   R-
#define INA228_DEVICE_ID            0x3F    //  16   R-


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



class INA228
{
public:
  //  address between 0x40 and 0x4F
  explicit INA228(const uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //
  //  CORE FUNCTIONS
  //
  float    getBusVoltage();       //  Volt
  float    getShuntVoltage();     //  Volt
  float    getCurrent();          //  Ampere
  float    getPower();            //  Watt
  float    getTemperature();      //  Celsius
  float    getEnergy();           //  Joule
  float    getCharge();           //  Coulombs

  //  Scale helpers milli range
  float    getBusVoltage_mV()   { return getBusVoltage()   * 1e3; };
  float    getShuntVoltage_mV() { return getShuntVoltage() * 1e3; };
  float    getCurrent_mA()      { return getCurrent()      * 1e3; };
  float    getPower_mW()        { return getPower()        * 1e3; };
  float    getEnergy_mJ()       { return getEnergy()       * 1e3; };
  float    getCharge_mC()       { return getCharge()       * 1e3; };

  //  Scale helpers micro range
  float    getBusVoltage_uV()   { return getBusVoltage()   * 1e6; };
  float    getShuntVoltage_uV() { return getShuntVoltage() * 1e6; };
  float    getCurrent_uA()      { return getCurrent()      * 1e6; };
  float    getPower_uW()        { return getPower()        * 1e6; };
  float    getEnergy_uJ()       { return getEnergy()       * 1e6; };
  float    getCharge_uC()       { return getCharge()       * 1e6; };

  //
  //  CONFIG REGISTER 0
  //  read datasheet for details.
  void     reset();
  //  val: 0 == normal operation,  1 = clear registers
  bool     setAccumulation(uint8_t val);
  bool     getAccumulation();
  //  Conversion delay in 0..255 steps of 2 ms
  void     setConversionDelay(uint8_t steps);
  uint8_t  getConversionDelay();
  void     setTemperatureCompensation(bool on);
  bool     getTemperatureCompensation();
  //  flag = false => 164 mV, true => 41 mV
  void     setADCRange(bool flag);
  bool     getADCRange();

  //
  //  CONFIG ADC REGISTER 1
  //  read datasheet for details.
  bool     setMode(uint8_t mode = INA228_MODE_CONT_TEMP_BUS_SHUNT);
  uint8_t  getMode();
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
  //  maxCurrent <= 10, shunt > 0.005.
  int      setMaxCurrentShunt(float maxCurrent, float shunt);
  bool     isCalibrated()    { return _current_LSB != 0.0; };
  float    getMaxCurrent();
  float    getShunt();

  //
  //  SHUNT TEMPERATURE COEFFICIENT REGISTER 3
  //  read datasheet for details. use with care.
  //  ppm = 0..16383.
  bool     setShuntTemperatureCoefficent(uint16_t ppm = 0);
  uint16_t getShuntTemperatureCoefficent();


  //
  //  DIAGNOSE ALERT REGISTER 11  (0x0B)
  //  read datasheet for details. use with care.
  //  TODO


  //
  //  THRESHOLD AND LIMIT REGISTERS 12-17
  //  read datasheet for details. use with care.
  //  TODO



  //
  //  MANUFACTURER and ID REGISTER 3E/3F
  //
  bool     getManufacturer();
  uint16_t getDieID();
  uint16_t getRevision();


  ///////////////////
  //
  //  SHOULD BE PRIVATE
  //
  uint32_t _readRegister(uint8_t reg, uint8_t bytes);  //  max 4.
  float    _readRegisterF(uint8_t reg, uint8_t bytes);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);


private:


  float    _current_LSB;
  float    _shunt;
  float    _maxCurrent;

  uint8_t   _address;
  TwoWire * _wire;
};


//  -- END OF FILE --


