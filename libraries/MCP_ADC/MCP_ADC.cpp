//
//    FILE: MCP_ADC.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.1
//    DATE: 2019-10-24
// PURPOSE: Arduino library for MCP3001, MCP3002, MCP3004, MCP3008, MCP3201, MCP3202, MCP3204, MCP3208
//     URL: https://github.com/RobTillaart/MCP_ADC


#include "MCP_ADC.h"


  //       HARDWARE SPI
MCP_ADC::MCP_ADC(__SPI_CLASS__ * mySPI)
{
  _dataIn = 255;
  _dataOut= 255;
  _clock  = 255;
  _select = 255;
  _hwSPI  = true;
  _mySPI  = mySPI;
}


//       SOFTWARE SPI
MCP_ADC::MCP_ADC(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _dataIn  = dataIn;
  _dataOut = dataOut;
  _clock   = clock;
  _select  = 255;
  _hwSPI   = false;
  _mySPI   = NULL;
}


void MCP_ADC::begin(uint8_t select)
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


uint8_t MCP_ADC::channels()
{
  return _channels;
}


int16_t MCP_ADC::maxValue()
{
  return _maxValue;
}


uint32_t MCP_ADC::count()
{
  uint32_t cnt = _count;
  _count = 0;
  return cnt;
}


int16_t MCP_ADC::read(uint8_t channel)
{
  if (channel >= _channels) return 0;
  return readADC(channel, true);
}


void MCP_ADC::readMultiple(uint8_t channels[], uint8_t numChannels, int16_t readings[])
{
  readADCMultiple(channels, numChannels, readings);
}


int16_t MCP_ADC::differentialRead(uint8_t channel)
{
  if (channel >= _channels) return 0;
  return readADC(channel, false);
}


int16_t MCP_ADC::deltaRead(uint8_t channel)
{
  if (channel >= _channels) return 0;

  int16_t val0 = differentialRead(channel & 0xFE);
  //  int16_t val1 = differentialRead(channel | 0x01);
  //  no need to read if val0 has a positive value
  int16_t val1 = (val0 > 0) ? 0 : differentialRead(channel | 0x01);

  if (channel & 0x01) return val1 - val0;
  return val0 - val1;
}


void MCP_ADC::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}


uint32_t MCP_ADC::getSPIspeed()
{
  return _SPIspeed;
}


bool MCP_ADC::usesHWSPI()
{
  return _hwSPI;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
int16_t MCP_ADC::readADC(uint8_t channel, bool single)
{
  if (channel >= _channels) return 0;

  _count++;

  uint8_t  data[3] = { 0,0,0 };
  uint8_t  bytes = buildRequest(channel, single, data);

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    for (uint8_t b = 0; b < bytes; b++)
    {
      data[b] = _mySPI->transfer(data[b]);
    }
    _mySPI->endTransaction();
  }
  else  //  Software SPI
  {
    for (uint8_t b = 0; b < bytes; b++)
    {
      data[b] = swSPI_transfer(data[b]);
    }
  }
  digitalWrite(_select, HIGH);

  if (bytes == 2)
  {
    //  combine bytes
    int16_t raw = 256 * data[0] + data[1];
    //  patch bit pattern MCP3001
    if ((_channels == 1) && (_maxValue == 1023)) raw >>= 3;
    //  patch bit pattern MCP3201
    if ((_channels == 1) && (_maxValue == 4095)) raw >>= 1;
    return raw & _maxValue;
  }
  // data[0]?
  return ((256 * data[1] + data[2]) & _maxValue);
}


void MCP_ADC::readADCMultiple(uint8_t channels[], uint8_t numChannels, int16_t readings[])
{
  _count += numChannels;

  if (_hwSPI) {
    _mySPI->beginTransaction(_spi_settings);
  }

  for (uint8_t i = 0; i < numChannels; i++) {

    digitalWrite(_select, LOW);

    uint8_t data[3] = {0, 0, 0};
    uint8_t bytes = buildRequest(channels[i], true, data);

    if (_hwSPI) {
      for (uint8_t b = 0; b < bytes; b++) {
        data[b] = _mySPI->transfer(data[b]);
      }
    } else {
      for (uint8_t b = 0; b < bytes; b++) {
        data[b] = swSPI_transfer(data[b]);
      }
    }

    if (bytes == 2) {
      //  combine bytes
      int16_t raw = 256 * data[0] + data[1];
      //  patch bit pattern MCP3001
      if ((_channels == 1) && (_maxValue == 1023)) raw >>= 3;
      //  patch bit pattern MCP3201
      if ((_channels == 1) && (_maxValue == 4095)) raw >>= 1;
      readings[i] = raw & _maxValue;
    } else {
      readings[i] = ((256 * data[1] + data[2]) & _maxValue);
    }

    digitalWrite(_select, HIGH);
  }

  if (_hwSPI) {
    _mySPI->endTransaction();
  }
}


//  MSBFIRST
uint8_t  MCP_ADC::swSPI_transfer(uint8_t val)
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
//  MCP3001
//
MCP3001::MCP3001(__SPI_CLASS__ * mySPI)
        :MCP_ADC(mySPI)
{
  _channels = 1;
  _maxValue = 1023;
}

