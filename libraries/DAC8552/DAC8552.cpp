//
//    FILE: DAC8552.cpp 
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8552 SPI Digital Analog Convertor
// VERSION: 0.5.1
//    DATE: 2017-12-14
//     URL: https://github.com/RobTillaart/DAC8552


#include "DAC8552.h"


DAC8552::DAC8552(uint8_t select, __SPI_CLASS__ * spi)
{
  _select  = select;
  _dataOut = 255;
  _clock   = 255;
  _mySPI   = spi;
  _hwSPI   = true;
}


DAC8552::DAC8552(uint8_t select, uint8_t spiData, uint8_t spiClock)
{
  _select  = select;
  _dataOut = spiData;
  _clock   = spiClock;
  _mySPI   = NULL;
  _hwSPI   = false;
}


//  initializes the SPI
//  and sets internal state
void DAC8552::begin()
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

  _value[0] = 0;
  _value[1] = 0;
  _register[0] = 0x00;
  _register[1] = 0x04;  //  set BUFFER SELECT to 1
}


//  channel = 0, 1, 2, 3 depending on type
//  value = 0..65535
void DAC8552::bufferValue(uint8_t channel, uint16_t value)
{
  _value[channel] = value;
  updateDevice(channel, false);
}


//  channel = 0, 1, 2, 3 depending on type
//  value = 0..65535
void DAC8552::setValue(uint8_t channel, uint16_t value)
{
  _value[channel] = value;
  updateDevice(channel, true);
}


//  channel = 0, 1, 2, 3 depending on type
//  returns 0..65535
uint16_t DAC8552::getValue(uint8_t channel)
{
  return _value[channel];
}


void DAC8552::bufferPowerDown(uint8_t channel, uint8_t powerDownMode)
{
  _register[channel] &= 0xFC;
  _register[channel] |= (powerDownMode & 0x03);
  updateDevice(channel, false);
}


void DAC8552::setPowerDown(uint8_t channel, uint8_t powerDownMode)
{
  _register[channel] &= 0xFC;
  _register[channel] |= (powerDownMode & 0x03);
  updateDevice(channel, true);
}


uint8_t DAC8552::getPowerDownMode(uint8_t channel)
{
  return _register[channel] & 0x03;
}


void DAC8552::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
};


//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//

//  channel = 0, 1, 2, 3 depending on type
//  direct = true  ==> write buffers to both channel A and channel B
//  direct = false ==> buffer value
void DAC8552::updateDevice(uint8_t channel, bool directWrite)
{
  uint8_t configRegister = _register[channel];
  if (directWrite) configRegister |= 0x30;

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(configRegister);
    _mySPI->transfer(_value[channel] >> 8);
    _mySPI->transfer(_value[channel] & 0xFF);
    _mySPI->endTransaction();
  }
  else //  Software SPI
  {
    swSPI_transfer(configRegister);
    swSPI_transfer(_value[channel] >> 8);
    swSPI_transfer(_value[channel] & 0xFF);
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void DAC8552::swSPI_transfer(uint8_t value)
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
//  DERIVED CLASSES  DAC8532
//
DAC8532::DAC8532(uint8_t select, __SPI_CLASS__ * spi) : DAC8552(select, spi)
{
}

DAC8532::DAC8532(uint8_t select, uint8_t spiData, uint8_t spiClock)
                : DAC8552(select, spiData, spiClock)
{
}


//  -- END OF FILE --

