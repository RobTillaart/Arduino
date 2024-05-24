//
//    FILE: AD568X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2023-09-18
// PURPOSE: Arduino library for AD568X series Digital Analog Convertor.
//     URL: https://github.com/RobTillaart/AD568X


#include "AD568X.h"

//  not all "commands" implemented

#define AD568X_REG_NOP            0x00
#define AD568X_REG_WRITE          0x10
#define AD568X_REG_UPDATE         0x20
#define AD568X_REG_WRITE_UPDATE   0x30
#define AD568X_REG_CONTROL        0x40



//  HARDWARE SPI
AD568X::AD568X(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
{
  _select = slaveSelect;
  _hwSPI  = true;
  _mySPI  = mySPI;
  _value  = 0;
}

//  SOFTWARE SPI
AD568X::AD568X(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
{
  _select  = slaveSelect;
  _hwSPI   = false;
  _mySPI   = NULL;
  _dataOut = spiData;
  _clock   = spiClock;
  _value   = 0;
}


//  initializes the SPI
//  and sets internal state
void AD568X::begin()
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


uint8_t AD568X::getType()
{
  return _type;
}


void AD568X::setLDACPin(uint8_t ldac)
{
  _ldac = ldac;
  pinMode(_ldac, OUTPUT);
  digitalWrite(_ldac, HIGH);
}


bool AD568X::triggerLDAC()
{
  if (_ldac == 255) return false;
  digitalWrite(_ldac, LOW);
  digitalWrite(_ldac, HIGH);
  return true;
}


//  value = 0..65535 (16 bit), 16383 (14 bit), 4095 (12 bit) depending on type)
bool AD568X::setValue(uint16_t value)
{
  if ((_type == 12) && (value > 4095))  return false;
  if ((_type == 14) && (value > 16383)) return false;
  _value = value;
  updateDevice(AD568X_REG_WRITE_UPDATE, value);
  return true;
}


//  returns 0..65535 (16 bit), 16383 (14 bit), 4095 (12 bit) depending on type)
uint16_t AD568X::getValue()
{
  return _value;
}


bool AD568X::setPercentage(float percentage)
{
  uint16_t value = 0;
  if ((percentage < 0) || (percentage > 100)) return false;
  if      (_type == 16) value = round(655.35 * percentage);
  else if (_type == 14) value = round(163.83 * percentage);
  else /* type = 12 */  value = round( 40.95 * percentage);
  return setValue(value);
}


float AD568X::getPercentage()
{
  float value = getValue();
  if (value > 0)
  {
    if (_type == 16) return value * ( 1.0 / 655.35);
    if (_type == 14) return value * ( 1.0 / 163.83);
    if (_type == 12) return value * ( 1.0 /  40.95);
  }
  return 0;
}


bool AD568X::prepareValue(uint16_t value)
{
  if ((_type == 12) && (value > 4095))  return false;
  if ((_type == 14) && (value > 16383)) return false;
  _value = value;
  updateDevice(AD568X_REG_WRITE, value);
  return true;
}


bool AD568X::updateValue()
{
  updateDevice(AD568X_REG_UPDATE, 0);
  return true;
}


//////////////////////////////////////////////////////////////////
//
//  CONTROL REGISTER
//
bool AD568X::setControlRegister(uint16_t value)
{
  _controlReg = value & 0xFC00;
  updateDevice(AD568X_REG_CONTROL, _controlReg);
  return true;
}


bool AD568X::reset()
{
  _controlReg |= (1 << 15);  //  set RESET bit
  updateDevice(AD568X_REG_CONTROL, _controlReg);
  _controlReg = 0x0000;
  return true;
}


bool AD568X::setPowerDownMode(uint8_t mode)
{
  if (mode > 3) return false;
  _controlReg &= 0x9C00;  //  clear PD bits
  _controlReg |= (mode << 13);
  updateDevice(AD568X_REG_CONTROL, _controlReg);
  return true;
}


bool AD568X::disableReference(bool b)
{
  _controlReg &= 0xEC00;  //  clear REF bit
  if (b) _controlReg |= (1 << 12);
  updateDevice(AD568X_REG_CONTROL, _controlReg);
  return true;
}


bool AD568X::enableGain(bool enable)
{
  _controlReg &= 0xF400;  //  clear GAIN bit
  if (enable) _controlReg |= (1 << 11);
  updateDevice(AD568X_REG_CONTROL, _controlReg);
  return true;
}


bool AD568X::enableDaisyChain(bool enable)
{
  _controlReg &= 0xF800;  //  clear DCEN bit
  if (enable) _controlReg |= (1 << 10);
  updateDevice(AD568X_REG_CONTROL, _controlReg);
  return true;
}


//////////////////////////////////////////////////////////////////
//
//  SPI
//
void AD568X::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
};


uint32_t AD568X::getSPIspeed()
{
  return _SPIspeed;
};


bool AD568X::usesHWSPI()
{
  return _hwSPI;
}


//////////////////////////////////////////////////////////////////
//
//  PRIVATE
//

void AD568X::updateDevice(uint8_t cmd, uint16_t value)
{
  //  to be optimized - switch cmd etc
  uint8_t a = cmd | (value >> 12);
  uint8_t b = (value >> 4) & 0xFF;
  uint8_t c = (value << 4) & 0xF0;

  updateDevice(a, b, c);
}


void AD568X::updateDevice(uint8_t a, uint8_t b, uint8_t c)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(a);
    _mySPI->transfer(b);
    _mySPI->transfer(c);
    _mySPI->endTransaction();
  }
  else //  Software SPI
  {
    swSPI_transfer(a);
    swSPI_transfer(b);
    swSPI_transfer(c);
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void AD568X::swSPI_transfer(uint8_t value)
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
//  DERIVED  AD5680
//
// AD5680::AD5680(uint8_t slaveSelect) : AD568X(slaveSelect)
// {
  // _type  = 18;
  // _value = 0;
// }

// AD5680::AD5680(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)
                // : AD568X(spiData, spiClock, slaveSelect)
// {
  // _type  = 18;
  // _value = 0;
// }


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED  AD5681
//
AD5681R::AD5681R(uint8_t slaveSelect, __SPI_CLASS__ * mySPI) : AD568X(slaveSelect, mySPI)
{
  _type  = 12;
}

AD5681R::AD5681R(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
                : AD568X(slaveSelect, spiData, spiClock)
{
  _type = 12;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED  AD5682
//
AD5682R::AD5682R(uint8_t slaveSelect, __SPI_CLASS__ * mySPI) : AD568X(slaveSelect, mySPI)
{
  _type  = 14;
}

AD5682R::AD5682R(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
                : AD568X(slaveSelect, spiData, spiClock)
{
  _type  = 14;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED  AD5683
//
AD5683R::AD5683R(uint8_t slaveSelect, __SPI_CLASS__ * mySPI) : AD568X(slaveSelect, mySPI)
{
  _type  = 16;
}

AD5683R::AD5683R(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
                : AD568X(slaveSelect, spiData, spiClock)
{
  _type  = 16;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED  AD5683
//
AD5683::AD5683(uint8_t slaveSelect, __SPI_CLASS__ * mySPI) : AD568X(slaveSelect, mySPI)
{
  _type  = 16;
}

AD5683::AD5683(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
                : AD568X(slaveSelect, spiData, spiClock)
{
  _type  = 16;
}


//  -- END OF FILE --

