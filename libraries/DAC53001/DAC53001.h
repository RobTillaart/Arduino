#pragma once
//
//    FILE: DAC53001.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-12
// VERSION: 0.1.0
// PURPOSE: Arduino library for I2C DAC53001 10 bit DAC.
//     URL: https://github.com/RobTillaart/DAC53001
//
//  Connections see datasheet chapter 5 Pin Configuration and Functions


#include "Arduino.h"
#include "Wire.h"


#define DAC53001_LIB_VERSION         (F("0.1.0"))

#define DAC53001_OK                  0x00
#define DAC53001_PARAM_ERROR         0x81
#define DAC53001_I2C_ERROR           0x82


enum DACX300X_reference
{                    //  GAIN
  External  = 0x00,  //  1x
  VDD       = 0x01,  //  1x
  Internal1 = 0x02,  //  1.5x
  Internal2 = 0x03,  //  2x
  Internal3 = 0x04,  //  3x
  Internal4 = 0x05   //  4x
};


class DAC53001
{
  public:
  //  CONSTRUCTOR
  explicit  DAC53001(const uint8_t address, TwoWire * wire = &Wire);

  bool      begin();
  bool      isConnected();
  uint8_t   getAddress();     //  convenience.
  uint16_t  getMaxValue();    //  1023 (10 bit) or 4095 (12 bit)
  uint8_t   getChannels();    //  1 or 2


  //  DAC-X-VOUT-CMP-CONFIG  page 58
  //  VOLTAGE REFERENCE
  void      setReference(DACX300X_reference mode, uint8_t channel = 0);
  uint8_t   getReference(uint8_t channel = 0);


  //  DAC-X-IOUT-MISC-CONFIG page 59
  //  CURRENT RANGE
  //  00     0 μA  to    25 μA
  //  01     0 μA  to    50 μA
  //  02     0 μA  to   125 μA
  //  03     0 μA  to   250 μA
  //
  //  04     0 μA  to   ‒24 μA
  //  05     0 μA  to   ‒48 μA
  //  06     0 μA  to  ‒120 μA
  //  07     0 μA  to  ‒240 μA
  //
  //  08    ‒25 μA  to  +25 μA
  //  09    ‒50 μA  to  +50 μA
  //  10   ‒125 μA  to +125 μA
  //  11   ‒250 μA  to +250 μA
  void      setCurrentRange(uint8_t range, uint8_t channel = 0);
  uint8_t   getCurrentRange(uint8_t channel = 0);


  //  COMMON-CONFIG page 62
  //  OUTPUT MODE
  //          VOUT                             IOUT
  //  0x00    not allowed                      not allowed
  //  0x01    power up                         power down
  //  0x02    PowerDown + 10 kΩ to AGND        power up
  //  0x03    PowerDown + 10 kΩ to AGND        power down
  //  0x04    PowerDown + 100 kΩ to AGND       power up
  //  0x05    PowerDown + 100 kΩ to AGND       power down
  //  0x06    PowerDown + Hi-Z to AGND         power up
  //  0x07    PowerDown + Hi-Z to AGND         power down
  //
  void      setOutputMode(uint8_t mode, uint8_t channel = 0);
  uint8_t   getOutputMode(uint8_t channel = 0);


  //  GENERAL-STATUS page 65
  uint16_t getStatus();
  uint16_t getDeviceID();
  uint16_t getVersionID();


  //  SETDAC page 62
  uint16_t setDAC(uint16_t value, uint8_t channel = 0);
  uint16_t getDAC(uint8_t channel = 0);


  ////////////////////////////////////////////////////////
  //
  //  OTHER - chapter 7 - page 55 and beyond.
  //  registers not in first releases
  //
  //  NOP                     page 57
  //  DAC_X_MARGIN_HIGH       page 57
  //  DAC_X_MARGIN_LOW        page 57
  //  DAC-X-CMP-MODE-CONFIG   page 59
  //  DAC-X-FUNC-CONFIG       page 60  (direct write / LATCH DAC / CLR / FUNCGEN )
  //  COMMON-TRIGGER          page 63  (reset?)
  //  COMMON-DAC-TRIG         page 64
  //  CMP-STATUS              page 66
  //  GPIO-CONFIG             page 66
  //  DEVICE-MODE-CONFIG      page 68
  //  INTERFACE-CONFIG        page 68
  //  SRAM-CONFIG             page 69
  //  SRAM-DATA               page 69
  //  BRDCAST-DATA            page 69
  //  PM bus commands not over I2C.
  //


  //  ERROR HANDLING
  uint16_t lastError();


  //  SHOULD BE PROTECTED
  //  but allows access to all registers for now
  uint16_t _read16(uint8_t reg);
  uint16_t _write16(uint8_t reg, uint16_t value);


protected:

  uint8_t   _channels;
  uint16_t  _maxValue;
  uint16_t  _error;

  uint32_t  _lastWrite;
  uint8_t   _address;
  TwoWire*  _wire;
};



////////////////////////////////////////
//
//  DERIVED CLASSES
//
//  TODO - DAC53002 - DAC63001 - DAC63002 ??
class DAC53002 : public DAC53001
{
public:
  DAC53002(const uint8_t address, TwoWire * wire = &Wire);
};

class DAC63001 : public DAC53001
{
public:
  DAC63001(const uint8_t address, TwoWire * wire = &Wire);
};

class DAC63002 : public DAC53001
{
public:
  DAC63002(const uint8_t address, TwoWire * wire = &Wire);
};


//  -- END OF FILE --

