//
//    FILE: AD7367_SPI.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-02-10
// PURPOSE: Arduino library for the AD7367, 2 channel consecutive sampling 14 bit ADC.
//     URL: https://github.com/RobTillaart/AD7367_SPI


#include "AD7367_SPI.h"


AD7367_SPI::AD7367_SPI(uint8_t select, uint8_t convert, uint8_t busy, __SPI_CLASS__ * mySPI)
{
  _type    = 67;
  _bits    = 14;
  _select  = select;
  _convert = convert;
  _busy    = busy;
  _mySPI   = mySPI;
}

//  sets internal state
void AD7367_SPI::begin()
{
  pinMode(_select, OUTPUT);
  pinMode(_convert, OUTPUT);
  pinMode(_busy, INPUT);

  digitalWrite(_select, HIGH);
  digitalWrite(_convert, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}


uint8_t AD7367_SPI::getType()
{
  return _type;
}

int AD7367_SPI::getBits()
{
  return _bits;
}


//////////////////////////////////////////////////////////////////
//
//  READ
//
int AD7367_SPI::read()
{
  //  simulation
  //  _value[0] = random(16384);  //  14 bits = 16383,  12 bits = 4095
  //  _value[1] = random(16384);

  //  datasheet page 07 + 20
  //  trigger conversion
  triggerConversion();
  //  wait for conversion to be done
  while (conversionBusy());
  return readAsync();
}

void AD7367_SPI::triggerConversion()
{
  //  Trigger conversion by 10 ns pulse.
  //  might need a delayMicroseconds(1); on very fast processors.
  //  needs a configuration flag, although checking the flag is already 10 ns.
  //  Are NOP's portable?
  digitalWrite(_convert, LOW);
  //  delayMicroseconds(1);
  digitalWrite(_convert, HIGH);
}

bool AD7367_SPI::conversionBusy()
{
  return digitalRead(_busy) == HIGH;
}

bool AD7367_SPI::conversionReady()
{
  return digitalRead(_busy) == LOW;
}

int AD7367_SPI::readAsync()
{
  uint32_t data = 0;

  digitalWrite(_select, LOW);
  _mySPI->beginTransaction(_spi_settings);
  data = _mySPI->transfer16(0xFFFF);
  data <<= 16;
  data = _mySPI->transfer16(0xFFFF);
  _mySPI->endTransaction();
  digitalWrite(_select, HIGH);

  // split of 2x 14 bits.
  _value[0] = data & 0x03FFF;
  data >>= 14;
  _value[1] = data & 0x03FFF;;
  return 0;
}

int AD7367_SPI::getLastADCA()
{
  return _value[0];
}

int AD7367_SPI::getLastADCB()
{
  return _value[1];
}


//////////////////////////////////////////////////////////////////
//
//  FASTREAD
//
int AD7367_SPI::fastRead(int &a, int &b)
{
  //  Trigger conversion by 10 ns pulse. (see above)
  digitalWrite(_convert, LOW);
  //  delayMicroseconds(1);
  digitalWrite(_convert, HIGH);
  //  wait for ready (blocking)
  while(digitalRead(_busy) == HIGH);
  //  fetch data
  digitalWrite(_select, LOW);
  _mySPI->beginTransaction(_spi_settings);
  uint32_t data = _mySPI->transfer16(0xFFFF);
  data <<= 16;
  data = _mySPI->transfer16(0xFFFF);
  _mySPI->endTransaction();
  digitalWrite(_select, HIGH);

  // split of 2x 14 bits.
  a = _value[0] = data & 0x03FFF;
  data >>= 14;
  b = _value[1] = data & 0x03FFF;
  return 0;
}


//////////////////////////////////////////////////////////////////
//
//  ADDR + REFSEL
//
void AD7367_SPI::setADDRpin(uint8_t pin)
{
  _addr = pin;
  pinMode(_addr, OUTPUT);
  digitalWrite(_addr, LOW);
}

void AD7367_SPI::setREFSELpin(uint8_t pin)
{
  _refsel = pin;
  pinMode(_refsel, OUTPUT);
  digitalWrite(_refsel, HIGH);
}


//////////////////////////////////////////////////////////////////
//
//  RANGE
//
void AD7367_SPI::setRangePin(uint8_t range0, uint8_t range1)
{
  _range0 = range0;
  _range1 = range1;
  pinMode(_range0, OUTPUT);
  pinMode(_range1, OUTPUT);
  digitalWrite(_range0, LOW);
  digitalWrite(_range1, LOW);
}

int AD7367_SPI::setRange(uint8_t range)
{
  if (range > 2) return -1;
  if (conversionBusy()) return -2;
  digitalWrite(_range0, range & 0x01);
  digitalWrite(_range1, (range >> 1) & 0x01);
  return 0;
}

uint8_t AD7367_SPI::getRange()
{
  if ((_range0 == 255) || (_range1 == 255)) return 255;
  uint8_t range = digitalRead(_range0) == LOW ? 0 : 1;
  range += digitalRead(_range1) == LOW ? 0 : 2;
  return range;
}


//////////////////////////////////////////////////////////////////
//
//  SPI
//
void AD7367_SPI::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}

uint32_t AD7367_SPI::getSPIspeed()
{
  return _SPIspeed;
}


//////////////////////////////////////////////////////////////////
//
//  OBSOLETE
//
int AD7367_SPI::getValue(uint8_t channel)
{
  return _value[channel];
}



//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//



/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS AD7366
//
AD7366_SPI::AD7366_SPI(uint8_t select, uint8_t convert, uint8_t busy, __SPI_CLASS__ * mySPI)
           :AD7367_SPI(select, convert, busy, mySPI)
{
  _type = 66;
  _bits = 12;
}


//  -- END OF FILE --

