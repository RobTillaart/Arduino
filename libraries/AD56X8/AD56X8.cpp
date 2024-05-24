//
//    FILE: AD56X8.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2022-07-28
// PURPOSE: Arduino library for AD56X8, SPI 8 channel Digital Analog Convertor.


#include "AD56X8.h"

//  not all "commands" implemented yet

#define AD56X8_REG_WRITE          0x00
#define AD56X8_REG_UPDATE         0x01
#define AD56X8_REG_WRITE_LDAC     0x02
#define AD56X8_REG_WRITE_UPDATE   0x03
#define AD56X8_REG_POWER          0x04
#define AD56X8_REG_LOAD_CLR       0x05
#define AD56X8_REG_LOAD_LDAC      0x06
#define AD56X8_REG_RESET          0x07
#define AD56X8_REG_SETUP_REF      0x08    //  not implemented


//  HARDWARE SPI
AD56X8::AD56X8(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
{
  _select = slaveSelect;
  _hwSPI  = true;
  _mySPI  = mySPI;
  for (int i = 0; i < 8; i++) _value[i] = 0;
}

//  SOFTWARE SPI
AD56X8::AD56X8(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
{
  _select  = slaveSelect;
  _hwSPI   = false;
  _mySPI   = NULL;
  _dataOut = spiData;
  _clock   = spiClock;
  for (int i = 0; i < 8; i++) _value[i] = 0;
}


//  initializes the SPI
//  and sets internal state
void AD56X8::begin()
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
}


uint8_t AD56X8::getType()
{
  return _type;
}


void AD56X8::setLDACPin(uint8_t ldac)
{
  _ldac = ldac;
  pinMode(_ldac, OUTPUT);
  digitalWrite(_ldac, HIGH);
}


bool AD56X8::triggerLDAC()
{
  if (_ldac == 255) return false;
  digitalWrite(_ldac, LOW);
  digitalWrite(_ldac, HIGH);
  return true;
}


//  value = 0..65535 (16 bit), 16383 (14 bit), 4095 (12 bit) depending on type)
bool AD56X8::setValue(uint8_t channel, uint16_t value)
{
  if (channel > 7) return false;
  if ((_type == 12) && (value > 4095))  return false;
  if ((_type == 14) && (value > 16383)) return false;
  _value[channel] = value;
  updateDevice(AD56X8_REG_WRITE_UPDATE, channel, value);
  return true;
}


//  returns 0..65535 (16 bit), 16383 (14 bit), 4095 (12 bit) depending on type)
uint16_t AD56X8::getValue(uint8_t channel)
{
  if (channel > 7) return 0;
  return _value[channel];
}


bool AD56X8::setPercentage(uint8_t channel, float percentage)
{
  uint16_t value = 0;
  if ((percentage < 0) || (percentage > 100)) return false;
  if      (_type == 16) value = round(655.35 * percentage);
  else if (_type == 14) value = round(163.83 * percentage);
  else /* type = 12 */  value = round( 40.95 * percentage);
  return setValue(channel, value);
}


float AD56X8::getPercentage(uint8_t channel)
{
  float value = getValue(channel);
  if (value > 0)
  {
    if (_type == 16) return value * ( 1.0 / 655.35);
    if (_type == 14) return value * ( 1.0 / 163.83);
    if (_type == 12) return value * ( 1.0 /  40.95);
  }
  return 0;
}


bool AD56X8::prepareChannel(uint8_t channel, uint16_t value)
{
  if (channel > 7) return false;
  if ((_type == 12) && (value > 4095))  return false;
  if ((_type == 14) && (value > 16383)) return false;
  _value[channel] = value;
  updateDevice(AD56X8_REG_WRITE, channel, value);
  return true;
}


bool AD56X8::updateChannel(uint8_t channel)
{
  if (channel > 7) return false;
  updateDevice(AD56X8_REG_UPDATE, channel, 0);
  return true;
}


void AD56X8::updateAllChannels()
{
  updateDevice(AD56X8_REG_WRITE_LDAC, 0, _value[0]);
}


void AD56X8::setLDACmask(uint8_t mask)
{
  _ldacMask = mask;
  updateDevice(AD56X8_REG_LOAD_LDAC, 0, 0, _ldacMask);
}


uint8_t AD56X8::getLDACmask()
{
  return _ldacMask;
}


bool AD56X8::inLDACmask(uint8_t channel)
{
  if (channel > 7) return false;
  return (_ldacMask & (1 << channel)) > 0;
}


bool AD56X8::setPowerMode(uint8_t powerDownMode, uint8_t channelMask)
{
  if (powerDownMode > 3) return false;
  updateDevice(AD56X8_REG_POWER, 0, 0, channelMask);
  return true;
}


void AD56X8::reset()
{
  updateDevice(AD56X8_REG_RESET, 0, 0, 0);
  //  reset the internal values.
  for (int i = 0; i < 8; i++) _value[i] = 0;
}


bool AD56X8::setClearCode(uint8_t CCmode)
{
  if (CCmode > 3) return false;
  updateDevice(AD56X8_REG_LOAD_CLR, 0, 0, CCmode);
  return true;
}


//
//  SPI
//
void AD56X8::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
};


