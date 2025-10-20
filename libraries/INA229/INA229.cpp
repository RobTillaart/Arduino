//    FILE: INA229.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.6.0
//    DATE: 2025-01-22
// PURPOSE: Arduino library for the INA229, SPI, 20 bit, voltage, current and power sensor.
//     URL: https://github.com/RobTillaart/INA229
//
//  Read the datasheet for the details


#include "INA229.h"

//      REGISTERS                   ADDRESS    BITS  RW   //  names same as in INA228
#define INA229_CONFIG               0x00    //  16   RW
#define INA229_ADC_CONFIG           0x01    //  16   RW
#define INA229_SHUNT_CAL            0x02    //  16   RW
#define INA229_SHUNT_TEMP_CO        0x03    //  16   RW
#define INA229_SHUNT_VOLTAGE        0x04    //  24   R-
#define INA229_BUS_VOLTAGE          0x05    //  24   R-
#define INA229_TEMPERATURE          0x06    //  16   R-
#define INA229_CURRENT              0x07    //  24   R-
#define INA229_POWER                0x08    //  24   R-
#define INA229_ENERGY               0x09    //  40   R-
#define INA229_CHARGE               0x0A    //  40   R-
#define INA229_DIAG_ALERT           0x0B    //  16   RW
#define INA229_SOVL                 0x0C    //  16   RW
#define INA229_SUVL                 0x0D    //  16   RW
#define INA229_BOVL                 0x0E    //  16   RW
#define INA229_BUVL                 0x0F    //  16   RW
#define INA229_TEMP_LIMIT           0x10    //  16   RW
#define INA229_POWER_LIMIT          0x11    //  16   RW
#define INA229_MANUFACTURER         0x3E    //  16   R-
#define INA229_DEVICE_ID            0x3F    //  16   R-


//  CONFIG MASKS (register 0)
#define INA229_CFG_RST              0x8000
#define INA229_CFG_RSTACC           0x4000
#define INA229_CFG_CONVDLY          0x3FC0
#define INA229_CFG_TEMPCOMP         0x0020
#define INA229_CFG_ADCRANGE         0x0010
#define INA229_CFG_RESERVED         0x000F  //  all unused bits


//  ADC MASKS (register 1)
#define INA229_ADC_MODE             0xF000
#define INA229_ADC_VBUSCT           0x0E00
#define INA229_ADC_VSHCT            0x01C0
#define INA229_ADC_VTCT             0x0038
#define INA229_ADC_AVG              0x0007


////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
//  HARDWARE SPI
INA229::INA229(uint8_t select, __SPI_CLASS__ * mySPI)
{
  _select   = select;
  _hwSPI    = true;
  _mySPI    = mySPI;

  //  no calibrated values by default.
  _shunt       = 0.015;
  _maxCurrent  = 10.0;
  _current_LSB = _maxCurrent * pow(2, -19);
}

//  SOFTWARE SPI
INA229::INA229(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _select   = select;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;

  //  no calibrated values by default.
  _shunt       = 0.015;
  _maxCurrent  = 10.0;
  _current_LSB = _maxCurrent * pow(2, -19);
}

bool INA229::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);

  if(_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else
  {
    pinMode(_dataIn, INPUT);
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }

  getADCRange();
  return true;
}


////////////////////////////////////////////////////////
//
//  CORE FUNCTIONS
//
//  PAGE 23 + PAGE 5
float INA229::getBusVoltage()
{
  //  always positive, remove reserved bits.
  int32_t value = _readRegister(INA229_BUS_VOLTAGE, 3) >> 4;
  float bus_LSB = 195.3125e-6;  //  195.3125 uV
  float voltage = value * bus_LSB;
  return voltage;
}

//  PAGE 23
float INA229::getShuntVoltage()
{
  //  shunt_LSB depends on ADCRANGE in INA229_CONFIG register.
  float shunt_LSB = 312.5e-9;  //  312.5 nV
  if (_ADCRange == true)
  {
    shunt_LSB = 78.125e-9;     //  78.125 nV
  }

  //  remove reserved bits.
  int32_t value = _readRegister(INA229_SHUNT_VOLTAGE, 3) >> 4;
  //  handle negative values (20 bit)
  if (value & 0x00080000)
  {
    value |= 0xFFF00000;
  }
  float voltage = value * shunt_LSB;
  return voltage;
}

