//
//    FILE: AD5680.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-09-19
// PURPOSE: Arduino library for AD5680 Digital Analog Convertor (18 bit).


#include "AD5680.h"


AD5680::AD5680(uint8_t slaveSelect)
{
  _hwSPI  = true;
  _select = slaveSelect;
  _value  = 0;
}


AD5680::AD5680(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)
{
  _hwSPI   = false;
  _dataOut = spiData;
  _clock   = spiClock;
  _select  = slaveSelect;
  _value   = 0;
}


//  initializes the SPI
//  and sets internal state
void AD5680::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);

  if(_hwSPI)
  {
    #if defined(ESP32)
    if (_useHSPI)      //  HSPI
    {
      mySPI = new SPIClass(HSPI);
      mySPI->end();
      mySPI->begin(14, 12, 13, _select);   //  CLK=14  MISO=12  MOSI=13
    }
    else               //  VSPI
    {
      mySPI = new SPIClass(VSPI);
      mySPI->end();
      mySPI->begin(18, 19, 23, _select);   //  CLK=18  MISO=19  MOSI=23
    }
    #else              //  generic hardware SPI
    mySPI = &SPI;
    mySPI->end();
    mySPI->begin();
    #endif
    delay(1);
  }
  else                 //  software SPI
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock, OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock, LOW);
  }
}


uint8_t AD5680::getType()
{
  return _type;
}


//  value = 0..262143 == 0x0003FFFF (18 bit)
bool AD5680::setValue(uint32_t value)
{
  if (value > 0x3FFFF) return false;
  _value = value;
  updateDevice(_value);
  return true;
}


//  returns 0..262143 == 0x0003FFFF (18 bit)
uint32_t AD5680::getValue()
{
  return _value;
}


bool AD5680::setPercentage(float percentage)
{
  if ((percentage < 0) || (percentage > 100)) return false;

  uint32_t value = round( 2621.43 * percentage);
  return setValue(value);
}


float AD5680::getPercentage()
{
  float value = getValue();
  if (value > 0)
  {
    return value * ( 1.0 / 2621.43);
  }
  return 0;
}


//
//  SPI
//
void AD5680::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
};


uint32_t AD5680::getSPIspeed()
{
  return _SPIspeed;
};


bool AD5680::usesHWSPI()
{
  return _hwSPI;
}


//  ESP32 specific
#if defined(ESP32)

void AD5680::selectHSPI()
{
  _useHSPI = true;
}


void AD5680::selectVSPI()
{
  _useHSPI = false;
}


bool AD5680::usesHSPI()
{
  return _useHSPI;
}


bool AD5680::usesVSPI()
{
  return !_useHSPI;
}


void AD5680::setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)
{
  _clock   = clk;
  _dataOut = mosi;
  _select  = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  mySPI->end();                            //  disable SPI
  mySPI->begin(clk, miso, mosi, select);   //  enable SPI
}

#endif


//////////////////////////////////////////////////////////////////
//
//  PRIVATE
//

void AD5680::updateDevice(uint32_t value)
{
  uint8_t a = (value >> 14) & 0x0F;  //  bit 14-17
  uint8_t b = (value >> 6)  & 0xFF;  //  bit 06-13
  uint8_t c = (value << 2)  & 0xF0;  //  bit 00-05

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer(a);
    mySPI->transfer(b);
    mySPI->transfer(c);
    mySPI->endTransaction();
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
void AD5680::swSPI_transfer(uint8_t value)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(value & mask));
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
}


//  -- END OF FILE --

