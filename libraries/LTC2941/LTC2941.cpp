//
//    FILE: LTC2941.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-09-18
// PURPOSE: Arduino library for the LTC2941 battery charge and discharge (Coulomb) meter.
//     URL: https://github.com/RobTillaart/LTC2941


#include "LTC2941.h"


const uint8_t LTC2941_REG_STATUS             = 0x00;
const uint8_t LTC2941_REG_CONTROL            = 0x01;
const uint8_t LTC2941_REG_CHARGE_MSB         = 0x02;
const uint8_t LTC2941_REG_CHARGE_LSB         = 0x03;
const uint8_t LTC2941_REG_CHARGE_TH_HIGH_MSB = 0x04;
const uint8_t LTC2941_REG_CHARGE_TH_HIGH_LSB = 0x05;
const uint8_t LTC2941_REG_CHARGE_TH_LOW_MSB  = 0x06;
const uint8_t LTC2941_REG_CHARGE_TH_LOW_LSB  = 0x07;


LTC2941::LTC2941(TwoWire *wire)
{
  _address = 0x64;
  _wire = wire;
}

bool LTC2941::begin(float mAh, float RSense)
{
  //  check parameters.
  //  RSense, what is minimum allowed? Max current?
  //  for now it should not be below 5 mOhm => maxCurrent = 10A.
  if (RSense < 0.005f)
  {
    _error = LTC2941_RSENSE_ERROR;
    return false;
  }
  //  Page 10, verify if RSense makes sense
  if (RSense > ((0.085 * 0.050f * 65535) / mAh))
  {
    _error = LTC2941_RSENSE_ERROR;
    return false;
  }
  if ((mAh < 100) || (mAh > 5500))  //  check limit
  {
    _error = LTC2941_MAH_ERROR;
    return false;
  }

  //  Page 11, calculate and verify pre-scaler
  float tmp = 128 * mAh /(65535 * 0.085f) * (RSense / 0.050f);
  uint8_t prescaler;
  for (prescaler = 1; prescaler < 128; prescaler *= 2)
  {
    if (prescaler > tmp) break;
  }
  if (prescaler <= tmp)
  {
    _error = LTC2941_PRESCALER_ERROR;
    return false;
  }

  // check connection
  _error = LTC2941_OK;
  if (! isConnected())
  {
    _error = LTC2941_NOT_READY;
    return false;
  }

  //  ALL OK  ==> so we can set the internals
  _RSense = RSense;
  _mAh = mAh;
  _prescaler = prescaler;
  _QLSB = _calculateQLSB();

  //  write pre-scaler to device.
  int ps;
  for (ps = 0; ps < 8; ps++)
  {
    if ((1 << ps) == _prescaler) break;
  }
  uint8_t control = 0;   //  no error check here yet.
  _getControl(control);  //  read current configuration
  control &= 0xC7;       //  clear pre-scaler bits
  control |= (ps << 3);  //  set pre-scaler bits
  _setControl(control);  //  write new configuration

  return _error == LTC2941_OK;
}

bool LTC2941::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t LTC2941::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  CHARGE
//
bool LTC2941::setRawCharge(uint16_t raw)
{
  uint8_t value[2];
  value[0] = raw >> 8;
  value[1] = raw & 0xFF;
  _write(LTC2941_REG_CHARGE_MSB, value, 2);
  return (_error == LTC2941_OK);
}

bool LTC2941::getRawCharge(uint16_t &raw)
{
  uint8_t value[2] = {0, 0};
  _read(LTC2941_REG_CHARGE_MSB, value, 2);
  raw = (value[0] << 8) + value[1];
  return (_error == LTC2941_OK);
}

bool LTC2941::setCharge(float charge)
{
  return setRawCharge(charge / _QLSB);
}

bool LTC2941::getCharge(float &charge)
{
  uint16_t raw = 0;
  getRawCharge(raw);
  charge = raw * _QLSB;
  return (_error == LTC2941_OK);
}

bool LTC2941::getPercentageFull(float &percentage)
{
  float perc;
  getCharge(perc);
  percentage = (100.0 * perc) / _mAh;
  return (_error == LTC2941_OK);
}

float LTC2941::getQLSB()
{
  return _QLSB;
}


/////////////////////////////////////////////
//
//  STATUS & CONTROL
//
bool LTC2941::getStatus(uint8_t &status)
{
  uint8_t value;
  _read(LTC2941_REG_STATUS, &value, 1);
  status = value;
  return (_error == LTC2941_OK);
}

