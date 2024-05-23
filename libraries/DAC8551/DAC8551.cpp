//
//    FILE: DAC8551.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8551 SPI Digital Analog Convertor
// VERSION: 0.4.1
//     URL: https://github.com/RobTillaart/DAC8551


#include "DAC8551.h"


DAC8551::DAC8551(uint8_t select, __SPI_CLASS__ * spi)
{
  _select  = select;
  _dataOut = 255;
  _clock   = 255;
  _mySPI   = spi;
  _hwSPI   = true;
}


DAC8551::DAC8551(uint8_t select, uint8_t spiData, uint8_t spiClock)
{
  _select  = select;
  _dataOut = spiData;
  _clock   = spiClock;
  _mySPI   = NULL;
  _hwSPI   = false;
}


//  initializes the SPI
//  and sets internal state
void DAC8551::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);

  if(_hwSPI)
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

  _register = 0;
  _value = 0;
}


//  value = 0..65535
void DAC8551::setValue(uint16_t value)
{
  _value = value;
  updateDevice();
}


//  returns 0..65535
uint16_t DAC8551::getValue()
{
  return _value;
}


void DAC8551::setPowerDown(uint8_t powerDownMode)
{
  _register = (powerDownMode & 0x03);
  updateDevice();
}


uint8_t DAC8551::getPowerDownMode()
{
  return _register & 0x03;
}


void DAC8551::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
};


//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
void DAC8551::updateDevice()
{
  uint8_t configRegister = _register;

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(configRegister);
    _mySPI->transfer(_value >> 8);
    _mySPI->transfer(_value & 0xFF);
    _mySPI->endTransaction();
  }
  else //  Software SPI
  {
    swSPI_transfer(configRegister);
    swSPI_transfer(_value >> 8);
    swSPI_transfer(_value & 0xFF);
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void DAC8551::swSPI_transfer(uint8_t value)
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


/////////////////////////////////////////////////////////
//
//  DERIVED CLASSES  DAC8501, DAC8531, DAC8550
//
DAC8501::DAC8501(uint8_t select, __SPI_CLASS__ * spi) : DAC8551(select, spi)
{
}

DAC8501::DAC8501(uint8_t select, uint8_t spiData, uint8_t spiClock)
                : DAC8551(select, spiData, spiClock)
{
} 


DAC8531::DAC8531(uint8_t select, __SPI_CLASS__ * spi) : DAC8551(select, spi)
{
}

DAC8531::DAC8531(uint8_t select, uint8_t spiData, uint8_t spiClock)
                : DAC8551(select, spiData, spiClock)
{
}


DAC8550::DAC8550(uint8_t select, __SPI_CLASS__ * spi) : DAC8551(select, spi)
{
}

DAC8550::DAC8550(uint8_t select, uint8_t spiData, uint8_t spiClock)
                : DAC8551(select, spiData, spiClock)
{
}


//  -- END OF FILE --

