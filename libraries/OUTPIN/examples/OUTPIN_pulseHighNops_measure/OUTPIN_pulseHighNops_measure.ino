//
//    FILE: OUTPIN_pulseHighNops_measure.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure range of function
//     URL: https://github.com/RobTillaart/OUTPIN
//
//  sketch to measure the timing on a scope


#include "OUTPIN.h"

//  adjust pin if needed
OUTPIN op(13, LOW);

uint32_t start, stop;

volatile uint8_t value;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("OUTPIN_LIB_VERSION: ");
  Serial.println(OUTPIN_LIB_VERSION);
  Serial.println();
  delay(100);

  //  value is volatile to prevent optimizations of compiler.
  value = 255;
  while (1)
  {
    //  constant values < 8 are optimized!
    op.pulseHigh(9);
    // op.pulseHigh(50);
    delayMicroseconds(20);
  }
}


void loop()
{
}


//  -- END OF FILE --
