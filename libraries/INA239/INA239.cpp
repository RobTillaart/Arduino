//    FILE: INA239.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2024-12-05
// PURPOSE: Arduino library for the INA239, SPI, 16 bit, voltage, current and power sensor.
//     URL: https://github.com/RobTillaart/INA239
//
//  Read the datasheet for the details


#include "INA239.h"

//      REGISTERS                   ADDRESS    BITS  RW   //  names same as in INA228
#define INA239_CONFIG               0x00    //  16   RW
#define INA239_ADC_CONFIG           0x01    //  16   RW
#define INA239_SHUNT_CAL            0x02    //  16   RW
#define INA239_SHUNT_VOLTAGE        0x04    //  16   R-
#define INA239_BUS_VOLTAGE          0x05    //  16   R-
#define INA239_TEMPERATURE          0x06    //  16   R-
#define INA239_CURRENT              0x07    //  16   R-
#define INA239_POWER                0x08    //  24   R-
#define INA239_DIAG_ALERT           0x0B    //  16   RW
#define INA239_SOVL                 0x0C    //  16   RW
#define INA239_SUVL                 0x0D    //  16   RW
#define INA239_BOVL                 0x0E    //  16   RW
#define INA239_BUVL                 0x0F    //  16   RW
#define INA239_TEMP_LIMIT           0x10    //  16   RW
#define INA239_POWER_LIMIT          0x11    //  16   RW
#define INA239_MANUFACTURER         0x3E    //  16   R-
#define INA239_DEVICE_ID            0x3F    //  16   R-


//  CONFIG MASKS (register 0)
#define INA239_CFG_RST              0x8000
#define INA239_CFG_CONVDLY          0x3FC0
#define INA239_CFG_ADCRANGE         0x0010
#define INA239_CFG_RESERVED         0x402F  //  all unused bits


//  ADC MASKS (register 1)
#define INA239_ADC_MODE             0xF000
#define INA239_ADC_VBUSCT           0x0E00
#define INA239_ADC_VSHCT            0x01C0
#define INA239_ADC_VTCT             0x0038
#define INA239_ADC_AVG              0x0007


