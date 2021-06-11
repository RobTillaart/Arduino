#pragma once
//
//    FILE: TCA9555.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for I2C TCA9555 16 channel port expander
//    DATE: 2021-06-09
//     URL: https://github.com/RobTillaart/TCA9555


#include "Arduino.h"
#include "Wire.h"


#define TCA9555_LIB_VERSION    (F("0.1.1"))

#define TCA9555_OK              0x00
#define TCA9555_PIN_ERROR       0x81
#define TCA9555_I2C_ERROR       0x82
#define TCA9555_VALUE_ERROR     0x83
#define TCA9555_PORT_ERROR      0x84

#define TCA9555_INVALID_READ    -100


class TCA9555
{
public:
  TCA9555(uint8_t address, TwoWire *wire = &Wire);


#if defined(ESP8266) || defined(ESP32)
  bool     begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  bool     begin();
  bool     isConnected();


  //  1 PIN INTERFACE
  //  pin    = 0..15
  //  mode  = INPUT, OUTPUT       (INPUT_PULLUP is not supported)
  //  value = LOW, HIGH
  bool     pinMode(uint8_t pin, uint8_t mode);
  bool     digitalWrite(uint8_t pin, uint8_t value);
  uint8_t  digitalRead(uint8_t pin);
  bool     setPolarity(uint8_t pin, uint8_t value);    // input pins only.
  uint8_t  getPolarity(uint8_t pin);


  //  8 PIN INTERFACE
  //  port  = 0..1
  //  mask  = bitpattern
  bool     pinMode8(uint8_t port, uint8_t mask);
  bool     write8(uint8_t port, uint8_t mask);
  int      read8(uint8_t port);
  bool     setPolarity8(uint8_t port, uint8_t value);
  uint8_t  getPolarity8(uint8_t port);


  //  16 PIN INTERFACE
  //  wraps 2x 8 PIN call.
  //  opportunistic implementation of functions
  //  needs error checking in between calls
  
  //  mask  = bitpattern
  bool     pinMode16(uint16_t mask);
  bool     write16(uint16_t mask);
  uint16_t read16();
  bool     setPolarity16(uint16_t mask);
  uint8_t  getPolarity16();


  int      lastError();

protected:
  bool     writeRegister(uint8_t reg, uint8_t value);
  uint8_t  readRegister(uint8_t reg);

  uint8_t   _address;
  TwoWire*  _wire;
  uint8_t   _error;
};


/////////////////////////////////////////////////////////////////////////////
//
// TCA9535 class which is just a wrapper (for now)
// 
class TCA9535 : public TCA9555
{
  TCA9535(uint8_t address, TwoWire *wire = &Wire);
};


// -- END OF FILE --
