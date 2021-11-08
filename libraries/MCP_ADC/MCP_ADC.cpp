//
//    FILE: MCP_ADC.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.7
//    DATE: 2019-10-24
// PURPOSE: Arduino library for MCP3002, MCP3004, MCP3008, MCP3202, MCP3204, MCP3208
//     URL: https://github.com/RobTillaart/MCP_ADC
//


#include "MCP_ADC.h"


MCP_ADC::MCP_ADC(uint8_t dataIn, uint8_t dataOut,  uint8_t clock)
{
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _select   = 0;
  _hwSPI    = (dataIn == 255) || (dataOut == 255) || (clock == 255);
}


void MCP_ADC::begin(uint8_t select)
{
  _select = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

  if (_hwSPI)
  {
    #if defined(ESP32)
    if (_useHSPI)      // HSPI
    {
      mySPI = new SPIClass(HSPI);
      mySPI->end();
      mySPI->begin(14, 12, 13, select);   // CLK=14 MISO=12 MOSI=13
    }
    else               // VSPI
    {
      mySPI = new SPIClass(VSPI);
      mySPI->end();
      mySPI->begin(18, 19, 23, select);   // CLK=18 MISO=19 MOSI=23
    }
    #else              // generic hardware SPI
    mySPI = &SPI;
    mySPI->end();
    mySPI->begin();
    #endif
  }
  else                 // software SPI
  {
    pinMode(_dataIn,  INPUT);
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }
}


#if defined(ESP32)
void MCP_ADC::setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)
{
  _clock   = clk;
  _dataIn  = miso;
  _dataOut = mosi;
  _select  = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  mySPI->end();  // disable SPI
  mySPI->begin(clk, miso, mosi, select);
}
#endif


uint32_t MCP_ADC::count()
{
  uint32_t cnt = _count;
  _count = 0;
  return cnt;
}


int16_t MCP_ADC::analogRead(uint8_t channel)
{
  if (channel >= _channels) return 0;
  return readADC(channel, true);
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
  // int16_t val1 = differentialRead(channel | 0x01);
  // no need to read if val0 has a positive value
  int16_t val1 = (val0 > 0) ? 0 : differentialRead(channel | 0x01);

  if (channel & 0x01) return val1 - val0;
  return val0 - val1;
}


void MCP_ADC::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};


int16_t MCP_ADC::readADC(uint8_t channel, bool single)
{
  if (channel >= _channels) return 0;

  _count++;

  uint8_t  data[3] = { 0,0,0 };
  uint8_t  bytes = buildRequest(channel, single, data);

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    for (uint8_t b = 0; b < bytes; b++)
    {
      data[b] = mySPI->transfer(data[b]);
    }
    mySPI->endTransaction();
  }
  else // Software SPI
  {
    for (uint8_t b = 0; b < bytes; b++)
    {
      data[b] = swSPI_transfer(data[b]);
    }
  }
  digitalWrite(_select, HIGH);

  if (bytes == 2) return ((256 * data[0] + data[1]) & _maxValue);
  // data[0]?
  return ((256 * data[1] + data[2]) & _maxValue);
}


// MSBFIRST
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
// MCP3002
//
MCP3002::MCP3002(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 2;
  _maxValue = 1023;
}

uint8_t MCP3002::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
    // P17  fig 6.1   MCP3002
  data[0] = 0x44;                          // start bit + MSB first bit
  if (single) data[0] |= 0x20;             // single read | differential
  if (channel) data[0] |= (channel << 4);  // channel = 0 or 1;
  return 2;
}


/////////////////////////////////////////////////////////////////////////////
//
// MCP3004
//
MCP3004::MCP3004(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 4;
  _maxValue = 1023;
}

uint8_t MCP3004::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  // P21  fig 6.1   MCP3004/3008
  data[0] = 0x01;                          // start bit
  if (single) data[1] = 0x80;              // single read | differential
  if (channel) data[1] |= (channel << 4);  // channel
  return 3;
}


/////////////////////////////////////////////////////////////////////////////
//
// MCP3008
//
MCP3008::MCP3008(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 8;
  _maxValue = 1023;
}

uint8_t MCP3008::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  // P21  fig 6.1   MCP3004/3008
  data[0] = 0x01;                          // start bit
  if (single) data[1] = 0x80;              // single read | differential
  if (channel) data[1] |= (channel << 4);  // channel
  return 3;
}


/////////////////////////////////////////////////////////////////////////////
//
// MCP3202
//
MCP3202::MCP3202(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 2;
  _maxValue = 4095;
}

uint8_t MCP3202::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  // P17  fig 6.2   MCP3202
  data[0] = 0x01;                          // start bit
  data[1] = 0x20;                          // MSB first bit
  if (single) data[1] |= 0x80;             // single read | differential
  if (channel) data[1] |= (channel << 6);  // channel = 0 or 1;
  return 3;
}


/////////////////////////////////////////////////////////////////////////////
//
// MCP3204
//
MCP3204::MCP3204(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 4;
  _maxValue = 4095;
}

uint8_t MCP3204::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  // P21  fig 6.1   MCP3204/3208
  data[0] = 0x04;                          // start bit
  if (single) data[0] |= 0x02;             // single read | differential
  if (channel > 3) data[0] |= 0x01;        // msb channel (D2)
  if (channel) data[1] |= (channel << 6);  // other 2 bits (D1 D0)
  return 3;
}


/////////////////////////////////////////////////////////////////////////////
//
// MCP3208
//
MCP3208::MCP3208(uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP_ADC(dataIn, dataOut, clock)
{
  _channels = 8;
  _maxValue = 4095;
}

uint8_t MCP3208::buildRequest(uint8_t channel, bool single, uint8_t * data)
{
  // P21  fig 6.1   MCP3204/3208
  data[0] = 0x04;                          // start bit
  if (single) data[0] |= 0x02;             // single read | differential
  if (channel > 3) data[0] |= 0x01;        // msb channel (D2)
  if (channel) data[1] |= (channel << 6);  // other 2 bits (D1 D0)
  return 3;
}


// -- END OF FILE --
