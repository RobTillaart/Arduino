//
//    FILE: AMT25.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for SPI based AMT25 series rotary encoder.
//    DATE: 2025-02-08
//     URL: https://github.com/RobTillaart/AMT25
//          https://www.sameskydevices.com/
//          16384 steps rotary encoder  14 bit 360°
//


#include "AMT25.h"


//  HARDWARE SPI
AMT25::AMT25(uint8_t select, __SPI_CLASS__ * mySPI)
{
  _select   = select;
  _dataIn   = 255;
  _dataOut  = 255;
  _clock    = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
}

//  SOFTWARE SPI
AMT25::AMT25(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _select   = select;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}


//  initializes the pins and starts SPI in case of hardware SPI
bool AMT25::begin(uint8_t bits)
{
  if ((bits != 12) && (bits != 14)) return false;
  _bits = bits;
  if (bits == 12) _steps = 4096;
  else            _steps = 16384;

  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  //  SPI_MODE1 => see email Benito
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

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


uint16_t AMT25::getRawValue()
{
  uint16_t raw = readDevice(0x0000);
  _lastRead = micros();
  return raw;
}

float AMT25::getAngle()
{
  float angle = (360.0 / _steps) * getRawValue();
  if (_offset != 0)
  {
    angle = fmod(angle + _offset, 360.0);
  }
  return angle;
}

void AMT25::setOffset(float offset)
{
  _offset = offset;
}

float AMT25::getOffset()
{
  return _offset;
}

uint16_t AMT25::setZero()
{
  uint16_t raw = readDevice(0x0070);
  _lastRead = micros();
  return raw;
}

uint16_t AMT25::getTurns()
{
  uint16_t raw = readDevice(0x00A0);
  delayMicroseconds(40);
  raw = readDevice(0x0000);
  _lastRead = micros();
  return raw;
}

uint32_t AMT25::lastRead()  //  time in micros
{
  return _lastRead;
}

//  SPI
void AMT25::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  if (_SPIspeed > 2000000) _SPIspeed = 2000000;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}

uint32_t AMT25::getSPIspeed()
{
  return _SPIspeed;
}

//       Debugging
bool AMT25::usesHWSPI()
{
  return _hwSPI;
}


////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint16_t AMT25::readDevice(uint16_t command)
{
  uint16_t raw = 0;
  digitalWrite(_select, LOW);
  delayMicroseconds(3);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    raw = _mySPI->transfer(command >> 8);
    raw <<= 8;
    delayMicroseconds(3);
    raw |= _mySPI->transfer(command & 0xFF);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    uint8_t clk = _clock;
    uint8_t dai = _dataIn;
    uint8_t dao = _dataOut;
    uint8_t byt = command >> 8;
    for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
    {
      digitalWrite(dao, (byt & mask) > 0);
      digitalWrite(clk, HIGH);
      raw <<= 1;
      raw += digitalRead(dai);
      digitalWrite(clk, LOW);
    }
    byt = command & 0xFF;
    delayMicroseconds(3);
    for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
    {
      digitalWrite(dao, (byt & mask) > 0);
      digitalWrite(clk, HIGH);
      raw <<= 1;
      raw += digitalRead(dai);
      digitalWrite(clk, LOW);
    }
  }
  digitalWrite(_select, HIGH);
  //  TODO check parity here

  raw &= 0x3FFF;
  if (_bits == 12) raw >>= 2;
  return raw;
}

bool AMT25::checkParity(uint16_t raw)
{
  uint16_t data = raw;  //  local variable is fast.
  uint16_t sum = 0x3;
  for (int i = 0; i < 7; i++)
  {
    sum ^= (data & 0x3);
    data >>= 2;
  }
  //  TODO set error flag
  //  data = shifted 7 times => MSB 2 bits remain.
  return sum == data;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//

/////////////////////////////////////////////////////////////////////////////
//
//  AMT22
//
AMT22::AMT22(uint8_t select, __SPI_CLASS__ * mySPI)
      :AMT25(select, mySPI)
{
  //  no diffs known (yet).
}

AMT22::AMT22(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
      :AMT25(select, dataIn, dataOut, clock)
{
  //  no diffs known (yet).
}


/////////////////////////////////////////////////////////////////////////////
//
//  AMT23
//
AMT23::AMT23(uint8_t select, __SPI_CLASS__ * mySPI)
      :AMT25(select, mySPI)
{
  //  no diffs known (yet).
}

AMT23::AMT23(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
      :AMT25(select, dataIn, dataOut, clock)
{
  //  no diffs known (yet).
}



//  -- END OF FILE --