int32_t INA229::getShuntVoltageRAW()
{
  //  remove reserved bits.
  uint32_t value = _readRegister(INA229_SHUNT_VOLTAGE, 3) >> 4;
  //  handle negative values (20 bit)
  if (value & 0x00080000)
  {
    value |= 0xFFF00000;
  }
  return (int32_t)value;
}

//  PAGE 24 + 8.1.2
float INA229::getCurrent()
{
  //  remove reserved bits.
  int32_t value = _readRegister(INA229_CURRENT, 3) >> 4;
  //  handle negative values (20 bit)
  if (value & 0x00080000)
  {
    value |= 0xFFF00000;
  }
  float current = value * _current_LSB;
  return current;
}

//  PAGE 24 + 8.1.2
float INA229::getPower()
{
  uint32_t value = _readRegister(INA229_POWER, 3);
  //  PAGE 28 (8.1.2)
  return value * 3.2 * _current_LSB;
}

//  PAGE 23
float INA229::getTemperature()
{
  uint32_t value = _readRegister(INA229_TEMPERATURE, 2);
  float LSB = 7.8125e-3;  //  milli degree Celsius
  return value * LSB;
}

//  PAGE 24 + 8.1.2
double INA229::getEnergy()
{
  //  read 40 bit UNSIGNED as a double to prevent 64 bit integers
  //  double might be 8 or 4 byte, depends on platform
  //  40 bit ==> O(10^12)
  double value = _readRegisterF(INA229_ENERGY, 'U');
  //  PAGE 31 (8.1.2)
  return value * (16 * 3.2) * _current_LSB;
}


//  PAGE 24 + 8.1.2
double INA229::getCharge()
{
  //  read 40 bit SIGNED as a float to prevent 64 bit integers
  //  double might be 8 or 4 byte, depends on platform
  //  40 bit ==> O(10^12)
  double value = _readRegisterF(INA229_CHARGE, 'S');
  //  PAGE 32 (8.1.2)
  return value * _current_LSB;
}


////////////////////////////////////////////////////////
//
//  CONFIG REGISTER 0
//
//  PAGE 20
void INA229::reset()
{
  uint16_t value = _readRegister(INA229_CONFIG, 2);
  value |= INA229_CFG_RST;
  _writeRegister(INA229_CONFIG, value);
}

bool INA229::setAccumulation(uint8_t value)
{
  if (value > 1) return false;
  uint16_t reg = _readRegister(INA229_CONFIG, 2);
  if (value == 1) reg |= INA229_CFG_RSTACC;
  else            reg &= ~INA229_CFG_RSTACC;
  _writeRegister(INA229_CONFIG, reg);
  return true;
}

bool INA229::getAccumulation()
{
  uint16_t value = _readRegister(INA229_CONFIG, 2);
  return (value & INA229_CFG_RSTACC) > 0;
}

//  PAGE 20
void INA229::setConversionDelay(uint8_t steps)
{
  uint16_t value = _readRegister(INA229_CONFIG, 2);
  value &= ~INA229_CFG_CONVDLY;
  value |= (steps << 6);
  _writeRegister(INA229_CONFIG, value);
}

uint8_t INA229::getConversionDelay()
{
  uint16_t value = _readRegister(INA229_CONFIG, 2);
  return (value >> 6) & 0xFF;
}

void INA229::setTemperatureCompensation(bool on)
{
  uint16_t value = _readRegister(INA229_CONFIG, 2);
  if (on) value |= INA229_CFG_TEMPCOMP;
  else    value &= ~INA229_CFG_TEMPCOMP;
  _writeRegister(INA229_CONFIG, value);
}

bool INA229::getTemperatureCompensation()
{
  uint16_t value = _readRegister(INA229_CONFIG, 2);
  return (value & INA229_CFG_TEMPCOMP) > 0;
}

