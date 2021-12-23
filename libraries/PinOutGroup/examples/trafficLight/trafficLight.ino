//    FILE: trafficLight.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PinOutGroup library for Arduino


#include "PinOutGroup.h"

PinOutGroup trafficLight;


uint8_t lights[]    = {11, 12, 13};  // connect 3 leds...
const int RED       = 4;
const int YELLOW    = 2;
const int GREEN     = 1;
const int YELLOWRED = 6;     // YELLOW | RED 

int state = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print(F("PINOUTGROUP_LIB_VERSION: "));
  Serial.println(PINOUTGROUP_LIB_VERSION);
  Serial.println();

  trafficLight.add(3, lights);
}


void loop()
{
  switch (state)
  {
    default:
      Serial.println("RED");
      trafficLight.write(RED);
      break;
    case 1:
      Serial.println("YELLOWRED");
      trafficLight.write(YELLOWRED);
      break;
    case 2:
      Serial.println("GREEN");
      trafficLight.write(GREEN);
      break;
    case 3:
      Serial.println("YELLOW");
      trafficLight.write(YELLOW);
      break;
  }
  state++;
  if (state == 4) state = 0;
  delay(1000);
}


// -- END OF FILE --