uint32_t AD56X8::getSPIspeed()
{
  return _SPIspeed;
};


bool AD56X8::usesHWSPI()
{
  return _hwSPI;
}


//////////////////////////////////////////////////////////////////
//
//  PRIVATE
//

void AD56X8::updateDevice(uint8_t cmd, uint8_t channel, uint16_t value)
{
  uint16_t val = value;
  if (_type == 12) val <<= 4;
  if (_type == 14) val <<= 2;
  uint8_t a = cmd;
  uint8_t b = (channel << 4) | (val >> 12);
  uint8_t c = val >> 4;
  uint8_t d = val << 4;
  updateDevice(a, b, c, d);
}


void AD56X8::updateDevice(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(a);
    _mySPI->transfer(b);
    _mySPI->transfer(c);
    _mySPI->transfer(d);
    _mySPI->endTransaction();
  }
  else //  Software SPI
  {
    swSPI_transfer(a);
    swSPI_transfer(b);
    swSPI_transfer(c);
    swSPI_transfer(d);
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void AD56X8::swSPI_transfer(uint8_t value)
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


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
AD5668_3::AD5668_3(uint8_t slaveSelect, __SPI_CLASS__ * mySPI) : AD56X8(slaveSelect, mySPI)
{
  _type = 16;
  //  AD5668_3 starts up at midscale
  for (int i = 0; i < 8; i++) _value[i] = 32768;  //  MIDSCALE
}

AD5668_3::AD5668_3(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
                : AD56X8(slaveSelect, spiData, spiClock)
{
  _type = 16;
  //  AD5668_3 starts up at midscale
  for (int i = 0; i < 8; i++) _value[i] = 32768;  //  MIDSCALE
}

void AD5668_3::reset()
{
  updateDevice(AD56X8_REG_RESET, 0, 0, 0);
  //  reset the internal values.
  for (int i = 0; i < 8; i++) _value[i] = 32768;  //  MIDSCALE
}


AD5668::AD5668(uint8_t slaveSelect, __SPI_CLASS__ * mySPI) : AD56X8(slaveSelect, mySPI)
{
  _type = 16;
}

AD5668::AD5668(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
                : AD56X8(slaveSelect, spiData, spiClock)
{
  _type = 16;
}


AD5648::AD5648(uint8_t slaveSelect, __SPI_CLASS__ * mySPI) : AD56X8(slaveSelect, mySPI)
{
  _type = 14;
}

AD5648::AD5648(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
                : AD56X8(slaveSelect, spiData, spiClock)
{
  _type = 14;
}


AD5628::AD5628(uint8_t slaveSelect, __SPI_CLASS__ * mySPI) : AD56X8(slaveSelect, mySPI)
{
  _type = 12;
}


AD5628::AD5628(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
                : AD56X8(slaveSelect, spiData, spiClock)
{
  _type = 12;
}


//  -- END OF FILE --

