#pragma once
//    FILE: APDS9900.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2024-12-09
// PURPOSE: Arduino library for the APDS9900 environment sensor.
//     URL: https://github.com/RobTillaart/APDS9900
//
//  Read the datasheet for the details


#include "Arduino.h"
#include "Wire.h"


#define APDS9900_LIB_VERSION          (F("0.2.0"))


class APDS9900
{
public:
  APDS9900(TwoWire * wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //
  //  SLEEP
  //
  void     wakeUp();  //  full awake Enable WEN = Wait, PEN = Prox, AEN = ALS, PON = Power On
  void     sleep();

  //
  //  TIMING
  //
  //  milliseconds in steps of 2.72 ms, range 3..696
  void     setIntegrationTime(uint16_t milliseconds);
  uint16_t getIntegrationTime();  //  might differ slightly due to rounding.

  //  USE WITH CARE READ DATASHEET
  //  milliseconds in steps of 2.72 ms, range 3..696
  void     setProximityTime(uint16_t milliseconds = 3);
  uint16_t getProximityTime();  //  might differ slightly due to rounding.

  //  if milliseconds > 696, WLONG = TRUE
  //  WLONG = false: milliseconds in steps of 2.72 ms, range 3..696
  //  WLONG = true:  milliseconds in steps of 32 ms, range 696..8192
  void     setWaitTime(uint16_t milliseconds);
  uint16_t getWaitTime();  //  might differ slightly due to rounding.

  //
  //  INTERRUPTS
  //
  //  lowTH must be smaller than highTH
  bool     setALSThresholds(uint16_t lowTH, uint16_t highTH);
  bool     setPROXThresholds(uint16_t lowTH, uint16_t highTH);
  bool     setALSInterruptPersistence(uint8_t value);   //  0..15
  bool     setPROXInterruptPersistence(uint8_t value);  //  0..15 see datasheet for meaning.

  //
  //  PPCount
  //
  void     setProximityPulseCount(uint8_t value);
  uint8_t  getProximityPulseCount();

  //
  //  CONFIGURATION datasheet P22
  //
  //  0 = 100 mA, 1 = 50 mA, 2 = 25 mA, 3 = 12.5 mA
  bool     setLedDriveStrength(uint8_t strength);
  uint8_t  getLedDriveStrength();  //  returns 0, 1, 2, 3

  //  channel must be 2 - datasheet P22
  //  read datasheet
  bool     setProximityDiodeSelect(uint8_t channel);
  uint8_t  getProximityDiodeSelect();  //  returns 2

  //  gain must be 0 - datasheet P22
  //  read datasheet
  bool     setProximityGain(uint8_t gain);
  uint8_t  getProximityGain();  //  returns 00 == 1x.

  //  0 = 1x,  1 = 8x,  2 = 16x,  3 = 120x
  bool     setALSGain(uint8_t gain);
  //  returns 1, 8, 16 or 120 actual gain, so not actual value.
  uint8_t  getALSGain();

  //
  //  MISC
  //
  uint8_t  getRevision();
  uint8_t  getDeviceID();

  //
  //  STATUS
  //
  uint8_t  getStatus();

  //
  //  MEASUREMENTS
  //
  //  LUX - datasheet page 9.
  //  Glass Attenuation Factor = default 0.48
  float    getLux(float GA = 0.48);
  //
  //  raw data
  uint16_t getALS_CDATA();
  uint16_t getALS_IRDATA();
  uint16_t getPROX_DATA();

  //
  //  ERROR
  //
  int      getLastError();

  //  SHOULD BE PROTECTED but allows full access at lowest level.
  //  will be moved when not experimental.
  //
  int      writeRegister(uint8_t reg);  //  typically only COMMAND call.
  int      writeRegister(uint8_t reg, uint8_t value);
  int      writeRegister16(uint8_t reg, uint16_t value);
  uint8_t  readRegister(uint8_t reg);
  uint16_t readRegister16(uint8_t reg);


protected:
  const uint8_t _address = 0x39;
  TwoWire  *    _wire;

  int      _error;

};


////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
class APDS9901 : public APDS9900
{
public:
  APDS9901(TwoWire * wire = &Wire);
};



//  -- END OF FILE --
