#pragma once
//    FILE: INA219.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2021-05-18
// PURPOSE: Arduino library for INA219 voltage, current and power sensor
//     URL: https://github.com/RobTillaart/INA219
//
//  Read the datasheet for the details how to connect!
//


#include "Arduino.h"
#include "Wire.h"


#define INA219_LIB_VERSION              (F("0.1.3"))


class INA219
{
public:
  //  address between 0x40 and 0x4F
  explicit INA219(const uint8_t address, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(const uint8_t sda, const uint8_t scl);
#endif
  bool     begin();
  bool     isConnected();


  //  CORE FUNCTIONS               //  Register
  float    getShuntVoltage();      //  01
  float    getBusVoltage();        //  02
  float    getPower();             //  03
  float    getCurrent();           //  04
  bool     getMathOverflowFlag();  //  02
  bool     getConversionFlag();    //  02


  //  SCALE HELPERS
  float    getBusVoltage_mV()   { return getBusVoltage() * 1e3; };
  float    getShuntVoltage_mV() { return getShuntVoltage() * 1e3; };
  float    getCurrent_mA()      { return getCurrent() * 1e3; };
  float    getPower_mW()        { return getPower() * 1e3; };
  float    getShuntVoltage_uV() { return getShuntVoltage() * 1e6; };
  float    getCurrent_uA()      { return getCurrent() * 1e6; };
  float    getPower_uW()        { return getPower() * 1e6; };


  //  CONFIGURATION
  //  need improvement API wise.
  void     reset();
  //  voltage = 16, 32  (values below 32 are rounded to 16 or 32)
  bool     setBusVoltageRange(uint8_t voltage = 16);
  uint8_t  getBusVoltageRange();  //  returns 16 or 32.
  //  factor = 1, 2, 4, 8
  bool     setGain(uint8_t factor = 1);
  uint8_t  getGain();
  //  mask 
  bool     setBusADC(uint8_t mask = 0x03);
  uint8_t  getBusADC();
  bool     setShuntADC(uint8_t mask = 0x03);
  uint8_t  getShuntADC();
  // Operating mode = 0..7
  bool     setMode(uint8_t mode = 7);
  uint8_t  getMode();
  bool     shutDown()                  { return setMode(0); };
  bool     setModeShuntTrigger()       { return setMode(1); };
  bool     setModeBusTrigger()         { return setMode(2); };
  bool     setModeShuntBusTrigger()    { return setMode(3); };
  bool     setModeADCOff()             { return setMode(4); };
  bool     setModeShuntContinuous()    { return setMode(5); };
  bool     setModeBusContinuous()      { return setMode(6); };
  bool     setModeShuntBusContinuous() { return setMode(7); };  //  default.

  
  //  CALIBRATION
  //  mandatory to set these! read datasheet.
  //  maxCurrent >= 0.001
  //  shunt      >= 0.001
  bool     setMaxCurrentShunt(float maxCurrent = 3.4, 
                              float shunt = 0.002);

  bool     isCalibrated()     { return _current_LSB != 0.0; };

  //  these return zero if not calibrated!
  float    getCurrentLSB()    { return _current_LSB; };
  float    getCurrentLSB_mA() { return _current_LSB * 1e3; };
  float    getCurrentLSB_uA() { return _current_LSB * 1e6; };
  float    getShunt()         { return _shunt; };
  float    getMaxCurrent()    { return _maxCurrent; };


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

