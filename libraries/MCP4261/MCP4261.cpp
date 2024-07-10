//
//    FILE: MCP4261.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2024-02-21
// PURPOSE: Arduino library for MCP4261 SPI based digital potentiometers.
//     URL: https://github.com/RobTillaart/MCP4261


#include "MCP4261.h"


#define MCP4261_CMD_WRITE         0x00
#define MCP4261_CMD_INCR          0x04
#define MCP4261_CMD_DECR          0x08
#define MCP4261_CMD_READ          0x0C

#define MCP4261_REG_TCON          0x04
#define MCP4261_REG_STATUS        0x05
#define MCP4261_REG_EEPROM(x)     (0x06 + x)


  //       HARDWARE SPI
MCP4261::MCP4261(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI)
{
  _pmCount  = 2;
  _maxValue = MCP42XX_MAX_VALUE;
  _select   = select;
  _shutdown = shutdown;
  _dataIn   = 255;
  _dataOut  = 255;
  _clock    = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}


//       SOFTWARE SPI
MCP4261::MCP4261(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _pmCount  = 2;
  _maxValue = MCP42XX_MAX_VALUE;
  _select   = select;
  _shutdown = shutdown;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}


void MCP4261::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);
  pinMode(_shutdown, OUTPUT);
  digitalWrite(_shutdown, HIGH);

  setSPIspeed(1000000);

  if(_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else
  {
    pinMode(_dataIn, INPUT);
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }
  //  get initial values from device.
  getValueDevice(0);
  getValueDevice(1);
}


void MCP4261::reset(uint16_t value)
{
  digitalWrite(_shutdown, LOW);
  digitalWrite(_shutdown, HIGH);
  setValue(value);  //  set all to same value.
}


uint8_t MCP4261::pmCount()
{
  return _pmCount;
}


/////////////////////////////////////////////////////////////////////////////
//
//  SET VOLATILE VALUE
//
bool MCP4261::setValue(uint16_t value)
{
  setValue(0, value);
  setValue(1, value);
  return true;
}


bool MCP4261::setValue(uint8_t pm, uint16_t value)
{
  if (pm >= _pmCount) return false;
  if (value > _maxValue) return false;
  _value[pm] = value;

  uint8_t value1 = MCP4261_CMD_WRITE | (pm << 4);
  if (value > 0xFF) value1 |= (value >> 8);  //  high bits
  writeRegister2(value1, value & 0xFF);
  return true;
}


uint16_t MCP4261::getValue(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  return _value[pm];
}


uint16_t MCP4261::getValueDevice(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  uint8_t value1 = MCP4261_CMD_READ | (pm << 4);
  _value[pm] = readRegister(value1);
  return _value[pm];
}


bool MCP4261::incrValue(uint8_t pm)
{
  if (pm >= _pmCount) return false;
  if (_value[pm] >= _maxValue) return false;
  _value[pm]++;

  uint8_t value1 = MCP4261_CMD_INCR | (pm << 4);
  writeRegister1(value1);
  return true;
}


bool MCP4261::decrValue(uint8_t pm)
{
  if (pm >= _pmCount) return false;
  if (_value[pm] == 0) return false;
  _value[pm]--;

  uint8_t value1 = MCP4261_CMD_DECR | (pm << 4);
  writeRegister1(value1);
  return true;
}



/////////////////////////////////////////////////////////////////////////////
//
//  SET NON-VOLATILE VALUE
//
bool MCP4261::setValueNV(uint8_t pm, uint16_t value)
{
  if (pm >= _pmCount) return false;
  if (value > _maxValue) return false;

  uint8_t value1 = MCP4261_CMD_WRITE | ((pm + 2) << 4);
  if (value > 0xFF) value1 |= (value >> 8);  //  high bits
  writeRegister2(value1, value & 0xFF);
  return true;
}


uint16_t MCP4261::getValueNV(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  uint8_t value1 = MCP4261_CMD_READ | ((pm + 2) << 4);
  return readRegister(value1);
}


/////////////////////////////////////////////////////////////////////////////
//
//  TERMINAL CONTROL
//
void MCP4261::setTCONMask(uint16_t mask)
{
  uint8_t value1 = MCP4261_CMD_WRITE | (MCP4261_REG_TCON << 4);
  mask &= 0xFF;  //  only lower 8 bits used.
  writeRegister2(value1, mask);
}


uint16_t MCP4261::getTCONMask()
{
  uint8_t value1 = MCP4261_CMD_READ | (MCP4261_REG_TCON << 4);
  uint16_t mask = readRegister(value1);
  return mask & 0x01FF;  //  0x1FF to get bit 8 which is always HIGH.
}


/////////////////////////////////////////////////////////////////////////////
//
//  STATUS
//
uint16_t MCP4261::getStatusMask()
{
  uint8_t value1 = MCP4261_CMD_READ | (MCP4261_REG_STATUS << 4);
  uint16_t mask = readRegister(value1);
  return mask & 0x1F;
}


/////////////////////////////////////////////////////////////////////////////
//
//  EEPROM
//
bool MCP4261::setEEPROM(uint8_t index, uint16_t value)
{
  if (index > 9) return false;
  if (value > 0x1FF) return false;  //  511
  uint8_t value1 = MCP4261_CMD_WRITE | (MCP4261_REG_EEPROM(index) << 4);
  if (value > 0xFF) value1 |= (value >> 8);
  writeRegister2(value1, value & 0xFF);
  return true;
}


