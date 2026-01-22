//
//    FILE: PT2259_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/PT2257


#include "PT2257.h"


PT2259 myPT;


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

  myPT.mute();
  Serial.println(myPT.isMuted());  //  expect 1
  myPT.muteLeft();
  Serial.println(myPT.isMuted());  //  expect 0
  myPT.muteRight();
  Serial.println(myPT.isMuted());  //  expect 0
  myPT.muteOff();
  Serial.println(myPT.isMuted());  //  expect 0
}


void loop()
{
  for (int db = -79; db <= -45; db++)
  {
    myPT.stereo(db);
    Serial.print(myPT.getLeft());
    Serial.print(" - ");
    Serial.println(myPT.getRight());
    delay(100);
  }
  Serial.println();

  for (int db = -45; db >= -79; db--)
  {
    myPT.right(db);
    Serial.print(myPT.getLeft());
    Serial.print(" - ");
    Serial.println(myPT.getRight());
    delay(100);
  }
  Serial.println();

  for (int db = -45; db >= -79; db--)
  {
    myPT.left(db);
    Serial.print(myPT.getLeft());
    Serial.print(" - ");
    Serial.println(myPT.getRight());
    delay(100);
  }
  Serial.println("\n\n\n");
  delay(2000);
}


//  -- END OF FILE --
