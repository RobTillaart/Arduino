//
//    FILE: AD5620.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2024-10-25
// PURPOSE: Arduino library for AD5620 / AD5640 Digital Analog Convertor (12/14 bit).


#include "AD5620.h"


//  HARDWARE SPI
AD5620::AD5620(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
{
  _select    = slaveSelect;
  _hwSPI     = true;
  _mySPI     = mySPI;
  _value     = 0;
  _type      = 12;
  _maxValue  = 4095;
  _powerMode = 0;
}

//  SOFTWARE SPI
AD5620::AD5620(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
{
  _select    = slaveSelect;
  _hwSPI     = false;
  _mySPI     = NULL;
  _dataOut   = spiData;
  _clock     = spiClock;
  _value     = 0;
  _type      = 12;
  _maxValue  = 4095;
  _powerMode = 0;
}


//  initializes the SPI
//  and sets internal state
void AD5620::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);

  if (_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else  //  SOFTWARE SPI
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock, OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock, LOW);
  }
}


uint8_t AD5620::getType()
{
  return _type;
}


//
//  SET VALUE
//
bool AD5620::setValue(uint16_t value)
{
  //  range check
  if (value > _maxValue) return false;
  _value = value;
  //  prepare 12 bit transfer.
  //  datasheet page 18, LSB 2 bits don't care
  uint32_t data = value << 2;
  //  set powerMode bits if not 0.
  if (_powerMode) data |= (_powerMode << 14);
  updateDevice(data);
  return true;
}


uint16_t AD5620::getValue()
{
  return _value;
}


uint16_t AD5620::getMaxValue()
{
  return _maxValue;
}


bool AD5620::setPercentage(float percentage)
{
  //  range check
  if ((percentage < 0) || (percentage > 100)) return false;

  uint32_t value = round(40.95 * percentage);
  return setValue(value);
}


float AD5620::getPercentage()
{
  float value = getValue();
  if (value > 0)
  {
    return value * (100.0 / 4095);
  }
  return 0;
}


//
//  POWER DOWN
//
bool AD5620::setPowerDownMode(uint8_t mode)
{
  //  range check
  if (mode > 3) return false;
  _powerMode = mode;
  return true;
}


uint8_t AD5620::getPowerDownMode()
{
  return _powerMode;
}


//
//  SPI
//
void AD5620::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
};


uint32_t AD5620::getSPIspeed()
{
  return _SPIspeed;
}


bool AD5620::usesHWSPI()
{
  return _hwSPI;
}


//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//

void AD5620::updateDevice(uint16_t data)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer((data >> 8) & 0xFF);
    _mySPI->transfer(data & 0xFF);
    _mySPI->endTransaction();
  }
  else  //  Software SPI
  {
    swSPI_transfer(data);
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void AD5620::swSPI_transfer(uint16_t value)
{
  int clk = _clock;
  int dao = _dataOut;
  //  Shifting 16 bits starting from MSB to LSB
  for (uint16_t mask = 0x8000; mask; mask >>= 1)
  {
    digitalWrite(dao,(value & mask)? HIGH : LOW);
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
}


//////////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
AD5640::AD5640(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
       :AD5620(slaveSelect, mySPI)
{
  _type      = 14;
  _maxValue  = 16383;
}


//  SOFTWARE SPI
AD5640::AD5640(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
       :AD5620(slaveSelect, spiData, spiClock)
{
  _type      = 14;
  _maxValue  = 16383;
}


bool AD5640::setValue(uint16_t value)
{
  //  range check
  if (value > _maxValue) return false;
  _value = value;
  //  prepare 14 bit transfer.
  //  datasheet page 18.
  uint16_t data = value;
  //  set powerMode bits if not 0.
  if (_powerMode) data |= (_powerMode << 14);
  updateDevice(data);
  return true;
}


bool AD5640::setPercentage(float percentage)
{
  //  range check
  if ((percentage < 0) || (percentage > 100)) return false;

  uint32_t value = round(163.83 * percentage);
  return setValue(value);
}


float AD5640::getPercentage()
{
  float value = getValue();
  if (value > 0)
  {
    return value * ( 100.0 / 16383);
  }
  return 0;
}



//  -- END OF FILE --

