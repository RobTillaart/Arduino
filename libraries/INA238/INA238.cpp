//    FILE: INA238.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-06-11
// PURPOSE: Arduino library for the INA238, I2C, 16 bit, voltage, current and power sensor.
//     URL: https://github.com/RobTillaart/INA238
//          https://www.adafruit.com/product/6349

//
//  Read the datasheet for the details


#include "INA238.h"

//      REGISTERS                   ADDRESS    BITS  RW
#define INA238_CONFIG               0x00    //  16   RW
#define INA238_ADC_CONFIG           0x01    //  16   RW
#define INA238_SHUNT_CAL            0x02    //  16   RW
#define INA238_SHUNT_VOLTAGE        0x04    //  16   R-
#define INA238_BUS_VOLTAGE          0x05    //  16   R-
#define INA238_TEMPERATURE          0x06    //  16   R-
#define INA238_CURRENT              0x07    //  16   R-
#define INA238_POWER                0x08    //  24   R-
#define INA238_DIAG_ALERT           0x0B    //  16   RW
#define INA238_SOVL                 0x0C    //  16   RW
#define INA238_SUVL                 0x0D    //  16   RW
#define INA238_BOVL                 0x0E    //  16   RW
#define INA238_BUVL                 0x0F    //  16   RW
#define INA238_TEMP_LIMIT           0x10    //  16   RW
#define INA238_POWER_LIMIT          0x11    //  16   RW
#define INA238_MANUFACTURER         0x3E    //  16   R-
#define INA238_DEVICE_ID            0x3F    //  16   R-


//  CONFIG MASKS (register 0)
#define INA238_CFG_RST              0x8000
#define INA238_CFG_CONVDLY          0x3FC0
#define INA238_CFG_ADCRANGE         0x0010
#define INA238_CFG_RESERVED         0x402F  //  all unused bits


//  ADC MASKS (register 1)
#define INA238_ADC_MODE             0xF000
#define INA238_ADC_VBUSCT           0x0E00
#define INA238_ADC_VSHCT            0x01C0
#define INA238_ADC_VTCT             0x0038
#define INA238_ADC_AVG              0x0007


////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
INA238::INA238(const uint8_t address, TwoWire *wire)
{
  _address     = address;
  _wire        = wire;
  //  no calibrated values by default.
  _shunt       = 0.015;
  _maxCurrent  = 10.0;
  //  3.0517578125e-5 = pow(2, -15) 8.1.2 formula (2)
  _current_LSB = _maxCurrent * 3.0517578125e-5;
  _error       = 0;
}


bool INA238::begin()
{
  if (! isConnected()) return false;

  getADCRange();
  return true;
}


bool INA238::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t INA238::getAddress()
{
  return _address;
}


////////////////////////////////////////////////////////
//
//  CORE FUNCTIONS
//
//  PAGE 23  CHECK
float INA238::getBusVoltage()
{
  //  always positive, remove reserved bits.
  int16_t value = _readRegister(INA238_BUS_VOLTAGE, 2);
  float bus_LSB = 3.125e-3;  //  3.125 mV
  float voltage = value * bus_LSB;
  return voltage;
}

//  PAGE 23  CHECK
float INA238::getShuntVoltage()
{
  //  shunt_LSB depends on ADCRANGE in INA238_CONFIG register.
  float shunt_LSB = 5.0e-6;  //  5.0 uV
  if (_ADCRange == true)
  {
    shunt_LSB = 1.25e-6;     //  1.25 uV
  }

  //  remove reserved bits.
  int16_t value = _readRegister(INA238_SHUNT_VOLTAGE, 2);
  //  int16_t handles negative values (16 bit)
  float voltage = value * shunt_LSB;
  return voltage;
}

//  PAGE 24 + 8.1.2  CHECK
float INA238::getCurrent()
{
  //  remove reserved bits.
  int16_t value = _readRegister(INA238_CURRENT, 2);
  //  int16_t handles negative values (16 bit)
  float current = value * _current_LSB;  //  8.1.2 formula (3)
  return current;
}

//  PAGE 24 + 8.1.2  CHECK
float INA238::getPower()
{
  //  24 bit !!
  uint32_t value = _readRegister(INA238_POWER, 3);
  //  PAGE 28-29 (8.1.2)
  return value * 0.2 * _current_LSB;  //  formula (4)
}

//  PAGE 24  CHECK
float INA238::getTemperature()
{
  uint32_t value = _readRegister(INA238_TEMPERATURE, 2);
  float LSB = 125e-3;  //  125 milli degree Celsius
  return value * LSB;
}


////////////////////////////////////////////////////////
//
//  CONFIG REGISTER 0
//
void INA238::reset()
{
  uint16_t value = _readRegister(INA238_CONFIG, 2);
  value |= INA238_CFG_RST;
  _writeRegister(INA238_CONFIG, value);
}


void INA238::setConversionDelay(uint8_t steps)
{
  uint16_t value = _readRegister(INA238_CONFIG, 2);
  value &= ~INA238_CFG_CONVDLY;
  value |= (steps << 6);
  _writeRegister(INA238_CONFIG, value);
}

