//
//    FILE: LTC2943.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-09-18
// PURPOSE: Arduino library for the LTC2943 battery charge and discharge (Coulomb) meter.
//     URL: https://github.com/RobTillaart/LTC2943


#include "LTC2943.h"


const uint8_t LTC2943_REG_STATUS              = 0x00;  //  RO
const uint8_t LTC2943_REG_CONTROL             = 0x01;  //  RW

const uint8_t LTC2943_REG_CHARGE_MSB          = 0x02;  //  RW
const uint8_t LTC2943_REG_CHARGE_LSB          = 0x03;  //  RW
const uint8_t LTC2943_REG_CHARGE_TH_HIGH_MSB  = 0x04;  //  RW
const uint8_t LTC2943_REG_CHARGE_TH_HIGH_LSB  = 0x05;  //  RW
const uint8_t LTC2943_REG_CHARGE_TH_LOW_MSB   = 0x06;  //  RW
const uint8_t LTC2943_REG_CHARGE_TH_LOW_LSB   = 0x07;  //  RW

const uint8_t LTC2943_REG_VOLTS_MSB           = 0x08;  //  RO
const uint8_t LTC2943_REG_VOLTS_LSB           = 0x09;  //  RO
const uint8_t LTC2943_REG_VOLTS_TH_HIGH_MSB   = 0x0A;  //  RW
const uint8_t LTC2943_REG_VOLTS_TH_HIGH_LSB   = 0x0B;  //  RW
const uint8_t LTC2943_REG_VOLTS_TH_LOW_MSB    = 0x0C;  //  RW
const uint8_t LTC2943_REG_VOLTS_TH_LOW_LSB    = 0x0D;  //  RW

const uint8_t LTC2943_REG_CURRENT_MSB         = 0x0E;  //  RO
const uint8_t LTC2943_REG_CURRENT_LSB         = 0x0F;  //  RO
const uint8_t LTC2943_REG_CURRENT_TH_HIGH_MSB = 0x10;  //  RW
const uint8_t LTC2943_REG_CURRENT_TH_HIGH_LSB = 0x11;  //  RW
const uint8_t LTC2943_REG_CURRENT_TH_LOW_MSB  = 0x12;  //  RW
const uint8_t LTC2943_REG_CURRENT_TH_LOW_LSB  = 0x13;  //  RW

const uint8_t LTC2943_REG_TEMP_MSB            = 0x14;  //  RO
const uint8_t LTC2943_REG_TEMP_LSB            = 0x15;  //  RO
const uint8_t LTC2943_REG_TEMP_TH_HIGH        = 0x16;  //  RW
const uint8_t LTC2943_REG_TEMP_TH_LOW         = 0x17;  //  RW



LTC2943::LTC2943(TwoWire *wire)
{
  _address = 0x64;
  _wire = wire;
}

bool LTC2943::begin(float mAh, float RSense)
{
  //  check parameters.
  //  RSense, what is minimum allowed? Max current?
  //  for now it should not be below 5 mOhm => maxCurrent = 10A.
  if (RSense < 0.005f)
  {
    _error = LTC2943_RSENSE_ERROR;
    return false;
  }
  //  Page 12, verify if RSense makes sense
  if (RSense > ((0.000340 * 0.050f * 65535) / mAh))
  {
    _error = LTC2943_RSENSE_ERROR;
    return false;
  }
  //  TODO check limit page 13
  // if ((mAh < 100) || (mAh > 22000))
  // {
    // _error = LTC2943_MAH_ERROR;
    // return false;
  // }

  //  Page 12/13, calculate and verify pre-scaler
  float tmp = 4096 * mAh /(65535 * 0.000340f) * (RSense / 0.050f);
  uint16_t prescaler;
  for (prescaler = 1; prescaler < 4096; prescaler *= 4)
  {
    if (prescaler > tmp) break;
  }
  if (prescaler <= tmp)
  {
    _error = LTC2943_PRESCALER_ERROR;
    return false;
  }

  // check connection
  _error = LTC2943_OK;
  if (! isConnected())
  {
    _error = LTC2943_NOT_READY;
    return false;
  }

  //  ALL OK  ==> so we can set the internals
  _RSense = RSense;
  _mAh = mAh;
  _prescaler = prescaler;
  _QLSB = _calculateQLSB();

  //  write pre-scaler to device.
  uint8_t ps;
  for (ps = 0; ps < 8; ps++)
  {
    if ((1UL << ps) == _prescaler) break;
  }
  uint8_t control = 0;   //  no error check here yet.
  _getControl(control);  //  read current configuration
  control &= 0xC7;       //  clear pre-scaler bits
  control |= (ps << 3);  //  set pre-scaler bits
  _setControl(control);  //  write new configuration

  return _error == LTC2943_OK;
}

