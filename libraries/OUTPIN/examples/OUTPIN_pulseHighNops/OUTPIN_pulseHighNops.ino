//
//    FILE: OUTPIN_pulseHighNops.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure range of function
//     URL: https://github.com/RobTillaart/OUTPIN


#include "OUTPIN.h"

//  adjust pin if needed
OUTPIN op(13, LOW);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("OUTPIN_LIB_VERSION: ");
  Serial.println(OUTPIN_LIB_VERSION);
  Serial.println();
  delay(100);

  test_pulseHigh();
}


void loop()
{
}


void test_pulseHigh()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(50);

  for (int nop = 0; nop < 256; nop++)
  {
    start = micros();
    for (int k = 0; k < 100; k++)
    {
      op.pulseHigh(nop);
    }
    stop = micros();
    Serial.print("NOP:\t");
    Serial.print(nop);
    Serial.print("\t=>\t");
    Serial.println((stop - start) * 0.01);
    delay(50);
  }
}

//  -- END OF FILE --
