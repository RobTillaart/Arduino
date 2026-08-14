//
//    FILE: MLX90316.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for SPI based MLX90316 rotary encoder.
//    DATE: 2026-08-04
//     URL: https://github.com/RobTillaart/MLX90316


#include "MLX90316.h"


//  HARDWARE SPI
MLX90316::MLX90316(uint8_t select, __SPI_CLASS__ * mySPI)
{
  _select   = select;
  _dataIn   = 255;
  _dataOut  = 255;
  _clock    = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
}

//  SOFTWARE SPI
MLX90316::MLX90316(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _select   = select;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}

//  initializes the pins and starts SPI in case of hardware SPI
bool MLX90316::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  //  SPI_MODE1 ==> CPHA = 1, CPOL = 0
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

uint16_t MLX90316::getRawValue()
{
  uint16_t raw = readDevice();
  _lastRead = micros();
  return raw;
}

float MLX90316::getAngle()
{
  float angle = (360.0 / 16384) * getRawValue();
  if (_offset != 0)
  {
    angle = fmod(angle + _offset, 360.0);
  }
  return angle;
}

void MLX90316::setOffset(float offset)
{
  _offset = offset;
}

float MLX90316::getOffset()
{
  return _offset;
}

uint32_t MLX90316::lastRead()  //  time in micros
{
  return _lastRead;
}

//  SPI
void MLX90316::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  //  MAX speed about 150kbps, page 33 datasheet.
  if (_SPIspeed > 150000) _SPIspeed = 150000;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
}

uint32_t MLX90316::getSPIspeed()
{
  return _SPIspeed;
}

bool MLX90316::usesHWSPI()
{
  return _hwSPI;
}


//  DEBUG
uint16_t MLX90316::getStatus()
{
  return mlx;
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint16_t MLX90316::readDevice()
{
  //  Page 33 datasheet, gives details about timing.
  raw = 0;
  mlx = 0;
  digitalWrite(_select, LOW);
  delayMicroseconds(7);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    //  trigger bytes
    raw = _mySPI->transfer(0xAA);
    delayMicroseconds(38);
    raw = _mySPI->transfer(0xFF);
    delayMicroseconds(38);

    raw = _mySPI->transfer(0xFF);
    delayMicroseconds(38);
    raw = _mySPI->transfer(0xFF);
    delayMicroseconds(38);

    mlx = _mySPI->transfer(0xFF);
    delayMicroseconds(38);
    mlx = _mySPI->transfer(0xFF);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    //  TODO verify.
    SWSPI_byte(0xAA);
    delayMicroseconds(38);
    SWSPI_byte(0xFF);
    delayMicroseconds(38);

    raw = SWSPI_byte(0xFF);
    delayMicroseconds(38);
    raw <<= 8;
    raw |= SWSPI_byte(0xFF);
    delayMicroseconds(38);
    raw <<= 8;

    mlx = SWSPI_byte(0xFF);
    delayMicroseconds(38);
    mlx <<= 8;
    mlx |= SWSPI_byte(0xFF);
    mlx <<= 8;
  }
  delayMicroseconds(7);
  digitalWrite(_select, HIGH);
  delayMicroseconds(1500);
  return raw & 0x3FFF;  //  only lowest 14 bits.
}


uint8_t MLX90316::SWSPI_byte(uint8_t data)
{
  uint8_t clk = _clock;
  uint8_t dai = _dataIn;
  uint8_t dao = _dataOut;
  uint8_t val = 0;

  for (uint8_t bit = 0x80; bit; bit >>= 1)
  {
    digitalWrite(dao, (data & bit));  //  MSB - check TODO
    digitalWrite(clk, HIGH);
    delayMicroseconds(7);
    val <<= 1;
    val += digitalRead(dai);
    digitalWrite(clk, LOW);
    delayMicroseconds(7);
  }
  return val;
}


//  -- END OF FILE --

