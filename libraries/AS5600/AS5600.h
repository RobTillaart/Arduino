#pragma once
//
//    FILE: AS5600.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for AS5600 magnetic rotation meter
//    DATE: 2022-05-28
//     URL: https://github.com/RobTillaart/AS5600


#include "Arduino.h"
#include "Wire.h"


#define AS5600_LIB_VERSION              (F("0.1.0"))

#define AS5600_CLOCK_WISE               1
#define AS5600_COUNTERCLOCK_WISE        0

#define AS5600_RAW_TO_DEGREES           (0.0879120879120879121)

class AS5600
{
public:
  AS5600(TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(int sda, int scl, int directionPin =  AS5600_CLOCK_WISE);
#endif
  bool     begin(int directionPin = AS5600_CLOCK_WISE);
  bool     isConnected();

  uint8_t  getAddress() { return _address; };  //  0x36


  //  CONFIGURE
  //  read datasheet first
  void     setDirection(uint8_t direction = AS5600_CLOCK_WISE);
  uint8_t  getDirection();

  uint8_t  getZMCO();

  void     setZPosition(uint16_t value);
  uint16_t getZPosition();

  void     setMPosition(uint16_t value);
  uint16_t getMPosition();

  void     setMaxAngle(uint16_t value);
  uint16_t getMaxAngle();

  //  access the whole configuration register
  void     setConfigure(uint16_t value);
  uint16_t getConfigure();

  //  details configure
  void     setPowerMode(uint8_t powerMode);    // 0..3
  uint8_t  getPowerMode();

  void     setHysteresis(uint8_t hysteresis);  // 0..3
  uint8_t  getHysteresis();

  void     setOutputMode(uint8_t outputMode);  // 0..2
  uint8_t  getOutputMode();

  void     setPWMFrequency(uint8_t pwmFreq);   // 0..3
  uint8_t  getPWMFrequency();

  void     setSlowFilter(uint8_t mask);        // 0..3
  uint8_t  getSlowFilter();

  void     setFastFilter(uint8_t mask);        // 0..7
  uint8_t  getFastFilter();

  void     setWatchDog(uint8_t mask);          // 0..1
  uint8_t  getWatchDog();


  //  OUTPUT REGISTERS
  uint16_t rawAngle();
  uint16_t readAngle();


  //  STATUS REGISTERS
  uint8_t  readStatus();
  uint8_t  readAGC();
  uint16_t readMagnitude();

  //  detail status
  bool     detectMagnet();


  //  BURN COMMANDS
  //  DO NOT UNCOMMENT - USE AT OWN RISK - READ DATASHEET
  //  void burnAngle();
  //  void burnSetting();


private:
  uint8_t readReg(uint8_t reg);
  uint8_t writeReg(uint8_t reg, uint8_t value);

  const uint8_t _address = 0x36;
  uint8_t _directionPin;
  uint8_t _error         = 0;   // TODO

  TwoWire*  _wire;
};


//  -- END OF FILE --


