//
//    FILE: FastShiftIn.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: Fast ShiftIn for 74HC165 register, AVR optimized
//    DATE: 2013-09-29
//     URL: https://github.com/RobTillaart/FastShiftIn


#include "FastShiftIn.h"


FastShiftIn::FastShiftIn(const uint8_t datapin, const uint8_t clockpin, const uint8_t bitOrder)
{
  _bitorder = bitOrder;
  _value    = 0;
  pinMode(datapin, INPUT);
  pinMode(clockpin, OUTPUT);
  // https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftin/
  digitalWrite(clockpin, LOW);  // assume rising pulses from clock 

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  // uint8_t _datatimer  = digitalPinToTimer(datapin);
  // if (_datatimer != NOT_ON_TIMER) turnOffPWM(_datatimer); TODO
  uint8_t _dataport   = digitalPinToPort(datapin);
  _datain = portOutputRegister(_dataport);
  _databit = digitalPinToBitMask(datapin);

  // uint8_t _clocktimer = digitalPinToTimer(clockpin);
  // if (_clocktimer != NOT_ON_TIMER) turnOffPWM(_clocktimer);
  uint8_t _clockport  = digitalPinToPort(clockpin);
  _clockin = portOutputRegister(_clockport);
  _clockbit = digitalPinToBitMask(clockpin);

#else

  // reference implementation
  // reuse these local vars as pin to save some space
  _databit = datapin;
  _clockbit = clockpin;

#endif
}

int FastShiftIn::read()
{
  if (_bitorder == LSBFIRST)
  {
    return readLSBFIRST();
  }
  return readMSBFIRST();
}

int FastShiftIn::readLSBFIRST()
{
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t value   = 0;
  uint8_t cbmask1 = _clockbit;
  uint8_t cbmask2 = ~_clockbit;
  uint8_t dbmask  = _databit;

  for (uint8_t m = 1; m > 0; m <<= 1)
  {
    uint8_t oldSREG = SREG;
    noInterrupts();
    *_clockin |= cbmask1;
    if ((*_datain & dbmask) > 0)
    {
      value |= m;
    }
    *_clockin &= cbmask2;
    SREG = oldSREG;
  }
  _value = value;
  return _value;

#else

  // reference implementation
  _value = shiftIn(_databit, _clockbit, LSBFIRST);
  return _value;

#endif
}

int FastShiftIn::readMSBFIRST()
{
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t value   = 0;
  uint8_t cbmask1 = _clockbit;
  uint8_t cbmask2 = ~cbmask1;
  uint8_t dbmask  = _databit;

  for (uint8_t n = 128; n > 0; n >>= 1)
  {
    uint8_t oldSREG = SREG;
    noInterrupts();
    *_clockin |= cbmask1;
    if ((*_datain & dbmask) > 0)
    {
      value |= n;
    }
    *_clockin &= cbmask2;
    SREG = oldSREG;
  }
  _value = value;
  return _value;

#else

  // reference implementation
  _value = shiftIn(_databit, _clockbit, MSBFIRST);
  return _value;

#endif
}

bool FastShiftIn::setBitOrder(const uint8_t bitOrder)
{
  if ((bitOrder == LSBFIRST) || (bitOrder == MSBFIRST))
  {
    _bitorder = bitOrder; 
    return true;
  };
  return false;
}

// -- END OF FILE --
