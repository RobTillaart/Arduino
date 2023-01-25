//
//    FILE: HC4067_4_channel_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4067 16 channel (simple) multiplexer
//

//  setup description
//

#include "HC4067.h"

//  4..7 channel select pins
//  8 = enable pin
HC4067 mp(4, 5, 6, 7, 8);  


uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4067 LIBRARY VERSION: ");
  Serial.println(HC4067_LIB_VERSION);
  Serial.println();

  delay(1000);
}


void loop()
{
  if (millis() - lastTime > 50)
  {
    lastTime = millis();

    mp.enable();
    for (uint8_t channel = 0; channel < 4; channel++)
    {
      mp.setChannel(channel);
      Serial.print(analogRead(A0));
      Serial.print(",");
    }
    Serial.println();
    mp.disable();
  }
}


//  -- END OF FILE --
