//
//    FILE: countdown_demo2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://forum.arduino.cc/index.php?topic=356253
//          https://github.com/RobTillaart/CountDown
//


#include "CountDown.h"

CountDown CD[5];

uint8_t lines = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("COUNTDOWN_LIB_VERSION: ");
  Serial.println(COUNTDOWN_LIB_VERSION);

  for (int i = 0; i < 5; i++)
  {
    CD[i].start(10000UL * i);
  }
  delay(1234);
  CD[3].stop();
}


void loop()
{
  if (lines == 10)
  {
    lines = 0;
    Serial.println();
  }
  lines++;

  for (int i = 0; i < 5; i++)
  {
    Serial.print("\t");
    Serial.print(CD[i].remaining());
  }
  for (int i = 0; i < 5; i++)
  {
    Serial.print("\t");
    Serial.print(CD[i].isRunning());
  }
  Serial.println();

  if (CD[1].isRunning() == false && CD[3].isRunning() == false)
  {
    uint32_t x = CD[3].remaining();
    CD[3].start(x);
  }

  delay(250);
}


//  -- END OF FILE --

