//
//    FILE: FastShiftIn.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.4
// PURPOSE: Fast ShiftIn for 74HC165 register, AVR optimized
//    DATE: 2013-09-29
//     URL: https://github.com/RobTillaart/FastShiftIn


#include "FastShiftIn.h"


FastShiftIn::FastShiftIn(uint8_t dataIn, uint8_t clockPin, uint8_t bitOrder)
{
  _bitOrder  = bitOrder;
  _lastValue = 0;
  pinMode(dataIn, INPUT);
  pinMode(clockPin, OUTPUT);
  //  https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftin/
  digitalWrite(clockPin, LOW);  //  assume rising pulses from clock

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
  if (_bitOrder == LSBFIRST)
  {
    uint16_t rv = readLSBFIRST();
    rv += uint16_t(readLSBFIRST()) << 8;
    return rv;
  }
  uint16_t rv = readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  return rv;
}


uint32_t FastShiftIn::read24()
{
  if (_bitOrder == LSBFIRST)
  {
    uint32_t rv = readLSBFIRST();
    rv += uint32_t(readLSBFIRST()) << 8;
    rv += uint32_t(readLSBFIRST()) << 16;
    return rv;
  }
  uint32_t rv = readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  return rv;
}


uint32_t FastShiftIn::read32()
{
  if (_bitOrder == LSBFIRST)
  {
    uint32_t rv = readLSBFIRST();
    rv += uint32_t(readLSBFIRST()) << 8;
    rv += uint32_t(readLSBFIRST()) << 16;
    rv += uint32_t(readLSBFIRST()) << 24;
    return rv;
  }
  uint32_t rv = readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  rv <<= 8;
  rv += readMSBFIRST();
  return rv;
}


uint32_t FastShiftIn::lastRead(void)
{
  return _lastValue;
}


void FastShiftIn::read(uint8_t * array, uint8_t size)
{
  if (_bitOrder == LSBFIRST)
  {
    for (uint8_t i = 0; i < size; i++)
    {
      array[size - i - 1] = readLSBFIRST();
    }
    return;
  }
  for (uint8_t i = 0; i < size; i++)
  {
    array[i] = readMSBFIRST();
  }
  return;
}


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
}


uint8_t FastShiftIn::readLSBFIRST()
{
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t rv       = 0;
  uint8_t cbmask1  = _clockBit;
  uint8_t cbmask2  = ~_clockBit;
  uint8_t inmask1  = _dataInBit;

  for (uint8_t m = 0x01; m > 0; m <<= 1)
  {
    //  remember state register
    uint8_t oldSREG = SREG;
    //  disable interrupts
    noInterrupts();
    //  clock pulse HIGH
    *_clockRegister |= cbmask1;
    //  read one bit
    if ((*_dataInRegister & inmask1) > 0) rv |= m;
    //  clock pulse LOW
    *_clockRegister &= cbmask2;
    //  reset interrupts flag to previous state
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
    //  remember state register
    uint8_t oldSREG = SREG;
    //  disable interrupts
    noInterrupts();
    //  clock pulse HIGH
    *_clockRegister |= cbmask1;
    //  read one bit
    if ((*_dataInRegister & inmask1) > 0) rv |= m;
    //  clock pulse LOW
    *_clockRegister &= cbmask2;
    //  reset interrupts flag to previous state
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


//  -- END OF FILE --

