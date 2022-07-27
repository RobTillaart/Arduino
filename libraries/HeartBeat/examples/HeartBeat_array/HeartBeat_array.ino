//
//    FILE: HeartBeat_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "HeartBeat.h"


HeartBeat HB[3];


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HEARTBEAT_LIB_VERSION: ");
  Serial.println(HEARTBEAT_LIB_VERSION);

  HB[0].begin(11, 1);
  HB[1].begin(12, 3);
  HB[2].begin(13, 5);
  HB[0].setDutyCycle(20);
  HB[1].setDutyCycle(30);
  HB[2].setDutyCycle(40);
}


void loop()
{
  // update all heartbeats
  for (int i = 0; i < 3; i++) HB[i].beat();

  // do other stuff here
}


// -- END OF FILE --
