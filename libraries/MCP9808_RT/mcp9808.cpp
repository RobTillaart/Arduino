//
//    FILE: mcp9808.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino Library for I2C mcp9808 temperature sensor
//    DATE: 2020-05-03
//     URL: https://github.com/RobTillaart/MCP9808_RT
//
//  HISTORY:
//  0.1.0   2020-05-03  initial version
//  0.1.1   2020-11-12  refactor
//  0.1.2   2020-11-16  removed hasAlert, removed setAlertPin, 
//                      added 2 alert examples, refactor low level
//  0.1.3   2021-01-01  arduino-ci + unit test                    

#include "mcp9808.h"

#define MCP9808_RFU     0x00
#define MCP9808_CONFIG  0x01
#define MCP9808_TUPPER  0x02
#define MCP9808_TLOWER  0x03
#define MCP9808_TCRIT   0x04
#define MCP9808_TA      0x05
#define MCP9808_MID     0x06
#define MCP9808_DID     0x07
#define MCP9808_RES     0x08

/*
  0000 = RFU, Reserved for Future Use (Read-Only register)
  0001 = Configuration register (CONFIG)
  0010 = Alert Temperature Upper Boundary Trip register (TUPPER)
  0011 = Alert Temperature Lower Boundary Trip register (TLOWER)
  0100 = Critical Temperature Trip register (TCRIT)
  0101 = Temperature register (TA)
  0110 = Manufacturer ID register
  0111 = Device ID/Revision register
  1000 = Resolution register
  1xxx = Reserved(1)
*/

#if defined(ESP8266) || defined(ESP32)
MCP9808::MCP9808(const uint8_t address, const uint8_t dataPin, const uint8_t clockPin)
{
  _address = address;
  if ((address < 24) || (_address > 31)) return;
  _wire = &Wire;

  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
}
#else
MCP9808::MCP9808(const uint8_t address)
{
  MCP9808::setAddress(address, &Wire);
}
#endif

bool MCP9808::setAddress(const uint8_t address, TwoWire *wire)
{
  if ((address < 24) || (address > 31)) return false;
  _address = address;
  _wire = wire;
  _wire->begin();
  return true;
}

bool MCP9808::isConnected()
{
  Wire.beginTransmission(_address);
  return (Wire.endTransmission() == 0);
}

void MCP9808::setConfigRegister(uint16_t config)
{
  writeReg16(MCP9808_CONFIG, config);
}

uint16_t MCP9808::getConfigRegister()
{
  return readReg16(MCP9808_CONFIG);
}

void  MCP9808::setTupper(float temp)
{
  writeFloat(MCP9808_TUPPER, temp);
}

float MCP9808::getTupper()
{
  return readFloat(MCP9808_TUPPER);
}

void  MCP9808::setTlower(float temp)
{
  writeFloat(MCP9808_TLOWER, temp);
}

float MCP9808::getTlower()
{
  return readFloat(MCP9808_TLOWER);
}

void  MCP9808::setTcritical(float temp)
{
  writeFloat(MCP9808_TCRIT, temp);
}

float MCP9808::getTcritical()
{
  return readFloat(MCP9808_TCRIT);
}

void MCP9808::setOffset(float offset)
{
  _offset = offset;
};

float MCP9808::getOffset()
{
  return _offset; 
};

float MCP9808::getTemperature()
{
  return readFloat(MCP9808_TA) + _offset;
}

uint8_t MCP9808::getStatus()
{
  return _status;
}

uint16_t MCP9808::getManufacturerID()
{
  return readReg16(MCP9808_MID);
}

uint8_t MCP9808::getDeviceID()
{
  return readReg16(MCP9808_DID) >> 8;
}

uint8_t MCP9808::getRevision()
{
  return readReg16(MCP9808_DID) & 0xFF;
}

void MCP9808::setResolution(uint8_t res)
{
  if (res < 4) writeReg8(MCP9808_RES, res);
}

uint8_t MCP9808::getResolution()
{
  return readReg8(MCP9808_RES);
}

uint16_t MCP9808::getRFU()
{
  return readReg16(MCP9808_RFU);
}


////////////////////////////////////////////////////////////////
//
// PRIVATE
//
void MCP9808::writeFloat(uint8_t reg, float f)
{
  bool neg = (f < 0.0);
  if (neg) f = -f;
  uint16_t val = uint16_t(f * 4 + 0.5) * 4;
  if (neg) val |= 0x1000;
  writeReg16(reg, val);
}

float MCP9808::readFloat(uint8_t reg)
{
  uint16_t val = readReg16(reg);
  if (reg == MCP9808_TA)
  {
    _status = (val & 0xE000) >> 13;
  }
  if (val & 0x1000)  // negative value
  {
    return 256 - (val & 0x0FFF) * 0.0625;
  }
  return (val & 0x0FFF) * 0.0625;
}

void MCP9808::writeReg8(uint8_t reg, uint8_t value)
{
  if (reg > MCP9808_RES) return;  // see p.16
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t MCP9808::readReg8(uint8_t reg)
{
  if (reg > MCP9808_RES) return 0;  // see p.16
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(_address, (uint8_t)1);
  return Wire.read();
}

void MCP9808::writeReg16(uint8_t reg, uint16_t value)
{
  if (reg > MCP9808_RES) return;  // see p.16
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write(value >> 8);   // hi byte
  Wire.write(value & 0xFF); // lo byte
  Wire.endTransmission();
}

uint16_t MCP9808::readReg16(uint8_t reg)
{
  if (reg > MCP9808_RES) return 0;  // see p.16
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(_address, (uint8_t)2);
  uint16_t val = Wire.read() << 8;
  val += Wire.read();
  return val;
}

// -- END OF FILE --