bool LTC2943::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t LTC2943::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  STATUS & CONTROL
//
bool LTC2943::getStatus(uint8_t &status)
{
  uint8_t value;
  _read(LTC2943_REG_STATUS, &value, 1);
  status = value;
  return (_error == LTC2943_OK);
}


bool LTC2943::setControl( uint8_t ALCC,
                          uint8_t prescaler,
                          uint8_t shutDown,
                          uint8_t ADCMode)
{
  if ((ALCC > 2)     || (prescaler > 7) ||
      (shutDown > 1) || (ADCMode > 3))
  {
    _error = LTC2943_CONTROL_ERROR;
    return false;
  }
  //  0..7 ==> 1..128
  _prescaler = 1 << prescaler;
  _QLSB = _calculateQLSB();

  uint8_t control = shutDown | (ALCC << 1) | (prescaler << 3) | (ADCMode << 6);
  return _setControl(control);
}


bool LTC2943::getControl( uint8_t &ALCC,
                          uint8_t &prescaler,
                          uint8_t &shutDown,
                          uint8_t &ADCMode)
{
  uint8_t control;
  if (_getControl(control) != LTC2943_OK)
  {
    return false;
  }
  shutDown  = control & 0x01;
  ALCC      = (control >> 1) & 0x03;
  prescaler = (control >> 3) & 0x07;
  ADCMode   = (control >> 6) & 0x03;
  return true;
}


/////////////////////////////////////////////
//
//  CHARGE
//
bool LTC2943::setRawCharge(uint16_t raw)
{
  uint8_t value[2];
  value[0] = raw >> 8;
  value[1] = raw & 0xFF;
  _write(LTC2943_REG_CHARGE_MSB, value, 2);
  return (_error == LTC2943_OK);
}

bool LTC2943::getRawCharge(uint16_t &raw)
{
  uint8_t value[2] = {0, 0};
  _read(LTC2943_REG_CHARGE_MSB, value, 2);
  raw = (value[0] << 8) + value[1];
  return (_error == LTC2943_OK);
}

bool LTC2943::setCharge(float charge)
{
  return setRawCharge(charge / _QLSB);
}

bool LTC2943::getCharge(float &charge)
{
  uint16_t raw = 0;
  getRawCharge(raw);
  charge = raw * _QLSB;
  return (_error == LTC2943_OK);
}

bool LTC2943::getPercentageFull(float &percentage)
{
  float perc;
  getCharge(perc);
  percentage = (100.0 * perc) / _mAh;
  return (_error == LTC2943_OK);
}

float LTC2943::getQLSB()
{
  return _QLSB;
}


/////////////////////////////////////////////
//
//  THRESHOLD
//
bool LTC2943::setRawChargeThresholdHigh(uint16_t th)
{
  uint8_t value[2];
  value[0] = th >> 8;
  value[1] = th & 0xFF;
  _write(LTC2943_REG_CHARGE_TH_HIGH_MSB, value, 2);
  return (_error == LTC2943_OK);
}

bool LTC2943::getRawChargeThresholdHigh(uint16_t &th)
{
  uint8_t value[2];
  _read(LTC2943_REG_CHARGE_TH_HIGH_MSB, value, 2);
  th = (value[0] << 8) + value[1];
  return (_error == LTC2943_OK);
}

bool LTC2943::setRawChargeThresholdLow(uint16_t th)
{
  uint8_t value[2];
  value[0] = th >> 8;
  value[1] = th & 0xFF;
  _write(LTC2943_REG_CHARGE_TH_LOW_MSB, value, 2);
  return (_error == LTC2943_OK);
}

