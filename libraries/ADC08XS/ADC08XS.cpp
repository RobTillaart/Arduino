//
//    FILE: ADC08XS.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2024-01-13
// PURPOSE: Arduino library for ADC082S, ADC084S, ADC102S, ADC104S, ADC122S, ADC124S,
//                              8, 10, 12 bits, 2 or 4 channel ADC (SPI).
//     URL: https://github.com/RobTillaart/ADC08XS


#include "ADC08XS.h"


//       HARDWARE SPI
ADC08XS::ADC08XS(__SPI_CLASS__ * mySPI)
{
  _dataIn     = 255;
  _dataOut    = 255;
  _clock      = 255;
  _select     = 255;
  _hwSPI      = true;
  _mySPI      = mySPI;
  _maxValue   = 255;
  _isLowPower = false;
  _maxChannel = 2;
}


//       SOFTWARE SPI
ADC08XS::ADC08XS(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _dataIn     = dataIn;
  _dataOut    = dataOut;
  _clock      = clock;
  _select     = 255;
  _hwSPI      = false;
  _mySPI      = NULL;
  _maxValue   = 255;
  _isLowPower = false;
  _maxChannel = 2;
}


void ADC08XS::begin(uint8_t select)
{
  _select = select;
  pinMode(_select, OUTPUT);
  //  pulse
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
    pinMode(_dataIn, INPUT);
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,  OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   HIGH);
  }
}


uint16_t ADC08XS::maxValue()
{
  return _maxValue;
}


uint8_t ADC08XS::maxChannel()
{
  return _maxChannel;
}


uint32_t ADC08XS::count()
{
  return _count;
}


uint16_t ADC08XS::read(uint8_t channel)
{
  return readADC(channel) >> 4;  //  remove 4 trailing zero's
}


int ADC08XS::deltaRead(uint8_t chanA, uint8_t chanB)
{
  return int(read(chanA)) - int(read(chanB));
}


void ADC08XS::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}


uint32_t ADC08XS::getSPIspeed()
{
  return _SPIspeed;
}


bool ADC08XS::usesHWSPI()
{
  return _hwSPI;
}


void ADC08XS::lowPower()
{
  _isLowPower = true;
  shutDown();
}


void ADC08XS::wakeUp()
{
  readADC(0);
  _isLowPower = false;
}


bool ADC08XS::isLowPower()
{
  return _isLowPower;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint16_t ADC08XS::readADC(uint8_t channel)
{
  if (channel >= _maxChannel) return 0;

  _count++;

  uint16_t address = channel << 11;
  uint16_t data = 0;

  digitalWrite(_select, LOW);
  if (_hwSPI)  //  hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
     data = _mySPI->transfer16(address);
    _mySPI->endTransaction();
  }
  else  //  Software SPI
  {
     data = swSPI_transfer16(address);
  }
  digitalWrite(_select, HIGH);

  return data;
}


void ADC08XS::shutDown()
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
     swSPI_transfer16(0, 0x0010);  //  4 pulses is enough
  }
  digitalWrite(_select, HIGH);
}


//  MSBFIRST
uint16_t  ADC08XS::swSPI_transfer16(uint16_t address, uint16_t m)
{
  uint8_t clk = _clock;
  uint8_t dai = _dataIn;
  uint8_t dao = _dataOut;
  uint16_t addr = address;

  uint16_t rv = 0;
  for (uint16_t mask = m; mask; mask >>= 1)
  {
    digitalWrite(dao, (addr & mask));
    digitalWrite(clk, LOW);
    digitalWrite(clk, HIGH);
    if (digitalRead(dai) == HIGH) rv |= mask;
  }
  return rv;
}


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS ADC082S
//
ADC082S::ADC082S(__SPI_CLASS__ * mySPI) : ADC08XS(mySPI)
{
  _maxValue = 255;
  _maxChannel = 2;
}

ADC082S::ADC082S(uint8_t dataIn, uint8_t dataOut, uint8_t clock) : ADC08XS(dataIn, dataOut, clock)
{
  _maxValue = 255;
  _maxChannel = 2;
}

uint16_t ADC082S::read(uint8_t channel)
{
  return readADC(channel) >> 4;  //  remove 4 trailing zero's
}


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS ADC084S
//
ADC084S::ADC084S(__SPI_CLASS__ * mySPI) : ADC08XS(mySPI)
{
  _maxValue = 255;
  _maxChannel = 4;
}

ADC084S::ADC084S(uint8_t dataIn, uint8_t dataOut, uint8_t clock) : ADC08XS(dataIn, dataOut, clock)
{
  _maxValue = 255;
  _maxChannel = 4;
}

uint16_t ADC084S::read(uint8_t channel)
{
  return readADC(channel) >> 4;  //  remove 4 trailing zero's
}


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS ADC102S
//
ADC102S::ADC102S(__SPI_CLASS__ * mySPI) : ADC08XS(mySPI)
{
  _maxValue = 1023;
  _maxChannel = 2;
}

ADC102S::ADC102S(uint8_t dataIn, uint8_t dataOut, uint8_t clock) : ADC08XS(dataIn, dataOut, clock)
{
  _maxValue = 1023;
  _maxChannel = 2;
}

uint16_t ADC102S::read(uint8_t channel)
{
  return readADC(channel) >> 2;  //  remove 2 trailing zero's
}



//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS ADC104S
//
ADC104S::ADC104S(__SPI_CLASS__ * mySPI) : ADC08XS(mySPI)
{
  _maxValue = 1023;
  _maxChannel = 4;
}

ADC104S::ADC104S(uint8_t dataIn, uint8_t dataOut, uint8_t clock) : ADC08XS(dataIn, dataOut, clock)
{
  _maxValue = 1023;
  _maxChannel = 4;
}

uint16_t ADC104S::read(uint8_t channel)
{
  return readADC(channel) >> 2;  //  remove 2 trailing zero's
}


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS ADC122S
//
ADC122S::ADC122S(__SPI_CLASS__ * mySPI) : ADC08XS(mySPI)
{
  _maxValue = 4095;
  _maxChannel = 2;
}

ADC122S::ADC122S(uint8_t dataIn, uint8_t dataOut, uint8_t clock) : ADC08XS(dataIn, dataOut, clock)
{
  _maxValue = 4095;
  _maxChannel = 2;
}

uint16_t ADC122S::read(uint8_t channel)
{
  return readADC(channel);
}


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS ADC124S
//
ADC124S::ADC124S(__SPI_CLASS__ * mySPI) : ADC08XS(mySPI)
{
  _maxValue = 4095;
  _maxChannel = 4;
}

ADC124S::ADC124S(uint8_t dataIn, uint8_t dataOut, uint8_t clock) : ADC08XS(dataIn, dataOut, clock)
{
  _maxValue = 4095;
  _maxChannel = 4;
}

uint16_t ADC124S::read(uint8_t channel)
{
  return readADC(channel);
}


//  -- END OF FILE --

