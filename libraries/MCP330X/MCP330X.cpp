//
//    FILE: MCP330X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2025-04-16
// PURPOSE: Arduino library for MCP3302 and MCP3304 13-Bit Differential ADC, SPI
//     URL: https://github.com/RobTillaart/MCP330X
//


#include "MCP330X.h"


  //       HARDWARE SPI
MCP330X::MCP330X(__SPI_CLASS__ * mySPI)
{
  _dataIn = 255;
  _dataOut= 255;
  _clock  = 255;
  _select = 255;
  _hwSPI  = true;
  _mySPI  = mySPI;
}


//       SOFTWARE SPI
MCP330X::MCP330X(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _dataIn  = dataIn;
  _dataOut = dataOut;
  _clock   = clock;
  _select  = 255;
  _hwSPI   = false;
  _mySPI   = NULL;
}


void MCP330X::begin(uint8_t select)
{
  _select = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);
  digitalWrite(_select, LOW);    //  force communication See datasheet)
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

  if (_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
  }
  else                 //  software SPI
  {
    pinMode(_dataIn,  INPUT);
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }
}


uint8_t MCP330X::channels()
{
  return _channels;
}


int16_t MCP330X::maxValue()
{
  return _maxValue;
}


uint32_t MCP330X::count()
{
  uint32_t cnt = _count;
  _count = 0;
  return cnt;
}


int16_t MCP330X::read(uint8_t channel)
{
  if (channel >= _channels) return 0;
  return readADC(channel, true);
}


int16_t MCP330X::differentialRead(uint8_t channel)
{
  if (channel >= _channels) return 0;
  return readADC(channel, false);
}


//
//  SPI
//
void MCP330X::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}


uint32_t MCP330X::getSPIspeed()
{
  return _SPIspeed;
}


bool MCP330X::usesHWSPI()
{
  return _hwSPI;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
int16_t MCP330X::readADC(uint8_t channel, bool single)
{
  if (channel >= _channels) return 0;

  _count++;

  //  datasheet figure 6.4 page 27
  uint8_t  data[3] = { 0, 0, 0 };
  data[0] = 0x08;                      //  start bit
  if (single) data[0] |= 0x04;         //  single read | differential
  data[0] |= channel >> 1;             //  channel d2 and d1;
  if (channel & 0x01) data[1] = 0x80;  //  channel d0

  //  send request and read answer
  int bytes = 3;
  digitalWrite(_select, LOW);
  if (_hwSPI)  //  hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    for (int b = 0; b < bytes; b++)
    {
      data[b] = _mySPI->transfer(data[b]);
    }
    _mySPI->endTransaction();
  }
  else  //  software SPI
  {
    for (int b = 0; b < bytes; b++)
    {
      data[b] = swSPI_transfer(data[b]);
    }
  }
  digitalWrite(_select, HIGH);

  //  construct value
  //  skip data[0]
  int16_t raw = 256 * data[1] + data[2];
  raw &= 0x1FFF;      //  clear all unknown bits.
  if (raw & 0x1000)   //  sign bit set?
  {
    // extend sign bits
    raw |= 0xF000;    //  absolute value
    return raw;
  }
  //  positive value
  return raw;
}

//  MSBFIRST
uint8_t  MCP330X::swSPI_transfer(uint8_t val)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  uint8_t dai = _dataIn;

  uint8_t rv = 0;
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao, (val & mask));
    digitalWrite(clk, HIGH);
    if (digitalRead(dai) == HIGH) rv |= mask;
    digitalWrite(clk, LOW);
  }
  return rv;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//

/////////////////////////////////////////////////////////////////////////////
//
//  MCP3302
//
MCP3302::MCP3302(__SPI_CLASS__ * mySPI)
        :MCP330X(mySPI)
{
  _channels = 4;
  _maxValue = 4095;
}

MCP3302::MCP3302(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP330X(dataIn, dataOut, clock)
{
  _channels = 4;
  _maxValue = 4095;
}




/////////////////////////////////////////////////////////////////////////////
//
//  MCP3304
//
MCP3304::MCP3304(__SPI_CLASS__ * mySPI)
        :MCP330X(mySPI)
{
  _channels = 8;
  _maxValue = 4095;
}

MCP3304::MCP3304(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP330X(dataIn, dataOut, clock)
{
  _channels = 8;
  _maxValue = 4095;
}


//  -- END OF FILE --

