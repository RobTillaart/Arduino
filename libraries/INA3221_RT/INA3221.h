#pragma once
//    FILE: INA3221.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2024-02-05
// PURPOSE: Arduino library for the I2C INA3221 3 channel voltage and current sensor.
//     URL: https://github.com/RobTillaart/INA3221_RT
//
//  Read the datasheet for the details


#include "Arduino.h"
#include "Wire.h"


#define INA3221_LIB_VERSION                "0.3.0"


class INA3221
{
public:
  //  address between 0x40 and 0x43
  explicit INA3221(const uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //  CORE functions
  float    getBusVoltage(uint8_t channel);       //  Volt
  float    getShuntVoltage(uint8_t channel);     //  Volt
  float    getCurrent(uint8_t channel);          //  Ampere
  float    getPower(uint8_t channel);            //  Watt

  //  wrappers milli range
  float    getBusVoltage_mV(uint8_t channel)   { return getBusVoltage(channel)   * 1e3; };
  float    getShuntVoltage_mV(uint8_t channel) { return getShuntVoltage(channel) * 1e3; };
  float    getCurrent_mA(uint8_t channel)      { return getCurrent(channel)      * 1e3; };
  float    getPower_mW(uint8_t channel)        { return getPower(channel)        * 1e3; };

  //  wrappers micro range
  float    getBusVoltage_uV(uint8_t channel)   { return getBusVoltage(channel)   * 1e6; };
  float    getShuntVoltage_uV(uint8_t channel) { return getShuntVoltage(channel) * 1e6; };
  float    getCurrent_uA(uint8_t channel)      { return getCurrent(channel)      * 1e6; };
  float    getPower_uW(uint8_t channel)        { return getPower(channel)        * 1e6; };

  //  SHUNT
  int      setShuntR(uint8_t channel, float ohm);
  float    getShuntR(uint8_t channel);

  //  SHUNT ALERT WARNINGS & CRITICAL
  //  NOTE: full scale voltage == 163.8 mV == 163800 uV
  //  NOTE: LSB == 40 uV so microVolt should be >= 40uV
  int      setCriticalAlert(uint8_t channel, uint32_t microVolt);
  uint32_t getCriticalAlert(uint8_t channel);  //  returns microVolt
  int      setWarningAlert(uint8_t channel, uint32_t microVolt);
  uint32_t getWarningAlert(uint8_t channel);   //  returns microVolt

  //  Wrappers using milliAmpere (Shunt must be set correctly!).
  //  NOTE: LSB = 40 uV so milliAmpere should be >= 0.4 mA (assume R = 0.1)
  int      setCriticalCurrent(uint8_t channel, float milliAmpere);
  float    getCriticalCurrent(uint8_t channel);
  int      setWarningCurrent(uint8_t channel, float milliAmpere);
  float    getWarningCurrent(uint8_t channel);

  //  SHUNT VOLTAGE SUM
  //  NOTE: LSB = 40 uV (15 bits)
  int32_t  getShuntVoltageSum();       //  returns microVolt
  //  microVolt = max 655.320 == 16383L * 40L
  int      setShuntVoltageSumLimit(int32_t microVolt);
  int32_t  getShuntVoltageSumLimit();  //  returns microVolt

  //  CONFIGURATION
  //  all fields at once. (short/fast/atomic code)
  int      setConfiguration(uint16_t mask = 0x7127);  //  default!
  uint16_t getConfiguration();
  //  individual functions.
  int      reset();
  int      enableChannel(uint8_t channel);
  int      disableChannel(uint8_t channel);
  int      getEnableChannel(uint8_t channel);
  int      setAverage(uint8_t avg = 0);  //  0..7
  int      getAverage();
  int      setBusVoltageConversionTime(uint8_t bvct = 4);  //  0..7
  int      getBusVoltageConversionTime();
  int      setShuntVoltageConversionTime(uint8_t svct = 4);
  int      getShuntVoltageConversionTime();
  //  operating mode
  int      setMode(uint8_t mode = 7);  //  default 7 == ModeShuntBusContinuous
  int      getMode();
  int      shutDown()                  { return setMode(0); };
  int      setModeShuntTrigger()       { return setMode(1); };
  int      setModeBusTrigger()         { return setMode(2); };
  int      setModeShuntBusTrigger()    { return setMode(3); };
  int      setModeShuntContinuous()    { return setMode(5); };
  int      setModeBusContinuous()      { return setMode(6); };
  int      setModeShuntBusContinuous() { return setMode(7); };  //  default.

  //  MASK/ENABLE
  //  all fields at once. (short/fast/atomic code)
  int      setMaskEnable(uint16_t mask);
  uint16_t getMaskEnable();
  //  convenience wrappers for MASK/ENABLE?

  //  POWER LIMIT (guards BUS voltage)
  //  max = 4095 * 8 mV = 32760 mV
  int     setPowerUpperLimit(int16_t milliVolt);
  int16_t getPowerUpperLimit();
  int     setPowerLowerLimit(int16_t milliVolt);
  int16_t getPowerLowerLimit();

  //  META information
  uint16_t getManufacturerID();   //  should return 0x5449
  uint16_t getDieID();            //  should return 0x2260


  //  DEBUG (develop)
  uint16_t getRegister(uint8_t reg)
  {
    return _readRegister(reg);
  };
  uint16_t putRegister(uint8_t reg, uint16_t value)
  {
    return _writeRegister(reg, value);
  };


private:

  uint16_t _readRegister(uint8_t reg);
  uint16_t _writeRegister(uint8_t reg, uint16_t value);
  float    _shunt[3];

  uint8_t   _address;
  TwoWire * _wire;
};


//  -- END OF FILE --