MCP3001::MCP3001(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 1;
  _maxValue = 1023;
}

uint8_t MCP3001::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  //  P16  fig 6.1   MCP3001
  //  no specific data needed
  //  keep build CI compiler (ESP32) happy next statement
  data[0] = data[1] = 0;
  if ((channel == 0) || (single == false)) return 2;
  return 2;
}


/////////////////////////////////////////////////////////////////////////////
//
//  MCP3002
//
MCP3002::MCP3002(__SPI_CLASS__ * mySPI)
        :MCP_ADC(mySPI)
{
  _channels = 2;
  _maxValue = 1023;
}

MCP3002::MCP3002(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 2;
  _maxValue = 1023;
}

uint8_t MCP3002::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  //  P17  fig 6.1   MCP3002
  data[0] = 0x44;                          //  start bit + MSB first bit
  if (single) data[0] |= 0x20;             //  single read | differential
  if (channel) data[0] |= (channel << 4);  //  channel = 0 or 1;
  return 2;
}


/////////////////////////////////////////////////////////////////////////////
//
//  MCP3004
//
MCP3004::MCP3004(__SPI_CLASS__ * mySPI)
        :MCP_ADC(mySPI)
{
  _channels = 4;
  _maxValue = 1023;
}

MCP3004::MCP3004(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 4;
  _maxValue = 1023;
}

uint8_t MCP3004::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  //  P21  fig 6.1   MCP3004/3008
  data[0] = 0x01;                          //  start bit
  if (single) data[1] = 0x80;              //  single read | differential
  if (channel) data[1] |= (channel << 4);  //  channel
  return 3;
}


/////////////////////////////////////////////////////////////////////////////
//
//  MCP3008
//
MCP3008::MCP3008(__SPI_CLASS__ * mySPI)
        :MCP_ADC(mySPI)
{
  _channels = 8;
  _maxValue = 1023;
}

MCP3008::MCP3008(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 8;
  _maxValue = 1023;
}

uint8_t MCP3008::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  //  P21  fig 6.1   MCP3004/3008
  data[0] = 0x01;                          //  start bit
  if (single) data[1] = 0x80;              //  single read | differential
  if (channel) data[1] |= (channel << 4);  //  channel
  return 3;
}


/////////////////////////////////////////////////////////////////////////////
//
//  MCP3201
//
MCP3201::MCP3201(__SPI_CLASS__ * mySPI)
        :MCP_ADC(mySPI)
{
  _channels = 1;
  _maxValue = 4095;
}

MCP3201::MCP3201(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 1;
  _maxValue = 4095;
}

uint8_t MCP3201::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  //  P21  fig 6.1   MCP3201
  //  no specific data needed
  //  keep build CI compiler (ESP32) happy next statements
  data[0] = data[1] = 0;
  if ((channel == 0) || (single == false)) return 2;
  return 2;
}


/////////////////////////////////////////////////////////////////////////////
//
//  MCP3202
//
MCP3202::MCP3202(__SPI_CLASS__ * mySPI)
        :MCP_ADC(mySPI)
{
  _channels = 2;
  _maxValue = 4095;
}

MCP3202::MCP3202(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 2;
  _maxValue = 4095;
}

uint8_t MCP3202::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  //  P17  fig 6.2   MCP3202
  data[0] = 0x01;                          //  start bit
  data[1] = 0x20;                          //  MSB first bit
  if (single) data[1] |= 0x80;             //  single read | differential
  if (channel) data[1] |= (channel << 6);  //  channel = 0 or 1;
  return 3;
}


/////////////////////////////////////////////////////////////////////////////
//
//  MCP3204
//
MCP3204::MCP3204(__SPI_CLASS__ * mySPI)
        :MCP_ADC(mySPI)
{
  _channels = 4;
  _maxValue = 4095;
}

MCP3204::MCP3204(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 4;
  _maxValue = 4095;
}

uint8_t MCP3204::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  //  P21  fig 6.1   MCP3204/3208
  data[0] = 0x04;                          //  start bit
  if (single) data[0] |= 0x02;             //  single read | differential
  if (channel > 3) data[0] |= 0x01;        //  MSB channel (D2)
  if (channel) data[1] |= (channel << 6);  //  other 2 bits (D1 D0)
  return 3;
}


/////////////////////////////////////////////////////////////////////////////
//
//  MCP3208
//
MCP3208::MCP3208(__SPI_CLASS__ * mySPI)
        :MCP_ADC(mySPI)
{
  _channels = 8;
  _maxValue = 4095;
}

MCP3208::MCP3208(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 8;
  _maxValue = 4095;
}

uint8_t MCP3208::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  //  P21  fig 6.1   MCP3204/3208
  data[0] = 0x04;                          //  start bit
  if (single) data[0] |= 0x02;             //  single read | differential
  if (channel > 3) data[0] |= 0x01;        //  MSB channel (D2)
  if (channel) data[1] |= (channel << 6);  //  other 2 bits (D1 D0)
  return 3;
}


//  -- END OF FILE --

