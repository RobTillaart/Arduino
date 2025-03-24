//
//    FILE: countdown_resume.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://forum.arduino.cc/index.php?topic=356253
//          https://github.com/RobTillaart/CountDown


#include "CountDown.h"

CountDown CD[2];


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("COUNTDOWN_LIB_VERSION: ");
  Serial.println(COUNTDOWN_LIB_VERSION);
  Serial.println();

  CD[0].start(10000UL);
  CD[1].start(10000UL);
  delay(1234);
  CD[1].stop();
}


void loop()
{
  for (int i = 0; i < 2; i++)
  {
    Serial.print("\t");
    Serial.print(CD[i].remaining());
  }
  for (int i = 0; i < 2; i++)
  {
    Serial.print("\t");
    Serial.print(CD[i].isRunning());
  }
  Serial.println();

  if (CD[0].isRunning() == false && CD[1].isRunning() == false)
  {
    CD[1].resume();
  }

  delay(250);
}


//  -- END OF FILE --
