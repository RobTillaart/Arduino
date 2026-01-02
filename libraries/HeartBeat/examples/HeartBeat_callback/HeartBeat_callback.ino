//
//    FILE: HeartBeat_callback.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/HeartBeat

#include "HeartBeat.h"


HeartBeat HB;

//  prints timestap of HIGH pulses.
//  although printing might not be the best idea
//  as it might corrupt other output
void hbStateChanged(uint8_t state)
{
  if (state == HIGH)
  {
    Serial.println(millis());
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HEARTBEAT_LIB_VERSION: ");
  Serial.println(HEARTBEAT_LIB_VERSION);
  Serial.println();

  HB.begin(13, 3);  //  PIN 13 with frequency 3

  HB.onStateChange(hbStateChanged);  //  register callback function
}


void loop()
{
  HB.beat();
  //  do other stuff here
}


//  -- END OF FILE --