uint16_t MCP4261::getEEPROM(uint8_t index)
{
  if (index > 9) return 0;  //  0xFFFF ?
  uint8_t value1 = MCP4261_CMD_READ | (MCP4261_REG_EEPROM(index) << 4);
  uint16_t value = readRegister(value1);
  return value;
}


/////////////////////////////////////////////////////////////////////////////
//
//  POWER
//
void MCP4261::powerOn()
{
  digitalWrite(_shutdown, HIGH);
}


void MCP4261::powerOff()
{
  digitalWrite(_shutdown, LOW);
}


bool MCP4261::isPowerOn()
{
  return digitalRead(_shutdown) == HIGH;
}


/////////////////////////////////////////////////////////////////////////////
//
//  SPI
//
void MCP4261::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}


uint32_t MCP4261::getSPIspeed()
{
  return _SPIspeed;
}


bool MCP4261::usesHWSPI()
{
  return _hwSPI;
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//

//
//  USES SPI MODE 0
//
void MCP4261::writeRegister1(uint8_t value1)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(value1);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    swSPI_write(value1);
  }
  digitalWrite(_select, HIGH);
}


void MCP4261::writeRegister2(uint8_t value1, uint8_t value2)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(value1);
    _mySPI->transfer(value2);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    swSPI_write(value1);
    swSPI_write(value2);
  }
  digitalWrite(_select, HIGH);
}


uint16_t MCP4261::readRegister(uint8_t value)
{
  uint16_t rv = 0;
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    rv += _mySPI->transfer(value);
    rv <<= 8;
    rv += _mySPI->transfer(0x00);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    rv += swSPI_write(value);
    rv <<= 8;
    rv += swSPI_write(0x00);
  }
  digitalWrite(_select, HIGH);
  rv &= 0x01FF;  //  9 bits data only
  return rv;
}


//  MSBFIRST
uint8_t MCP4261::swSPI_write(uint8_t value)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  uint8_t dai = _dataIn;
  uint8_t val = 0;

  //  MSBFIRST
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(value & mask));
    digitalWrite(clk, HIGH);
    if (digitalRead(dai)) val |= mask;
    digitalWrite(clk, LOW);
  }
  return val;
}



////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES MCP41xx SERIES
//
MCP4141::MCP4141(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI)
        :MCP4261(select, shutdown, mySPI)
{
  _pmCount  = 1;
  _maxValue = MCP41XX_MAX_VALUE;
}

MCP4141::MCP4141(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP4261(select, shutdown, dataIn, dataOut, clock)
{
  _pmCount  = 1;
  _maxValue = MCP41XX_MAX_VALUE;
}

//

MCP4142::MCP4142(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI)
        :MCP4261(select, shutdown, mySPI)
{
  _pmCount  = 1;
  _maxValue = MCP41XX_MAX_VALUE;
}

MCP4142::MCP4142(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP4261(select, shutdown, dataIn, dataOut, clock)
{
  _pmCount  = 1;
  _maxValue = MCP41XX_MAX_VALUE;
}

//

MCP4161::MCP4161(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI)
        :MCP4261(select, shutdown, mySPI)
{
  _pmCount  = 1;
  _maxValue = MCP41XX_MAX_VALUE;
}

MCP4161::MCP4161(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP4261(select, shutdown, dataIn, dataOut, clock)
{
  _pmCount  = 1;
  _maxValue = MCP41XX_MAX_VALUE;
}

//

MCP4162::MCP4162(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI)
        :MCP4261(select, shutdown, mySPI)
{
  _pmCount  = 1;
  _maxValue = MCP41XX_MAX_VALUE;
}

MCP4162::MCP4162(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP4261(select, shutdown, dataIn, dataOut, clock)
{
  _pmCount  = 1;
  _maxValue = MCP41XX_MAX_VALUE;
}


////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES MCP42xx SERIES
//
MCP4241::MCP4241(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI)
        :MCP4261(select, shutdown, mySPI)
{
  _pmCount  = 2;
  _maxValue = MCP42XX_MAX_VALUE;
}

MCP4241::MCP4241(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP4261(select, shutdown, dataIn, dataOut, clock)
{
  _pmCount  = 2;
  _maxValue = MCP42XX_MAX_VALUE;
}

//

MCP4242::MCP4242(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI)
        :MCP4261(select, shutdown, mySPI)
{
  _pmCount  = 2;
  _maxValue = MCP42XX_MAX_VALUE;
}

MCP4242::MCP4242(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP4261(select, shutdown, dataIn, dataOut, clock)
{
  _pmCount  = 2;
  _maxValue = MCP42XX_MAX_VALUE;
}

//

MCP4262::MCP4262(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI)
        :MCP4261(select, shutdown, mySPI)
{
  _pmCount  = 2;
  _maxValue = MCP42XX_MAX_VALUE;
}

MCP4262::MCP4262(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
        :MCP4261(select, shutdown, dataIn, dataOut, clock)
{
  _pmCount = 2;
  _maxValue = MCP42XX_MAX_VALUE;
}



//  -- END OF FILE --

