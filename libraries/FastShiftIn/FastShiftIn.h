//
//    FILE: FastShiftIn.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: shiftin
//    DATE: 2013-09-29
//     URL:
//
// Released to the public domain
//

#ifndef FastShiftIn_h
#define FastShiftIn_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define FASTSHIFTIN_LIB_VERSION "0.1.00"

class FastShiftIn
{
  public:
	FastShiftIn(uint8_t, uint8_t, uint8_t);
    int read(void);

  private:
    uint8_t _bitorder;
    int _value;
    
	uint8_t _databit;
    volatile uint8_t *_datain;
    
	uint8_t _clockbit;
    volatile uint8_t *_clockin;
};

#endif
// -- END OF FILE --