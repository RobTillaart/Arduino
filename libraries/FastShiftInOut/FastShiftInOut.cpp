//
//    FILE: FastShiftInOut.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for (AVR) optimized shiftInOut (simultaneously)
//     URL: https://github.com/RobTillaart/FastShiftInOut


#include "FastShiftInOut.h"


FastShiftInOut::FastShiftInOut(uint8_t dataIn, uint8_t dataOut, uint8_t clockPin, uint8_t bitOrder)
{
  _bitOrder = bitOrder;
  pinMode(dataIn, INPUT);
  pinMode(dataOut, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/
  digitalWrite(clockPin, LOW);  // assume rising pulses from clock 

  // reuse these vars as pin to save some space
  _dataPinIn  = dataIn;
  _dataPinOut = dataOut;
  _clockPin   = clockPin;
}


uint8_t FastShiftInOut::write(uint8_t data)
{
  _value = data;
  if (_bitOrder == LSBFIRST)
  {
    return writeLSBFIRST(_value);
  }
  return writeMSBFIRST(_value);
}


uint8_t FastShiftInOut::writeLSBFIRST(uint8_t data)
{
  uint8_t rv    = 0;
  uint8_t value = data;
  for (uint8_t i = 0; i < 8; i++)
  {
    // write one bit
    digitalWrite(_clockPin, HIGH);
    digitalWrite(_dataPinOut, value & 0x01);
    value >>= 1;
    //  read one bit
    rv >>= 1;
    if (digitalRead(_dataPinIn) == HIGH)  rv |= 0x80;
    digitalWrite(_clockPin, LOW);
  }
  return rv;
}


uint8_t FastShiftInOut::writeMSBFIRST(uint8_t data)
{
  uint8_t rv    = 0;
  uint8_t value = data;
  for (uint8_t i = 0; i < 8; i++)
  {
    // write one bit
    digitalWrite(_clockPin, HIGH);
    digitalWrite(_dataPinOut, value & 0x80);
    value <<= 1;
    //  read one bit
    rv <<= 1;
    if (digitalRead(_dataPinIn) == HIGH) rv |= 1;
    digitalWrite(_clockPin, LOW);
  }
  return rv;
}

uint8_t FastShiftInOut::lastWritten(void)
{
  return _value;
};
  

bool FastShiftInOut::setBitOrder(uint8_t bitOrder)
{
  if ((bitOrder == LSBFIRST) || (bitOrder == MSBFIRST))
  {
    _bitOrder = bitOrder; 
    return true;
  };
  return false;
}


uint8_t FastShiftInOut::getBitOrder(void)
{
  return _bitOrder; 
};


// -- END OF FILE --

