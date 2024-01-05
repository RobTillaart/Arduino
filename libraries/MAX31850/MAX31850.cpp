//
//    FILE: MAX31850.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
//    DATE: 2021-06-03
// PURPOSE: Arduino library for the MAX31850 thermocouple temperature sensor.
//     URL: https://github.com/RobTillaart/MAX31850


#include "MAX31850.h"


//  OneWire commands
#define STARTCONVO                 0x44
#define READSCRATCH                0xBE
#define WRITESCRATCH               0x4E


//   SCRATCHPAD registers
//   bit 1 = reserved   bit 0 = error flag
#define TC_TEMP_LSB                   0
#define TC_TEMP_MSB                   1

//   bit 3 = reserved   bit 0-2 = error codes
#define INTERN_TEMP_LSB               2
#define INTERN_TEMP_MSB               3

//   4  address bits  0..15
#define CONFIGURATION                 4
#define RESERVED_1                    5
#define RESERVED_2                    6
#define RESERVED_3                    7
#define SCRATCHPAD_CRC                8


/////////////////////////////////////////////////////////////////////////////
//
//  MAX31850
//
MAX31850::MAX31850(OneWire* oneWire)
{
  _oneWire      = oneWire;
  _addresFound  = false;
  _typeTC       = 'K';     //  most used.
  _TCTemp       = 0;
  _internalTemp = 0;
  _errorBits    = 0;
  _failFlag     = false;
  _addrBits     = 0;
}


bool MAX31850::begin(uint8_t retries)
{
  _addresFound = false;
  for (uint8_t r = retries; (r > 0) && (_addresFound == false); r--)
  {
    _oneWire->reset();
    _oneWire->reset_search();
    _deviceAddress[0] = 0x00;
    _oneWire->search(_deviceAddress);
    _addresFound = _deviceAddress[0] != 0x00 &&
                _oneWire->crc8(_deviceAddress, 7) == _deviceAddress[7];
  }
  return _addresFound;
}


bool MAX31850::getAddress(uint8_t* buffer)
{
  if (_addresFound)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      buffer[i] = _deviceAddress[i];
    }
  }
  return _addresFound;
}


void MAX31850::requestTemperatures(void)
{
  _oneWire->reset();
  _oneWire->skip();
  _oneWire->write(STARTCONVO, 0);
}


bool MAX31850::isConversionComplete(void)
{
  return (_oneWire->read_bit() == 1);
}


float MAX31850::read(void)
{
  ScratchPad scratchPad;
  for (int i = 0; i < 9; i++) scratchPad[i] = 0;

  //  NO CRC CHECK
  readScratchPad(scratchPad, 5);

  _failFlag = scratchPad[TC_TEMP_LSB] & 0x01;
  int16_t rawTemperature = (((int16_t)scratchPad[TC_TEMP_MSB]) << 6) | scratchPad[TC_TEMP_LSB] >> 2;
  _TCTemp = 0.25 * rawTemperature;

  _errorBits = scratchPad[INTERN_TEMP_LSB] & 0x07;
  rawTemperature = (((int16_t)scratchPad[INTERN_TEMP_LSB]) << 4) | scratchPad[INTERN_TEMP_LSB] >> 4;
  _internalTemp = 0.0625 * rawTemperature;

  _addrBits = scratchPad[CONFIGURATION] & 0x0F;

  return _TCTemp;
}


float MAX31850::getTempTC(void)
{
  return _TCTemp;
}


float MAX31850::getTempInternal(void)
{
  return _internalTemp;
}


uint8_t MAX31850::getErrorCode()
{
  return _errorBits;
}


uint8_t MAX31850::getAddressPins()
{
  return _addrBits;
};


bool MAX31850::setTypeTC(char typeTC)
{
  switch(toupper(typeTC))
  {
    case 'E':
    case 'J':
    case 'K':
    case 'N':
    case 'R':
    case 'S':
    case 'T':
    _typeTC = toupper(typeTC);
    return true;
  }
  return false;
}


char MAX31850::getTypeTC()
{
  return _typeTC;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//

void MAX31850::readScratchPad(uint8_t *scratchPad, uint8_t fields)
{
  _oneWire->reset();
  _oneWire->select(_deviceAddress);
  _oneWire->write(READSCRATCH);

  for (uint8_t i = 0; i < fields; i++)
  {
    scratchPad[i] = _oneWire->read();
  }
  _oneWire->reset();
}


/////////////////////////////////////////////////////////////////////////////
//
//  MAX31851
//
MAX31851::MAX31851(OneWire * onewire) : MAX31850(onewire)
{
}


//  -- END OF FILE --

