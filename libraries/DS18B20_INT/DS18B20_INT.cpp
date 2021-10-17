//
//    FILE: DS18B20_INT.cpp
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.6
//    DATE: 2017-07-25
// PUPROSE: library for DS18B20 temperature sensor - integer only.
//     URL: https://github.com/RobTillaart/DS18B20_INT
//
//  HISTORY:
//  0.1.0   2017-07-25  initial version
//  0.1.1   2019-
//  0.1.2   2020-08-05  refactor / sync with DS18B20 
//  0.1.3   2020-12-20  add arduino-ci + unit test
//  0.1.4   2021-05-26  add onewire.reset() to begin()
//  0.1.5   2021-06-16  add retries param to begin()
//  0.1.6   2021-10-03  add dependency + fix build-CI


#include "DS18B20_INT.h"

// OneWire commands
#define STARTCONVO      0x44
#define READSCRATCH     0xBE
#define WRITESCRATCH    0x4E


// Device resolution
#define TEMP_9_BIT  0x1F //  9 bit


DS18B20_INT::DS18B20_INT(OneWire* _oneWire)
{
  _wire = _oneWire;
  _addresFound = false;
}


bool DS18B20_INT::begin(uint8_t retries)
{
  _addresFound = false;
  for (uint8_t rtr = retries; (rtr > 0) && (_addresFound == false); rtr--)
  {
    _wire->reset();
    _wire->reset_search();
    _deviceAddress[0] = 0x00;
    _wire->search(_deviceAddress);
    _addresFound = _deviceAddress[0] != 0x00 &&
                _wire->crc8(_deviceAddress, 7) == _deviceAddress[7];
  }

  if (_addresFound)
  {
    _wire->reset();
    _wire->select(_deviceAddress);
    _wire->write(WRITESCRATCH);
    // two dummy values for LOW & HIGH ALARM
    _wire->write(0);
    _wire->write(100);
    _wire->write(TEMP_9_BIT);     // lowest as we do only integer math.
    _wire->reset();
  }
  return _addresFound;
}


void DS18B20_INT::requestTemperatures(void)
{
  _wire->reset();
  _wire->skip();
  _wire->write(STARTCONVO, 0);
}


bool DS18B20_INT::isConversionComplete(void)
{
  return (_wire->read_bit() == 1);
}


int16_t DS18B20_INT::getTempC(void)
{
  _wire->reset();
  _wire->select(_deviceAddress);
  _wire->write(READSCRATCH);
  int16_t rawTemperature = ((int16_t)_wire->read()) << 8;
  rawTemperature |= _wire->read();
  _wire->reset();
  rawTemperature >>= 4;
  if (rawTemperature < -55) return DEVICE_DISCONNECTED;
  return rawTemperature;
}


bool  DS18B20_INT::getAddress(uint8_t* buf)
{
  if (_addresFound)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      buf[i] = _deviceAddress[i];
    }
  }
  return _addresFound;
}


//  -- END OF FILE --
