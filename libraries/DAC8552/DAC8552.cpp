//
//    FILE: DAC8552.cpp 
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8552 SPI Digital Analog Convertor
// VERSION: 0.2.5
//    DATE: 2017-12-14
//     URL: https://github.com/RobTillaart/DAC8552


#include "DAC8552.h"


#define MAXVOLTAGE              5.0
#define MAXVALUE                0xFFFF


DAC8552::DAC8552(uint8_t slaveSelect)
{
  _hwSPI = true;
  _select = slaveSelect;
}


DAC8552::DAC8552(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)
{
  _hwSPI   = false;
  _dataOut = spiData;
  _clock   = spiClock;
  _select  = slaveSelect;
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

  _value[0] = 0;
  _value[1] = 0;
  _register[0] = 0x00;
  _register[1] = 0x40;
}


#if defined(ESP32)
void DAC8552::setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)
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
//  PRIVATE
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
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer(configRegister);
    mySPI->transfer(_value[channel] >> 8);
    mySPI->transfer(_value[channel] & 0xFF);
    mySPI->endTransaction();
  }
  else // Software SPI
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


//  -- END OF FILE --

