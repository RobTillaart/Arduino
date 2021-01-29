#pragma once

//    FILE: Max44009.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.4.3
// PURPOSE: library for MAX44009 lux sensor Arduino
// HISTORY: See Max440099.cpp

//  breakout MAX44009 / GY-49
//
//      +--------+
//  VCC |o       |
//  GND |o       |
//  SCL |o      o| ADDRESS
//  SDA |o      o| -INT
//      +--------+
//
// ADDRESS:
// 0 = 0x4A
// 1 = 0x4B
//
// INT:
// Connect the INT pin to an pull up resistor
// 0 = interrupt
// 1 = no interrupt
// connect to an LED or an interrupt pin of an Arduino
//


#include "Wire.h"
#include "Arduino.h"


#define MAX44009_LIB_VERSION        (F("0.4.3"))
#define MAX44009_DEFAULT_ADDRESS    0x4A
#define MAX44009_ALT_ADDRESS        0x4B


// REGISTERS
#define MAX44009_INTERRUPT_STATUS   0x00
#define MAX44009_INTERRUPT_ENABLE   0x01
#define MAX44009_CONFIGURATION      0x02
#define MAX44009_LUX_READING_HIGH   0x03
#define MAX44009_LUX_READING_LOW    0x04
#define MAX44009_THRESHOLD_HIGH     0x05
#define MAX44009_THRESHOLD_LOW      0x06
#define MAX44009_THRESHOLD_TIMER    0x07


// CONFIGURATION MASKS
#define MAX44009_CFG_CONTINUOUS     0x80
#define MAX44009_CFG_MANUAL         0x40
#define MAX44009_CFG_CDR            0x08
#define MAX44009_CFG_TIMER          0x07


// ERROR CODES
#define MAX44009_OK                     0
#define MAX44009_ERROR_WIRE_REQUEST    -10
#define MAX44009_ERROR_OVERFLOW        -20
#define MAX44009_ERROR_HIGH_BYTE       -30
#define MAX44009_ERROR_LOW_BYTE        -31


class Max44009
{
public:
  // enum class to prevent bool to be implicitly casted to int
  enum class Boolean { True, False };

#if defined(ESP8266) || defined(ESP32)
  // dataPin and clockPin can be used for ESP8266
  Max44009(const uint8_t address, const uint8_t dataPin, const uint8_t clockPin);
#endif

  // ctor for UNO
  Max44009(const uint8_t address, const Boolean begin = Boolean::True);
  // default ctor with default address
  Max44009(const Boolean begin = Boolean::True);
  // Change I2C interface and address
  void configure(const uint8_t address, TwoWire *wire, const Boolean begin = Boolean::True);

  bool    isConnected();
  float   getLux();
  int     getError();

  void    setHighThreshold(const float);
  float   getHighThreshold(void);
  void    setLowThreshold(const float);
  float   getLowThreshold(void);
  void    setThresholdTimer(const uint8_t);    // 2 seems practical minimum
  uint8_t getThresholdTimer();

  void    enableInterrupt()    { write(MAX44009_INTERRUPT_ENABLE, 1); };
  void    disableInterrupt()   { write(MAX44009_INTERRUPT_ENABLE, 0); };
  bool    interruptEnabled()   { return read(MAX44009_INTERRUPT_ENABLE) & 0x01; };
  uint8_t getInterruptStatus() { return read(MAX44009_INTERRUPT_STATUS) & 0x01; };

  // check datasheet for detailed behavior
  void    setConfiguration(uint8_t);
  uint8_t getConfiguration();
  void    setAutomaticMode();
  void    setContinuousMode();    // uses more power
  void    clrContinuousMode();    // uses less power
  // CDR = Current Divisor Ratio
  // CDR = 1 ==> only 1/8th is measured
  // TIM = Time Integration Measurement (table)
  // 000  800ms
  // 001  400ms
  // 010  200ms
  // 011  100ms
  // 100   50ms       manual only
  // 101   25ms       manual only
  // 110   12.5ms     manual only
  // 111    6.25ms    manual only
  void    setManualMode(uint8_t CDR, uint8_t TIM);
  int     getIntegrationTime() { return 800 >> (getConfiguration() & 0x07); };  // ms

private:
  void    setThreshold(uint8_t, float);
  float   getThreshold(uint8_t);

  uint8_t read(uint8_t reg);
  void    write(uint8_t, uint8_t);

  uint8_t _address;
  uint8_t _data;
  int     _error;

  TwoWire* _wire;
};

// END OF FILE
