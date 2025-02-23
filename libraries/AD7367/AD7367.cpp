//
//    FILE: AD7367.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-01-10
// PURPOSE: Arduino library for the AD7367, 2 channel simultaneous sampling 14 bit ADC.
//     URL: https://github.com/RobTillaart/AD7367


#include "AD7367.h"


AD7367::AD7367(uint8_t select, uint8_t clock, uint8_t convert, uint8_t busy, uint8_t data0, uint8_t data1)
{
  _type    = 67;
  _bits    = 14;
  _select  = select;
  _clock   = clock;
  _convert = convert;
  _busy    = busy;
  _data0   = data0;
  _data1   = data1;
}

//  sets internal state
void AD7367::begin()
{
  pinMode(_select, OUTPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_convert, OUTPUT);
  pinMode(_busy, INPUT);
  pinMode(_data0, INPUT);
  pinMode(_data1, INPUT);

  digitalWrite(_select, HIGH);
  digitalWrite(_clock, HIGH);
  digitalWrite(_convert, HIGH);
}

uint8_t AD7367::getType()
{
  return _type;
}

int AD7367::getBits()
{
  return _bits;
}


//////////////////////////////////////////////////////////////////
//
//  READ
//
int AD7367::read()
{
  //  simulation
  //  _value[0] = random(16384);  //  14 bits = 16383,  12 bits = 4095
  //  _value[1] = random(16384);

  //  datasheet page 07 + 20
  //  trigger conversion
  triggerConversion();
  //  wait for conversion to be done
  while (conversionBusy());
  return readAsync();
}

void AD7367::triggerConversion()
{
  //  Trigger conversion by 10 ns pulse.
  //  might need a delayMicroseconds(1); on very fast processors.
  //  needs a configuration flag, although checking the flag is already 10 ns.
  //  Are NOP's portable?
  digitalWrite(_convert, LOW);
  //  delayMicroseconds(1);
  digitalWrite(_convert, HIGH);
}

bool AD7367::conversionBusy()
{
  return digitalRead(_busy) == HIGH;
}

bool AD7367::conversionReady()
{
  return digitalRead(_busy) == LOW;
}

int AD7367::readAsync()
{
  digitalWrite(_select, LOW);
  //  use local variables for clocking
  int d0 = 0;
  int d1 = 0;
  //  clock in the bits
  for (int i = 0; i < _bits; i++)
  {
    digitalWrite(_clock, LOW);
    digitalWrite(_clock, HIGH);
    d0 = (d0 << 1) | digitalRead(_data0);
    d1 = (d1 << 1) | digitalRead(_data1);
  }
  digitalWrite(_select, HIGH);

  _value[0] = d0;
  _value[1] = d1;
  return 0;
}

int AD7367::getLastADCA()
{
  return _value[0];
}

int AD7367::getLastADCB()
{
  return _value[1];
}


//////////////////////////////////////////////////////////////////
//
//  FASTREAD
//
int AD7367::fastRead(int &a, int &b)
{
  //  Trigger conversion by 10 ns pulse. (see above)
  digitalWrite(_convert, LOW);
  //  delayMicroseconds(1);
  digitalWrite(_convert, HIGH);
  //  wait for ready (blocking)
  while(digitalRead(_busy) == HIGH);
  //  fetch data
  digitalWrite(_select, LOW);
  //  reset data received.
  a = 0;
  b = 0;
  //  clock in the bits
  for (int i = 0; i < _bits; i++)
  {
    digitalWrite(_clock, LOW);
    digitalWrite(_clock, HIGH);
    a = (a << 1) | digitalRead(_data0);
    b = (b << 1) | digitalRead(_data1);
  }
  digitalWrite(_select, HIGH);

  _value[0] = a;
  _value[1] = b;
  return 0;
}


//////////////////////////////////////////////////////////////////
//
//  ADDR + REFSEL
//
void AD7367::setADDRpin(uint8_t pin)
{
  _addr = pin;
  pinMode(_addr, OUTPUT);
  digitalWrite(_addr, LOW);
}

void AD7367::setREFSELpin(uint8_t pin)
{
  _refsel = pin;
  pinMode(_refsel, OUTPUT);
  digitalWrite(_refsel, HIGH);
}


//////////////////////////////////////////////////////////////////
//
//  RANGE
//
void AD7367::setRangePin(uint8_t range0, uint8_t range1)
{
  _range0 = range0;
  _range1 = range1;
  pinMode(_range0, OUTPUT);
  pinMode(_range1, OUTPUT);
  digitalWrite(_range0, LOW);
  digitalWrite(_range1, LOW);
}

int AD7367::setRange(uint8_t range)
{
  if (range > 2) return -1;
  if (conversionBusy()) return -2;
  digitalWrite(_range0, range & 0x01);
  digitalWrite(_range1, (range >> 1) & 0x01);
  return 0;
}

uint8_t AD7367::getRange()
{
  if ((_range0 == 255) || (_range1 == 255)) return 255;
  uint8_t range = digitalRead(_range0) == LOW ? 0 : 1;
  range += digitalRead(_range1) == LOW ? 0 : 2;
  return range;
}



//////////////////////////////////////////////////////////////////
//
//  OBSOLETE
//
int AD7367::getValue(uint8_t channel)
{
  return _value[channel];
}



//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//



/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS AD7366
//
AD7366::AD7366(uint8_t select, uint8_t clock, uint8_t convert, uint8_t busy, uint8_t data0, uint8_t data1)
        :AD7367(select, clock, convert, busy, data0, data1)
{
  _type = 66;
  _bits = 12;
}


//  -- END OF FILE --

