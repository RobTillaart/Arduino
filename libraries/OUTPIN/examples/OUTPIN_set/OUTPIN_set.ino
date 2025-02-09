//
//    FILE: OUTPIN_set.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/OUTPIN


#include "OUTPIN.h"

//  adjust pin if needed
OUTPIN op(13, LOW);

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println(__FILE__);
  Serial.print("OUTPIN_LIB_VERSION: ");
  Serial.println(OUTPIN_LIB_VERSION);
  Serial.println();
}


void loop()
{
  op.set(LOW);
  delay(500);
  op.set(HIGH);
  delay(500);
  op.low();
  delay(500);
  op.high();
  delay(500);
}


//  -- END OF FILE --