//
//    FILE: AD5660.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2024-10-29
// PURPOSE: Arduino library for AD5660 Digital Analog Convertor (16 bit).


#include "AD5660.h"


//  HARDWARE SPI
AD5660::AD5660(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
{
  _select    = slaveSelect;
  _hwSPI     = true;
  _mySPI     = mySPI;
  _value     = 0;
  _type      = 16;
  _maxValue  = 65535;
  _powerMode = 0;
}

//  SOFTWARE SPI
AD5660::AD5660(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
{
  _select    = slaveSelect;
  _hwSPI     = false;
  _mySPI     = NULL;
  _dataOut   = spiData;
  _clock     = spiClock;
  _value     = 0;
  _type      = 16;
  _maxValue  = 65535;
  _powerMode = 0;
}


//  initializes the SPI
//  and sets internal state
void AD5660::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

  if (_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else  //  SOFTWARE SPI MODE0
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock, OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock, LOW);
  }
}


uint8_t AD5660::getType()
{
  return _type;
}


//
//  SET VALUE
//
bool AD5660::setValue(uint16_t value)
{
  //  range check not needed.
  //  if (value > _maxValue) return false;
  _value = value;
  //  prepare 12 bit transfer.
  uint32_t data = value;
  //  set powerMode bits if not 0.
  if (_powerMode) data |= (((uint32_t)_powerMode) << 16);
  updateDevice(data);
  return true;
}


uint16_t AD5660::getValue()
{
  return _value;
}


uint16_t AD5660::getMaxValue()
{
  return _maxValue;
}


bool AD5660::setPercentage(float percentage)
{
  //  range check
  if ((percentage < 0) || (percentage > 100)) return false;

  uint32_t value = round(655.35 * percentage);
  return setValue(value);
}


float AD5660::getPercentage()
{
  float value = getValue();
  if (value > 0)
  {
    return value * ( 1.0 / 655.35);
  }
  return 0;
}


//
//  POWER DOWN
//
bool AD5660::setPowerDownMode(uint8_t mode)
{
  //  range check
  if (mode > 3) return false;
  _powerMode = mode;
  return true;
}


uint8_t AD5660::getPowerDownMode()
{
  return _powerMode;
}


//
//  SPI
//
void AD5660::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};


uint32_t AD5660::getSPIspeed()
{
  return _SPIspeed;
}


bool AD5660::usesHWSPI()
{
  return _hwSPI;
}


//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//

void AD5660::updateDevice(uint32_t data)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer((data >> 16) & 0xFF);
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
void AD5660::swSPI_transfer(uint32_t value)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  //  Shifting 24 bits starting from MSB to LSB
  for (uint8_t bit = 24; bit; bit--)
  {
    digitalWrite(dao, (value >> (bit - 1)) & 0x01);
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
}


//  -- END OF FILE --

