#pragma once
//
//    FILE: ADT7470.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library for I2C ADT7470 Fan Monitoring
//     URL: https://github.com/RobTillaart/ADT7470
//          http://forum.arduino.cc/index.php?topic=363218.0
//
// HISTORY:
// see ADT7470.cpp file


#include "Arduino.h"
#include "Wire.h"

#define ADT7470_LIB_VERSION         (F("0.1.3"))

#ifndef ADT7470_TIMEOUT
#define ADT7470_TIMEOUT             1000
#endif
#ifndef ADT7470_ADDR_HIGH
#define ADT7470_ADDR_HIGH           0x2F
#endif
#ifndef ADT7470_ADDR_LOW
#define ADT7470_ADDR_LOW            0x2C
#endif
#ifndef ADT7470_ADDR_FLOAT
#define ADT7470_ADDR_FLOAT          0x2E
#endif


class ADT7470
{
public:
  ADT7470(uint8_t address);

#if defined (ESP8266) || defined(ESP32)
  void begin(uint8_t sda, uint8_t scl);
#endif
  void begin();

  // GENERIC
  boolean  isConnected();
  uint8_t  getRevision();
  uint8_t  getDeviceID();  // should return 0x70
  uint8_t  getCompanyID(); // should return 0x41
  void     startMonitoring();
  void     stopMonitoring();
  void     powerDown();
  void     powerUp();


  // MEASURE TEMPERATURE - not tested
  // Page 13    daisy chained specific TMP05 / TMP06 sensors
  int8_t   getTemperature(uint8_t idx);
  int8_t   getMaxTemperature();
  // Page 16
  bool     setTemperatureLimit(uint8_t idx, int8_t low, int8_t high);
  int8_t   getTemperatureLowLimit(uint8_t idx);
  int8_t   getTemperatureHighLimit(uint8_t idx);


  // SET FAN SPEED
  // Page 25    idx = 0..3
  bool     setPWM(uint8_t idx, uint8_t val);  
  uint8_t  getPWM(uint8_t idx);
  // Page 36    val = 0..7
  bool     setFanLowFreq(uint8_t val = 0);    // PWM freq..
  bool     setFanHighFreq(uint8_t val = 0);
  // Page 21
  void     setInvertPWM(uint8_t idx);
  uint8_t  getInvertPWM(uint8_t idx);


  // MEASURE FAN SPEED
  // Page 23-24   idx = 0..3   val = 1..4
  bool     setPulsesPerRevolution(uint8_t idx, uint8_t val);
  // returns 1..4
  uint8_t  getPulsesPerRevolution(uint8_t idx);
  // P30 FST_TCH   fast = measurement/250 ms  slow = measurement/1000ms. 
  void     setFastTach();
  void     setSlowTach();
  uint16_t getTach(uint8_t idx);
  uint32_t getRPM(uint8_t idx);
  // Page 16 TACH/FAN ALARM
  bool     setTachLimits(uint8_t idx, uint16_t low, uint16_t high);
  uint16_t getTachLowLimits(uint8_t idx);
  uint16_t getTachHighLimits(uint8_t idx);


  // INTERRUPTS
  // Page 17 - every bit set 0..10 represents one temp limit (high /low) exceeded
  // if it return 0 => no limits exceeded.
  uint16_t getTemperatureIRQstatus();
  uint8_t  getFanIRQstatus();
  // idx = 0..9
  void     setTemperatureIRQMask(uint8_t idx);
  void     clrTemperatureIRQMask(uint8_t idx);
  uint8_t  getTemperatureIRQMask(uint8_t idx);
  // idx = 0..3
  void     setFanIRQMask(uint8_t idx);
  void     clrFanIRQMask(uint8_t idx);
  uint8_t  getFanIRQMask(uint8_t idx);


  // REGISTER OPERATORS
  // set/clr one or more bits. 
  void     setRegMask(uint8_t reg, uint8_t mask);
  void     clrRegMask(uint8_t reg, uint8_t mask);
  // low level register interface
  uint8_t  getReg8(uint8_t reg);
  void     setReg8(uint8_t reg, uint8_t val);
  uint16_t getReg16(uint8_t reg);
  void     setReg16(uint8_t reg, uint16_t val);


private:
  // LOW LEVEL I2C
  int     _write(const uint8_t reg, uint8_t value);
  int     _write(const uint8_t reg, uint8_t *buffer, uint8_t length);
  int     _read(const uint8_t reg, uint8_t *value);
  int     _read(const uint8_t reg, uint8_t *buffer, uint8_t length);

  uint8_t  _address = 0;
};

// -- END OF FILE --
