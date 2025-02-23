#pragma once
//
//    FILE: PCT2075.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-11
// VERSION: 0.1.1
// PURPOSE: Arduino library for I2C PCT2075 temperature sensor / thermal watchdog.
//     URL: https://github.com/RobTillaart/PCT2075
//
//  user must handle OS pin


#include "Arduino.h"
#include "Wire.h"


#define PCT2075_LIB_VERSION         (F("0.1.1"))

#define PCT2075_OK                  0x00
#define PCT2075_PARAM_ERROR         0x81
#define PCT2075_I2C_ERROR           0x82


class PCT2075
{
public:
  //  CONSTRUCTOR
  //   address see table 5+6 datasheet
  explicit  PCT2075(const uint8_t address, TwoWire * wire = &Wire);

  bool      begin();
  bool      isConnected();
  uint8_t   getAddress();  //  convenience.

  //  CONFIGURATION
  void      setConfiguration(uint8_t mask);
  uint8_t   getConfiguration();

  void      setOSFQUE(uint8_t value);
  void      setOSPolarityLOW();
  void      setOSPolarityHIGH();
  void      setOSComparatorMode();
  void      setOSInterruptMode();
  void      wakeUp();
  void      shutDown();

  //  TEMPERATURE
  float     getTemperature();

  //  OPERATING MODE - OS pin => datasheet section 7
  void      setHysteresis(float temp);
  float     getHysteresis();
  void      setOverTemperature(float temp);
  float     getOverTemperature();

  //  SAMPLE FREQUENCY
  void      setSampleDelay(uint8_t steps);  //  0..31, step == 100 ms
  uint8_t   getSampleDelay();

  //  ERROR HANDLING
  uint16_t  lastError();


  //  public for now (until stable)
  uint16_t  _read8(uint8_t reg);
  uint16_t  _read16(uint8_t reg);
  uint16_t  _write8(uint8_t reg, uint8_t value);
  uint16_t  _write16(uint8_t reg, uint16_t value);


private:

  uint8_t   _error = 0;
  uint8_t   _address;
  TwoWire*  _wire;


};


//  -- END OF FILE --