uint8_t INA238::getConversionDelay()
{
  uint16_t value = _readRegister(INA238_CONFIG, 2);
  return (value >> 6) & 0xFF;  //  8 bits
}

void INA238::setADCRange(bool flag)
{
  //  if (flag == _ADCRange) return;
  _ADCRange = flag;
  uint16_t value = _readRegister(INA238_CONFIG, 2);
  if (flag) value |= INA238_CFG_ADCRANGE;
  else      value &= ~INA238_CFG_ADCRANGE;
  //  if value has not changed we do not need to write it back.
  _writeRegister(INA238_CONFIG, value);
}

bool INA238::getADCRange()
{
  uint16_t value = _readRegister(INA238_CONFIG, 2);
  _ADCRange = (value & INA238_CFG_ADCRANGE) > 0;
  return _ADCRange;
}


////////////////////////////////////////////////////////
//
//  CONFIG ADC REGISTER 1
//
bool INA238::setMode(uint8_t mode)
{
  if (mode > 0x0F) return false;
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  value &= ~INA238_ADC_MODE;
  value |= (mode << 12);
  _writeRegister(INA238_ADC_CONFIG, value);
  return true;
}

uint8_t INA238::getMode()
{
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  return (value & INA238_ADC_MODE) >> 12;
}

bool INA238::setBusVoltageConversionTime(uint8_t bvct)
{
  if (bvct > 7) return false;
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  value &= ~INA238_ADC_VBUSCT;
  value |= (bvct << 9);
  _writeRegister(INA238_ADC_CONFIG, value);
  return true;
}

uint8_t INA238::getBusVoltageConversionTime()
{
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  return (value & INA238_ADC_VBUSCT) >> 9;
}

bool INA238::setShuntVoltageConversionTime(uint8_t svct)
{
  if (svct > 7) return false;
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  value &= ~INA238_ADC_VSHCT;
  value |= (svct << 6);
  _writeRegister(INA238_ADC_CONFIG, value);
  return true;
}

uint8_t INA238::getShuntVoltageConversionTime()
{
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  return (value & INA238_ADC_VSHCT) >> 6;
}

bool INA238::setTemperatureConversionTime(uint8_t tct)
{
  if (tct > 7) return false;
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  value &= ~INA238_ADC_VTCT;
  value |= (tct << 3);
  _writeRegister(INA238_ADC_CONFIG, value);
  return true;
}

uint8_t INA238::getTemperatureConversionTime()
{
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  return (value & INA238_ADC_VTCT) >> 3;
}

bool INA238::setAverage(uint8_t avg)
{
  if (avg > 7) return false;
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  value &= ~INA238_ADC_AVG;
  value |= avg;
  _writeRegister(INA238_ADC_CONFIG, value);
  return true;
}

uint8_t INA238::getAverage()
{
  uint16_t value = _readRegister(INA238_ADC_CONFIG, 2);
  return (value & INA238_ADC_AVG);
}


////////////////////////////////////////////////////////
//
//  SHUNT CALIBRATION REGISTER 2
//
int INA238::setMaxCurrentShunt(float maxCurrent, float shunt)
{
  //  Shunt can be really small
  if (shunt < 0.0001)   return -2;
  if (maxCurrent < 0.0) return -3;
  _maxCurrent = maxCurrent;
  _shunt = shunt;
  _current_LSB = _maxCurrent * 3.0517578125e-5;  //  pow(2, -15);

  //  PAGE 28-29 (8.1.2)
  float shunt_cal = 819.2e6 * _current_LSB * _shunt;  //  8.1.2  formula (1,2)
  //  depends on ADCRANGE in INA238_CONFIG register.
  if (_ADCRange == true)
  {
    shunt_cal *= 4;
  }
  //  shunt_cal must be written to its REGISTER.
  _writeRegister(INA238_SHUNT_CAL, shunt_cal);

  return 0;
}

float INA238::getMaxCurrent()
{
  return _maxCurrent;
}

float INA238::getShunt()
{
  return _shunt;
}

float INA238::getCurrentLSB()
{
  return _current_LSB;
}


////////////////////////////////////////////////////////
//
//  DIAGNOSE ALERT REGISTER 11
//
void INA238::setDiagnoseAlert(uint16_t flags)
{
  _writeRegister(INA238_DIAG_ALERT, flags);
}

uint16_t INA238::getDiagnoseAlert()
{
  return _readRegister(INA238_DIAG_ALERT, 2);
}

//  INA238.h has an enum for the bit fields.
void INA238::setDiagnoseAlertBit(uint8_t bit)
{
  uint16_t value = _readRegister(INA238_DIAG_ALERT, 2);
  uint16_t mask = (1 << bit);
  //  only write new value if bit not set
  if ((value & mask) == 0)
  {
    value |= mask;
    _writeRegister(INA238_DIAG_ALERT, value);
  }
}

