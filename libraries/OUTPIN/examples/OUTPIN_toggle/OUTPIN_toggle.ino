//
//    FILE: OUTPIN_toggle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: create a 1 Hz reference signal
//     URL: https://github.com/RobTillaart/OUTPIN


#include "OUTPIN.h"

//  adjust pin if needed
OUTPIN op(13, LOW);

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("OUTPIN_LIB_VERSION: ");
  Serial.println(OUTPIN_LIB_VERSION);
  Serial.println();
}


void loop()
{
  while(1)
  {
    op.toggle();
    delay(500);
  }
}


//  -- END OF FILE --