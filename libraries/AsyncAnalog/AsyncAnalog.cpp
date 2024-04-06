//
//    FILE: AsyncAnalog.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2018-09-05
// PURPOSE: Async version of analogRead, prevent blocking wait
//     URL: https://github.com/RobTillaart/AsyncAnalog


#include "AsyncAnalog.h"


#if defined(ARDUINO_ARCH_AVR)

AsyncAnalog::AsyncAnalog(const uint8_t pin)
{
  _pin = pin;
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  if (_pin >= 54) _pin -= 54;
#else
  if (_pin >= 14) _pin -= 14;
#endif
}


void AsyncAnalog::start()
{
#if defined(ADCSRB) && defined(MUX5)
  //  the MUX5 bit of ADCSRB selects whether we're reading from channels
  //  0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
  ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((_pin >> 3) & 0x01) << MUX5);
#endif

#if defined(ADMUX)
  //  set the analogue reference (high two bits of ADMUX) and select the
  //  channel (low 4 bits).  this also sets ADLAR (left-adjust result)
  //  to 0 (the default).
  ADMUX = (DEFAULT << 6) | (_pin & 0x07);
#endif

  sbi(ADCSRA, ADSC);
}


bool AsyncAnalog::ready()
{
  // ADSC is cleared when the conversion finishes
  bool _ready = bit_is_set(ADCSRA, ADSC) == 0;

  if (_ready)  //  calculate the measurement
  {
    //  ADCL has to be read first.
    //  Doing so locks both ADCL and ADCH until ADCH is read.
    //  Reading ADCL second would cause the results of each conversion to
    //  be discarded as ADCL and ADCH would be locked when it completed.
    uint16_t lo = ADCL;
    uint16_t hi = ADCH;
    //  Combine two parts.
    _lastValue = (hi * 256) + lo;
  }
  return _ready;
}


uint16_t AsyncAnalog::value()
{
  return _lastValue;
}

#else


#endif        //  ARDUINO_ARCH_AVR


//  -- END OF FILE --