void INA238::clearDiagnoseAlertBit(uint8_t bit)
{
  uint16_t value = _readRegister(INA238_DIAG_ALERT, 2);
  uint16_t mask = (1 << bit);
  //  only write new value if bit not set.
  if ((value & mask ) != 0)
  {
    value &= ~mask;
    _writeRegister(INA238_DIAG_ALERT, value);
  }
}

uint16_t INA238::getDiagnoseAlertBit(uint8_t bit)
{
  uint16_t value = _readRegister(INA238_DIAG_ALERT, 2);
  return (value >> bit) & 0x01;
}


////////////////////////////////////////////////////////
//
//  THRESHOLD AND LIMIT REGISTERS 12-17
//  section 7.3.6, 7.6.1.10
//
//  (sync INA228 whenever fixed)
//  - API
//  - return bool for setters?
//  - float voltage interface instead of uint16_t?  breaking!
void INA238::setShuntOvervoltageTH(uint16_t threshold)
{
  //  ADCRANGE DEPENDENT
  //  Conversion Factor: 5 μV/LSB when ADCRANGE = 0
  //  1.25 μV/LSB when ADCRANGE = 1.
  //  float LSB = 5.0e-6;
  //  if (_ADCRange == 1) LSB = 1.25e-6;
  _writeRegister(INA238_SOVL, threshold);
}

uint16_t INA238::getShuntOvervoltageTH()
{
  //  ADCRANGE DEPENDENT
  //  float LSB = 5.0e-6;
  //  if (_ADCRange == 1) LSB = 1.25e-6;
  return _readRegister(INA238_SOVL, 2);
}

void INA238::setShuntUndervoltageTH(uint16_t threshold)
{
  //  ADCRANGE DEPENDENT
  //  float LSB = 5.0e-6;
  //  if (_ADCRange == 1) LSB = 1.25e-6;
  _writeRegister(INA238_SUVL, threshold);
}

uint16_t INA238::getShuntUndervoltageTH()
{
  //  ADCRANGE DEPENDENT
  //  float LSB = 5.0e-6;
  //  if (_ADCRange == 1) LSB = 1.25e-6;
  return _readRegister(INA238_SUVL, 2);
}

void INA238::setBusOvervoltageTH(uint16_t threshold)
{
  if (threshold > 0x7FFF) return;  //  false;
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  _writeRegister(INA238_BOVL, threshold);
}

uint16_t INA238::getBusOvervoltageTH()
{
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  return _readRegister(INA238_BOVL, 2);
}

void INA238::setBusUndervoltageTH(uint16_t threshold)
{
  if (threshold > 0x7FFF) return;
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  _writeRegister(INA238_BUVL, threshold);
}

uint16_t INA238::getBusUndervoltageTH()
{
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  return _readRegister(INA238_BUVL, 2);
}

void INA238::setTemperatureOverLimitTH(uint16_t threshold)
{
  //float LSB = 125e-3;  //  milli degrees Celsius
  _writeRegister(INA238_TEMP_LIMIT, threshold);
}

uint16_t INA238::getTemperatureOverLimitTH()
{
  //float LSB = 125e-3;  //  milli degrees Celsius
  return _readRegister(INA238_TEMP_LIMIT, 2);
}

void INA238::setPowerOverLimitTH(uint16_t threshold)
{
  //  P27
  //  Conversion factor: 256 × Power LSB.
  _writeRegister(INA238_POWER_LIMIT, threshold);
}

uint16_t INA238::getPowerOverLimitTH()
{
  //  P27
  //  Conversion factor: 256 × Power LSB.
  return _readRegister(INA238_POWER_LIMIT, 2);
}


////////////////////////////////////////////////////////
//
//  MANUFACTURER and ID REGISTER 3E/3F
//
uint16_t INA238::getManufacturer()
{
  uint16_t value = _readRegister(INA238_MANUFACTURER, 2);
  return value;
}

uint16_t INA238::getDieID()
{
  uint16_t value = _readRegister(INA238_DEVICE_ID, 2);
  return (value >> 4) & 0x0FFF;
}

uint16_t INA238::getRevision()
{
  uint16_t value = _readRegister(INA238_DEVICE_ID, 2);
  return value & 0x000F;
}


////////////////////////////////////////////////////////
//
//  ERROR HANDLING
//
int INA238::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint32_t INA238::_readRegister(uint8_t reg, uint8_t bytes)
{
  _error = 0;
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    _error = -1;
    return 0;
  }

  uint32_t value = 0;
  if (bytes == _wire->requestFrom(_address, (uint8_t)bytes))
  {
    for (int i = 0; i < bytes; i++)
    {
      value <<= 8;
      value |= _wire->read();
    }
  }
  else
  {
    _error = -2;
    return 0;
  }
  return value;
}


uint16_t INA238::_writeRegister(uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value >> 8);
  _wire->write(value & 0xFF);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    _error = -1;
  }
  return n;
}


//////////////////////////////////////////////////////////////
//
//  DERIVED INA237
//
INA237::INA237(const uint8_t address, TwoWire *wire)
       :INA238(address, wire)
{
  //  wrapper for now.
}


//  -- END OF FILE --

