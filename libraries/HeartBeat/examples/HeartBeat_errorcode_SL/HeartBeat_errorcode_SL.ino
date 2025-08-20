//
//    FILE: HeartBeat_errorcode_SL.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/HeartBeat

#include "HeartBeat.h"


HeartBeatSL HB;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HEARTBEAT_LIB_VERSION: ");
  Serial.println(HEARTBEAT_LIB_VERSION);
  Serial.println();

  HB.begin(13, 1);  //  PIN 13 with frequency 3

  //  make heartbeat invisible
  HB.disable();
}


void loop()
{
  HB.beat();

  if (millis() > 2000) HB.code("LSSL");
  if (millis() > 20000) HB.codeOff();
}


//  -- END OF FILE --
