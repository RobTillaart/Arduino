//
//    FILE: DS2438.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2023-07-28
// PURPOSE: Arduino Library for DS2438 battery monitor
//     URL: https://github.com/RobTillaart/DS2438


#include "DS2438.h"


//      OneWire commands
#define DS2438_READ_TEMPERATURE           0x44
#define DS2438_READ_VOLTAGE               0xB4

#define DS2438_RECALL_SCRATCH             0xB8
#define DS2438_READ_SCRATCH               0xBE
#define DS2438_WRITE_SCRATCH              0x4E
#define DS2438_COPY_SCRATCH               0x48


#define DS2438_CONVERSION_DELAY           10


//  ScratchPad pages
#define DS2438_PAGE_CORE                  0
#define DS2438_PAGE_ETM_ICA_OFFSET        1
#define DS2438_PAGE_DIS_EOC               2
#define DS2438_PAGE_EEPROM_BASE           3
#define DS2438_PAGE_CCA_DCA               7


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
  _RICA        = DS2438_INVALID;
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
  //  datasheet p.4
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
void DS2438::enableVoltageSelector()
{
  //  datasheet p.8 + 16
  setConfigBit(DS2438_CONFIG_AD);
}

void DS2438::disableVoltageSelector()
{
  //  datasheet p.8 + 16
  clearConfigBit(DS2438_CONFIG_AD);
}

float DS2438::readVDD()
{
  //  datasheet p.4
  setConfigBit(DS2438_CONFIG_AD);  //  AD bit == 1;

  //  requestVoltage
  _oneWire->reset();
  _oneWire->select(_address);
  _oneWire->write(DS2438_READ_VOLTAGE, 0);
  delay(DS2438_CONVERSION_DELAY);
  readScratchPad(DS2438_PAGE_CORE);

  //  10 mV resolution
  _vdd = ((_scratchPad[4] & 0x03) * 256 + _scratchPad[3]) * 0.01;

  //  convert current in same call?!

  return _vdd;
}

float DS2438::getVDD()
{
  return _vdd;
}

float DS2438::readVAD()
{
  //  datasheet p.4
  clearConfigBit(DS2438_CONFIG_AD);  //  AD bit == 0;

  //  requestVoltage
  _oneWire->reset();
  _oneWire->select(_address);
  _oneWire->write(DS2438_READ_VOLTAGE, 0);
  delay(DS2438_CONVERSION_DELAY);
  readScratchPad(DS2438_PAGE_CORE);

  //  10 mV resolution
  _vad = ((_scratchPad[4] & 0x03) * 256 + _scratchPad[3]) * 0.01;

  //  convert current in same call?!

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
  _RICA     = 1.0 / (2048.0 * resistor);
}


void DS2438::enableCurrentMeasurement()
{
  //  The DS2438 will only perform current A/D measurements
  //  if the IAD bit is set to “1” in the status/Configuration Register.
  //  The current A/D measures at a rate of 36.41 times per second,
  //  or once every 27.46 ms.
  setConfigBit(DS2438_CONFIG_IAD);
}


void DS2438::disableCurrentMeasurement()
{
  clearConfigBit(DS2438_CONFIG_IAD);
}


float DS2438::readCurrent()
{
  //  datasheet p.5/6
  readScratchPad(DS2438_PAGE_CORE);
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
  //  datasheet p.6
  //  to write, measurements must be disabled.
  //  add three zero's
  value *= 8;
  clearConfigBit(DS2438_CONFIG_IAD);
  readScratchPad(DS2438_PAGE_ETM_ICA_OFFSET);
  //  split in HIGH and LOW byte
  _scratchPad[6] = value >> 8;
  _scratchPad[5] = value & 0xFF;
  writeScratchPad(DS2438_PAGE_ETM_ICA_OFFSET);
  setConfigBit(DS2438_CONFIG_IAD);
}


int DS2438::readCurrentOffset()
{
  //  datasheet p.6
  //  read does not need to disable measurements.
  readScratchPad(DS2438_PAGE_ETM_ICA_OFFSET);
  int offset = (int(_scratchPad[6]) * 256 + _scratchPad[5]);
  //  sign extend offset.
  if (offset & 0x1000) offset |= 0xE000;
  return offset / 8;
}


///////////////////////////////////////////////////////////
//
//  ICA + THRESHOLD
//
float DS2438::readRemaining()
{
  //  datasheet p.7
  readScratchPad(DS2438_PAGE_ETM_ICA_OFFSET);
  //  factor 2.0 from optimization (need to explain this factor)
  //  Remaining Capacity = ICA / (2048 * RSENS)
  float remaining = _scratchPad[4] / _RICA;  //   mAhr
  return remaining;
}


void DS2438::writeThreshold(uint8_t value)
{
  //  datasheet p.8
  clearConfigBit(DS2438_CONFIG_IAD);
  readScratchPad(DS2438_PAGE_CORE);
  _scratchPad[7] = value & 0xC0;  //  zero lower 6 bits.
  writeScratchPad(DS2438_PAGE_CORE);
  setConfigBit(DS2438_CONFIG_IAD);
}


uint8_t DS2438::readThreshold()
{
  readScratchPad(DS2438_PAGE_CORE);
  return _scratchPad[7];
}


