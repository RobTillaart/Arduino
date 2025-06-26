
//
//    FILE: TCRT5000_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCRT5000


#include "TCRT5000.h"


TCRT5000 tcrt(14);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TCRT5000_LIB_VERSION: ");
  Serial.println(TCRT5000_LIB_VERSION);
  Serial.println();

  tcrt.setThreshold(250);
}


void loop()
{
  if (tcrt.belowThreshold())
  {
    Serial.println(tcrt.lastRead());
  }
  delay(25);
}


//  -- END OF FILE --
