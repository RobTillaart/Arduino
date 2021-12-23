//    FILE: led13.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo pinOutGroup library for Arduino
//          blink the build in led by means of a PinOutGroup


#include "PinOutGroup.h"

PinOutGroup led13;

uint8_t ar[1] = { 13 } ;

uint32_t start , stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print(F("PINOUTGROUP_LIB_VERSION: "));
  Serial.println(PINOUTGROUP_LIB_VERSION);

  led13.add(1, ar );
}


void loop()
{
  Serial.println();
  start = micros();
  led13.write(0, HIGH);  // could be led13.write(1); as there is just one in the group.
  stop = micros();
  Serial.println(stop - start);
  delay(250);

  led13.write(0, LOW);  // could be led13.write(0); as there is just one in the group.
  delay(250);
}


// -- END OF FILE --

