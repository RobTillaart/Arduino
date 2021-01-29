//
//    FILE: AsyncAnalog.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2018-09-05
// PURPOSE: async version of analogRead, prevent blocking wait
//
// backgrounder
// https://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-adc?name=PNphpBB2&file=viewtopic&t=56429
//
// HISTORY:
// 0.1.0   2018-09-05  initial version, based upon analogRead()
// 0.1.1   2020-03-26  minor refactor
// 0.1.2   2020-05-27  update library.json
// 0.1.3   2020-12-12  added Arduino CI, minor fixes


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
  // the MUX5 bit of ADCSRB selects whether we're reading from channels
  // 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
  ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((_pin >> 3) & 0x01) << MUX5);
#endif

#if defined(ADMUX)
  // set the analog reference (high two bits of ADMUX) and select the
  // channel (low 4 bits).  this also sets ADLAR (left-adjust result)
  // to 0 (the default).
  ADMUX = (DEFAULT << 6) | (_pin & 0x07);
#endif

  sbi(ADCSRA, ADSC);
}


bool AsyncAnalog::ready()
{
  // ADSC is cleared when the conversion finishes
  return bit_is_set(ADCSRA, ADSC) == 0;
}


int AsyncAnalog::value()
{
  // we have to read ADCL first; doing so locks both ADCL
  // and ADCH until ADCH is read.  reading ADCL second would
  // cause the results of each conversion to be discarded,
  // as ADCL and ADCH would be locked when it completed.
  int low  = ADCL;
  int high = ADCH;
  // combine the two bytes
  return (high << 8) | low;
}

#endif        // ARDUINO_ARCH_AVR

// -- END OF FILE --