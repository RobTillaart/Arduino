//
//    FILE: sinusHeartBeat.ino
//  AUTHOR: Rob Tillaart 
// PURPOSE: demo


#include "HeartBeat.h"


HeartBeat HB;


void setup() 
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(HEARTBEAT_LIB_VERSION);

  HB.begin(13, 1.0);
}


void loop()
{
  HB.beat();

  float frequency = 5 * (1 + sin(millis()/1000.0));
  HB.setFrequency(frequency);
  // Serial.println(frequency, 6);
  // do other stuff here
}


// -- END OF FILE --
