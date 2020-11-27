//
//    FILE: FastShiftOut.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: shiftout that implements the Print interface
//    DATE: 2013-08-22
//     URL: https://github.com/RobTillaart/FastShiftOut
//

#include "FastShiftOut.h"

FastShiftOut::FastShiftOut(const uint8_t datapin, const uint8_t clockpin, const uint8_t bitOrder)
{
  _bitorder = bitOrder;
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  // uint8_t _datatimer  = digitalPinToTimer(datapin);
  // if (_datatimer != NOT_ON_TIMER) turnOffPWM(_datatimer); TODO
  uint8_t _dataport   = digitalPinToPort(datapin);
  _dataout = portOutputRegister(_dataport);
  _databit = digitalPinToBitMask(datapin);

  // uint8_t _clocktimer = digitalPinToTimer(clockpin);
  // if (_clocktimer != NOT_ON_TIMER) turnOffPWM(_clocktimer);
  uint8_t _clockport  = digitalPinToPort(clockpin);
  _clockout = portOutputRegister(_clockport);
  _clockbit = digitalPinToBitMask(clockpin);

#else   // reference implementation

  // reuse these vars as pin to save some space
  _databit = datapin;
  _clockbit = clockpin;

#endif
}

size_t FastShiftOut::write(const uint8_t data)
{
  if (_bitorder == LSBFIRST)
  {
    return writeLSBFIRST(data);
  }
  return writeMSBFIRST(data);
}

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

size_t FastShiftOut::writeLSBFIRST(const uint8_t data)
{
  uint8_t cbmask1 = _clockbit;
  uint8_t cbmask2 = ~_clockbit;
  uint8_t dbmask1 = _databit;
  uint8_t dbmask2 = ~_databit;

  for (uint8_t i = 0, m = 1; i < 8; i++)
  {
    uint8_t oldSREG = SREG;
    cli();
    if ((data & m) == 0) *_dataout &= dbmask2;
    else                 *_dataout |= dbmask1;
    *_clockout |= cbmask1;
    *_clockout &= cbmask2;
    SREG = oldSREG;
    m <<= 1;
  }
  return 1;
}

size_t FastShiftOut::writeMSBFIRST(const uint8_t data)
{
  uint8_t cbmask1 = _clockbit;
  uint8_t cbmask2 = ~_clockbit;
  uint8_t dbmask1 = _databit;
  uint8_t dbmask2 = ~_databit;

  for (uint8_t i = 0, n = 128; i < 8; i++)
  {
    uint8_t oldSREG = SREG;
    cli();
    if ((data & n) == 0) *_dataout &= dbmask2;
    else                 *_dataout |= dbmask1;
    *_clockout |= cbmask1;
    *_clockout &= cbmask2;
    SREG = oldSREG;
    n >>= 1;
  }
  return 1;
}

#else  // reference implementation  // note this has no cli()

size_t FastShiftOut::writeLSBFIRST(const uint8_t data)
{
  shiftOut(_databit, _clockbit, LSBFIRST, data);
    return 1;
}

size_t FastShiftOut::writeMSBFIRST(const uint8_t data)
{
  shiftOut(_databit, _clockbit, MSBFIRST, data);
    return 1;
}

#endif

// -- END OF FILE --