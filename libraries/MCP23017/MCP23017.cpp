//
//    FILE: MCP23017.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for I2C MCP23017 16 channel port expander
//    DATE: 2019-10-12
//     URL: https://github.com/RobTillaart/MCP23017_RT
// LICENSE: MIT
//
// HISTORY:
// 0.1.0    2019-10-12 initial version
// 0.1.1    2020-06-19 refactor; #pragma once
//
//    TODO: 
//  interrupts
//  caching for performance?
//  INPUT_PULLUP
//

#include "MCP23017.h"

#define MCP23017_DDR_A   0x00   // Data Direction Register
#define MCP23017_DDR_B   0x01
#define MCP23017_PUR_A   0x0C   // Pull Up Resistors
#define MCP23017_PUR_B   0x0D

#define MCP23017_IOCR    0x0A   // IO control register

#define MCP23017_GPIOA   0x12
#define MCP23017_GPIOB   0x13


MCP23017::MCP23017(uint8_t addr)
{
  _addr = addr;
}

#if defined(ESP8266) || defined(ESP32)
void MCP23017::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  Wire.begin(dataPin, clockPin);
  // Force INPUT_PULLUP
  writeReg(MCP23017_PUR_A, 0xFF);
  writeReg(MCP23017_PUR_B, 0xFF);
}
#endif

void MCP23017::begin()
{
  Wire.begin();
  // Force INPUT_PULLUP
  writeReg(MCP23017_IOCR, 0b00100000); // disable addres increment (datasheet)
  writeReg(MCP23017_PUR_A, 0xFF);
  writeReg(MCP23017_PUR_B, 0xFF);
}

// single pin interface
// pin 0..15
// value INPUT, OUTPUT, INPUT_PULLUP  
// TODO: split INPUT_PULLUP and INPUT, for now they are the same
void MCP23017::pinMode(uint8_t pin, uint8_t value)
{
  if (pin > 15) return;
  if (value != INPUT && value != INPUT_PULLUP && value != OUTPUT) return;
  
  uint8_t DDR = MCP23017_DDR_A;   // Data Direction Register
  if (pin > 7)
  {
    DDR = MCP23017_DDR_B;
    pin -= 8;
  }
  uint8_t val = readReg(DDR);
  uint8_t mask = 1 << pin;
  // only work with valid
  if (value == INPUT || value == INPUT_PULLUP)
  {
    val |= mask;
  }
  else if (value == OUTPUT)
  {
    val &= ~mask;
  }
  // other values won't change val ....
  writeReg(DDR, val);
}

void MCP23017::digitalWrite(uint8_t pin, uint8_t value)   // pin = 0..15
{
  if (pin > 15) return;
  uint8_t IOR = MCP23017_GPIOA;
  if (pin > 7)
  {
    IOR = MCP23017_GPIOB;
    pin -= 8;
  }
  uint8_t val = readReg(IOR);
  uint8_t mask = 1 << pin;
  if (value) val |= mask;
  else val &= ~mask;
  writeReg(IOR, val);
}

uint8_t MCP23017::digitalRead(uint8_t pin)
{
  if (pin > 15) return -100;    // TODO magic number
  uint8_t IOR = MCP23017_GPIOA;
  if (pin > 7)
  {
    IOR = MCP23017_GPIOB;
    pin -= 8;
  }
  uint8_t val = readReg(IOR);
  uint8_t mask = 1 << pin;
  if (val & mask) return HIGH;
  return LOW;
}

// 8 pins interface
// whole register at once
void MCP23017::pinMode8(uint8_t port, uint8_t value)
{
  if (port == 0) writeReg(MCP23017_DDR_A, value);
  if (port == 1) writeReg(MCP23017_DDR_B, value);
  // explicitely ignore other values.
}

void MCP23017::write8(uint8_t port, uint8_t value)   // port = 0..1
{
  if (port == 0) writeReg(MCP23017_GPIOA, value);
  if (port == 1) writeReg(MCP23017_GPIOB, value);
  // explicitely ignore other values.
}

int MCP23017::read8(uint8_t port)
{
  if (port == 0) return readReg(MCP23017_GPIOA);
  if (port == 1) return readReg(MCP23017_GPIOB);
  return -100;  // TODO magic number
}


void MCP23017::writeReg(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t MCP23017::readReg(uint8_t reg)
{
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(_addr, (uint8_t)1);
  return Wire.read();
}

// -- END OF FILE --
