//
//    FILE: AD5370.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-24
// VERSION: 0.1.0
// PURPOSE: Arduino library for AD5370
//     URL: https://github.com/RobTillaart/AD5370
//          http://www.aosong.com/en/products-77.html


#include "AD5370.h"


/////////////////////////////////////////////
//
//  CONSTRUCTORS
//
//  HARDWARE SPI
AD5370::AD5370(uint8_t select, uint8_t reset, uint8_t clear, __SPI_CLASS__ * mySPI)
{
  _select   = select;
  _reset    = reset;
  _clear    = clear;
  _busy     = 255;
  _ldac     = 255;
  _dataIn   = 255;
  _dataOut  = 255;
  _clock    = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
}

//  SOFTWARE SPI
AD5370::AD5370(uint8_t select, uint8_t reset, uint8_t clear, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _select   = select;
  _reset    = reset;
  _clear    = clear;
  _busy     = 255;
  _ldac     = 255;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}

//  initializes the pins and starts SPI in case of hardware SPI
void AD5370::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);
  pinMode(_reset, OUTPUT);
  digitalWrite(_reset, HIGH);
  pinMode(_clear, OUTPUT);
  digitalWrite(_clear, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

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
}

void AD5370::setBusyPin(uint8_t busyPin)
{
  _busy = busyPin;
  pinMode(_busy, INPUT);
}

void AD5370::setLDACPin(uint8_t ldacPin)
{
  _ldac = ldacPin;
  pinMode(_ldac, OUTPUT);
  digitalWrite(_ldac, HIGH);
}



/////////////////////////////////////////////
//
//  WRITE
//
//  TODO reuse 3x - sendMessage(M, channel, value);
bool AD5370::setDAC(uint8_t channel, uint16_t value)
{
  if (channel > 39) return false;
  //  5 groups of 8
  //  table 9 mode bits M1 = 1, M0 = 1
  uint32_t msg = 3;
  msg <<= 3;
  //  Table 11  column 001-101
  //  determine group
  msg |= ((channel / 8) + 1);  //  A5..A3
  msg <<= 3;
  //  determine channel within group
  msg |= (channel % 8);        //  A2..A0
  msg <<= 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}

bool AD5370::setGain(uint8_t channel, uint16_t value)
{
  if (channel > 39) return false;
  //  5 groups of 8
  //  table 9 mode bits M1 = 0, M0 = 1
  uint32_t msg = 1;
  msg <<= 3;
  //  Table 11  column 001-101
  //  determine group
  msg |= ((channel / 8) + 1);  //  A5..A3
  msg <<= 3;
  //  determine channel within group
  msg |= (channel % 8);        //  A2..A0
  msg <<= 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}

bool AD5370::setOffset(uint8_t channel, uint16_t value)
{
  if (channel > 39) return false;
  //  5 groups of 8
  //  table 9 mode bits M1 = 1, M0 = 0
  uint32_t msg = 2;
  msg <<= 3;
  //  Table 11  column 001-101
  //  determine group
  msg |= ((channel / 8) + 1);  //  A5..A3
  msg <<= 3;
  //  determine channel within group
  msg |= (channel % 8);        //  A2..A0
  msg <<= 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}



/////////////////////////////////////////////
//
//  GROUP COMMANDS
//
bool AD5370::setAllAllDAC(uint16_t value)
{
  //  table 9 mode bits M1 = 1, M0 = 1
  uint32_t msg = 3;
  //  Table 11  column 000
  msg <<= 3;
  msg |=  0;     //  A5..A3
  msg <<= 3;
  //  add group  //  A2..A0
  msg |=  0;
  msg <<= 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}

bool AD5370::setGroupAllChannelDAC(uint8_t group, uint16_t value)
{
  if (group > 4) return false;
  //  table 9 mode bits M1 = 1, M0 = 1
  uint32_t msg = 3;
  //  Table 11  column 000 (0)
  msg <<= 3;
  msg |=  0;     //  A5..A3
  msg <<= 3;
  //  add group  //  A2..A0
  msg |= (group + 1);
  msg <<= 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}

bool AD5370::setAllGroupChannelDAC(uint8_t channel, uint16_t value)
{
  if (channel > 7) return false;
  //  table 9 mode bits M1 = 1, M0 = 1
  uint32_t msg = 3;
  //  Table 11  column 110 (6)
  msg <<= 3;
  msg |=  6;     //  A5..A3
  msg <<= 3;
  //  add group  //  A2..A0
  msg |= channel;
  msg <<= 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}