//  PAGE 20
bool INA229::setADCRange(bool flag)
{
  uint16_t value = _readRegister(INA229_CONFIG, 2);
  _ADCRange = (value & INA229_CFG_ADCRANGE) > 0;
  //  nothing changed ==> we're done.
  if (flag == _ADCRange) return true;
  _ADCRange = flag;
  if (flag) value |= INA229_CFG_ADCRANGE;
  else      value &= ~INA229_CFG_ADCRANGE;
  _writeRegister(INA229_CONFIG, value);
  //  INA228, #26
  bool rv = setMaxCurrentShunt(getMaxCurrent(), getShunt()) == 0;
  return rv;
}

bool INA229::getADCRange()
{
  uint16_t value = _readRegister(INA229_CONFIG, 2);
  _ADCRange = (value & INA229_CFG_ADCRANGE) > 0;
  return _ADCRange;
}


////////////////////////////////////////////////////////
//
//  CONFIG ADC REGISTER 1
//
//  PAGE 21 + 22
bool INA229::setMode(uint8_t mode)
{
  if (mode > 0x0F) return false;
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  value &= ~INA229_ADC_MODE;
  value |= (mode << 12);
  _writeRegister(INA229_ADC_CONFIG, value);
  return true;
}

uint8_t INA229::getMode()
{
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  return (value & INA229_ADC_MODE) >> 12;
}

bool INA229::setBusVoltageConversionTime(uint8_t bvct)
{
  if (bvct > 7) return false;
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  value &= ~INA229_ADC_VBUSCT;
  value |= (bvct << 9);
  _writeRegister(INA229_ADC_CONFIG, value);
  return true;
}

uint8_t INA229::getBusVoltageConversionTime()
{
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  return (value & INA229_ADC_VBUSCT) >> 9;
}

bool INA229::setShuntVoltageConversionTime(uint8_t svct)
{
  if (svct > 7) return false;
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  value &= ~INA229_ADC_VSHCT;
  value |= (svct << 6);
  _writeRegister(INA229_ADC_CONFIG, value);
  return true;
}

uint8_t INA229::getShuntVoltageConversionTime()
{
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  return (value & INA229_ADC_VSHCT) >> 6;
}

bool INA229::setTemperatureConversionTime(uint8_t tct)
{
  if (tct > 7) return false;
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  value &= ~INA229_ADC_VTCT;
  value |= (tct << 3);
  _writeRegister(INA229_ADC_CONFIG, value);
  return true;
}

uint8_t INA229::getTemperatureConversionTime()
{
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  return (value & INA229_ADC_VTCT) >> 3;
}

bool INA229::setAverage(uint8_t avg)
{
  if (avg > 7) return false;
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  value &= ~INA229_ADC_AVG;
  value |= avg;
  _writeRegister(INA229_ADC_CONFIG, value);
  return true;
}

uint8_t INA229::getAverage()
{
  uint16_t value = _readRegister(INA229_ADC_CONFIG, 2);
  return (value & INA229_ADC_AVG);
}


////////////////////////////////////////////////////////
//
//  SHUNT CALIBRATION REGISTER 2
//
//  PAGE 22 + 8.1.2
int INA229::setMaxCurrentShunt(float maxCurrent, float shunt)
{
  //  Shunt can be really small
  if (shunt < 0.0001)
  {
    return -2;  //  TODO error code
  }
  _maxCurrent = maxCurrent;
  _shunt = shunt;
  _current_LSB = _maxCurrent * 1.9073486328125e-6;  //  pow(2, -19);

  //  PAGE 31 (8.1.2)
  float shunt_cal = 13107.2e6 * _current_LSB * _shunt;
  //  depends on ADCRANGE in INA229_CONFIG register.
  if (_ADCRange == true)
  {
    shunt_cal *= 4;
  }
  //  shunt_cal must be written to REGISTER.
  //  work in progress PR #7
  _writeRegister(INA229_SHUNT_CAL, shunt_cal);

  return 0;
}

float INA229::getMaxCurrent()
{
  return _maxCurrent;
}

float INA229::getShunt()
{
  return _shunt;
}

float INA229::getCurrentLSB()
{
  return _current_LSB;
}