bool LTC2941::setControl( uint8_t ALCC,
                          uint8_t prescaler,
                          uint8_t shutDown,
                          uint8_t batAlert)
{
  if ((ALCC > 2)     || (prescaler > 7) ||
      (shutDown > 1) || (batAlert > 3))
  {
    _error = LTC2941_CONTROL_ERROR;
    return false;
  }
  //  0..7 ==> 1..128
  _prescaler = 1 << prescaler;
  _QLSB = _calculateQLSB();

  uint8_t control = shutDown | (ALCC << 1) | (prescaler << 3) | (batAlert << 6);
  return _setControl(control);
}


bool LTC2941::getControl( uint8_t &ALCC,
                          uint8_t &prescaler,
                          uint8_t &shutDown,
                          uint8_t &batAlert)
{
  uint8_t control;
  if (_getControl(control) != LTC2941_OK)
  {
    return false;
  }
  shutDown  = control & 0x01;
  ALCC      = (control >> 1) & 0x03;
  prescaler = (control >> 3) & 0x07;
  batAlert  = (control >> 6) & 0x03;
  return true;
}


/////////////////////////////////////////////
//
//  THRESHOLD
//
bool LTC2941::setRawThresholdHigh(uint16_t th)
{
  uint8_t value[2];
  value[0] = th >> 8;
  value[1] = th & 0xFF;
  _write(LTC2941_REG_CHARGE_TH_HIGH_MSB, value, 2);
  return (_error == LTC2941_OK);
}

bool LTC2941::getRawThresholdHigh(uint16_t &th)
{
  uint8_t value[2];
  _read(LTC2941_REG_CHARGE_TH_HIGH_MSB, value, 2);
  th = (value[0] << 8) + value[1];
  return (_error == LTC2941_OK);
}

bool LTC2941::setRawThresholdLow(uint16_t th)
{
  uint8_t value[2];
  value[0] = th >> 8;
  value[1] = th & 0xFF;
  _write(LTC2941_REG_CHARGE_TH_LOW_MSB, value, 2);
  return (_error == LTC2941_OK);
}

bool LTC2941::getRawThresholdLow(uint16_t &th)
{
  uint8_t value[2];
  _read(LTC2941_REG_CHARGE_TH_LOW_MSB, value, 2);
  th = (value[0] << 8) + value[1];
  return (_error == LTC2941_OK);
}

bool LTC2941::setThresholdHigh(float th)
{
  return setRawThresholdHigh(th / _QLSB);
}

bool LTC2941::getThresholdHigh(float &th)
{
  uint16_t raw = 0;
  getRawThresholdHigh(raw);
  th = raw * _QLSB;
  return (_error == LTC2941_OK);
}

bool LTC2941::setThresholdLow(float th)
{
  return setRawThresholdLow(th / _QLSB);
}

bool LTC2941::getThresholdLow(float &th)
{
  uint16_t raw = 0;
  getRawThresholdLow(raw);
  th = raw * _QLSB;
  return (_error == LTC2941_OK);
}


/////////////////////////////////////////////
//
//  DEBUG
//
int LTC2941::getLastError()
{
  int e = _error;
  _error = LTC2941_OK;
  return e;
}

uint8_t LTC2941::getPrescaler()
{
  return _prescaler;
}

float LTC2941::getMaxCurrent()
{
  return 0.050f / _RSense;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
bool LTC2941::_setControl(uint8_t control)
{
  //  not allowed bit pattern. Page 9.
  if (control & 0x06)
  {
    _error = LTC2941_CONTROL_ERROR;
    return false;
  }
  _write(LTC2941_REG_CONTROL, &control, 1);
  return (_error == LTC2941_OK);
}

bool LTC2941::_getControl(uint8_t &control)
{
  uint8_t value = 0;
  _read(LTC2941_REG_CONTROL, &value, 1);
  control = value;
  return (_error == LTC2941_OK);
}

float LTC2941::_calculateQLSB()
{
  //  datasheet, page 4
  //  0.085f = mAh,
  //  0.050f is default RSense = 50 mOhm
  return (0.085f * 0.050f) / _RSense * (_prescaler * (1.0f / 128.0f));
}

//
//  LOW LEVEL IO
//
int LTC2941::_write(uint8_t reg, uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
  return _error;
}

int LTC2941::_read(uint8_t reg, uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != LTC2941_OK)
  {
    return _error;
  }
  uint8_t bytes = _wire->requestFrom(_address, size);
  if (bytes == 0)
  {
    _error = LTC2941_REQUEST_ERROR1;
    return _error;
  }
  if (bytes < size)
  {
    _error = LTC2941_REQUEST_ERROR2;
    return _error;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    arr[i] = _wire->read();
  }
  _error = LTC2941_OK;
  return LTC2941_OK;
}


//  -- END OF FILE --

