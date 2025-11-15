//
//    FILE: ADC08XS.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
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
  _lastChannel = 255;
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
  _lastChannel = 255;
}


void ADC08XS::begin(uint8_t select)
{
  _select = select;
  pinMode(_select, OUTPUT);
  //  pulse
  digitalWrite(_select, HIGH);
  digitalWrite(_select, LOW);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE3);

  if (_hwSPI)          //  hardware SPI
  {
    //  _mySPI->end();
    //  _mySPI->begin();
  }
  else                 //  software SPI
  {
    pinMode(_dataIn, INPUT_PULLUP);
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


uint8_t ADC08XS::lastChannel()
{
  return _lastChannel;
}


uint32_t ADC08XS::count()
{
  return _count;
}


uint16_t ADC08XS::read(uint8_t channel)
{
  return readADC(channel) >> 4;  //  remove 4 trailing zero's
}


int ADC08XS::deltaRead(uint8_t channelA, uint8_t channelB)
{
  return int(read(channelA)) - int(read(channelB));
}


void ADC08XS::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE3);
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

  uint16_t address = 0x0000;
  if (channel == 1) address = 0x0800;
  if (channel == 2) address = 0x1000;
  if (channel == 3) address = 0x1800;

  uint16_t data = 0;

  //  handle channel swap.
  //  by doing an extra call
  if (channel != _lastChannel)
  {
    _lastChannel = channel;

    if (_hwSPI)  //  hardware SPI
    {
      _mySPI->beginTransaction(_spi_settings);
      //  after beginTransaction to prevent false clock edges.
      digitalWrite(_select, LOW);
      data = _mySPI->transfer16(address);
      digitalWrite(_select, HIGH);
      _mySPI->endTransaction();
    }
    else  //  Software SPI
    {
      digitalWrite(_select, LOW);
      data = swSPI_transfer16(address);
      digitalWrite(_select, HIGH);
    }
  }

  //  call to retrieve actual data
  if (_hwSPI)  //  hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    digitalWrite(_select, LOW);
    data = _mySPI->transfer16(address);
    digitalWrite(_select, HIGH);
    _mySPI->endTransaction();
  }
  else  //  Software SPI
  {
    digitalWrite(_select, LOW);
    data = swSPI_transfer16(address);
    digitalWrite(_select, HIGH);
  }
  return data;
}


void ADC08XS::shutDown()
{

  if (_hwSPI)  //  hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    digitalWrite(_select, LOW);
    _mySPI->transfer(0);        //  8 pulses
    digitalWrite(_select, HIGH);
    _mySPI->endTransaction();
  }
  else  //  Software SPI
  {
    digitalWrite(_select, LOW);
    swSPI_transfer16(0, 0x0010);  //  4 pulses is enough
    digitalWrite(_select, HIGH);
  }

}


//  MSBFIRST, SPI MODE 3
uint16_t  ADC08XS::swSPI_transfer16(uint16_t address, uint16_t m)
{
  uint8_t clk = _clock;
  uint8_t dai = _dataIn;
  uint8_t dao = _dataOut;
  uint16_t addr = address;

  uint16_t rv = 0;
  //  Page 2 datasheet ADC122s101
  for (uint16_t mask = m; mask; mask >>= 1)
  {
    digitalWrite(clk, LOW);
    digitalWrite(dao, ((addr >> 8) & mask) > 0);
    digitalWrite(clk, HIGH);
    if (digitalRead(dai) == HIGH) rv |= mask;
  }
  return rv;
}


//  MSBFIRST
// uint16_t  ADC08XS::swSPI_transfer16(uint16_t address, uint16_t m)
// {
  // uint8_t clk = _clock;
  // uint8_t dai = _dataIn;
  // uint8_t dao = _dataOut;
  // uint16_t addr = address;

  // uint16_t rv = 0;
  // //  Page 2 datasheet ADC122s101
  // for (uint16_t mask = m; mask; mask >>= 1)
  // {
    // digitalWrite(clk, LOW);
    // digitalWrite(clk, HIGH);
    // digitalWrite(dao, (addr & mask) > 0);
    // if (digitalRead(dai) == HIGH) rv |= mask;
  // }
  // return rv;
// }


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