bool AD5370::set1234GroupChannelDAC(uint8_t channel, uint16_t value)
{
  if (channel > 7) return false;
  //  table 9 mode bits M1 = 1, M0 = 1
  uint32_t msg = 3;
  //  Table 11  column 111 (7)
  msg <<= 3;
  msg |=  7;     //  A5..A3
  msg <<= 3;
  //  add group  //  A2..A0
  msg |= channel;
  msg <<= 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}



/////////////////////////////////////////////
//
//  SPECIAL FUNCTIONS
//
uint32_t AD5370::writeNOP()
{
  //  table 9 mode bits M1 = 0, M0 = 0
  //  all bits 0
  updateDevice(0, 3);
  //  TODO implement read back
  return 0;
}

bool AD5370::writeControlRegister(uint8_t mask)
{
  if (mask > 7) return false;
  //  table 9 mode bits M1 = 0, M0 = 0
  uint32_t msg = 1L << 16;
  //  add mask
  msg |= mask;
  //  send data
  updateDevice(msg, 3);
  return true;
}

bool AD5370::writeOffset0Register(uint16_t value)
{
  if (value > 16383) return false;
  //  table 9 mode bits M1 = 0, M0 = 0
  uint32_t msg = 2L << 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}

bool AD5370::writeOffset1Register(uint16_t value)
{
  if (value > 16383) return false;
  //  table 9 mode bits M1 = 0, M0 = 0
  uint32_t msg = 3L << 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}

//  command 4L reserved, see table 13.

bool AD5370::selectReadBackRegister(uint16_t selection)
{
  //  table 9 mode bits M1 = 0, M0 = 0
  uint32_t msg = 5L << 16;
  //  add selection
  msg |= selection;
  //  send data
  updateDevice(msg, 3);
  return true;
}

bool AD5370::writeABSelectRegister(uint8_t reg, uint8_t value)
{
  //  table 9 mode bits M1 = 0, M0 = 0
  //  command = 6..10 for reg 0..5
  uint32_t msg = (6L + reg) << 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}

bool AD5370::blockABSelectRegister(uint8_t value)
{
  //  table 9 mode bits M1 = 0, M0 = 0
  uint32_t msg = 11L << 16;
  //  add value
  msg |= value;
  //  send data
  updateDevice(msg, 3);
  return true;
}



/////////////////////////////////////////////
//
//  SPI
//
void AD5370::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}

uint32_t AD5370::getSPIspeed()
{
  return _SPIspeed;
}



/////////////////////////////////////////////
//
//  CONTROL SIGNALS
//
bool AD5370::isBusy()
{
  return digitalRead(_busy) == HIGH;
}

void AD5370::pulseLDAC()
{
  digitalWrite(_ldac, LOW);
  digitalWrite(_ldac, HIGH);
}

void AD5370::reset()
{
  digitalWrite(_reset, LOW);
  digitalWrite(_reset, HIGH);
}


void AD5370::clear()
{
  digitalWrite(_clear, LOW);
  digitalWrite(_clear, HIGH);
}



///////////////////////////////////////////////
//
//  PRIVATE
//
uint32_t AD5370::updateDevice(uint32_t value, uint8_t bytes)
{
  if (bytes > 4) return 0;
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    if (bytes == 4) _mySPI->transfer((value >> 24) & 0xFF);
    if (bytes >= 3) _mySPI->transfer((value >> 16) & 0xFF);
    if (bytes >= 3) _mySPI->transfer((value >>  8) & 0xFF);
    if (bytes >= 3) _mySPI->transfer((value >>  0) & 0xFF);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    if (bytes == 4) swSPI_transfer((value >> 24) & 0xFF);
    if (bytes >= 3) swSPI_transfer((value >> 16) & 0xFF);
    if (bytes >= 3) swSPI_transfer((value >>  8) & 0xFF);
    if (bytes >= 3) swSPI_transfer((value >>  0) & 0xFF);
  }
  digitalWrite(_select, HIGH);
  return 0;
}


//  SW SPI byte transfer
uint32_t AD5370::swSPI_transfer(uint8_t value)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  for (uint16_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(value & mask));
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
  return 0;
}


//  -- END OF FILE --