bool LTC2943::getRawChargeThresholdLow(uint16_t &th)
{
  uint8_t value[2];
  _read(LTC2943_REG_CHARGE_TH_LOW_MSB, value, 2);
  th = (value[0] << 8) + value[1];
  return (_error == LTC2943_OK);
}

bool LTC2943::setChargeThresholdHigh(float th)
{
  return setRawChargeThresholdHigh(th / _QLSB);
}

bool LTC2943::getChargeThresholdHigh(float &th)
{
  uint16_t raw = 0;
  getRawChargeThresholdHigh(raw);
  th = raw * _QLSB;
  return (_error == LTC2943_OK);
}

bool LTC2943::setChargeThresholdLow(float th)
{
  return setRawChargeThresholdLow(th / _QLSB);
}

bool LTC2943::getChargeThresholdLow(float &th)
{
  uint16_t raw = 0;
  getRawChargeThresholdLow(raw);
  th = raw * _QLSB;
  return (_error == LTC2943_OK);
}


/////////////////////////////////////////////
//
//  VOLTS
//
bool LTC2943::getVoltage(float &voltage)
{
  uint8_t value[2] = {0, 0};
  _read(LTC2943_REG_VOLTS_MSB, value, 2);
  voltage = ((value[0] << 8) + value[1]) * (23.6f / 65535.0f);
  return (_error == LTC2943_OK);
}

bool LTC2943::setVoltageThresholdHigh(float th)
{
  //  page 14
  uint16_t raw = round(th * (65535.0f / 23.6f));
  uint8_t value[2];
  value[0] = raw >> 8;
  value[1] = raw & 0xFF;
  _write(LTC2943_REG_VOLTS_TH_HIGH_MSB, value, 2);
  return (_error == LTC2943_OK);
}

bool LTC2943::getVoltageThresholdHigh(float &th)
{
  uint8_t value[2];
  _read(LTC2943_REG_VOLTS_TH_HIGH_MSB, value, 2);
  uint16_t raw = value[0] * 256 + value[1];
  th = raw * (23.6f / 65535.0f);
  return (_error == LTC2943_OK);
}

bool LTC2943::setVoltageThresholdLow(float th)
{
  uint16_t raw = round(th * (65535.0f / 23.6f));
  uint8_t value[2];
  value[0] = raw >> 8;
  value[1] = raw & 0xFF;
  _write(LTC2943_REG_VOLTS_TH_LOW_MSB, value, 2);
  return (_error == LTC2943_OK);
}

bool LTC2943::getVoltageThresholdLow(float &th)
{
  uint8_t value[2];
  _read(LTC2943_REG_VOLTS_TH_LOW_MSB, value, 2);
  uint16_t raw = value[0] * 256 + value[1];
  th = raw * (23.6f / 65535.0f);
  return (_error == LTC2943_OK);
}


/////////////////////////////////////////////
//
//  CURRENT
//
bool LTC2943::getCurrent(float &current)
{
  uint8_t value[2] = {0, 0};
  _read(LTC2943_REG_CURRENT_MSB, value, 2);  //  page 14
  int16_t Vsense = ((value[0] * 256) + value[1]) - 32767;
  current = Vsense / _RSense * (0.060f / 32767.0f);
  return (_error == LTC2943_OK);
}

bool LTC2943::setCurrentThresholdHigh(float th)
{
  //  page 15
  uint16_t raw = round(th * ((32767 * 0.050) / 0.060)) + 32767;
  uint8_t value[2];
  value[0] = raw >> 8;
  value[1] = raw & 0xFF;
  _write(LTC2943_REG_CURRENT_TH_HIGH_MSB, value, 2);
  return (_error == LTC2943_OK);
}

bool LTC2943::getCurrentThresholdHigh(float &th)
{
  uint8_t value[2];
  _read(LTC2943_REG_CURRENT_TH_HIGH_MSB, value, 2);
  int16_t raw = ((value[0] * 256) + value[1]) - 32767;
  th = raw * (0.060 / (0.050 * 32767));
  return (_error == LTC2943_OK);
}

bool LTC2943::setCurrentThresholdLow(float th)
{
  uint16_t raw = round(th * (0.050 / 0.060 * 32767)) + 32767;  //  page 15
  uint8_t value[2];
  value[0] = raw >> 8;
  value[1] = raw & 0xFF;
  _write(LTC2943_REG_CURRENT_TH_LOW_MSB, value, 2);
  return (_error == LTC2943_OK);
}

