#pragma once
//    FILE: INA226.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.3
//    DATE: 2021-05-18
// PURPOSE: Arduino library for INA226 power sensor
//     URL: https://github.com/RobTillaart/INA226
//
//  Read the datasheet for the details
//


#include "Arduino.h"
#include "Wire.h"


#define INA226_LIB_VERSION              (F("0.4.3"))


//  set by setAlertRegister
#define INA226_SHUNT_OVER_VOLTAGE        0x8000
#define INA226_SHUNT_UNDER_VOLTAGE       0x4000
#define INA226_BUS_OVER_VOLTAGE          0x2000
#define INA226_BUS_UNDER_VOLTAGE         0x1000
#define INA226_POWER_OVER_LIMIT          0x0800
#define INA226_CONVERSION_READY          0x0400

//  returned by getAlertFlag
#define INA226_ALERT_FUNCTION_FLAG       0x0010
#define INA226_CONVERSION_READY_FLAG     0x0008
#define INA226_MATH_OVERFLOW_FLAG        0x0004
#define INA226_ALERT_POLARITY_FLAG       0x0002
#define INA226_ALERT_LATCH_ENABLE_FLAG   0x0001

//  returned by setMaxCurrentShunt
#define INA226_ERR_NONE                  0x0000
#define INA226_ERR_SHUNTVOLTAGE_HIGH     0x8000
#define INA226_ERR_MAXCURRENT_LOW        0x8001
#define INA226_ERR_SHUNT_LOW             0x8002


//  See issue #26
#define INA226_MINIMAL_SHUNT             (0.001)


class INA226
{
public:
  //  address between 0x40 and 0x4F
  explicit INA226(const uint8_t address, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(const uint8_t sda, const uint8_t scl);
#endif
  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  Core functions
  float    getBusVoltage();    //  Volt
  float    getShuntVoltage();  //  Volt
  float    getCurrent();       //  Ampere
  float    getPower();         //  Watt


  //  Scale helpers milli range
  float    getBusVoltage_mV()   { return getBusVoltage() * 1e3; };
  float    getShuntVoltage_mV() { return getShuntVoltage() * 1e3; };
  float    getCurrent_mA()      { return getCurrent() * 1e3; };
  float    getPower_mW()        { return getPower() * 1e3; };
  //  Scale helpers micro range
  float    getBusVoltage_uV()   { return getBusVoltage() * 1e6; };
  float    getShuntVoltage_uV() { return getShuntVoltage() * 1e6; };
  float    getCurrent_uA()      { return getCurrent() * 1e6; };
  float    getPower_uW()        { return getPower() * 1e6; };


  //  Configuration
  void     reset();
  bool     setAverage(uint8_t avg = 0);
  uint8_t  getAverage();
  bool     setBusVoltageConversionTime(uint8_t bvct = 4);
  uint8_t  getBusVoltageConversionTime();
  bool     setShuntVoltageConversionTime(uint8_t svct = 4);
  uint8_t  getShuntVoltageConversionTime();


  //  Calibration
  //  mandatory to set these!
  //  shunt * maxCurrent < 81 mV
  //  maxCurrent >= 0.001
  //  shunt      >= 0.001
  int      setMaxCurrentShunt(float macCurrent = 20.0,
                              float shunt = 0.002,
                              bool normalize = true);
  bool     isCalibrated()     { return _current_LSB != 0.0; };

  //  These functions return zero if not calibrated!
  float    getCurrentLSB()    { return _current_LSB; };
  float    getCurrentLSB_mA() { return _current_LSB * 1e3; };
  float    getCurrentLSB_uA() { return _current_LSB * 1e6; };
  float    getShunt()         { return _shunt; };
  float    getMaxCurrent()    { return _maxCurrent; };


  //  Operating mode
  bool     setMode(uint8_t mode = 7);
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
  void     setAlertRegister(uint16_t mask);
  uint16_t getAlertFlag();
  void     setAlertLimit(uint16_t limit);
  uint16_t getAlertLimit();


  //  Meta information
  uint16_t getManufacturerID();   //  should return 0x5449
  uint16_t getDieID();            //  should return 0x2260


  //  DEBUG
  uint16_t getRegister(uint8_t reg)  { return _readRegister(reg); };


private:

  uint16_t _readRegister(uint8_t reg);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);
  float    _current_LSB;
  float    _shunt;
  float    _maxCurrent;

  uint8_t   _address;
  TwoWire * _wire;

};


//  -- END OF FILE --