////////////////////////////////////////////////////////
//
//  SHUNT TEMPERATURE COEFFICIENT REGISTER 3
//
//  PAGE 23
bool INA229::setShuntTemperatureCoefficent(uint16_t ppm)
{
  if (ppm > 16383) return false;
  _writeRegister(INA229_SHUNT_TEMP_CO, ppm);
  return true;
}

uint16_t INA229::getShuntTemperatureCoefficent()
{
  uint16_t value = _readRegister(INA229_SHUNT_TEMP_CO, 2);
  return value;
}


////////////////////////////////////////////////////////
//
//  DIAGNOSE ALERT REGISTER 11
//
//  PAGE 25
void INA229::setDiagnoseAlert(uint16_t flags)
{
  _writeRegister(INA229_DIAG_ALERT, flags);
}

uint16_t INA229::getDiagnoseAlert()
{
  return _readRegister(INA229_DIAG_ALERT, 2);
}

//  INA229.h has an enum for the bit fields.
void INA229::setDiagnoseAlertBit(uint8_t bit)
{
  uint16_t value = _readRegister(INA229_DIAG_ALERT, 2);
  uint16_t mask = (1 << bit);
  //  only write new value if bit not set.
  if ((value & mask) == 0)
  {
    value |= mask;
    _writeRegister(INA229_DIAG_ALERT, value);
  }
}

void INA229::clearDiagnoseAlertBit(uint8_t bit)
{
  uint16_t value = _readRegister(INA229_DIAG_ALERT, 2);
  uint16_t mask = (1 << bit);
  //  only write new value if bit not set.
  if ((value & mask ) != 0)
  {
    value &= ~mask;
    _writeRegister(INA229_DIAG_ALERT, value);
  }
}

uint16_t INA229::getDiagnoseAlertBit(uint8_t bit)
{
  uint16_t value = _readRegister(INA229_DIAG_ALERT, 2);
  return (value >> bit) & 0x01;
}


////////////////////////////////////////////////////////
//
//  THRESHOLD AND LIMIT REGISTERS 12-17
//
//  TODO - API also for INA228
//  PAGE 26 - minimalistic
void INA229::setShuntOvervoltageTH(uint16_t threshold)
{
  //  TODO ADCRANGE DEPENDENT
  _writeRegister(INA229_SOVL, threshold);
}

uint16_t INA229::getShuntOvervoltageTH()
{
  //  TODO ADCRANGE DEPENDENT
  return _readRegister(INA229_SOVL, 2);
}

void INA229::setShuntUndervoltageTH(uint16_t threshold)
{
  //  TODO ADCRANGE DEPENDENT
  _writeRegister(INA229_SUVL, threshold);
}

uint16_t INA229::getShuntUndervoltageTH()
{
  //  TODO ADCRANGE DEPENDENT
  return _readRegister(INA229_SUVL, 2);
}

void INA229::setBusOvervoltageTH(uint16_t threshold)
{
  if (threshold > 0x7FFF) return;
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  _writeRegister(INA229_BOVL, threshold);
}

uint16_t INA229::getBusOvervoltageTH()
{
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  return _readRegister(INA229_BOVL, 2);
}

void INA229::setBusUndervoltageTH(uint16_t threshold)
{
  if (threshold > 0x7FFF) return;
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  _writeRegister(INA229_BUVL, threshold);
}

uint16_t INA229::getBusUndervoltageTH()
{
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  return _readRegister(INA229_BUVL, 2);
}

void INA229::setTemperatureOverLimitTH(uint16_t threshold)
{
  //float LSB = 7.8125e-3;  //  milliCelsius
  _writeRegister(INA229_TEMP_LIMIT, threshold);
}

uint16_t INA229::getTemperatureOverLimitTH()
{
  //float LSB = 7.8125e-3;  //  milliCelsius
  return _readRegister(INA229_TEMP_LIMIT, 2);
}

void INA229::setPowerOverLimitTH(uint16_t threshold)
{
  //  PAGE 28
  //  Conversion factor: 256 × Power LSB.
  _writeRegister(INA229_POWER_LIMIT, threshold);
}