////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
//  HARDWARE SPI
INA239::INA239(uint8_t select, __SPI_CLASS__ * mySPI)
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
INA239::INA239(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
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

bool INA239::begin()
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
//  PAGE 22
float INA239::getBusVoltage()
{
  //  always positive, remove reserved bits.
  int32_t value = _readRegister(INA239_BUS_VOLTAGE, 2) >> 4;
  float bus_LSB = 3.125e-3;  //  3.125 mV/LSB
  float voltage = value * bus_LSB;
  return voltage;
}

//  PAGE 22
float INA239::getShuntVoltage()
{
  //  shunt_LSB depends on ADCRANGE in INA239_CONFIG register.
  float shunt_LSB = 5e-6;  //  5.0 uV/LSB
  if (_ADCRange == true)
  {
    shunt_LSB = 1.25e-6;   //  1.25 uV/LSB
  }

  //  remove reserved bits.
  int32_t value = _readRegister(INA239_SHUNT_VOLTAGE, 2);
  //  handle negative values (16 bit)
  if (value & 0x00008000)
  {
    value |= 0xFFFF00000;
  }
  float voltage = value * shunt_LSB;
  return voltage;
}

//  PAGE 23 + 8.1.2
float INA239::getCurrent()
{
  int16_t value = _readRegister(INA239_CURRENT, 2);
  float current = value * _current_LSB;
  return current;
}

//  PAGE 23 + 8.1.2
float INA239::getPower()
{
  uint32_t value = _readRegister(INA239_POWER, 3);
  //  PAGE 28 (8.1.2)
  return value * 0.2 * _current_LSB;
}

//  PAGE 23 DONE
float INA239::getTemperature()
{
  uint32_t value = _readRegister(INA239_TEMPERATURE, 2);
  float LSB = 125e-3;  //  125 m°C/LSB
  return value * LSB;
}


////////////////////////////////////////////////////////
//
//  CONFIG REGISTER 0
//
//  PAGE 20
void INA239::reset()
{
  uint16_t value = _readRegister(INA239_CONFIG, 2);
  value |= INA239_CFG_RST;
  _writeRegister(INA239_CONFIG, value);
}

//  PAGE 20
void INA239::setConversionDelay(uint8_t steps)
{
  uint16_t value = _readRegister(INA239_CONFIG, 2);
  value &= ~INA239_CFG_CONVDLY;
  value |= (steps << 6);
  _writeRegister(INA239_CONFIG, value);
}

uint8_t INA239::getConversionDelay()
{
  uint16_t value = _readRegister(INA239_CONFIG, 2);
  return (value >> 6) & 0xFF;
}

//  PAGE 20
bool INA239::setADCRange(bool flag)
{
  uint16_t value = _readRegister(INA239_CONFIG, 2);
  _ADCRange = (value & INA239_CFG_ADCRANGE) > 0;
  //  nothing changed ==> we're done.
  if (flag == _ADCRange) return true;

  if (flag) value |= INA239_CFG_ADCRANGE;
  else      value &= ~INA239_CFG_ADCRANGE;
  //  if value has not changed we do not need to write it back.
  _writeRegister(INA239_CONFIG, value);
  //  INA228, #26
  bool rv = setMaxCurrentShunt(getMaxCurrent(), getShunt()) == 0;
  return rv;
}

bool INA239::getADCRange()
{
  uint16_t value = _readRegister(INA239_CONFIG, 2);
  _ADCRange = (value & INA239_CFG_ADCRANGE) > 0;
  return _ADCRange;
}


////////////////////////////////////////////////////////
//
//  CONFIG ADC REGISTER 1
//
//  PAGE 21 + 22
bool INA239::setMode(uint8_t mode)
{
  if (mode > 0x0F) return false;
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  value &= ~INA239_ADC_MODE;
  value |= (mode << 12);
  _writeRegister(INA239_ADC_CONFIG, value);
  return true;
}

uint8_t INA239::getMode()
{
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  return (value & INA239_ADC_MODE) >> 12;
}

bool INA239::setBusVoltageConversionTime(uint8_t bvct)
{
  if (bvct > 7) return false;
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  value &= ~INA239_ADC_VBUSCT;
  value |= (bvct << 9);
  _writeRegister(INA239_ADC_CONFIG, value);
  return true;
}

uint8_t INA239::getBusVoltageConversionTime()
{
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  return (value & INA239_ADC_VBUSCT) >> 9;
}

bool INA239::setShuntVoltageConversionTime(uint8_t svct)
{
  if (svct > 7) return false;
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  value &= ~INA239_ADC_VSHCT;
  value |= (svct << 6);
  _writeRegister(INA239_ADC_CONFIG, value);
  return true;
}

uint8_t INA239::getShuntVoltageConversionTime()
{
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  return (value & INA239_ADC_VSHCT) >> 6;
}

bool INA239::setTemperatureConversionTime(uint8_t tct)
{
  if (tct > 7) return false;
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  value &= ~INA239_ADC_VTCT;
  value |= (tct << 3);
  _writeRegister(INA239_ADC_CONFIG, value);
  return true;
}

uint8_t INA239::getTemperatureConversionTime()
{
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  return (value & INA239_ADC_VTCT) >> 3;
}

bool INA239::setAverage(uint8_t avg)
{
  if (avg > 7) return false;
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  value &= ~INA239_ADC_AVG;
  value |= avg;
  _writeRegister(INA239_ADC_CONFIG, value);
  return true;
}

uint8_t INA239::getAverage()
{
  uint16_t value = _readRegister(INA239_ADC_CONFIG, 2);
  return (value & INA239_ADC_AVG);
}


////////////////////////////////////////////////////////
//
//  SHUNT CALIBRATION REGISTER 2
//
//  PAGE 28 + 8.1.2
int INA239::setMaxCurrentShunt(float maxCurrent, float shunt)
{
  //  Shunt can be really small
  if (shunt < 0.0001) return -2;   //  TODO error code
  _maxCurrent = maxCurrent;
  _shunt = shunt;
  _current_LSB = _maxCurrent * 3.0517578125e-5;  //  pow(2, -15);

  //  PAGE 31 (8.1.2)
  float shunt_cal = 819.2e6 * _current_LSB * _shunt;
  //  depends on ADCRANGE in INA239_CONFIG register.
  if (_ADCRange == true)
  {
    shunt_cal *= 4;
  }
  //  shunt_cal must be written to REGISTER.
  //  work in progress PR #7
  _writeRegister(INA239_SHUNT_CAL, shunt_cal);

  return 0;
}

float INA239::getMaxCurrent()
{
  return _maxCurrent;
}

float INA239::getShunt()
{
  return _shunt;
}

float INA239::getCurrentLSB()
{
  return _current_LSB;
}


////////////////////////////////////////////////////////
//
//  DIAGNOSE ALERT REGISTER 11
//
//  PAGE 23
void INA239::setDiagnoseAlert(uint16_t flags)
{
  _writeRegister(INA239_DIAG_ALERT, flags);
}

uint16_t INA239::getDiagnoseAlert()
{
  return _readRegister(INA239_DIAG_ALERT, 2);
}

//  INA239.h has an enum for the bit fields.
void INA239::setDiagnoseAlertBit(uint8_t bit)
{
  uint16_t value = _readRegister(INA239_DIAG_ALERT, 2);
  uint16_t mask = (1 << bit);
  //  only write new value if bit not set.
  if ((value & mask) == 0)
  {
    value |= mask;
    _writeRegister(INA239_DIAG_ALERT, value);
  }
}

void INA239::clearDiagnoseAlertBit(uint8_t bit)
{
  uint16_t value = _readRegister(INA239_DIAG_ALERT, 2);
  uint16_t mask = (1 << bit);
  //  only write new value if needed.
  if ((value & mask ) != 0)
  {
    value &= ~mask;
    _writeRegister(INA239_DIAG_ALERT, value);
  }
}

uint16_t INA239::getDiagnoseAlertBit(uint8_t bit)
{
  uint16_t value = _readRegister(INA239_DIAG_ALERT, 2);
  return (value >> bit) & 0x01;
}


////////////////////////////////////////////////////////
//
//  THRESHOLD AND LIMIT REGISTERS 12-17
//
//  TODO - API also for INA228
//  PAGE 25 - minimalistic
void INA239::setShuntOvervoltageTH(uint16_t threshold)
{
  //  TODO ADCRANGE DEPENDENT
  _writeRegister(INA239_SOVL, threshold);
}

uint16_t INA239::getShuntOvervoltageTH()
{
  //  TODO ADCRANGE DEPENDENT
  return _readRegister(INA239_SOVL, 2);
}

void INA239::setShuntUndervoltageTH(uint16_t threshold)
{
  //  TODO ADCRANGE DEPENDENT
  _writeRegister(INA239_SUVL, threshold);
}

uint16_t INA239::getShuntUndervoltageTH()
{
  //  TODO ADCRANGE DEPENDENT
  return _readRegister(INA239_SUVL, 2);
}

void INA239::setBusOvervoltageTH(uint16_t threshold)
{
  if (threshold > 0x7FFF) return;
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  _writeRegister(INA239_BOVL, threshold);
}

uint16_t INA239::getBusOvervoltageTH()
{
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  return _readRegister(INA239_BOVL, 2);
}

void INA239::setBusUndervoltageTH(uint16_t threshold)
{
  if (threshold > 0x7FFF) return;
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  _writeRegister(INA239_BUVL, threshold);
}

uint16_t INA239::getBusUndervoltageTH()
{
  //float LSB = 3.125e-3;  //  3.125 mV/LSB.
  return _readRegister(INA239_BUVL, 2);
}

void INA239::setTemperatureOverLimitTH(uint16_t threshold)
{
  //float LSB = 125e-3;  //  125 m°C/LSB.
  _writeRegister(INA239_TEMP_LIMIT, threshold);
}

uint16_t INA239::getTemperatureOverLimitTH()
{
  //float LSB = 125e-3;  //  125 m°C/LSB.
  return _readRegister(INA239_TEMP_LIMIT, 2);
}

void INA239::setPowerOverLimitTH(uint16_t threshold)
{
  //  PAGE 26
  //  Conversion factor: 256 × Power LSB.
  _writeRegister(INA239_POWER_LIMIT, threshold);
}

uint16_t INA239::getPowerOverLimitTH()
{
  //  PAGE 26
  //  Conversion factor: 256 × Power LSB.
  return _readRegister(INA239_POWER_LIMIT, 2);
}


////////////////////////////////////////////////////////
//
//  MANUFACTURER and ID REGISTER 3E/3F
//
//  PAGE 26
uint16_t INA239::getManufacturer()
{
  uint16_t value = _readRegister(INA239_MANUFACTURER, 2);
  return value;
}

uint16_t INA239::getDieID()
{
  uint16_t value = _readRegister(INA239_DEVICE_ID, 2);
  return (value >> 4) & 0x0FFF;
}

uint16_t INA239::getRevision()
{
  uint16_t value = _readRegister(INA239_DEVICE_ID, 2);
  return value & 0x000F;
}



/////////////////////////////////////////////////////////////////////////////
//
//  SPI
//
void INA239::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
}


uint32_t INA239::getSPIspeed()
{
  return _SPIspeed;
}


bool INA239::usesHWSPI()
{
  return _hwSPI;
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint32_t INA239::_readRegister(uint8_t reg, uint8_t bytes)  //  bytes = 2 or 3.
{
  //  Dedicated SPI code
  uint32_t rv = 0;
  uint8_t addr = (reg << 2) + 1;  //  1 = Read flag.  P18 datasheet
  uint8_t count = bytes;
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    rv += _mySPI->transfer(addr);
    while (count--)
    {
      rv <<= 8;
      rv += _mySPI->transfer(0x00);
    }
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    rv += swSPI_transfer(addr);
    while (count--)
    {
      rv <<= 8;
      rv += swSPI_transfer(0x00);
    }
  }
  digitalWrite(_select, HIGH);
  return rv;
}


uint16_t INA239::_writeRegister(uint8_t reg, uint16_t value)
{
  uint32_t rv = 0;
  uint8_t addr = (reg << 2);  //  0 = Write flag.  P18 datasheet
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


uint8_t INA239::swSPI_transfer(uint8_t value)
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

