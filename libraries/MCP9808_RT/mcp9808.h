#pragma once
//
//    FILE: mcp9808.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: Arduino Library for I2C mcp9808 temperature sensor
//    DATE: 2020-05-03
//     URL: https://github.com/RobTillaart/MCP9808_RT
//


#include "Arduino.h"
#include "Wire.h"

//  VALID ADDRESSES,
//  max 8 sensors on one bus
//  24..31  ==  0x18..0x1F


#define MCP9808_LIB_VERSION               (F("0.4.0"))


//  CONFIGURATION REGISTER MASKS
//  check the datasheet for exact usage
#define MCP9808_THYSTERESIS               0x0600
#define MCP9808_SHUTDOWN                  0x0100
#define MCP9808_CRIT_LOCK                 0x0080
#define MCP9808_WIN_LOCK                  0x0040
#define MCP9808_INT_CLEAR                 0x0020
#define MCP9808_ALERT_STATUS              0x0010
#define MCP9808_ALERT_CTRL                0x0008
#define MCP9808_ALERT_SELECT              0x0004
#define MCP9808_ALERT_POLAR               0x0002
#define MCP9808_ALERT_MODE                0x0001


class MCP9808
{
public:
  MCP9808(const uint8_t address, TwoWire *wire = &Wire);

  bool      isConnected();

  void      setConfigRegister(uint16_t configuration);
  uint16_t  getConfigRegister();

  void      setTupper(float temperature);
  float     getTupper();
  void      setTlower(float temperature);
  float     getTlower();
  void      setTcritical(float temperature);
  float     getTcritical();

  void      setOffset(float offset = 0.0);
  float     getOffset();
  float     getTemperature();

  //  getStatus() returns 0..7
  //  to get latest status, getTemperature() must be called first
  uint8_t   getStatus();

  void      setResolution(uint8_t resolution = 3);
  uint8_t   getResolution();

  uint16_t  getManufacturerID();
  uint8_t   getDeviceID();
  uint8_t   getRevision();

  //  Reserved Register, not used
  uint16_t  getRFU();


private:
  float     _offset = 0;
  uint8_t   _status = 0;     //  0..7
  uint8_t   _address;
  TwoWire*  _wire;

  void      writeFloat(uint8_t reg, float f);
  float     readFloat(uint8_t reg);

  void      writeReg8(uint8_t reg, uint8_t value);
  uint8_t   readReg8(uint8_t reg);
  void      writeReg16(uint8_t reg, uint16_t value);
  uint16_t  readReg16(uint8_t reg);
};


//  -- END OF FILE --

