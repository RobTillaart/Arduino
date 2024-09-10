//
//    FILE: HeartBeat_errorcode.ino
//  AUTHOR: Rob Tillaart 
// PURPOSE: demo

// In this demo the heartbeat is disabled.
// When code(pattern) is called it will show the code. 
// The assumption is that a code can be diagnostic or error 
// has a higher importance than a regular heartbeat.
  

#include "HeartBeat.h"


HeartBeatDiag HB;

bool flag = true;

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HEARTBEAT_LIB_VERSION: ");
  Serial.println(HEARTBEAT_LIB_VERSION);

  HB.begin(13, 3);  // PIN 13 with frequency 3

  // make heartbeat invisible
  HB.disable();
}


void loop()
{
  HB.beat();

  // if (millis() > 2000) HB.code(123454321);
  if (millis() > 3000) HB.code(1369631);
  if (millis() > 20000) HB.codeOff();
  if (millis() > 30000) HB.enable();
  Serial.println(HB.codeCompleted());
  delay(200);
}


// -- END OF FILE --
