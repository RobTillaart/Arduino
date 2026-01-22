//
//    FILE: PT2257_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure basic performance
//     URL: https://github.com/RobTillaart/PT2257


#include "PT2257.h"


PT2257 myPT;
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PT2257_LIB_VERSION: ");
  Serial.println(PT2257_LIB_VERSION);
  Serial.println();

  Wire.begin();

  delay(200);  // needed by PT225x
  myPT.begin();

  myPT.allOff();

  Serial.println("times in micros\n");
  delay(100);
  start = micros();
  myPT.mute();
  stop = micros();
  Serial.print("MUTE:     ");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  myPT.muteOff();
  stop = micros();
  Serial.print("MUTEOFF:  ");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  myPT.stereo(-50);
  stop = micros();
  Serial.print("STEREO:   ");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  int v = myPT.getLeft();
  stop = micros();
  Serial.print("GETLEFT:  ");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  v = myPT.getRight();
  stop = micros();
  Serial.print("GETRIGHT: ");
  Serial.println(stop - start);

  Serial.println();
  Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --
