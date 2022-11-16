//
//    FILE: FastShiftIn.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Fast ShiftIn for 74HC165 register, AVR optimized
//    DATE: 2013-09-29
//     URL: https://github.com/RobTillaart/FastShiftIn
//
// HISTORY: see changelog.md


#include "FastShiftIn.h"


FastShiftIn::FastShiftIn(uint8_t dataIn, uint8_t clockPin, uint8_t bitOrder)
{
  _bitOrder = bitOrder;
  _value    = 0;
  pinMode(dataIn, INPUT);
  pinMode(clockPin, OUTPUT);
  //  https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftin/
  digitalWrite(clockPin, LOW);  // assume rising pulses from clock

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t _port    = digitalPinToPort(dataIn);
  _dataInRegister  = portInputRegister(_port);
  _dataInBit       = digitalPinToBitMask(dataIn);

  _port            = digitalPinToPort(clockPin);
  _clockRegister   = portOutputRegister(_port);
  _clockBit        = digitalPinToBitMask(clockPin);

#else

  _dataPinIn  = dataIn;
  _clockPin   = clockPin;

#endif

}



int FastShiftIn::read()
{
  if (_bitOrder == LSBFIRST)
  {
    return readLSBFIRST();
  }
  return readMSBFIRST();
}



int FastShiftIn::readLSBFIRST()
{
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t rv       = 0;
  uint8_t cbmask1  = _clockBit;
  uint8_t cbmask2  = ~_clockBit;
  uint8_t inmask1  = _dataInBit;

  for (uint8_t m = 1; m > 0; m <<= 1)
  {
    uint8_t oldSREG = SREG;
    noInterrupts();
    //  clock pulse HIGH
    *_clockRegister |= cbmask1;
    //  read one bit
    if ((*_dataInRegister & inmask1) > 0) rv |= m;
    //  clock pulse LOW
    *_clockRegister &= cbmask2;
    SREG = oldSREG;
  }
  _value = rv;
  return rv;

#else

  // reference implementation
  _value = shiftIn(_dataPinIn, _clockPin, LSBFIRST);
  return _value;

#endif
}


int FastShiftIn::readMSBFIRST()
{
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t rv       = 0;
  uint8_t cbmask1  = _clockBit;
  uint8_t cbmask2  = ~_clockBit;
  uint8_t inmask1  = _dataInBit;

  for (uint8_t m = 0x80; m > 0; m >>= 1)
  {
    uint8_t oldSREG = SREG;
    noInterrupts();
    //  clock pulse HIGH
    *_clockRegister |= cbmask1;
    //  read one bit
    if ((*_dataInRegister & inmask1) > 0) rv |= m;
    //  clock pulse LOW
    *_clockRegister &= cbmask2;
    SREG = oldSREG;
  }
  _value = rv;
  return rv;

#else

  // reference implementation
  _value = shiftIn(_dataPinIn, _clockPin, MSBFIRST);
  return _value;

#endif

}


int FastShiftIn::lastRead(void)
{
  return _value;
};


bool FastShiftIn::setBitOrder(const uint8_t bitOrder)
{
  if ((bitOrder == LSBFIRST) || (bitOrder == MSBFIRST))
  {
    _bitOrder = bitOrder;
    return true;
  };
  return false;
}


uint8_t FastShiftIn::getBitOrder(void)
{
  return _bitOrder;
};


// -- END OF FILE --

