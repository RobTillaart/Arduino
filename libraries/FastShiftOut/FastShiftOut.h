//
//    FILE: FastShiftOut.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1
// PURPOSE: 
//     URL:
//
// Released to the public domain
//

#ifndef FastShiftOut_h
#define FastShiftOut_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define FASTSHIFTOUT_LIB_VERSION "0.1.00"

class FastShiftOut
{
  public:
	FastShiftOut(uint8_t, uint8_t, uint8_t);
    void write(uint8_t);
    int read(void);

  private:
    uint8_t _datapin;
    uint8_t _clockpin;
    uint8_t _bitorder;
    int _value;
    
    uint8_t _datatimer;
	uint8_t _databit;
	uint8_t _dataport;
    volatile uint8_t *_dataout;
        
    uint8_t _clocktimer;
	uint8_t _clockbit;
	uint8_t _clockport;
    volatile uint8_t *_clockout;
    
};

#endif
// -- END OF FILE --