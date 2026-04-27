//
//    FILE: AD5684.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-04-20
// PURPOSE: Arduino library for AD5684/5/6 4 channel SPI-DAC (12/14/16 bit).


#include "AD5684.h"


constexpr uint8_t AD5684_AB_CHANNEL        = 0x03;
constexpr uint8_t AD5684_ALL_CHANNEL       = 0x0F;


//  HARDWARE SPI
AD5684::AD5684(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
{
  _select    = slaveSelect;
  _hwSPI     = true;
  _mySPI     = mySPI;
}

//  SOFTWARE SPI
AD5684::AD5684(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
{
  _select    = slaveSelect;
  _hwSPI     = false;
  _mySPI     = NULL;
  _dataOut   = spiData;
  _clock     = spiClock;
}


//  initializes the SPI
//  and sets internal state
void AD5684::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);

  if (_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else  //  SOFTWARE SPI
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock, OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock, LOW);
  }
}

uint8_t AD5684::getType()
{
  return _type;
}


//
//  LDAC
//
void AD5684::setLDACPin(uint8_t ldac)
{
  _ldac = ldac;
  pinMode(_ldac, OUTPUT);
  digitalWrite(_ldac, HIGH);
}

bool AD5684::triggerLDAC()
{
  if (_ldac == 255) return false;
  digitalWrite(_ldac, LOW);
  digitalWrite(_ldac, HIGH);
  return true;
}


//
//  SET VALUE
//
bool AD5684::setValue(uint8_t channel, uint16_t value)
{
  //  range check
  if (value > _maxValue) return false;
  //  keep last value
  _value[channel] = value;
  //  prepare transfer.
  updateDevice(AD5684_REG_WRITE_UPDATE, channel, value);
  return true;
}

bool AD5684::setAll(uint16_t value)
{
  //  range check
  if (value > _maxValue) return false;
  //  keep last value
  for (int i = 0; i < 4; i++) _value[i] = value;
  //  prepare transfer.
  updateDevice(AD5684_REG_WRITE_UPDATE, AD5684_ALL_CHANNEL, value);
  return true;
}

//  returns 0.._maxValue
uint16_t AD5684::getValue(uint8_t channel)
{
  return _value[channel];
}

uint16_t AD5684::getMaxValue()
{
  return _maxValue;
}

bool AD5684::setPercentage(uint8_t channel, float percentage)
{
  //  range check
  if ((percentage < 0) || (percentage > 100)) return false;

  uint16_t value = round( (0.01 * _maxValue) * percentage);
  return setValue(channel, value);
}

float AD5684::getPercentage(uint8_t channel)
{
  float value = getValue(channel);
  if (value > 0)
  {
    return value * ( 100.0 / _maxValue);
  }
  return 0;
}



bool AD5684::prepareValue(uint8_t channel, uint16_t value)
{
  if (value > _maxValue)  return false;
  _value[channel] = value;
  updateDevice(AD5684_REG_WRITE, channel, value);
  return true;
}

bool AD5684::updateAll()
{
  updateDevice(AD5684_REG_UPDATE, AD5684_ALL_CHANNEL, 0);
  return true;
}


/////////////////////////////////////////////////////////
//
//  COMMANDS
//
void AD5684::sendCommand(uint8_t command, uint8_t channel, uint16_t data)
{
  updateDevice(command, channel, data);
}


bool AD5684::softwareReset()
{
  updateDevice(AD5684_REG_SW_RESET, 0, 0);
  return true;
}

bool AD5684::setPowerDownMode(uint8_t mode)
{
  if (mode > 3) return false;
  uint16_t data = mode | (mode << 2) | (mode << 4) | (mode << 6);
  updateDevice(AD5684_REG_POWER_UPDOWN, 0x00, data);
  return true;
}


//
//  SPI
//
void AD5684::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
}

uint32_t AD5684::getSPIspeed()
{
  return _SPIspeed;
}

bool AD5684::usesHWSPI()
{
  return _hwSPI;
}


//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
void AD5684::updateDevice(uint8_t command, uint8_t channel, uint16_t data)
{
  uint8_t a = command | (1 << channel);
  if (_type == 12) data <<= 4;
  if (_type == 14) data <<= 2;
  uint8_t b = (data >> 8) & 0xFF;
  uint8_t c = data & 0xFF;

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(a);
    _mySPI->transfer(b);
    _mySPI->transfer(c);
    _mySPI->endTransaction();
  }
  else  //  Software SPI
  {
    swSPI_transfer(a);
    swSPI_transfer(b);
    swSPI_transfer(c);
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void AD5684::swSPI_transfer(uint8_t value)
{
  int clk = _clock;
  int dao = _dataOut;
  //  Shifting 24 bits starting from MSB to LSB
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao, (value & mask)? HIGH : LOW);
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
}


///////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//


///////////////////////////////////////////////////////
//
//  AD5685
//
AD5685::AD5685(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
       :AD5684(slaveSelect, mySPI = &SPI)
{
  _type     = 14;    //  #bits
  _maxValue = 16383;
}

AD5685::AD5685(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
       :AD5684(slaveSelect, spiData, spiClock)
{
  _type     = 14;    //  #bits
  _maxValue = 19383;
}


///////////////////////////////////////////////////////
//
//  AD5685
//
AD5686::AD5686(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
       :AD5684(slaveSelect, mySPI = &SPI)
{
  _type     = 16;    //  #bits
  _maxValue = 65535;
}

AD5686::AD5686(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
       :AD5684(slaveSelect, spiData, spiClock)
{
  _type     = 16;    //  #bits
  _maxValue = 65535;
}


//  -- END OF FILE --

