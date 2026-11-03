//
//    FILE: SLF3S.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-11-02
// PURPOSE: Arduino library for the Sensirion I2C Low Flow sensor SLF3S
//     URL: https://github.com/RobTillaart/SLF3S


#include "SLF3S.h"

//       COMMANDS
uint16_t SLF3S_START_H2O    = 0x3608;
uint16_t SLF3S_START_IPA    = 0x3615;
uint16_t SLF3S_STOP         = 0x3FF9;
uint16_t SLF3S_READ_ID      = 0x367C;
uint16_t SLF3S_READ_SERIAL  = 0xE102;
//  SLF3C-1300F only
uint16_t SLF3C_READ_THERMAL = 0x3646;


/////////////////////////////////////////////
//
//  CONSTRUCTOR
//
SLF3S::SLF3S(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _error = SLF3S_OK;
  _lastRead = 0;
}

bool SLF3S::begin(uint16_t type)
{
  //  reset variables
  _error = SLF3S_OK;
  _lastRead = 0;
  if (type == 1300)
  {
    _flowScale = 1.0f / 500.0f;
  }
  else  //  type == 600 default.
  {
    _flowScale = 1.0f / 10.0f;
  }

  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool SLF3S::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == SLF3S_OK);
}

uint8_t SLF3S::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  REQUEST
//
int SLF3S::requestH2O()
{
  _lastRequest = millis();
  return _command(SLF3S_START_H2O);
}

int SLF3S::requestIPA()
{
  _lastRequest = millis();
  return _command(SLF3S_START_IPA);
}

bool SLF3S::isReady()
{
  _error = SLF3S_OK;
  if (_lastRequest == 0)
  {
    _error = SLF3S_NO_REQUEST;
    return false;
  }
  //  datasheet page 9 60 ms warm up time.
  if (millis() - _lastRequest < 60)
  {
    _error = SLF3S_NOT_READY;
    return false;
  }
  _error = SLF3S_OK;
  return true;
}

int SLF3S::stopMeasurement()
{
  _lastRequest = 0;
  return _command(SLF3S_STOP);
}


/////////////////////////////////////////////
//
//  READ
//
int SLF3S::readFlow()
{
  _error = SLF3S_OK;
  uint8_t arr[3];
  _read(arr, 3);
  _rawFlow = arr[0] * 256 + arr[1];
  //  CRC check
  if (arr[2] != _crc8(arr, 2)) _error = SLF3S_CRC_ERROR;
  return _error;
}

int SLF3S::readFlowTemp()
{
  _error = SLF3S_OK;
  uint8_t arr[6];
  _read(arr, 6);
  _rawFlow = arr[0] * 256 + arr[1];
  _rawTemp = arr[3] * 256 + arr[4];
  //  CRC check
  if (arr[2] != _crc8(arr, 2))     _error = SLF3S_CRC_ERROR;
  if (arr[5] != _crc8(&arr[3], 2)) _error = SLF3S_CRC_ERROR;
  return _error;
}

int SLF3S::readFlowTempSignal()
{
  _error = SLF3S_OK;
  uint8_t arr[9];
  _read(arr, 9);
  _rawFlow = arr[0] * 256 + arr[1];
  _rawTemp = arr[3] * 256 + arr[4];
  _rawSignal = arr[6] * 256 + arr[7];
  //  CRC check
  if (arr[2] != _crc8(arr, 2))     _error = SLF3S_CRC_ERROR;
  if (arr[5] != _crc8(&arr[3], 2)) _error = SLF3S_CRC_ERROR;
  if (arr[8] != _crc8(&arr[6], 2)) _error = SLF3S_CRC_ERROR;
  return _error;
}

float SLF3S::getFlow()
{
  return _rawFlow * _flowScale;
}

float SLF3S::getTemperature()
{
  return _rawTemp * _tempScale;
}

uint16_t SLF3S::getSignalFlags()
{
  return _rawSignal;
}


/////////////////////////////////////////////
//
//  ID and SERIAL
//
uint32_t SLF3S::readProductID()
{
  _error = SLF3S_OK;
  uint8_t arr[6];
  _read(arr, 6);
  uint32_t id = arr[0];
  id <<= 8;
  id += arr[1];
  id <<= 8;
  id += arr[3];
  id <<= 8;
  id += arr[4];
  //  CRC check
  if (arr[2] != _crc8(arr, 2))      _error = SLF3S_CRC_ERROR;
  if (arr[5] != _crc8(&arr[3], 2))  _error = SLF3S_CRC_ERROR;
  return id;
}

uint64_t SLF3S::readSerialNR()
{
  _error = SLF3S_OK;
  uint8_t arr[12];
  _read(arr, 12);
  uint64_t sr = arr[0];
  sr <<= 8;
  sr += arr[1];
  sr <<= 8;
  sr += arr[3];
  sr <<= 8;
  sr += arr[4];
  sr <<= 8;
  sr += arr[6];
  sr <<= 8;
  sr += arr[7];
  sr <<= 8;
  sr += arr[9];
  sr <<= 8;
  sr += arr[10];
  //  CRC check
  if (arr[2] != _crc8(arr, 2))      _error = SLF3S_CRC_ERROR;
  if (arr[5] != _crc8(&arr[3], 2))  _error = SLF3S_CRC_ERROR;
  if (arr[8] != _crc8(&arr[6], 2))  _error = SLF3S_CRC_ERROR;
  if (arr[11] != _crc8(&arr[9], 2)) _error = SLF3S_CRC_ERROR;
  return sr;
}


/////////////////////////////////////////////
//
//  MISC
//
int SLF3S::genericReset()
{
  _wire->beginTransmission(0x00);
  _wire->write(0x06);
  _error = _wire->endTransmission();
  return _error;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int SLF3S::getLastError()
{
  int e = _error;
  _error = SLF3S_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
int SLF3S::_command(uint16_t cmd)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd >> 8);
  _wire->write(cmd & 0xFF);
  _error = _wire->endTransmission();
  return _error;
}


int SLF3S::_read(uint8_t * arr, uint8_t size)
{
  uint8_t bytes = _wire->requestFrom(_address, size);
  if (bytes == 0)
  {
    _error = -1;
    return _error;
  }
  if (bytes < size)
  {
    _error = -2;
    return _error;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    arr[i] = _wire->read();
  }
  _error = SLF3S_OK;
  return _error;
}


uint8_t SLF3S::_crc8(uint8_t * arr, uint8_t size)
{
  uint8_t crc = 0xFF;
  for (uint8_t b = 0; b < size; b++)
  {
    crc ^= arr[b];
    for (uint8_t bit = 0x80; bit; bit >>= 1)
    {
      if (crc & 0x80)
      {
        crc <<= 1;
        crc ^= 0x31;
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  return crc;
}


//  -- END OF FILE --

