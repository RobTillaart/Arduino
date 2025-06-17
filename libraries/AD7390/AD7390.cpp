//
//    FILE: AD7390.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-06-14
// PURPOSE: Arduino library for AD7390/AD7391 12/10 bit SPI DAC.
//     URL: https://github.com/RobTillaart/AD7390


#include "AD7390.h"

//  SOFTWARE SPI
AD7390::AD7390(uint8_t select, uint8_t clear, uint8_t dataOut, uint8_t clock)
{
  _select     = select;
  _clear      = clear;
  _dataOut    = dataOut;
  _clock      = clock;
  _hwSPI      = false;
  _mySPI      = NULL;
  _maxValue   = 4095;
  _refVoltage = 0;
}

//  HARDWARE SPI
AD7390::AD7390(uint8_t select, uint8_t clear, __SPI_CLASS__ * mySPI)
{
  _select     = select;
  _clear      = clear;
  _dataOut    = 255;
  _clock      = 255;
  _hwSPI      = true;
  _mySPI      = mySPI;
  _maxValue   = 4095;
  _refVoltage = 0;
}

//  initializes the pins and starts SPI in case of hardware SPI
void AD7390::begin(uint16_t value)
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, LOW);
  pinMode(_clear, OUTPUT);
  digitalWrite(_clear, HIGH);

  setSPIspeed(16000000);

  if(_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }

  setValue(value);
}


/////////////////////////////////////////////////////////////////////////////
//
//  SET VALUE
//
bool AD7390::setValue(uint16_t value)
{
  if (value > _maxValue) return false;
  _value = value;
  updateDevice(value);
  return true;
}

uint16_t AD7390::getValue()
{
  return _value;
}

uint16_t AD7390::getMaxValue()
{
  return _maxValue;
}

bool AD7390::setPercentage(float percentage)
{
  if ((percentage < 0) || (percentage > 100.0)) return false;
  return setValue(round(percentage * (_maxValue / 100.0)));
}

float AD7390::getPercentage()
{
  uint16_t v = _value;
  if (v == 0) return 0.0;
  return (100.0 / _maxValue) * v;
}

void AD7390::clear()
{
  digitalWrite(_clear, LOW);
  delayMicroseconds(1);
  digitalWrite(_clear, HIGH);
  _value = 0;
}

bool AD7390::setRefVoltage(float volts)
{
  if ((volts < 0) || (volts > 5.5)) return false;
  _refVoltage = volts;
  return true;
}

float AD7390::getRefVoltage()
{
  return _refVoltage;
}

bool AD7390::setVoltage(float volts)
{
  if ((volts < 0) || (volts > _refVoltage)) return false;
  return setValue(round(volts * (_maxValue / _refVoltage)));
}

float AD7390::getVoltage()
{
  uint16_t v = _value;
  if (v == 0) return 0.0;
  return (_refVoltage / _maxValue) * v;
}


/////////////////////////////////////////////////////////////////////////////
//
//  SPI
//
void AD7390::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE3);
}

uint32_t AD7390::getSPIspeed()
{
  return _SPIspeed;
}

bool AD7390::usesHWSPI()
{
  return _hwSPI;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
void AD7390::updateDevice(uint16_t value)
{
  digitalWrite(_select, HIGH);
  if (_hwSPI)  //  hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer16(value);
    _mySPI->endTransaction();
  }
  else         //  software SPI
  {
    swSPI_transfer(value);
  }
  digitalWrite(_select, LOW);
}

void AD7390::swSPI_transfer(uint16_t value)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  for (uint16_t mask = 0x8000; mask; mask >>= 1)
  {
    digitalWrite(dao,(value & mask));
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
AD7391::AD7391(uint8_t select, uint8_t clear, __SPI_CLASS__ * mySPI)
             : AD7390(select, clear, mySPI)
{
  _maxValue = 1023;
}


AD7391::AD7391(uint8_t select, uint8_t clear, uint8_t dataOut, uint8_t clock)
             : AD7390(select, clear, dataOut, clock)
{
  _maxValue = 1023;
}


//  -- END OF FILE --