bool LTC2943::getCurrentThresholdLow(float &th)
{
  uint8_t value[2];
  _read(LTC2943_REG_CURRENT_TH_LOW_MSB, value, 2);
  int16_t raw = ((value[0] * 256) + value[1]) - 32767;
  th = raw * (0.060 / (0.050 * 32767));
  return (_error == LTC2943_OK);
}


/////////////////////////////////////////////
//
//  TEMPERATURE
//
bool LTC2943::getTemperature(float &temperature)
{
  //  page 15
  uint8_t value[2] = {0, 0};
  _read(LTC2943_REG_TEMP_MSB, value, 2);
  temperature = ((value[0] << 8) + value[1]) * (510.0f / 65535.0f) - 273.15f;
  return (_error == LTC2943_OK);
}

bool LTC2943::setTemperatureThresholdHigh(float th)
{
  uint16_t raw = round((th + 273.15f) * (65535.0f / 510.0f));
  uint8_t value[2];
  value[0] = raw >> 8;
  value[1] = raw & 0xFF;
  _write(LTC2943_REG_TEMP_TH_HIGH, value, 2);
  return (_error == LTC2943_OK);
}

bool LTC2943::getTemperatureThresholdHigh(float &th)
{
  uint8_t value[2];
  _read(LTC2943_REG_TEMP_TH_HIGH, value, 2);
  int16_t raw = (value[0] * 256) + value[1];
  th = raw * (510.0f / 65535.0f) - 273.15;
  return (_error == LTC2943_OK);
}

bool LTC2943::setTemperatureThresholdLow(float th)
{
  uint16_t raw = round((th + 273.15f) * (65535.0f / 510.0f));
  uint8_t value[2];
  value[0] = raw >> 8;
  value[1] = raw & 0xFF;
  _write(LTC2943_REG_TEMP_TH_LOW, value, 2);
  return (_error == LTC2943_OK);
}

bool LTC2943::getTemperatureThresholdLow(float &th)
{
  uint8_t value[2];
  _read(LTC2943_REG_TEMP_TH_LOW, value, 2);
  int16_t raw = (value[0] * 256) + value[1];
  th = raw * (510.0f / 65535.0f) - 273.15;
  return (_error == LTC2943_OK);
}


/////////////////////////////////////////////
//
//  DEBUG
//
int LTC2943::getLastError()
{
  int e = _error;
  _error = LTC2943_OK;
  return e;
}

uint16_t LTC2943::getPrescaler()
{
  return _prescaler;
}

float LTC2943::getMaxCurrent()
{
  return 0.050f / _RSense;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
bool LTC2943::_setControl(uint8_t control)
{
  //  not allowed bit pattern. Page 9.
  if (control & 0x06)
  {
    _error = LTC2943_CONTROL_ERROR;
    return false;
  }
  _write(LTC2943_REG_CONTROL, &control, 1);
  return (_error == LTC2943_OK);
}

bool LTC2943::_getControl(uint8_t &control)
{
  uint8_t value = 0;
  _read(LTC2943_REG_CONTROL, &value, 1);
  control = value;
  return (_error == LTC2943_OK);
}

float LTC2943::_calculateQLSB()
{
  //  datasheet, page 4
  //  0.000340f = 0.340 mAh,
  //  0.050f is default RSense = 50 mOhm
  return (0.000340f * 0.050f) / _RSense * (_prescaler * (1.0f / 4096.0f));
}

//
//  LOW LEVEL IO
//
int LTC2943::_write(uint8_t reg, uint8_t * arr, uint8_t size)
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

int LTC2943::_read(uint8_t reg, uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != LTC2943_OK)
  {
    return _error;
  }
  uint8_t bytes = _wire->requestFrom(_address, size);
  if (bytes == 0)
  {
    _error = LTC2943_REQUEST_ERROR1;
    return _error;
  }
  if (bytes < size)
  {
    _error = LTC2943_REQUEST_ERROR2;
    return _error;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    arr[i] = _wire->read();
  }
  _error = LTC2943_OK;
  return LTC2943_OK;
}


//  -- END OF FILE --

