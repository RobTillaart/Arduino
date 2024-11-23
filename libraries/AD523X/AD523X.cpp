//
//    FILE: AD523X.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-21
// VERSION: 0.1.0
// PURPOSE: Arduino library for SPI AD5231 and AD5235 10 bit digital potentiometers.
//     URL: https://github.com/RobTillaart/AD523X


#include "AD523X.h"


//  HARDWARE SPI
AD523X::AD523X(uint8_t select, uint8_t reset, __SPI_CLASS__ * mySPI)
{
  _pmCount  = 2;
  _select   = select;
  _reset    = reset;
  _dataOut  = 255;
  _dataIn   = 255;
  _clock    = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
}

//  SOFTWARE SPI
AD523X::AD523X(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _pmCount  = 2;
  _select   = select;
  _reset    = reset;
  _dataOut  = dataOut;
  _dataIn   = dataIn;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}

//  initializes the pins and starts SPI in case of hardware SPI
void AD523X::begin(uint16_t value)
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);
  pinMode(_reset, OUTPUT);
  digitalWrite(_reset, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

  if(_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else
  {
    pinMode(_dataIn,  INPUT_PULLUP);  //  INPUT
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }

  reset(value);
}

void AD523X::reset(uint16_t value)
{
  digitalWrite(_reset, LOW);
  digitalWrite(_reset, HIGH);
  setAll(value);
}

//  command #8
void AD523X::resetDevice()
{
  uint8_t cmd = 0x80;
  updateDevice(cmd, 0x0000);
}


/////////////////////////////////////////////////////////////////////////////
//
//  SET VALUE
//
//  command #11
bool AD523X::setValue(uint16_t value)
{
  _value[0] = value;
  uint8_t cmd = 0xB0;
  updateDevice(cmd, value);
  return true;
}

bool AD523X::setValue(uint8_t pm, uint16_t value)
{
  if (pm >= _pmCount) return false;
  _value[pm] = value;
  uint8_t cmd = 0xB0 | pm;  //  P17
  updateDevice(cmd, value);
  return true;
}

uint16_t AD523X::getValue(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  return _value[pm];
  //  P23 - AD5235 get from device.
}

bool AD523X::setAll(uint16_t value)
{
  for (uint8_t pm = 0; pm < _pmCount; pm++ )
  {
    _value[pm] = value;
    uint8_t cmd = 0xB0 | pm;  //  P17
    updateDevice(cmd, value);
  }
  return true;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PERCENTAGE
//
bool AD523X::setPercentage(uint8_t pm, float percentage)
{
  if ((percentage < 0) || (percentage > 100.0)) return false;
  return setValue(pm, round(percentage * (1023.0 / 100.0)));
}

float AD523X::getPercentage(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  uint16_t value = _value[pm];
  if (value == 0) return 0.0;
  return (100.0 / 1023.0) * value;
}

bool AD523X::setPercentageAll(float percentage)
{
  if ((percentage < 0) || (percentage > 100.0)) return false;
  return setAll(round(percentage * (1023.0 / 100.0)));
}


/////////////////////////////////////////////////////////////////////////////
//
//  INCR / DECR interface
//
//  TODO update cache
//
//  //  command #4
//  void AD523X::decrement6DB(uint8_t pm)
//  {
//    //  P16
//    uint8_t cmd = 0x40 | pm;
//    if (_value[pm] > 0) _value[pm] >>= 1;
//    updateDevice(cmd, 0x0000);
//  }
//
//  //  command #6
//  void AD523X::decrementOne(uint8_t pm)
//  {
//    //  P16
//    uint8_t cmd = 0x60 | pm;
//    if (_value[pm] > 0) _value[pm] -= 1;
//    updateDevice(cmd, 0x0000);
//  }
//
//  //  command #12
//  void AD523X::increment6DB(uint8_t pm)
//  {
//    //  P16
//    uint8_t cmd = 0xC0 | pm;
//    // if (_value[pm] < 1023) _value[pm] >>= 1;
//    updateDevice(cmd, 0x0000);
//  }
//
//  //  command #14
//  void AD523X::incrementOne(uint8_t pm)
//  {
//    //  P16
//    uint8_t cmd = 0xE0 | pm;
//    // if (_value[pm] < 1023) _value[pm] += 1;
//    updateDevice(cmd, 0x0000);
//  }


/////////////////////////////////////////////////////////////////////////////
//
//  OTHER
//
uint8_t AD523X::pmCount()
{
  return _pmCount;
}



/////////////////////////////////////////////////////////////////////////////
//
//  SPI
//
void AD523X::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};


uint32_t AD523X::getSPIspeed()
{
  return _SPIspeed;
}


bool AD523X::usesHWSPI()
{
  return _hwSPI;
}


/////////////////////////////////////////////////////////////////////////////
//
//  EEMEM (~P14-19 )
//

//  command #0
uint32_t AD523X::rawRead()
{
  return updateDevice(0x00, 0x0000);
}

//  command #1
void AD523X::loadWiperEEMEM(uint8_t pm)
{
  uint8_t cmd = 0x10 | pm;
  updateDevice(cmd, 0x0000);
  rawRead();
}

//  command #2
void AD523X::storeWiperEEMEM(uint8_t pm)
{
  uint8_t cmd = 0x20 | pm;
  updateDevice(cmd, 0x0000);
}

//  command #9
uint16_t AD523X::loadEEMEM(uint8_t address)
{
  uint8_t cmd = 0x90 | address;
  updateDevice(cmd, 0x0000);
  return rawRead() & 0xFFFF;   //  P23 - AD5235
}

//  command #3
void AD523X::storeEEMEM(uint8_t address, uint16_t value)
{
  uint8_t cmd = 0x30 | address;
  updateDevice(cmd, value);
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
uint32_t AD523X::updateDevice(uint8_t pm, uint16_t value)
{
  uint32_t rv = 0;
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    rv += _mySPI->transfer(pm);
    rv <<= 8;
    rv += _mySPI->transfer(value >> 8);
    rv <<= 8;
    rv += _mySPI->transfer(value & 0xFF);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    rv += swSPI_transfer(pm);
    rv <<= 8;
    rv += swSPI_transfer(value >> 8);
    rv <<= 8;
    rv += swSPI_transfer(value & 0xFF);
  }
  digitalWrite(_select, HIGH);
  return rv;
}


uint8_t AD523X::swSPI_transfer(uint8_t value)
{
  uint8_t rv = 0;
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  uint8_t dai = _dataIn;
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(value & mask));
    digitalWrite(clk, HIGH);
    rv <<= 1;
    if (digitalRead(dai) == HIGH) rv |= 1;
    digitalWrite(clk, LOW);
  }
  return rv;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
AD5231::AD5231(uint8_t select, uint8_t reset, __SPI_CLASS__ * mySPI)
             : AD523X(select, reset, mySPI)
{
  _pmCount = 1;
}


AD5231::AD5231(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
             : AD523X(select, reset, dataIn, dataOut, clock)
{
  _pmCount = 1;
}


AD5235::AD5235(uint8_t select, uint8_t reset, __SPI_CLASS__ * mySPI)
             : AD523X(select, reset, mySPI)
{
  _pmCount = 2;
}


AD5235::AD5235(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
             : AD523X(select, reset, dataIn, dataOut, clock)
{
  _pmCount = 2;
}


//  -- END OF FILE --

