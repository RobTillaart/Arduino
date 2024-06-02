//
//    FILE: ADC081S.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2024-01-10
// PURPOSE: Arduino library for ADC081S 8 bit ADC (SPI)
//     URL: https://github.com/RobTillaart/ADC081S


#include "ADC081S.h"


//       HARDWARE SPI
ADC081S::ADC081S(__SPI_CLASS__ * mySPI)
{
  _data       = 255;
  _clock      = 255;
  _select     = 255;
  _hwSPI      = true;
  _mySPI      = mySPI;
  _maxValue   = 255;
  _isLowPower = false;
}


//       SOFTWARE SPI
ADC081S::ADC081S(uint8_t dataIn, uint8_t clock)
{
  _data       = dataIn;
  _clock      = clock;
  _select     = 255;
  _hwSPI      = false;
  _mySPI      = NULL;
  _maxValue   = 255;
  _isLowPower = false;
}


void ADC081S::begin(uint8_t select)
{
  _select = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);
  digitalWrite(_select, LOW);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

  if (_hwSPI)          //  hardware SPI
  {
    //  _mySPI->end();
    //  _mySPI->begin();
  }
  else                 //  software SPI
  {
    pinMode(_data, INPUT);
    pinMode(_clock,  OUTPUT);
    digitalWrite(_clock, HIGH);
  }
}


uint16_t ADC081S::maxValue()
{
  return _maxValue;
}


uint32_t ADC081S::count()
{
  return _count;
}


uint16_t ADC081S::read()
{
  return readADC() >> 4;  //  remove 4 trailing zero's
}


void ADC081S::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}


uint32_t ADC081S::getSPIspeed()
{
  return _SPIspeed;
}


bool ADC081S::usesHWSPI()
{
  return _hwSPI;
}


void ADC081S::lowPower()
{
  _isLowPower = true;
  shutDown();
}


void ADC081S::wakeUp()
{
  readADC();
  _isLowPower = false;
}


bool ADC081S::isLowPower()
{
  return _isLowPower;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint16_t ADC081S::readADC()
{
  _count++;

  uint16_t data = 0;

  digitalWrite(_select, LOW);
  if (_hwSPI)  //  hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
     data = _mySPI->transfer16(0);
    _mySPI->endTransaction();
  }
  else  //  Software SPI
  {
     data = swSPI_transfer16();
  }
  digitalWrite(_select, HIGH);

  return data;
}


void ADC081S::shutDown()
{
  digitalWrite(_select, LOW);
  if (_hwSPI)  //  hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(0);        //  8 pulses
    _mySPI->endTransaction();
  }
  else  //  Software SPI
  {
     swSPI_transfer16(0x0010);  //  4 pulses is enough
  }
  digitalWrite(_select, HIGH);
}


//  MSBFIRST
uint16_t  ADC081S::swSPI_transfer16(uint16_t m)
{
  uint8_t clk = _clock;
  uint8_t dai = _data;

  uint16_t rv = 0;
  for (uint16_t mask = m; mask; mask >>= 1)
  {
    digitalWrite(clk, LOW);
    digitalWrite(clk, HIGH);
    if (digitalRead(dai) == HIGH) rv |= mask;
  }
  return rv;
}


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS ADC101S
//
ADC101S::ADC101S(__SPI_CLASS__ * mySPI) : ADC081S(mySPI)
{
  _maxValue = 1023;
}

ADC101S::ADC101S(uint8_t data, uint8_t clock) : ADC081S(data, clock)
{
  _maxValue = 1023;
}

uint16_t ADC101S::read()
{
  return readADC() >> 2;  //  remove 2 trailing zero's
}


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS ADC121S
//
ADC121S::ADC121S(__SPI_CLASS__ * mySPI) : ADC081S(mySPI)
{
  _maxValue = 4095;
}

ADC121S::ADC121S(uint8_t data, uint8_t clock) : ADC081S(data, clock)
{
  _maxValue = 4095;
}

uint16_t ADC121S::read()
{
  return readADC();
}


//  -- END OF FILE --