///////////////////////////////////////////////////////////
//
//  TIME
//
void DS2438::writeElapsedTimeMeter(uint32_t seconds)
{
  //  datasheet p.9
  readScratchPad(DS2438_PAGE_ETM_ICA_OFFSET);
  _scratchPad[0] = seconds & 0xFF;
  seconds >>= 8;
  _scratchPad[1] = seconds & 0xFF;
  seconds >>= 8;
  _scratchPad[2] = seconds & 0xFF;
  seconds >>= 8;
  _scratchPad[3] = seconds & 0xFF;
  writeScratchPad(DS2438_PAGE_ETM_ICA_OFFSET);
}


uint32_t DS2438::readElapsedTimeMeter()
{
  readScratchPad(DS2438_PAGE_ETM_ICA_OFFSET);
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
  readScratchPad(DS2438_PAGE_DIS_EOC);
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
  readScratchPad(DS2438_PAGE_DIS_EOC);
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

  readScratchPad(DS2438_PAGE_EEPROM_BASE + page);
  if (_scratchPad[index] == value) return;  //  no need to write.
  _scratchPad[index] = value;
  writeScratchPad(DS2438_PAGE_EEPROM_BASE + page);
}


uint8_t DS2438::readEEPROM(uint8_t address)
{
  if (address > 39) return 0;    //  0..39
  uint8_t page  = address / 8;
  uint8_t index = address % 8;

  readScratchPad(DS2438_PAGE_EEPROM_BASE + page);
  return _scratchPad[index];
}


///////////////////////////////////////////////////////////
//
//  Charging + Discharging Current Accumulator
//
void DS2438::enableCCA()
{
  //  datasheet p.8 + 16
  setConfigBit(DS2438_CONFIG_CA);
}

void DS2438::disableCCA()
{
  //  datasheet p.8 + 16
  clearConfigBit(DS2438_CONFIG_CA);
}

void DS2438::enableCCAShadow()
{
  //  datasheet p.8 + 16
  setConfigBit(DS2438_CONFIG_EE);
}

void DS2438::disableCCAShadow()
{
  //  datasheet p.8 + 16
  clearConfigBit(DS2438_CONFIG_EE);
}

float DS2438::readCCA()
{
  //  datasheet p.8 + 16
  readScratchPad(DS2438_PAGE_CCA_DCA);
  uint16_t raw = (_scratchPad[5] * 256 + _scratchPad[4]);
  return raw * 15.625;
}

float DS2438::readDCA()
{
  //  datasheet p.8 + 16
  readScratchPad(DS2438_PAGE_CCA_DCA);
  uint16_t raw = (_scratchPad[7] * 256 + _scratchPad[6]);
  return raw * 15.625;
}

bool DS2438::setCCA(float CCA)
{
  //  note: no upper bound check
  if (CCA < 0) return false;
   clearConfigBit(DS2438_CONFIG_IAD);
  readScratchPad(DS2438_PAGE_CCA_DCA);
  uint16_t tmp = round(CCA / 15.625);
  _scratchPad[4] = tmp & 0xFF;
  _scratchPad[5] = tmp >> 8;
  writeScratchPad(DS2438_PAGE_CCA_DCA);
  delay(10);
  setConfigBit(DS2438_CONFIG_IAD);
  return true;
}

bool DS2438::setDCA(float DCA)
{
  //  note: no upper bound check
  if (DCA < 0) return false;
  clearConfigBit(DS2438_CONFIG_IAD);
  readScratchPad(DS2438_PAGE_CCA_DCA);
  uint16_t tmp = round(DCA / 15.625);
  _scratchPad[6] = tmp & 0xFF;
  _scratchPad[7] = tmp >> 8;
  writeScratchPad(DS2438_PAGE_CCA_DCA);
  delay(10);
  setConfigBit(DS2438_CONFIG_IAD);
  return true;
}

void DS2438::resetAccumulators()
{
  clearConfigBit(DS2438_CONFIG_IAD);
  readScratchPad(DS2438_PAGE_CCA_DCA);
  _scratchPad[4] = 0;
  _scratchPad[5] = 0;
  _scratchPad[6] = 0;
  _scratchPad[7] = 0;
  writeScratchPad(DS2438_PAGE_CCA_DCA);
  delay(10);
  setConfigBit(DS2438_CONFIG_IAD);
}


///////////////////////////////////////////////////////////
//
//  CONFIG REGISTER
//  datasheet Page 15
//
void DS2438::setConfigBit(uint8_t bit)
{
  if (bit > 3) return;
  uint8_t mask = (0x01 << bit);
  readScratchPad(DS2438_PAGE_CORE);
  if ((_scratchPad[0] & mask) == mask) return;  //  already 1
  _scratchPad[0] |= mask;
  writeScratchPad(DS2438_PAGE_CORE);
}

void DS2438::clearConfigBit(uint8_t bit)
{
  if (bit > 3) return;
  uint8_t mask = (0x01 << bit);
  readScratchPad(DS2438_PAGE_CORE);
  if ((_scratchPad[0] & mask) == 0x00) return;  //  already 0
  _scratchPad[0] &= ~mask;
  writeScratchPad(DS2438_PAGE_CORE);
}

uint8_t DS2438::getConfigRegister()
{
  readScratchPad(0);
  return _scratchPad[0];
}

bool DS2438::busy()
{
  return (getConfigRegister() & 0x70) > 0;
}

bool DS2438::busyTemperature()
{
  return (getConfigRegister() & 0x10) > 0;
}

bool DS2438::busyNVRAM()
{
  return (getConfigRegister() & 0x20) > 0;
}

bool DS2438::busyADC()
{
  return (getConfigRegister() & 0x40) > 0;
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

