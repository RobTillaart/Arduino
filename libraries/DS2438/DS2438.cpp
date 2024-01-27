//
//    FILE: DS2438.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2023-07-28
// PURPOSE: Arduino Library for DS2438 battery monitor
//     URL: https://github.com/RobTillaart/DS2438


#include "DS2438.h"


//      OneWire commands
#define DS2438_READ_TEMPERATURE     0x44
#define DS2438_READ_VOLTAGE         0xB4

#define DS2438_RECALL_SCRATCH       0xB8
#define DS2438_READ_SCRATCH         0xBE
#define DS2438_WRITE_SCRATCH        0x4E
#define DS2438_COPY_SCRATCH         0x48


#define DS2438_CONVERSION_DELAY     10

//  bits configuration register 
#define DS2438_CFG_IAD              0
#define DS2438_CFG_CA               1
#define DS2438_CFG_EE               2
#define DS2438_CFG_AD               3


DS2438::DS2438(OneWire * ow)
{
  _oneWire = ow;
  //  no sensor found yet
  _addressFound = false;

  //  no data read yet
  _temperature = DS2438_INVALID;
  _vad         = DS2438_INVALID;
  _vdd         = DS2438_INVALID;
  _current     = DS2438_INVALID;
  _inverseR    = DS2438_INVALID;
}


bool DS2438::begin(uint8_t retries)
{
  return isConnected(retries);
}


bool DS2438::isConnected(uint8_t retries)
{
  if (_oneWire == NULL) return false;
  _addressFound = false;
  for (uint8_t rtr = retries; (rtr > 0) && (_addressFound == false); rtr--)
  {
    _oneWire->reset();
    _oneWire->reset_search();
    _address[0] = 0x00;
    _oneWire->search(_address);
    _addressFound = (_address[0] != 0x00) && (_oneWire->crc8(_address, 7) == _address[7]);
  }
  return _addressFound;
}


///////////////////////////////////////////////////////////
//
//  TEMPERATURE
//
float DS2438::readTemperature()
{
  //  requestTemperature()
  _oneWire->reset();
  _oneWire->select(_address);
  _oneWire->write(DS2438_READ_TEMPERATURE, 0);

  //  async version should return here
  delay(DS2438_CONVERSION_DELAY);
  readScratchPad(0);

  //             sign    MSB               LSB         step      >> 3
 _temperature = (int(_scratchPad[2]) * 256 + _scratchPad[1]) * 0.03125 * 0.125;

  return _temperature;
}


float DS2438::getTemperature()
{
  return _temperature;
}


///////////////////////////////////////////////////////////
//
//  VOLTAGE
//
float DS2438::readVDD()
{
  setConfigBit(3);

  //  requestVoltage
  _oneWire->reset();
  _oneWire->select(_address);
  _oneWire->write(DS2438_READ_VOLTAGE, 0);
  delay(DS2438_CONVERSION_DELAY);
  readScratchPad(0);

  //  10 mV resolution
  _vdd = ((_scratchPad[4] & 0x03) * 256 + _scratchPad[3]) * 0.01;

  return _vdd;
}


float DS2438::getVDD()
{
  return _vdd;
}


float DS2438::readVAD()
{
  clearConfigBit(3);

  //  requestVoltage
  _oneWire->reset();
  _oneWire->select(_address);
  _oneWire->write(DS2438_READ_VOLTAGE, 0);
  delay(DS2438_CONVERSION_DELAY);
  readScratchPad(0);

  //  10 mV resolution
  _vad = ((_scratchPad[4] & 0x03) * 256 + _scratchPad[3]) * 0.01;

  return _vad;
}


float DS2438::getVAD()
{
  return _vad;
}



///////////////////////////////////////////////////////////
//
//  CURRENT
//
void DS2438::setResistor(float resistor)
{
  _inverseR = 1.0 / (4096.0 * resistor);
}


void DS2438::enableCurrentMeasurement()
{
  //  The DS2438 will only perform current A/D measurements 
  //  if the IAD bit is set to “1” in the status/Configuration Register.
  //  The current A/D measures at a rate of 36.41 times per second, or once every 27.46 ms.
  readScratchPad(0);
  if ((_scratchPad[0] & 0x01) == 0x01) return;  //  already 1
  _scratchPad[0] |= 0x01;
  writeScratchPad(0);
}


void DS2438::disableCurrentMeasurement()
{
  readScratchPad(0);
  if ((_scratchPad[0] & 0x01) == 0x00) return;  //  already 0
  _scratchPad[0] &= ~0x01;
  writeScratchPad(0);
}


float DS2438::readCurrent()
{
  readScratchPad(0);
  int voltageSense = (int(_scratchPad[6]) * 256 + _scratchPad[5]);
  _current = voltageSense * _inverseR;  //  I = V / (4096 * R)
  return _current;
}


float DS2438::getCurrent()
{
  return _current;
}


void DS2438::writeCurrentOffset(int value)
{
  value *= 8;
  readScratchPad(1);
  _scratchPad[6] = value / 8;
  _scratchPad[5] = value % 8;
  writeScratchPad(1);
}


int DS2438::readCurrentOffset()
{
  readScratchPad(1);
  int offset = (int(_scratchPad[6]) * 256 + _scratchPad[5]);
  return offset / 8;
}


///////////////////////////////////////////////////////////
//
//  ICA + THRESHOLD
//
float DS2438::readRemaining()
{
  readScratchPad(1);
  //  factor 2 from optimization
  float remaining = _scratchPad[4] * _inverseR * (2 * 0.4882);  //   mVhr
  return remaining;
}


