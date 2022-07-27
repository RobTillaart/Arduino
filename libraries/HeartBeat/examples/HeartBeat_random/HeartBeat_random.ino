//
//    FILE: HeartBeat_random.ino
//  AUTHOR: Rob Tillaart 
// PURPOSE: demo


#include "HeartBeat.h"


HeartBeat HB;

uint32_t lastUpdate = 0;


void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HEARTBEAT_LIB_VERSION: ");
  Serial.println(HEARTBEAT_LIB_VERSION);

  HB.begin(13, 1);
}


void loop()
{
  HB.beat();

  // set a new frequency every 2 seconds
  if (millis() - lastUpdate >= 2000)
  {
    lastUpdate = millis();
    float f = 1.0 + 0.1 * random(50);
    HB.setFrequency(f);
  }
  
  // do other stuff here
}


// -- END OF FILE --
