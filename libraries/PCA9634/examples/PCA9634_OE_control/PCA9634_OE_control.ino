//
//    FILE: PCA9634_OE_control.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9635 library


#include "Arduino.h"
#include "Wire.h"
#include "PCA9634.h"


PCA9634 ledArray(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.print("PCA9634 LIB version: ");
  Serial.println(PCA9634_LIB_VERSION);
  Serial.println();

  ledArray.begin();

  //  just one channel
  ledArray.write1(1, 100);

  ledArray.setOutputEnablePin(12);
  ledArray.setOutputEnable(true);
  delay(1000);
  ledArray.setOutputEnable(false);
  delay(1000);
  ledArray.setOutputEnable(true);

  //  TODO  elaborate

  Serial.println("done...");
}

void loop()
{
}


//  -- END OF FILE --
