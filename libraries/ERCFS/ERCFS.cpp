//
//    FILE: ERCFS.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for SPI based ERCFS rotary encoder.
//    DATE: 2025-02-08
//     URL: https://github.com/RobTillaart/ERCFS


#include "ERCFS.h"


//  HARDWARE SPI
ERCFS::ERCFS(uint8_t select, __SPI_CLASS__ * mySPI)
{
  _select   = select;
  _dataIn   = 255;
  _dataOut  = 255;
  _clock    = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
}

//  SOFTWARE SPI
ERCFS::ERCFS(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _select   = select;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}

//  initializes the pins and starts SPI in case of hardware SPI
bool ERCFS::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  //  SPI_MODE1 => see email Benito
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);

  if(_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else
  {
    pinMode(_dataIn, INPUT);
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }

  return true;
}

uint16_t ERCFS::getRawValue()
{
  uint16_t raw = readDevice();
  _lastRead = micros();
  return raw;
}

float ERCFS::getAngle()
{
  float angle = (360.0 / 16384) * getRawValue();
  if (_offset != 0)
  {
    angle = fmod(angle + _offset, 360.0);
  }
  return angle;
}

void ERCFS::setOffset(float offset)
{
  _offset = offset;
}

float ERCFS::getOffset()
{
  return _offset;
}

uint32_t ERCFS::lastRead()  //  time in micros
{
  return _lastRead;
}

//  SPI
void ERCFS::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  //  don't know if there is a MAX speed?
  //  if (_SPIspeed > 2000000) _SPIspeed = 2000000;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
}

uint32_t ERCFS::getSPIspeed()
{
  return _SPIspeed;
}

bool ERCFS::usesHWSPI()
{
  return _hwSPI;
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint16_t ERCFS::readDevice()
{
  uint16_t raw = 0;
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    raw = _mySPI->transfer16(0xFFFF);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    uint8_t clk = _clock;
    uint8_t dai = _dataIn;
    uint8_t dao = _dataOut;
    digitalWrite(dao, HIGH);  //  send 0xFFFF, no need to set DAO in loop.
    for (int i = 0; i < 16; i++)
    {
      digitalWrite(clk, HIGH);
      raw <<= 1;
      raw += digitalRead(dai);
      digitalWrite(clk, LOW);
    }
  }
  digitalWrite(_select, HIGH);
  return raw & 0x3FFF;  //  only lowest 14 bits.
}


//  -- END OF FILE --

