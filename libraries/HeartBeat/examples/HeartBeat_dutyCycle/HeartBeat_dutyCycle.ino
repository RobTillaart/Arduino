//
//    FILE: HeartBeat_dutyCycle.ino
//  AUTHOR: Rob Tillaart 
// PURPOSE: demo


#include "HeartBeat.h"


HeartBeat HB;


void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HEARTBEAT_LIB_VERSION: ");
  Serial.println(HEARTBEAT_LIB_VERSION);

  HB.begin(13, 3);          // PIN 13 with frequency 3
  HB.setDutyCycle(17.53);

  Serial.print("FR: ");
  Serial.println(HB.getFrequency());
  Serial.print("DC: ");
  Serial.println(HB.getDutyCycle());
}


void loop()
{
  HB.beat();

  // do other stuff here
}


// -- END OF FILE --
