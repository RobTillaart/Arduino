//
//    FILE: LTC2942.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-09-20
// PURPOSE: Arduino library for the LTC2942 battery charge and discharge (Coulomb) meter.
//     URL: https://github.com/RobTillaart/LTC2942_RT


#include "LTC2942.h"


const uint8_t LTC2942_REG_STATUS             = 0x00;  //  RO
const uint8_t LTC2942_REG_CONTROL            = 0x01;  //  RW

const uint8_t LTC2942_REG_CHARGE_MSB         = 0x02;  //  RW
const uint8_t LTC2942_REG_CHARGE_LSB         = 0x03;  //  RW
const uint8_t LTC2942_REG_CHARGE_TH_HIGH_MSB = 0x04;  //  RW
const uint8_t LTC2942_REG_CHARGE_TH_HIGH_LSB = 0x05;  //  RW
const uint8_t LTC2942_REG_CHARGE_TH_LOW_MSB  = 0x06;  //  RW
const uint8_t LTC2942_REG_CHARGE_TH_LOW_LSB  = 0x07;  //  RW

const uint8_t LTC2942_REG_VOLTS_MSB          = 0x08;  //  RO
const uint8_t LTC2942_REG_VOLTS_LSB          = 0x09;  //  RO
const uint8_t LTC2942_REG_VOLTS_TH_HIGH      = 0x0A;  //  RW
const uint8_t LTC2942_REG_VOLTS_TH_LOW       = 0x0B;  //  RW

const uint8_t LTC2942_REG_TEMP_MSB           = 0x0C;  //  RO
const uint8_t LTC2942_REG_TEMP_LSB           = 0x0D;  //  RO
const uint8_t LTC2942_REG_TEMP_TH_HIGH       = 0x0E;  //  RW
const uint8_t LTC2942_REG_TEMP_TH_LOW        = 0x0F;  //  RW



LTC2942::LTC2942(TwoWire *wire)
{
  _address = 0x64;
  _wire = wire;
}

