//
//    FILE: AD520X.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-24
// VERSION: 0.1.1
// PURPOSE: Arduino library for AD5204 and AD5206 digital potentiometers (+ older AD8400, AD8402, AD8403)
//     URL: https://github.com/RobTillaart/AD520X
//
// HISTORY:
// 0.0.1    2020-07-24 initial version
// 0.0.2    2020-07-25 support for AD8400 series in documentation.
// 0.1.0    2020-07-26 refactor, fix #2 select pin for HW SPI; add shutdown.
// 0.1.1    2020-12-08 Arduino-CI + unit test + isPowerOn()


#include "AD520X.h"


AD520X::AD520X(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
{
  _pmCount  = 6;
  _select   = select;
  _data     = dataOut;
  _clock    = clock;
  _reset    = reset;
  _shutdown = shutdown;
  _hwSPI    = (dataOut == 255) && (clock == 255);
}

// initializes the pins and starts SPI in case of hardware SPI
void AD520X::begin(uint8_t value)
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);
  pinMode(_reset, OUTPUT);
  digitalWrite(_reset, LOW);
  pinMode(_shutdown, OUTPUT);
  digitalWrite(_shutdown, LOW);

  if(_hwSPI)
  {
    SPI.begin();
    delay(1);
  }
  else
  {
    pinMode(_data, OUTPUT);
    pinMode(_clock, OUTPUT);
    digitalWrite(_data, LOW);
    digitalWrite(_clock, LOW);
  }

  setAll(value);
}

void AD520X::setValue(uint8_t pm, uint8_t value)
{
  if (pm >= _pmCount) return;
  _value[pm] = value;
  updateDevice(pm);
}

void  AD520X::setAll(uint8_t value)
{
  for (uint8_t pm = 0; pm < _pmCount; pm++)
  {
    setValue(pm, value);
  }
}

uint8_t AD520X::getValue(uint8_t pm)
{
  if (pm >= _pmCount) return 0;
  return _value[pm];
}

void AD520X::reset(uint8_t value)
{
  digitalWrite(_reset, HIGH);
  digitalWrite(_reset, LOW);
  setAll(value);
}

void AD520X::updateDevice(uint8_t pm)
{
  if (_hwSPI)
  {
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1));
    digitalWrite(_select, LOW);
    SPI.transfer(pm);
    SPI.transfer(_value[pm]);
    digitalWrite(_select, HIGH);
    SPI.endTransaction();
  }
  else // Software SPI
  {
    digitalWrite(_select, LOW);
    swSPI_transfer(pm);
    swSPI_transfer(_value[pm]);
    digitalWrite(_select, HIGH);
  }
}

// simple one mode version
void AD520X::swSPI_transfer(uint8_t value)
{
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(_data,(value & mask) != 0);
    digitalWrite(_clock, HIGH);
    digitalWrite(_clock, LOW);
  }
}


/////////////////////////////////////////////////////////////////////////////

AD5206::AD5206(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 6;
}

AD5204::AD5204(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 4;
}

AD8403::AD8403(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 4;
}

AD8402::AD8402(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 2;
}

AD8400::AD8400(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)
             : AD520X(select, reset, shutdown, dataOut, clock)
{
  _pmCount = 1;
}

// -- END OF FILE --
