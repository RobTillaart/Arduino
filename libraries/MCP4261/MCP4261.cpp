//
//    FILE: MCP4261.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-02-21
// PURPOSE: Arduino library for MCP4261 SPI based digital potentiometers.
//     URL: https://github.com/RobTillaart/MCP4261


#include "MCP4261.h"


//  see page 18 datasheet
#define MCP4261_IGNORE_CMD        0x00
#define MCP4261_WRITE_CMD         0x00
#define MCP4261_SHUTDOWN_CMD      0x20
#define MCP4261_NONE_CMD          0x30


  //       HARDWARE SPI
MCP4261::MCP4261(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI)
{
  _pmCount  = 2;
  _maxValue = 255;
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
  _maxValue = 255;
  _select   = select;
  _shutdown = shutdown;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}


void MCP4261::begin(uint16_t value)
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
  reset(value);
}


void MCP4261::reset(uint16_t value)
{
  digitalWrite(_shutdown, LOW);
  digitalWrite(_shutdown, HIGH);
  setValue(value);  //  set all to same value.
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

  uint8_t cmd = 0x00;
  if (pm == 1) cmd = 0x10;
  if (value > 0xFF) cmd |= (value >> 8);  //  high bits
  writeDevice(2, cmd, value & 0xFF);
  return true;
}


uint16_t MCP4261::getValue(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  return _value[pm];
}


bool MCP4261::incrValue(uint8_t pm)
{
  if (pm >= _pmCount) return false;
  if (_value[pm] >= _maxValue) return false;
  _value[pm]++;

  uint8_t cmd = 0x04;
  if (pm == 1) cmd = 0x14;
  writeDevice(1, cmd, cmd);  //  value2 = DUMMY
  return true;
}


bool MCP4261::decrValue(uint8_t pm)
{
  if (pm >= _pmCount) return false;
  if (_value[pm] == 0) return false;
  _value[pm]--;

  uint8_t cmd = 0x08;
  if (pm == 1) cmd = 0x18;
  writeDevice(1, cmd, cmd);  //  value2 = DUMMY
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

  uint8_t cmd = 0x20;
  if (pm == 1) cmd = 0x30;
  if (value > 0xFF) cmd |= (value >> 8);  //  high bits
  writeDevice(2, cmd, value & 0xFF);
  return true;
}


/////////////////////////////////////////////////////////////////////////////
//
//  MISC
//
uint8_t MCP4261::pmCount()
{
  return _pmCount;
}


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

/*
TODO - see page 46
- need read8, read16
- bid8, bidi16
*/


//
//  USES SPI MODE 0
//
void MCP4261::writeDevice(uint8_t count, uint8_t value1, uint8_t value2)
{
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(value1);
    if (count == 2) _mySPI->transfer(value2);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    swSPI_write(value1);
    if (count == 2) swSPI_write(value2);
  }
  digitalWrite(_select, HIGH);
}


//  MSBFIRST
void MCP4261::swSPI_write(uint8_t value)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  
  //  MSBFIRST
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(value & mask));
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
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

