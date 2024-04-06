#pragma once
//
//    FILE: ADT7470.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for I2C ADT7470 Fan Monitoring
//     URL: https://github.com/RobTillaart/ADT7470
//          http://forum.arduino.cc/index.php?topic=363218.0


#include "Arduino.h"
#include "Wire.h"

#define ADT7470_LIB_VERSION         (F("0.2.1"))

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
  ADT7470(uint8_t address, TwoWire *wire = &Wire);

  bool begin();

  //  GENERIC
  bool     isConnected();
  uint8_t  getRevision();
  uint8_t  getDeviceID();     //  should return 0x70
  uint8_t  getCompanyID();    //  should return 0x41
  void     startMonitoring();
  void     stopMonitoring();
  void     powerDown();
  void     powerUp();


  //  MEASURE TEMPERATURE - not tested
  //  Page 13    daisy chained specific TMP05 / TMP06 sensors
  int8_t   getTemperature(uint8_t index);
  int8_t   getMaxTemperature();
  //  Page 16
  bool     setTemperatureLimit(uint8_t index, int8_t low, int8_t high);
  int8_t   getTemperatureLowLimit(uint8_t index);
  int8_t   getTemperatureHighLimit(uint8_t index);


  //  SET FAN SPEED
  //  Page 25    index = 0..3
  bool     setPWM(uint8_t index, uint8_t value);
  uint8_t  getPWM(uint8_t index);
  //  Page 36    value = 0..7
  bool     setFanLowFreq(uint8_t value = 0);    // PWM freq..
  bool     setFanHighFreq(uint8_t value = 0);
  //  Page 21
  void     setInvertPWM(uint8_t index);
  uint8_t  getInvertPWM(uint8_t index);


  //  MEASURE FAN SPEED
  //  Page 23-24   index = 0..3   value = 1..4
  bool     setPulsesPerRevolution(uint8_t index, uint8_t value);
  //  returns 1..4
  uint8_t  getPulsesPerRevolution(uint8_t index);
  //  P30 FST_TCH   fast = measurement/250 ms  slow = measurement/1000ms.
  void     setFastTach();
  void     setSlowTach();
  uint16_t getTach(uint8_t index);
  uint32_t getRPM(uint8_t index);
  // Page 16 TACH/FAN ALARM
  bool     setTachLimits(uint8_t index, uint16_t low, uint16_t high);
  uint16_t getTachLowLimits(uint8_t index);
  uint16_t getTachHighLimits(uint8_t index);


  //  INTERRUPTS
  //  Page 17 - every bit set 0..10 represents one temp limit (high /low) exceeded
  //  if it return 0 => no limits exceeded.
  uint16_t getTemperatureIRQstatus();
  uint8_t  getFanIRQstatus();
  //  index = 0..9
  void     setTemperatureIRQMask(uint8_t index);
  void     clrTemperatureIRQMask(uint8_t index);
  uint8_t  getTemperatureIRQMask(uint8_t index);
  //  index = 0..3
  void     setFanIRQMask(uint8_t index);
  void     clrFanIRQMask(uint8_t index);
  uint8_t  getFanIRQMask(uint8_t index);


  //  REGISTER OPERATORS
  //  set/clr one or more bits.
  void     setRegMask(uint8_t reg, uint8_t mask);
  void     clrRegMask(uint8_t reg, uint8_t mask);
  //  low level register interface
  uint8_t  getReg8(uint8_t reg);
  void     setReg8(uint8_t reg, uint8_t value);
  uint16_t getReg16(uint8_t reg);
  void     setReg16(uint8_t reg, uint16_t value);


private:
  //  LOW LEVEL I2C
  int     _write(const uint8_t reg, uint8_t value);
  int     _write(const uint8_t reg, uint8_t *buffer, uint8_t length);
  int     _read(const uint8_t reg, uint8_t *value);
  int     _read(const uint8_t reg, uint8_t *buffer, uint8_t length);

  uint8_t  _address = 0;
  TwoWire* _wire;
};


//  -- END OF FILE --
