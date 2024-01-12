//
//    FILE: ADC081S.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-01-10
// PURPOSE: Arduino library for ADC081S 8 bit ADC (SPI)
//     URL: https://github.com/RobTillaart/ADC081S


#include "ADC081S.h"





//       HARDWARE SPI
ADC081S::ADC081S(__SPI_CLASS__ * mySPI)
{
  _dataIn   = 255;
  _clock    = 255;
  _select   = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
  _maxValue = 255;
}


//       SOFTWARE SPI
ADC081S::ADC081S(uint8_t dataIn, uint8_t clock)
{
  _dataIn   = dataIn;
  _clock    = clock;
  _select   = 255;
  _hwSPI    = false;
  _mySPI    = NULL;
  _maxValue = 255;
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
    _mySPI->end();
    _mySPI->begin();
  }
  else                 //  software SPI
  {
    pinMode(_dataIn, INPUT);
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
  return readADC();
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


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint16_t ADC081S::readADC()
{
  _count++;

  uint16_t data = 0;

  digitalWrite(_select, LOW);
  if (_hwSPI)
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

  return data >> 4;  //  remove 4 trailing zero's
}



//  MSBFIRST
uint16_t  ADC081S::swSPI_transfer16()
{
  uint8_t clk = _clock;
  uint8_t dai = _dataIn;

  uint16_t rv = 0;
  for (uint16_t mask = 0x8000; mask; mask >>= 1)
  {
    digitalWrite(clk, LOW);
    digitalWrite(clk, HIGH);
    if (digitalRead(dai) == HIGH) rv |= mask;
  }
  return rv;
}


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//

//  TODO


//  -- END OF FILE --