void DS2438::writeThreshold(uint8_t value)
{
  clearConfigBit(0);
  readScratchPad(0);
  _scratchPad[7] = value & 0xC0;  //  zero lower 6 bits.
  writeScratchPad(0);
  setConfigBit(0);
}


uint8_t DS2438::readThreshold()
{
  readScratchPad(0);
  return _scratchPad[7];
}


///////////////////////////////////////////////////////////
//
//  TIME
//
void DS2438::writeElapsedTimeMeter(uint32_t seconds)
{
  readScratchPad(1);
  _scratchPad[0] = seconds & 0xFF;
  seconds >>= 8;
  _scratchPad[1] = seconds & 0xFF;
  seconds >>= 8;
  _scratchPad[2] = seconds & 0xFF;
  seconds >>= 8;
  _scratchPad[3] = seconds & 0xFF;
  writeScratchPad(1);
}


uint32_t DS2438::readElapsedTimeMeter()
{
  readScratchPad(1);
  uint32_t seconds = _scratchPad[3];
  seconds <<= 8;
  seconds += _scratchPad[2];
  seconds <<= 8;
  seconds += _scratchPad[1];
  seconds <<= 8;
  seconds += _scratchPad[0];
  return seconds;
}

uint32_t DS2438::readDisconnectTime()
{
  readScratchPad(2);
  uint32_t seconds = _scratchPad[3];
  seconds <<= 8;
  seconds += _scratchPad[2];
  seconds <<= 8;
  seconds += _scratchPad[1];
  seconds <<= 8;
  seconds += _scratchPad[0];
  return seconds;
}


uint32_t DS2438::readEndOfChargeTime()
{
  readScratchPad(2);
  uint32_t seconds = _scratchPad[7];
  seconds <<= 8;
  seconds += _scratchPad[6];
  seconds <<= 8;
  seconds += _scratchPad[5];
  seconds <<= 8;
  seconds += _scratchPad[4];
  return seconds;
}


///////////////////////////////////////////////////////////
//
//  EEPROM
//
void DS2438::writeEEPROM(uint8_t address, uint8_t value)
{
  if (address > 39) return;    //  0..39
  uint8_t page  = address / 8;
  uint8_t index = address % 8;

  readScratchPad(page);
  if (_scratchPad[index] == value) return;  //  no need to write.
  _scratchPad[index] = value;
  writeScratchPad(page);
}


uint8_t DS2438::readEEPROM(uint8_t address)
{
  if (address > 39) return 0;    //  0..39
  uint8_t page  = address / 8;
  uint8_t index = address % 8;

  readScratchPad(page);
  return _scratchPad[index];
}


///////////////////////////////////////////////////////////
//
//  Charging + Discharging Current Accumulator
//
void DS2438::enableCCA()
{
  readScratchPad(0);
  if ((_scratchPad[0] & 0x02) == 0x02) return;  //  already 1
  _scratchPad[0] |= 0x02;
  writeScratchPad(0);
}


void DS2438::disableCCA()
{
  readScratchPad(0);
  if ((_scratchPad[0] & 0x02) != 0x02) return;  //  already 0
  _scratchPad[0] &= ~0x02;
  writeScratchPad(0);
}


float DS2438::readCCA()
{
  readScratchPad(7);
  uint16_t raw = (_scratchPad[5] * 256 + _scratchPad[4]);
  return raw * 15.625;
}


float DS2438::readDCA()
{
  readScratchPad(7);
  uint16_t raw = (_scratchPad[7] * 256 + _scratchPad[6]);
  return raw * 15.625;
}


///////////////////////////////////////////////////////////
//
//  CONFIG REGISTER
//
void DS2438::setConfigBit(uint8_t bit)
{
  uint8_t mask = (0x01 << bit);
  readScratchPad(0);
  if ((_scratchPad[0] & mask) == mask) return;  //  already 1
  _scratchPad[0] |= mask;
  writeScratchPad(0);
}


void DS2438::clearConfigBit(uint8_t bit)
{
  uint8_t mask = (0x01 << bit);
  readScratchPad(0);
  if ((_scratchPad[0] & mask) == 0x00) return;  //  already 0
  _scratchPad[0] &= ~mask;
  writeScratchPad(0);
}


uint8_t DS2438::getConfigRegister()
{
  readScratchPad(0);
  return _scratchPad[0];
}


///////////////////////////////////////////////////////////
//
//  PRIVATE
//
void DS2438::readScratchPad(uint8_t page)
{
  if (page > 7) return;
  _oneWire->reset();
  _oneWire->select(_address);  
  _oneWire->write(DS2438_RECALL_SCRATCH, 0);
  _oneWire->write(page, 0);
  _oneWire->reset();
  _oneWire->select(_address);
  _oneWire->write(DS2438_READ_SCRATCH, 0);
  _oneWire->write(page, 0);
  for (uint8_t i = 0; i < 8; i++) _scratchPad[i] = _oneWire->read();
  //  skip crc for now.
}


void DS2438::writeScratchPad(uint8_t page)
{
  if (page > 7) return;
  _oneWire->reset();
  _oneWire->select(_address);
  _oneWire->write(DS2438_WRITE_SCRATCH, 0);
  _oneWire->write(page, 0);
  for (uint8_t i = 0; i < 8; i++) _oneWire->write(_scratchPad[i], 0);
  _oneWire->reset();
  _oneWire->select(_address);
  _oneWire->write(DS2438_COPY_SCRATCH, 0);
  _oneWire->write(page, 0);
}


//  -- END OF FILE --

