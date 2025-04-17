#pragma once
//
//    FILE: TCA9554.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for I2C TCA9554 8 channel port expander.
//    DATE: 2025-01-09
//     URL: https://github.com/RobTillaart/TCA9554


#include "Arduino.h"
#include "Wire.h"


#define TCA9554_LIB_VERSION               (F("0.1.2"))

#define TCA9554_OK                        0x00
#define TCA9554_PIN_ERROR                 0x81
#define TCA9554_I2C_ERROR                 0x82
#define TCA9554_VALUE_ERROR               0x83
#define TCA9554_PORT_ERROR                0x84

#define TCA9554_INVALID_READ              -100


#if !defined(TCA9554_PIN_NAMES)
#define TCA9554_PIN_NAMES

  #define TCA_P00         0
  #define TCA_P01         1
  #define TCA_P02         2
  #define TCA_P03         3
  #define TCA_P04         4
  #define TCA_P05         5
  #define TCA_P06         6
  #define TCA_P07         7

#endif


class TCA9554
{
public:
  TCA9554(uint8_t address, TwoWire *wire = &Wire);

  //  mask has only meaning when mode == OUTPUT
  bool     begin(uint8_t = INPUT, uint8_t mask = 0x00);
  bool     isConnected();
  uint8_t  getAddress();


  //  1 PIN INTERFACE
  //  pin    = 0..15
  //  mode  = INPUT, OUTPUT       (INPUT_PULLUP is not supported)
  //  value = LOW, HIGH
  bool     pinMode1(uint8_t pin, uint8_t mode);
  bool     write1(uint8_t pin, uint8_t value);
  uint8_t  read1(uint8_t pin);
  bool     setPolarity(uint8_t pin, uint8_t value);    //  input pins only.
  uint8_t  getPolarity(uint8_t pin);


  //  8 PIN INTERFACE
  //  port  = 0..1
  //  mask  = bit pattern
  bool     pinMode8(uint8_t mask);
  bool     write8(uint8_t mask);
  int      read8();
  bool     setPolarity8(uint8_t mask);
  uint8_t  getPolarity8();


  //  OTHER
  int      lastError();
  uint8_t  getType();


protected:
  bool     writeRegister(uint8_t reg, uint8_t value);
  uint8_t  readRegister(uint8_t reg);

  uint8_t  _address;
  TwoWire* _wire;
  uint8_t  _error;
  uint8_t  _type;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES TCA9534 PCA9554 PCA95534 CAT9554 CAT9534
//
class TCA9534 : public TCA9554
{
public:
  TCA9534(uint8_t address, TwoWire *wire = &Wire);
};

class PCA9554 : public TCA9554
{
public:
  PCA9554(uint8_t address, TwoWire *wire = &Wire);
};

class PCA9534 : public TCA9554
{
public:
  PCA9534(uint8_t address, TwoWire *wire = &Wire);
};

class CAT9554 : public TCA9554
{
public:
  CAT9554(uint8_t address, TwoWire *wire = &Wire);
};

class CAT9534 : public TCA9554
{
public:
  CAT9534(uint8_t address, TwoWire *wire = &Wire);
};


//  -- END OF FILE --

