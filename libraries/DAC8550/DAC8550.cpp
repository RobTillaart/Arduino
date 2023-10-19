//
//    FILE: DAC8550.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8550 SPI Digital Analog Convertor
// VERSION: 0.1.4
//    DATE: 2021-02-04
//     URL: https://github.com/RobTillaart/DAC8550


#include "DAC8550.h"


DAC8550::DAC8550(uint8_t slaveSelect)
{
  _hwSPI  = true;
  _select = slaveSelect;
}


DAC8550::DAC8550(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)
{
  _hwSPI   = false;
  _dataOut = spiData;
  _clock   = spiClock;
  _select  = slaveSelect;
}


//  initializes the SPI
//  and sets internal state
void DAC8550::begin()
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

  _register = 0;
  _value = 0;
}


#if defined(ESP32)
void DAC8550::setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)
{
  _clock   = clk;
  _dataOut = mosi;
  _select  = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  mySPI->end();  //  disable SPI 
  mySPI->begin(clk, miso, mosi, select);
}
#endif


//  value = 0..65535
void DAC8550::setValue(uint16_t value)
{
  _value = value;
  updateDevice();
}


//  returns 0..65535
uint16_t DAC8550::getValue()
{
  return _value;
}


void DAC8550::setPowerDown(uint8_t powerDownMode)
{
  _register = powerDownMode;
  updateDevice();
}


uint8_t DAC8550::getPowerDownMode()
{
  return _register & 0x03;
}


void DAC8550::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
};


//////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
void DAC8550::updateDevice()
{
  uint8_t configRegister = _register;

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer(configRegister);
    mySPI->transfer(_value >> 8);
    mySPI->transfer(_value & 0xFF);
    mySPI->endTransaction();
  }
  else // Software SPI 
  {
    swSPI_transfer(configRegister);
    swSPI_transfer(_value >> 8);
    swSPI_transfer(_value & 0xFF);
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void DAC8550::swSPI_transfer(uint8_t value)
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

