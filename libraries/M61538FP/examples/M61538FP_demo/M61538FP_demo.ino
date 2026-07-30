//    FILE: M61538FP_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo M61538FP 6 channel volume processor.
//     URL: https://github.com/RobTillaart/M61538FP


#include "M61538FP.h"


//  adjust pins if needed
const uint8_t dataPin = 6;
const uint8_t clockPin = 7;

M61538FP vp(dataPin, clockPin);



void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("M61538FP_LIB_VERSION: ");
  Serial.println(M61538FP_LIB_VERSION);
  Serial.println();

  vp.begin();
  delay(300);

}

void loop()
{
  vp.setVolumeAll(10, 10, 10, 10, 10, 10);
  delay(3000);

  vp.setVolumeAll(0, 0, 3, 6, 10, 10);
  delay(3000);

  vp.muteAll();
  delay(3000);
}


//  -- END OF FILE --
