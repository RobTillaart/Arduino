#ifndef PulsePattern_h
#define PulsePattern_h
//
//    FILE: PulsePattern.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// PURPOSE: PulsePattern library for Arduino
//          sends a pulse pattern to a digital pin (continuously)
// HISTORY: See PulsePattern.cpp
//
// Released to the public domain
//

#include <inttypes.h>

#define PULSEPATTERN_LIB_VERSION "0.0.7"

#define NOTINIT -1
#define STOPPED 0
#define RUNNING 1

#define NO_CLOCK		0
#define PRESCALE_1		1
#define PRESCALE_8		2
#define PRESCALE_64		3
#define PRESCALE_256	4
#define PRESCALE_1024	5

class PulsePattern
{
public:
  PulsePattern();
  
  void init(const uint8_t pin,
    const uint16_t * ar, const uint8_t size,
    const uint8_t level, const uint8_t prescaler);

  void start();
  void stop();
  bool isRunning() const { return _state == RUNNING; };

  void worker();

private:
  void stopTimer();
  void setTimer(const uint16_t cc) const;
  
  uint16_t * _ar;
  uint8_t _size;
  uint8_t _pin;
  uint8_t _prescaler;
  volatile uint8_t _level;
  volatile int8_t _state;
  volatile uint8_t _cnt;
};

extern PulsePattern PPGenerator;

#endif
// END OF FILE