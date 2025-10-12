//
//    FILE: FastShiftInOut.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
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

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t _port    = digitalPinToPort(dataIn);
  _dataInRegister  = portInputRegister(_port);
  _dataInBit       = digitalPinToBitMask(dataIn);

  _port            = digitalPinToPort(dataOut);
  _dataOutRegister = portOutputRegister(_port);
  _dataOutBit      = digitalPinToBitMask(dataOut);

  _port            = digitalPinToPort(clockPin);
  _clockRegister   = portOutputRegister(_port);
  _clockBit        = digitalPinToBitMask(clockPin);

#else

  _dataPinIn  = dataIn;
  _dataPinOut = dataOut;
  _clockPin   = clockPin;

#endif

  _lastValue = 0;
  _lastRead  = 0;
}


uint8_t FastShiftInOut::write(uint8_t data)
{
  if (_bitOrder == LSBFIRST)
  {
    return writeLSBFIRST(data);
  }
  return writeMSBFIRST(data);
}



uint8_t FastShiftInOut::lastWritten(void)
{
  return _lastValue;
}


uint8_t FastShiftInOut::lastRead(void)
{
  return _lastRead;
}


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
}


uint8_t FastShiftInOut::writeLSBFIRST(uint8_t data)
{
  uint8_t rv    = 0;
  uint8_t value = data;
  _lastValue = value;

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

#if defined(FASTSHIFTINOUT_AVR_LOOP_UNROLLED)  //  AVR SPEED OPTIMIZED

  uint8_t cbmask1  = _clockBit;
  uint8_t inmask1  = _dataInBit;
  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  volatile uint8_t* localDataInRegister  = _dataInRegister;
  volatile uint8_t* localDataOutRegister = _dataOutRegister;
  volatile uint8_t* localClockRegister   = _clockRegister;

  //  disable interrupts (for all bits)
  uint8_t oldSREG = SREG;
  noInterrupts();

  //  See discussion #17 FastShiftOut
  uint8_t d0 = *localDataOutRegister & outmask2;  //  cache 0
  uint8_t d1 = d0 | outmask1;                     //  cache 1

  if ((value & 0x01) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  // *localClockRegister |= cbmask1;
  //  if ((*localDataInRegister & inmask1) > 0) rv |= 0x01;
  // *localClockRegister &= cbmask2;  // ~_clockBit;
  //  following code is allowed as interrupts are disabled.
  //  so register can not change
  uint8_t r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x01;
  *localClockRegister = r;            //  reset it

  if ((value & 0x02) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x02;
  *localClockRegister = r;            //  reset it

  if ((value & 0x04) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x04;
  *localClockRegister = r;            //  reset it

  if ((value & 0x08) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x08;
  *localClockRegister = r;            //  reset it

  if ((value & 0x10) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x10;
  *localClockRegister = r;            //  reset it

  if ((value & 0x20) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x20;
  *localClockRegister = r;            //  reset it

  if ((value & 0x40) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x40;
  *localClockRegister = r;            //  reset it

  if ((value & 0x80) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x80;
  *localClockRegister = r;            //  reset it

  SREG = oldSREG;

#else  //  AVR SIZE OPTIMIZED

  uint8_t cbmask1  = _clockBit;
  uint8_t inmask1  = _dataInBit;
  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  volatile uint8_t* localDataInRegister  = _dataInRegister;
  volatile uint8_t* localDataOutRegister = _dataOutRegister;
  volatile uint8_t* localClockRegister   = _clockRegister;

  uint8_t oldSREG = SREG;
  noInterrupts();

  uint8_t d0 = *localDataOutRegister & outmask2;  //  cache 0
  uint8_t d1 = d0 | outmask1;                     //  cache 1

  for (uint8_t m = 1; m > 0; m <<= 1)
  {
    //  write one bit
    if ((value & m) == 0) *localDataOutRegister = d0;
    else                  *localDataOutRegister = d1;
    uint8_t r = *localClockRegister;

    //  clock pulse HIGH
    *localClockRegister = r | cbmask1;
    //  read one bit
    if ((*localDataInRegister & inmask1) > 0) rv |= m;
    //  clock pulse LOW
    *localClockRegister = r;
  }
  SREG = oldSREG;

#endif  //  if (AVR)

#else   //  other platforms reference implementation

  for (uint8_t i = 0; i < 8; i++)
  {
    //  write one bit
    digitalWrite(_dataPinOut, value & 0x01);
    value >>= 1;
    //  clock pulse
    digitalWrite(_clockPin, HIGH);
    //  read one bit
    rv >>= 1;
    if (digitalRead(_dataPinIn) == HIGH)  rv |= 0x80;
    //  clock pulse
    digitalWrite(_clockPin, LOW);
  }

#endif

  _lastRead = rv;
  return rv;
}


uint8_t FastShiftInOut::writeMSBFIRST(uint8_t data)
{
  uint8_t rv    = 0;
  uint8_t value = data;
  _lastValue = value;

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

#if defined(FASTSHIFTINOUT_AVR_LOOP_UNROLLED)  //  AVR SPEED OPTIMIZED

  uint8_t cbmask1  = _clockBit;
  uint8_t inmask1  = _dataInBit;
  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  volatile uint8_t* localDataInRegister  = _dataInRegister;
  volatile uint8_t* localDataOutRegister = _dataOutRegister;
  volatile uint8_t* localClockRegister   = _clockRegister;

  uint8_t oldSREG = SREG;
  noInterrupts();

  //  See discussion #17 FastShiftOut
  uint8_t d0 = *localDataOutRegister & outmask2;  //  cache 0
  uint8_t d1 = d0 | outmask1;                     //  cache 1

  if ((value & 0x80) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  // *localClockRegister |= cbmask1;
  //  if ((*localDataInRegister & inmask1) > 0) rv |= 0x80;
  // *localClockRegister &= cbmask2;  // ~_clockBit;
  //  following code is allowed as interrupts are disabled.
  //  so register can not change
  uint8_t r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x80;
  *localClockRegister = r;            //  reset it

  if ((value & 0x40) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x40;
  *localClockRegister = r;            //  reset it

  if ((value & 0x20) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x20;
  *localClockRegister = r;            //  reset it

  if ((value & 0x10) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x10;
  *localClockRegister = r;            //  reset it

  if ((value & 0x08) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x08;
  *localClockRegister = r;            //  reset it

  if ((value & 0x04) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x04;
  *localClockRegister = r;            //  reset it

  if ((value & 0x02) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x02;
  *localClockRegister = r;            //  reset it

  if ((value & 0x01) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  if ((*localDataInRegister & inmask1) > 0) rv |= 0x01;
  *localClockRegister = r;            //  reset it

  SREG = oldSREG;

#else  //  AVR SIZE OPTIMIZED

  uint8_t cbmask1  = _clockBit;
  uint8_t inmask1  = _dataInBit;
  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  volatile uint8_t* localDataInRegister  = _dataInRegister;
  volatile uint8_t* localDataOutRegister = _dataOutRegister;
  volatile uint8_t* localClockRegister   = _clockRegister;

  uint8_t oldSREG = SREG;
  noInterrupts();

  //  See discussion #17 FastShiftOut
  uint8_t d0 = *localDataOutRegister & outmask2;  //  cache 0
  uint8_t d1 = d0 | outmask1;                     //  cache 1

  for (uint8_t m = 0x80; m > 0; m >>= 1)
  {
    //  write one bit
    if ((value & m) == 0) *localDataOutRegister = d0;
    else                  *localDataOutRegister = d1;
    uint8_t r = *localClockRegister;
    //  clock pulse HIGH
    *localClockRegister = r | cbmask1;
    //  read one bit
    if ((*localDataInRegister & inmask1) > 0) rv |= m;
    //  clock pulse LOW
    *localClockRegister = r;
  }

  //  reset interrupts flag to previous state
  SREG = oldSREG;

#endif  //  if (AVR)

#else   //  other platforms reference implementation

  for (uint8_t i = 0; i < 8; i++)
  {
    // write one bit
    digitalWrite(_dataPinOut, value & 0x80);
    value <<= 1;
    //  clock pulse
    digitalWrite(_clockPin, HIGH);
    //  read one bit
    rv <<= 1;
    if (digitalRead(_dataPinIn) == HIGH) rv |= 1;
    //  clock pulse
    digitalWrite(_clockPin, LOW);
  }

#endif

  _lastRead = rv;
  return rv;
}


//  -- END OF FILE --

