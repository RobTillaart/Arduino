//
//    FILE: FastShiftIn.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Fast ShiftIn for 74HC165 register, AVR optimized
//    DATE: 2013-09-29
//     URL: https://github.com/RobTillaart/FastShiftIn
//
// HISTORY: see changelog.md


#include "FastShiftIn.h"


FastShiftIn::FastShiftIn(uint8_t dataIn, uint8_t clockPin, uint8_t bitOrder)
{
  _bitOrder  = bitOrder;
  _lastValue = 0;
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


uint16_t FastShiftIn::read()
{
  if (_bitOrder == LSBFIRST)
  {
    return readLSBFIRST();
  }
  return readMSBFIRST();
}


uint16_t FastShiftIn::read16()
{
  uint16_t rv;
  if (_bitOrder == LSBFIRST)
  {
    rv = readLSBFIRST();
    rv += uint16_t(readLSBFIRST()) << 8;
    return rv;
  }
  rv = readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  return rv;
}


uint32_t FastShiftIn::read24()
{
  uint32_t rv;
  if (_bitOrder == LSBFIRST)
  {
    rv = readLSBFIRST();
    rv += uint32_t(readLSBFIRST()) << 8;
    rv += uint32_t(readLSBFIRST()) << 16;
    return rv;
  }
  rv = readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  return rv;
}


uint32_t FastShiftIn::read32()
{
  uint32_t rv;
  if (_bitOrder == LSBFIRST)
  {
    rv = readLSBFIRST();
    rv += uint32_t(readLSBFIRST()) << 8;
    rv += uint32_t(readLSBFIRST()) << 16;
    rv += uint32_t(readLSBFIRST()) << 24;
    return rv;
  }
  rv = readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  return rv;
}



uint8_t FastShiftIn::readLSBFIRST()
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
  _lastValue = rv;
  return rv;

#else

  //  reference implementation
  _lastValue = shiftIn(_dataPinIn, _clockPin, LSBFIRST);
  return _lastValue;

#endif
}


uint8_t FastShiftIn::readMSBFIRST()
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
  _lastValue = rv;
  return rv;

#else

  //  reference implementation
  _lastValue = shiftIn(_dataPinIn, _clockPin, MSBFIRST);
  return _lastValue;

#endif

}


uint32_t FastShiftIn::lastRead(void)
{
  return _lastValue;
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


//  -- END OF FILE --