uint16_t INA229::getPowerOverLimitTH()
{
  //  PAGE 28
  //  Conversion factor: 256 × Power LSB.
  return _readRegister(INA229_POWER_LIMIT, 2);
}


////////////////////////////////////////////////////////
//
//  MANUFACTURER and ID REGISTER 3E/3F
//
//  PAGE 28
uint16_t INA229::getManufacturer()
{
  uint16_t value = _readRegister(INA229_MANUFACTURER, 2);
  return value;
}

uint16_t INA229::getDieID()
{
  uint16_t value = _readRegister(INA229_DEVICE_ID, 2);
  return (value >> 4) & 0x0FFF;
}

uint16_t INA229::getRevision()
{
  uint16_t value = _readRegister(INA229_DEVICE_ID, 2);
  return value & 0x000F;
}



/////////////////////////////////////////////////////////////////////////////
//
//  SPI
//
void INA229::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
}


uint32_t INA229::getSPIspeed()
{
  return _SPIspeed;
}


bool INA229::usesHWSPI()
{
  return _hwSPI;
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint32_t INA229::_readRegister(uint8_t reg, uint8_t bytes)  //  bytes = 2 or 3.
{
  //  Dedicated SPI code
  uint32_t value = 0;
  uint8_t addr = (reg << 2) + 1;  //  1 = Read flag.  P18 datasheet
  uint8_t count = bytes;
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    value = _mySPI->transfer(addr);
    while (count--)
    {
      value <<= 8;
      value |= _mySPI->transfer(0x00);
    }
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    value = swSPI_transfer(addr);
    while (count--)
    {
      value <<= 8;
      value |= swSPI_transfer(0x00);
    }
  }
  digitalWrite(_select, HIGH);
  return value;
}


double INA229::_readRegisterF(uint8_t reg, char mode)
{
  //  Dedicated SPI code
  double value = 0;
  uint8_t addr = (reg << 2) + 1;  //  1 = Read flag.  P18 datasheet

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    uint32_t val = _mySPI->transfer(addr);
    //  fetch 4 MSB bytes
    for (int i = 0; i < 4; i++)
    {
      val <<= 8;
      val |= _mySPI->transfer(0x00);
    }
    //  handle signed / unsigned by casting.
    if (mode == 'U') value = val;
    else             value = (int32_t) val;
    //  process last byte
    value *= 256;
    //  fetch last LSB byte
    uint8_t n = _mySPI->transfer(0x00);
    value += n;
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    uint32_t val = swSPI_transfer(addr);
    //  fetch 4 MSB bytes
    for (int i = 0; i < 4; i++)
    {
      val <<= 8;
      val |= swSPI_transfer(0x00);
    }
    //  handle signed / unsigned by casting.
    if (mode == 'U') value = val;
    else             value = (int32_t) val;
    //  process last byte
    value *= 256;
    //  fetch last LSB byte
    uint8_t n = swSPI_transfer(0x00);
    value += n;
  }
  digitalWrite(_select, HIGH);
  return value;
}


uint16_t INA229::_writeRegister(uint8_t reg, uint16_t value)
{
  uint32_t rv = 0;
  uint8_t addr = (reg << 2);  //  0 = Write flag.  page 18 datasheet
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    rv += _mySPI->transfer(addr);
    rv <<= 8;
    rv += _mySPI->transfer(value >> 8);
    rv <<= 8;
    rv += _mySPI->transfer(value & 0xFF);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    rv += swSPI_transfer(addr);
    rv <<= 8;
    rv += swSPI_transfer(value >> 8);
    rv <<= 8;
    rv += swSPI_transfer(value & 0xFF);
  }
  digitalWrite(_select, HIGH);
  return 0;
}


uint8_t INA229::swSPI_transfer(uint8_t value)
{
  uint8_t rv = 0;
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  uint8_t dai = _dataIn;
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(value & mask));
    digitalWrite(clk, HIGH);
    rv <<= 1;
    if (digitalRead(dai) == HIGH) rv |= 1;
    digitalWrite(clk, LOW);
  }
  return rv;
}


//  -- END OF FILE --