bool LTC2942::begin(float mAh, float RSense)
{
  //  check parameters.
  //  RSense, what is minimum allowed? Max current?
  //  for now it should not be below 5 mOhm => maxCurrent = 10A.
  if (RSense < 0.005f)
  {
    _error = LTC2942_RSENSE_ERROR;
    return false;
  }
  //  Page 10, verify if RSense makes sense
  if (RSense > ((0.085 * 0.050f * 65535) / mAh))
  {
    _error = LTC2942_RSENSE_ERROR;
    return false;
  }
  //  TODO check limit page 10
  //  if ((mAh < 100) || (mAh > 5500))
  //  {
  //    _error = LTC2942_MAH_ERROR;
  //    return false;
  //  }

  //  Page 11, calculate and verify pre-scaler
  float tmp = 128 * mAh /(65535 * 0.085f) * (RSense / 0.050f);
  uint8_t prescaler;
  for (prescaler = 1; prescaler < 128; prescaler *= 2)
  {
    if (prescaler > tmp) break;
  }
  if (prescaler <= tmp)
  {
    _error = LTC2942_PRESCALER_ERROR;
    return false;
  }

  // check connection
  _error = LTC2942_OK;
  if (! isConnected())
  {
    _error = LTC2942_NOT_READY;
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

  return _error == LTC2942_OK;
}

bool LTC2942::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t LTC2942::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  STATUS & CONTROL
//
bool LTC2942::getStatus(uint8_t &status)
{
  uint8_t value;
  _read(LTC2942_REG_STATUS, &value, 1);
  status = value;
  return (_error == LTC2942_OK);
}


bool LTC2942::setControl( uint8_t ALCC,
                          uint8_t prescaler,
                          uint8_t shutDown,
                          uint8_t ADCMode)
{
  if ((ALCC > 2)     || (prescaler > 7) ||
      (shutDown > 1) || (ADCMode > 3))
  {
    _error = LTC2942_CONTROL_ERROR;
    return false;
  }
  //  0..7 ==> 1..128
  _prescaler = 1 << prescaler;
  _QLSB = _calculateQLSB();

  uint8_t control = shutDown | (ALCC << 1) | (prescaler << 3) | (ADCMode << 6);
  return _setControl(control);
}


bool LTC2942::getControl( uint8_t &ALCC,
                          uint8_t &prescaler,
                          uint8_t &shutDown,
                          uint8_t &ADCMode)
{
  uint8_t control;
  if (_getControl(control) != LTC2942_OK)
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
bool LTC2942::setRawCharge(uint16_t raw)
{
  uint8_t value[2];
  value[0] = raw >> 8;
  value[1] = raw & 0xFF;
  _write(LTC2942_REG_CHARGE_MSB, value, 2);
  return (_error == LTC2942_OK);
}

bool LTC2942::getRawCharge(uint16_t &raw)
{
  uint8_t value[2] = {0, 0};
  _read(LTC2942_REG_CHARGE_MSB, value, 2);
  raw = (value[0] << 8) + value[1];
  return (_error == LTC2942_OK);
}

bool LTC2942::setCharge(float charge)
{
  return setRawCharge(charge / _QLSB);
}

bool LTC2942::getCharge(float &charge)
{
  uint16_t raw = 0;
  getRawCharge(raw);
  charge = raw * _QLSB;
  return (_error == LTC2942_OK);
}

bool LTC2942::getPercentageFull(float &percentage)
{
  float perc;
  getCharge(perc);
  percentage = (100.0 * perc) / _mAh;
  return (_error == LTC2942_OK);
}

float LTC2942::getQLSB()
{
  return _QLSB;
}


/////////////////////////////////////////////
//
//  THRESHOLD CHARGE
//
bool LTC2942::setRawChargeThresholdHigh(uint16_t th)
{
  uint8_t value[2];
  value[0] = th >> 8;
  value[1] = th & 0xFF;
  _write(LTC2942_REG_CHARGE_TH_HIGH_MSB, value, 2);
  return (_error == LTC2942_OK);
}

bool LTC2942::getRawChargeThresholdHigh(uint16_t &th)
{
  uint8_t value[2];
  _read(LTC2942_REG_CHARGE_TH_HIGH_MSB, value, 2);
  th = (value[0] << 8) + value[1];
  return (_error == LTC2942_OK);
}

bool LTC2942::setRawChargeThresholdLow(uint16_t th)
{
  uint8_t value[2];
  value[0] = th >> 8;
  value[1] = th & 0xFF;
  _write(LTC2942_REG_CHARGE_TH_LOW_MSB, value, 2);
  return (_error == LTC2942_OK);
}

bool LTC2942::getRawChargeThresholdLow(uint16_t &th)
{
  uint8_t value[2];
  _read(LTC2942_REG_CHARGE_TH_LOW_MSB, value, 2);
  th = (value[0] << 8) + value[1];
  return (_error == LTC2942_OK);
}

bool LTC2942::setChargeThresholdHigh(float th)
{
  return setRawChargeThresholdHigh(th / _QLSB);
}

bool LTC2942::getChargeThresholdHigh(float &th)
{
  uint16_t raw = 0;
  getRawChargeThresholdHigh(raw);
  th = raw * _QLSB;
  return (_error == LTC2942_OK);
}

bool LTC2942::setChargeThresholdLow(float th)
{
  return setRawChargeThresholdLow(th / _QLSB);
}

bool LTC2942::getChargeThresholdLow(float &th)
{
  uint16_t raw = 0;
  getRawChargeThresholdLow(raw);
  th = raw * _QLSB;
  return (_error == LTC2942_OK);
}



/////////////////////////////////////////////
//
//  VOLTS
//
bool LTC2942::getVoltage(float &voltage)
{
  uint8_t value[2] = {0, 0};
  _read(LTC2942_REG_VOLTS_MSB, value, 2);
  voltage = ((value[0] << 8) + value[1]) * (6.0f / 65535.0f);
  return (_error == LTC2942_OK);
}

bool LTC2942::setVoltageThresholdHigh(float th)
{
  uint8_t value = round(th * (256.0f / 6.0f));
  _write(LTC2942_REG_VOLTS_TH_HIGH, &value, 1);
  return (_error == LTC2942_OK);
}

bool LTC2942::getVoltageThresholdHigh(float &th)
{
  uint8_t value;
  _read(LTC2942_REG_VOLTS_TH_HIGH, &value, 1);
  th = value * (6.0f / 256.0f);
  return (_error == LTC2942_OK);
}

bool LTC2942::setVoltageThresholdLow(float th)
{
  uint8_t value = round(th * (256.0f / 6.0f));
  _write(LTC2942_REG_VOLTS_TH_LOW, &value, 1);
  return (_error == LTC2942_OK);
}

bool LTC2942::getVoltageThresholdLow(float &th)
{
  uint8_t value;
  _read(LTC2942_REG_VOLTS_TH_LOW, &value, 1);
  th = value * (6.0f / 256.0f);
  return (_error == LTC2942_OK);
}


/////////////////////////////////////////////
//
//  TEMPERATURE
//
bool LTC2942::getTemperature(float &temperature)
{
  uint8_t value[2] = {0, 0};
  _read(LTC2942_REG_TEMP_MSB, value, 2);
  temperature = ((value[0] << 8) + value[1]) * (600.0f / 65535.0f) - 273.15f;
  return (_error == LTC2942_OK);
}

bool LTC2942::setTemperatureThresholdHigh(float th)
{
  uint8_t value = round((th + 273.15f) * (256.0f / 600.0f));
  _write(LTC2942_REG_TEMP_TH_HIGH, &value, 1);
  return (_error == LTC2942_OK);
}

bool LTC2942::getTemperatureThresholdHigh(float &th)
{
  uint8_t value;
  _read(LTC2942_REG_TEMP_TH_HIGH, &value, 1);
  th = value * (600.0f / 256.0f) - 273.15;
  return (_error == LTC2942_OK);
}

bool LTC2942::setTemperatureThresholdLow(float th)
{
  uint8_t value = round((th + 273.15f) * (256.0f / 600.0f));
  _write(LTC2942_REG_TEMP_TH_LOW, &value, 1);
  return (_error == LTC2942_OK);
}

bool LTC2942::getTemperatureThresholdLow(float &th)
{
  uint8_t value;
  _read(LTC2942_REG_TEMP_TH_LOW, &value, 1);
  th = value * (600.0f / 256.0f) - 273.15;
  return (_error == LTC2942_OK);
}


/////////////////////////////////////////////
//
//  DEBUG
//
int LTC2942::getLastError()
{
  int e = _error;
  _error = LTC2942_OK;
  return e;
}

uint8_t LTC2942::getPrescaler()
{
  return _prescaler;
}

float LTC2942::getMaxCurrent()
{
  return 0.050f / _RSense;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
bool LTC2942::_setControl(uint8_t control)
{
  //  not allowed bit pattern. Page 9.
  if (control & 0x06)
  {
    _error = LTC2942_CONTROL_ERROR;
    return false;
  }
  _write(LTC2942_REG_CONTROL, &control, 1);
  return (_error == LTC2942_OK);
}

bool LTC2942::_getControl(uint8_t &control)
{
  uint8_t value = 0;
  _read(LTC2942_REG_CONTROL, &value, 1);
  control = value;
  return (_error == LTC2942_OK);
}

float LTC2942::_calculateQLSB()
{
  //  datasheet, page 4
  //  0.085f = mAh,
  //  0.050f is default RSense = 50 mOhm
  return (0.085f * 0.050f) / _RSense * (_prescaler * (1.0f / 128.0f));
}

//
//  LOW LEVEL IO
//
int LTC2942::_write(uint8_t reg, uint8_t * arr, uint8_t size)
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

int LTC2942::_read(uint8_t reg, uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != LTC2942_OK)
  {
    return _error;
  }
  uint8_t bytes = _wire->requestFrom(_address, size);
  if (bytes == 0)
  {
    _error = LTC2942_REQUEST_ERROR1;
    return _error;
  }
  if (bytes < size)
  {
    _error = LTC2942_REQUEST_ERROR2;
    return _error;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    arr[i] = _wire->read();
  }
  _error = LTC2942_OK;
  return LTC2942_OK;
}


//  -- END OF FILE --

